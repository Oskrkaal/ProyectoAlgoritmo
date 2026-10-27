// ============================================================================
//  notas.cpp - Modulo 2: Notas y Archivos (RF06 - RF10)
//  RF06: exportar actas        RF07: cargar actas al iniciar
//  RF08: matriz (Alumno-Curso) x Evaluaciones  -> a.notas[FILAS][EVAL]
//  RF09: calcularNotaFinal con paso por referencia (&)
//  RF10: cuadro de honor y promedio general
//
//  Las notas se ingresan POR CADA CURSO asignado al estudiante. La matriz 2D
//  tiene una fila por (alumno, curso):   fila = alumno * MAX_CURSOS + curso
//  y 4 columnas: [0]=Parcial 1, [1]=Parcial 2, [2]=Actividades, [3]=Examen.
//  La matriz NO es global: vive dentro de la estructura Academia.
//
//  Formula (igual que la hoja de calculo):
//     Zona       = Parcial 1 + Parcial 2 + Actividades      (=SUMA(...))
//     Nota final = Zona + Examen final
// ============================================================================
#include "registro.h"
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Topes de punteo segun la tabla de evaluacion (son constantes, no variables)
const float MAX_PARCIAL1 = 15.0f;
const float MAX_PARCIAL2 = 15.0f;
const float MAX_ACTIVIDADES = 35.0f;
const float MAX_EXAMEN = 35.0f;

const float ZONA_MINIMA = 26.0f;     // minimo de zona para derecho a examen final
const float NOTA_APROBACION = 61.0f; // minimo para aprobar un curso
const float NOTA_HONOR = 90.0f;      // promedio minimo para cuadro de honor

// ---------------------------------------------------------------------------
// RF09 - Calculo por REFERENCIA: devuelve zona y nota final modificando las
// variables del que llama (zona y notaFinal son parametros &).
// ---------------------------------------------------------------------------
void calcularNotaFinal(float parcial1, float parcial2, float actividades,
                       float examen, float &zona, float &notaFinal) {
  zona = parcial1 + parcial2 + actividades; // =SUMA(Parc1:Actividades)
  notaFinal = zona + examen;                // =zona + examen final
}

// ---------------------------------------------------------------------------
// Acceso seguro a la matriz (RNF04: nunca se sale de los limites)
// ---------------------------------------------------------------------------

// Fila de la matriz para el curso 'curso' del alumno 'alumno' (-1 si no valida)
int filaNota(int alumno, int curso) {
  if (alumno < 0 || alumno >= TAM || curso < 0 || curso >= MAX_CURSOS)
    return -1;
  return alumno * MAX_CURSOS + curso;
}

// Borra todas las notas (todos los cursos) de un alumno
void limpiarNotasAlumno(Academia &a, int alumno) {
  for (int c = 0; c < MAX_CURSOS; c++) {
    int f = filaNota(alumno, c);
    if (f < 0)
      continue;
    a.conNotas[f] = false;
    for (int j = 0; j < EVAL; j++)
      a.notas[f][j] = 0.0f;
  }
}

static bool filaValida(int fila) { return fila >= 0 && fila < FILAS; }

static float zonaDeFila(const Academia &a, int fila) {
  if (!filaValida(fila))
    return 0.0f;
  return a.notas[fila][0] + a.notas[fila][1] + a.notas[fila][2];
}

static float notaFinalDeFila(const Academia &a, int fila) {
  if (!filaValida(fila))
    return 0.0f;
  float zona = 0, notaFinal = 0;
  calcularNotaFinal(a.notas[fila][0], a.notas[fila][1], a.notas[fila][2],
                    a.notas[fila][3], zona, notaFinal);
  return notaFinal;
}

// Resume los cursos de un alumno. Devuelve POR REFERENCIA cuantos cursos tiene,
// cuantos ya tienen notas y la suma de sus notas finales.
static void resumenAlumno(const Academia &a, int alumno, int &totalCursos,
                          int &conNota, float &sumaFinales) {
  vector<string> cursos = cursosDeAlumno(a.alumnos[alumno]);
  totalCursos = (int)cursos.size();
  conNota = 0;
  sumaFinales = 0;
  for (int c = 0; c < totalCursos; c++) {
    int f = filaNota(alumno, c);
    if (f >= 0 && a.conNotas[f]) {
      conNota++;
      sumaFinales += notaFinalDeFila(a, f);
    }
  }
}

// ---------------------------------------------------------------------------
// Validacion de entrada (RNF02) y rango (RF14)
// ---------------------------------------------------------------------------

// Verdadero si el texto es un numero (digitos y como maximo un punto)
static bool esNumero(const string &texto) {
  if (texto.empty())
    return false;
  int puntos = 0;
  int digitos = 0;
  for (size_t i = 0; i < texto.length(); i++) {
    if (texto[i] == '.') {
      puntos++;
    } else if (texto[i] >= '0' && texto[i] <= '9') {
      digitos++;
    } else {
      return false;
    }
  }
  return puntos <= 1 && digitos > 0;
}

// Verdadero si el texto son solo digitos (para elegir un numero de la lista)
static bool esEntero(const string &texto) {
  if (texto.empty() || texto.length() > 6)
    return false;
  for (size_t i = 0; i < texto.length(); i++) {
    if (texto[i] < '0' || texto[i] > '9')
      return false;
  }
  return true;
}

// Pide una nota hasta que sea numerica y este entre 0 y 'maximo'
static float leerNota(const string &evaluacion, float maximo) {
  string texto;
  while (true) {
    cout << "  " << evaluacion << " (0-" << (int)maximo << "): ";
    cin >> texto;

    if (!esNumero(texto)) {
      cout << "  [ERROR] Solo se permiten numeros.\n";
      continue;
    }

    float valor = (float)atof(texto.c_str());
    if (!validarRangoNota(valor, maximo)) // RF14 (reinicio.cpp)
      continue;
    return valor;
  }
}

// ---------------------------------------------------------------------------
// RF06 / RF07 - Archivo permanente de actas (una linea por alumno-curso)
// ---------------------------------------------------------------------------

// Escribe el acta en la ruta indicada (se usa para el acta y para respaldos)
bool exportarActaA(const Academia &a, const string &ruta) {
  ofstream archivo(ruta.c_str());
  if (!archivo.is_open())
    return false;

  string emision = fechaHoraActual(); // RF13

  archivo << "Carne\tCurso\tParcial1\tParcial2\tTareas\tZona\tExamenFinal\t"
             "NotaFinal\tEstado\tFechaEmision\tFechaRegistro\n";

  for (int i = 0; i < a.cantidad; i++) {
    vector<string> cursos = cursosDeAlumno(a.alumnos[i]);
    for (int c = 0; c < (int)cursos.size(); c++) {
      int f = filaNota(i, c);
      if (f < 0 || !a.conNotas[f])
        continue;

      float zona = zonaDeFila(a, f);
      float notaFinal = (float)redondearNota(notaFinalDeFila(a, f), 2);
      string estado = (notaFinal >= NOTA_APROBACION) ? "Aprobado" : "Reprobado";

      archivo << a.alumnos[i].carne << "\t" << cursos[c] << "\t" << a.notas[f][0]
              << "\t" << a.notas[f][1] << "\t" << a.notas[f][2] << "\t" << zona
              << "\t" << a.notas[f][3] << "\t" << notaFinal << "\t" << estado
              << "\t" << emision << "\t" << a.alumnos[i].fechaHora << "\n";
    }
  }
  archivo.close();
  return true;
}

bool exportarActa(const Academia &a) { return exportarActaA(a, ARCHIVO_ACTAS); }

// Carga el acta y "pega" cada linea a su alumno (carne + fecha de registro) y a
// su curso (por nombre). Debe llamarse DESPUES de cargarDesdeArchivo().
// Un acta con formato antiguo (sin columna Curso) se ignora.
bool cargarActas(Academia &a) {
  ifstream archivo(ARCHIVO_ACTAS.c_str());
  if (!archivo.is_open())
    return false;

  string linea;
  getline(archivo, linea); // encabezado
  if (linea.find("Carne\tCurso") != 0)
    return false; // formato antiguo: no se puede asignar a un curso

  while (getline(archivo, linea)) {
    if (!linea.empty() && linea[linea.size() - 1] == '\r')
      linea.erase(linea.size() - 1);
    if (linea.empty())
      continue;

    istringstream ss(linea);
    string carne, curso, n1, n2, n3, z, n4, notaFinal, estado, emision, fechaReg;
    getline(ss, carne, '\t');
    getline(ss, curso, '\t');
    getline(ss, n1, '\t');
    getline(ss, n2, '\t');
    getline(ss, n3, '\t');
    getline(ss, z, '\t');
    getline(ss, n4, '\t');
    getline(ss, notaFinal, '\t');
    getline(ss, estado, '\t');
    getline(ss, emision, '\t');
    getline(ss, fechaReg);

    if (!esNumero(n1) || !esNumero(n2) || !esNumero(n3) || !esNumero(n4))
      continue;

    float p1 = (float)atof(n1.c_str());
    float p2 = (float)atof(n2.c_str());
    float act = (float)atof(n3.c_str());
    float ex = (float)atof(n4.c_str());

    // Un archivo manipulado a mano no debe meter notas fuera de rango
    if (p1 > MAX_PARCIAL1 || p2 > MAX_PARCIAL2 || act > MAX_ACTIVIDADES ||
        ex > MAX_EXAMEN)
      continue;

    for (int i = 0; i < a.cantidad; i++) {
      if (a.alumnos[i].carne != carne || a.alumnos[i].fechaHora != fechaReg)
        continue;
      vector<string> cursos = cursosDeAlumno(a.alumnos[i]);
      for (int c = 0; c < (int)cursos.size(); c++) {
        if (cursos[c] != curso)
          continue;
        int f = filaNota(i, c);
        if (f < 0)
          break;
        a.notas[f][0] = p1;
        a.notas[f][1] = p2;
        a.notas[f][2] = act;
        a.notas[f][3] = ex;
        a.conNotas[f] = true;
        break;
      }
      break;
    }
  }
  archivo.close();
  return true;
}

// ---------------------------------------------------------------------------
// Busqueda y seleccion de alumnos
// ---------------------------------------------------------------------------

// Imprime los alumnos de una carrera y devuelve cuantos hay
static int listarPorCarrera(const Academia &a, const string &carrera) {
  int cantidad = 0;
  cout << "\n  " << left << setw(10) << "CARNE" << setw(32) << "ALUMNO"
       << "CURSOS CON NOTAS\n";
  cout << "  " << string(60, '-') << "\n";
  for (int i = 0; i < a.cantidad; i++) {
    if (aMinusculas(a.alumnos[i].carrera) != aMinusculas(carrera))
      continue;
    string nombre = a.alumnos[i].nombre + " " + a.alumnos[i].apellido;
    if (nombre.length() > 30)
      nombre = nombre.substr(0, 30);

    int total, conNota;
    float suma;
    resumenAlumno(a, i, total, conNota, suma);

    ostringstream estado;
    if (total == 0)
      estado << "(sin cursos asignados)";
    else
      estado << conNota << " de " << total;

    cout << "  " << left << setw(10) << a.alumnos[i].carne << setw(32) << nombre
         << estado.str() << "\n";
    cantidad++;
  }
  return cantidad;
}

// Coincidencia por palabras en el nombre completo del alumno i
static bool coincideNombre(const Academia &a, int i, const string &buscarMin) {
  string completo = aMinusculas(a.alumnos[i].nombre) + " " +
                    aMinusculas(a.alumnos[i].apellido);
  istringstream palabras(buscarMin);
  string palabra;
  bool hayPalabras = false;
  while (palabras >> palabra) {
    hayPalabras = true;
    if (completo.find(palabra) == string::npos)
      return false;
  }
  return hayPalabras;
}

// Devuelve el indice del alumno elegido por carne o nombre, o -1 si no hay
// una unica coincidencia
static int elegirAlumno(const Academia &a, const string &buscar,
                        const string &carrera) {
  string carreraMin = aMinusculas(carrera);
  string buscarMin = aMinusculas(buscar);

  int exactos = 0;
  int posicion = -1;
  for (int i = 0; i < a.cantidad; i++) {
    if (aMinusculas(a.alumnos[i].carrera) == carreraMin &&
        a.alumnos[i].carne == buscar) {
      exactos++;
      posicion = i;
    }
  }
  if (exactos == 1)
    return posicion;
  if (exactos > 1) {
    cout << "[INFO] Carne repetido. Busque por nombre.\n";
    return -1;
  }

  int coincidencias = 0;
  int ultimo = -1;
  for (int i = 0; i < a.cantidad; i++) {
    if (aMinusculas(a.alumnos[i].carrera) == carreraMin &&
        coincideNombre(a, i, buscarMin)) {
      coincidencias++;
      ultimo = i;
    }
  }

  if (coincidencias == 0) {
    cout << "[ERROR] No hay coincidencias en " << carrera << " para '" << buscar
         << "'.\n";
    return -1;
  }
  if (coincidencias > 1) {
    cout << "[INFO] Hay " << coincidencias
         << " coincidencias. Escriba el carne exacto:\n";
    for (int i = 0; i < a.cantidad; i++) {
      if (aMinusculas(a.alumnos[i].carrera) == carreraMin &&
          coincideNombre(a, i, buscarMin)) {
        cout << "   " << a.alumnos[i].carne << "  " << a.alumnos[i].nombre << " "
             << a.alumnos[i].apellido << "\n";
      }
    }
    return -1;
  }
  return ultimo;
}

// ---------------------------------------------------------------------------
// RF08 - Ingreso / modificacion de notas POR CURSO en la matriz
// ---------------------------------------------------------------------------

// Muestra los cursos del alumno con su estado de notas
static void mostrarCursosAlumno(const Academia &a, int alumno,
                                const vector<string> &cursos) {
  cout << fixed << setprecision(2);
  cout << "\n  " << left << setw(4) << "No." << setw(62) << "CURSO"
       << "NOTA FINAL\n";
  cout << "  " << string(82, '-') << "\n";
  for (int c = 0; c < (int)cursos.size(); c++) {
    int f = filaNota(alumno, c);
    cout << "  " << left << setw(4) << (c + 1) << setw(62) << cursos[c];
    if (f >= 0 && a.conNotas[f]) {
      float nf = (float)redondearNota(notaFinalDeFila(a, f), 2);
      cout << nf << " (" << (nf >= NOTA_APROBACION ? "Aprobado" : "Reprobado")
           << ")";
    } else {
      cout << "Pendiente";
    }
    cout << "\n";
  }
}

// Pide y guarda las 4 evaluaciones de UN curso (fila 'fila' de la matriz)
static void ingresarNotasCurso(Academia &a, int fila, const string &curso) {
  cout << "\nCurso: " << curso << "\n\n";

  float p1 = leerNota("Parcial 1", MAX_PARCIAL1);
  float p2 = leerNota("Parcial 2", MAX_PARCIAL2);
  float act = leerNota("Actividades", MAX_ACTIVIDADES);

  float zona = 0, notaFinal = 0;
  calcularNotaFinal(p1, p2, act, 0, zona, notaFinal);

  cout << fixed << setprecision(2);
  cout << "\n  -> Zona = " << p1 << " + " << p2 << " + " << act << " = " << zona
       << " / 65 puntos\n";

  float examen = 0;
  if (zona < ZONA_MINIMA) {
    cout << "  [AVISO] No alcanza la zona minima (" << ZONA_MINIMA
         << " pts). Sin derecho a Examen Final.\n";
    examen = 0;
  } else {
    examen = leerNota("Examen Final", MAX_EXAMEN);
  }

  // Se guarda en la fila (alumno, curso) de la matriz
  a.notas[fila][0] = p1;
  a.notas[fila][1] = p2;
  a.notas[fila][2] = act;
  a.notas[fila][3] = examen;
  a.conNotas[fila] = true;

  calcularNotaFinal(p1, p2, act, examen, zona, notaFinal); // por referencia
  float redondeada = (float)redondearNota(notaFinal, 2);

  exportarActa(a); // RF06: se guarda en cada ingreso

  cout << "  -> Nota final = Zona + Examen = " << zona << " + " << examen
       << " = " << redondeada << "\n";
  cout << "\n[OK] Notas guardadas. Nota final: " << redondeada << " ("
       << (redondeada >= NOTA_APROBACION ? "Aprobado" : "Reprobado") << ")\n";
}

static void ingresarNotas(Academia &a) {
  cout << "\n\t\t\t============================================\n";
  cout << "\t\t\t           INGRESO DE NOTAS                 \n";
  cout << "\t\t\t============================================\n";

  if (a.cantidad == 0) {
    cout << "\n[INFO] No hay alumnos registrados.\n";
    return;
  }

  string carrera;
  cout << "\n++++++++++++++++++++ CARRERAS DISPONIBLES ++++++++++++++++++++\n";
  cout << "1. Sistemas  2. Medicina  3. Arquitectura  4. Civil  5. Derecho\n";
  cout << "\nIngrese la carrera (escriba el nombre): ";
  cin >> carrera;

  string seguir = "s";
  while (seguir == "s" || seguir == "S") {
    int cantidad = listarPorCarrera(a, carrera);
    if (cantidad == 0) {
      cout << "\n[INFO] No hay estudiantes en la carrera: " << carrera << ".\n";
      return;
    }

    int alumno = -1;
    cin.ignore(1000, '\n');
    while (alumno == -1) {
      string buscar;
      cout << "\nCarne o nombre del alumno (0 = cancelar): ";
      getline(cin, buscar);
      if (buscar == "0")
        return;
      alumno = elegirAlumno(a, buscar, carrera);
    }

    cout << "\nAlumno: " << a.alumnos[alumno].carne << " - "
         << a.alumnos[alumno].nombre << " " << a.alumnos[alumno].apellido
         << "  (Semestre " << a.alumnos[alumno].semestre << ")\n";

    vector<string> cursos = cursosDeAlumno(a.alumnos[alumno]);
    if (cursos.empty()) {
      cout << "\n[INFO] Este alumno no tiene cursos asignados. Use "
              "'Modificar datos' para asignarle carrera y semestre.\n";
    } else {
      // Se eligen los cursos uno por uno hasta terminar con el alumno
      while (true) {
        mostrarCursosAlumno(a, alumno, cursos);
        string op;
        cout << "\nNumero de curso a calificar (0 = terminar con este alumno): ";
        cin >> op;

        if (!esEntero(op)) {
          cout << "[ERROR] Ingrese solo el numero del curso.\n";
          continue;
        }
        int n = atoi(op.c_str());
        if (n == 0)
          break;
        if (n < 1 || n > (int)cursos.size()) {
          cout << "[ERROR] Elija un numero entre 1 y " << cursos.size() << ".\n";
          continue;
        }

        int fila = filaNota(alumno, n - 1); // RNF04: validada
        if (fila < 0) {
          cout << "[ERROR] Fila fuera de los limites de la matriz.\n";
          continue;
        }
        ingresarNotasCurso(a, fila, cursos[n - 1]);
      }
    }

    cout << "\nIngresar notas de otro alumno de " << carrera << "? (s/n): ";
    cin >> seguir;
  }
}

// ---------------------------------------------------------------------------
// Reportes: matriz de notas y cuadro de honor (RF10)
// ---------------------------------------------------------------------------
static string recortar(const string &texto, size_t maximo) {
  return texto.length() > maximo ? texto.substr(0, maximo) : texto;
}

void mostrarMatriz(const Academia &a) {
  cout << "\n\t\t\t============================================\n";
  cout << "\t\t\t         MATRIZ DE NOTAS (ACTA)             \n";
  cout << "\t\t\t============================================\n";

  if (a.cantidad == 0) {
    cout << "\n[INFO] No hay alumnos registrados.\n";
    return;
  }

  const int ANCHO = 112;
  cout << fixed << setprecision(2);
  cout << "\n" << string(ANCHO, '=') << "\n";
  cout << "  " << left << setw(8) << "CARNE" << setw(20) << "ALUMNO"
       << setw(28) << "CURSO" << right << setw(7) << "P1" << setw(7) << "P2"
       << setw(8) << "ACTIV." << setw(7) << "ZONA" << setw(8) << "EXAMEN"
       << setw(8) << "FINAL" << "  " << left << "ESTADO\n";
  cout << string(ANCHO, '=') << "\n";

  for (int i = 0; i < a.cantidad; i++) {
    string nombre =
        recortar(a.alumnos[i].nombre + " " + a.alumnos[i].apellido, 18);
    vector<string> cursos = cursosDeAlumno(a.alumnos[i]);

    if (cursos.empty()) {
      cout << "  " << left << setw(8) << a.alumnos[i].carne << setw(20) << nombre
           << "(sin cursos asignados)\n";
      continue;
    }

    for (int c = 0; c < (int)cursos.size(); c++) {
      int f = filaNota(i, c);
      // El carne y el nombre solo se muestran en la primera fila del alumno
      cout << "  " << left << setw(8) << (c == 0 ? a.alumnos[i].carne : "")
           << setw(20) << (c == 0 ? nombre : "") << setw(28)
           << recortar(cursos[c], 26) << right;

      if (f >= 0 && a.conNotas[f]) {
        float zona = zonaDeFila(a, f);
        float nf = (float)redondearNota(notaFinalDeFila(a, f), 2);
        cout << setw(7) << a.notas[f][0] << setw(7) << a.notas[f][1] << setw(8)
             << a.notas[f][2] << setw(7) << zona << setw(8) << a.notas[f][3]
             << setw(8) << nf << "  " << left
             << (nf >= NOTA_APROBACION ? "Aprobado" : "Reprobado");
      } else {
        cout << setw(7) << "-" << setw(7) << "-" << setw(8) << "-" << setw(7)
             << "-" << setw(8) << "-" << setw(8) << "-" << "  " << left
             << "Sin notas";
      }
      cout << "\n";
    }
  }
  cout << string(ANCHO, '=') << "\n";
  mostrarFechaHoraEmision(); // RF13
}

void cuadroHonor(const Academia &a) {
  cout << "\n\t\t\t============================================\n";
  cout << "\t\t\t    CUADRO DE HONOR (POR CARRERAS)          \n";
  cout << "\t\t\t============================================\n";
  cout << "  Se listan alumnos con TODOS sus cursos calificados y promedio >= "
       << NOTA_HONOR << "\n";

  if (a.cantidad == 0) {
    cout << "\n[INFO] No hay alumnos registrados.\n";
    return;
  }

  const string carreras[5] = {"Sistemas", "Medicina", "Arquitectura", "Civil",
                              "Derecho"};

  float sumaClase = 0;
  int notasClase = 0;

  for (int k = 0; k < 5; k++) {
    int completos[TAM];       // alumnos con todos los cursos calificados
    float promedios[TAM];     // su promedio de notas finales
    int nCompletos = 0;

    float sumaCarrera = 0;    // suma de TODAS las notas finales de la carrera
    int notasCarrera = 0;     // cuantas notas (curso) hay
    int aprobados = 0;        // cuantas son >= NOTA_APROBACION

    for (int i = 0; i < a.cantidad; i++) {
      if (aMinusculas(a.alumnos[i].carrera) != aMinusculas(carreras[k]))
        continue;

      int total, conNota;
      float suma;
      resumenAlumno(a, i, total, conNota, suma);
      if (conNota == 0)
        continue;

      sumaCarrera += suma;
      notasCarrera += conNota;

      for (int c = 0; c < total; c++) {
        int f = filaNota(i, c);
        if (f >= 0 && a.conNotas[f] &&
            redondearNota(notaFinalDeFila(a, f), 2) >= NOTA_APROBACION)
          aprobados++;
      }

      if (total > 0 && conNota == total) {
        completos[nCompletos] = i;
        promedios[nCompletos] = suma / total;
        nCompletos++;
      }
    }

    cout << "\n>>> CARRERA: " << carreras[k] << " <<<\n";

    if (notasCarrera == 0) {
      cout << "  [INFO] No hay notas registradas en esta carrera.\n";
      continue;
    }

    sumaClase += sumaCarrera;
    notasClase += notasCarrera;

    // Ordenamiento burbuja de mayor a menor promedio (se mueven ambos arreglos)
    for (int i = 0; i < nCompletos - 1; i++) {
      for (int j = 0; j < nCompletos - 1 - i; j++) {
        if (promedios[j] < promedios[j + 1]) {
          float tp = promedios[j];
          promedios[j] = promedios[j + 1];
          promedios[j + 1] = tp;
          int ti = completos[j];
          completos[j] = completos[j + 1];
          completos[j + 1] = ti;
        }
      }
    }

    cout << fixed << setprecision(2);
    cout << string(70, '-') << "\n";
    cout << "  " << left << setw(8) << "PUESTO" << setw(10) << "CARNE"
         << setw(30) << "ALUMNO" << setw(8) << "CURSOS" << right << setw(10)
         << "PROMEDIO" << "\n";
    cout << string(70, '-') << "\n";

    int puesto = 0;
    for (int i = 0; i < nCompletos; i++) {
      float prom = (float)redondearNota(promedios[i], 2);
      if (prom < NOTA_HONOR)
        break; // ordenados: los siguientes tampoco llegan al honor
      puesto++;
      int al = completos[i];
      string nombre =
          recortar(a.alumnos[al].nombre + " " + a.alumnos[al].apellido, 28);
      cout << "  " << left << setw(8) << puesto << setw(10) << a.alumnos[al].carne
           << setw(30) << nombre << setw(8)
           << cursosDeAlumno(a.alumnos[al]).size() << right << setw(10) << prom
           << "\n";
    }

    if (puesto == 0)
      cout << "  Ningun alumno alcanza " << NOTA_HONOR
           << " de promedio en esta carrera.\n";
    cout << string(70, '-') << "\n";

    cout << "  Promedio de la carrera (todas las notas): "
         << redondearNota(sumaCarrera / notasCarrera, 2) << " pts\n";
    cout << "  Cursos aprobados: " << aprobados << " de " << notasCarrera << " ("
         << (int)calcularPorcentaje(aprobados, notasCarrera) << "%)\n"; // RF12
  }

  // RF10 - promedio general de la clase
  cout << "\n" << string(70, '=') << "\n";
  if (notasClase == 0) {
    cout << "  PROMEDIO GENERAL DE LA CLASE: sin notas registradas.\n";
  } else {
    cout << fixed << setprecision(2);
    cout << "  PROMEDIO GENERAL DE LA CLASE: "
         << redondearNota(sumaClase / notasClase, 2) << " pts (" << notasClase
         << " nota(s) de curso)\n";
  }
  cout << string(70, '=') << "\n";
  mostrarFechaHoraEmision(); // RF13
}

// Opcion 5 del menu principal: ambos reportes seguidos
void reportes(const Academia &a) {
  mostrarMatriz(a);
  cuadroHonor(a);
}

// ---------------------------------------------------------------------------
// Submenu del modulo de notas (opcion 4 del menu principal)
// ---------------------------------------------------------------------------
void menuNotas(Academia &a) {
  int opcion = 0;

  do {
    limpiarPantalla();
    cout << "\n\t\t\t============================================\n";
    cout << "\t\t\t              MODULO DE NOTAS               \n";
    cout << "\t\t\t============================================\n";
    cout << " 1. Ingresar / modificar notas por curso de un alumno \n";
    cout << " 2. Ver matriz de notas\n";
    cout << " 3. Cuadro de honor por carrera y promedios \n";
    cout << " 4. Exportar acta de notas a archivo \n";
    cout << " 5. Volver al menu principal\n";
    cout << "----------------------------------------------------\n";
    cout << " Seleccione una opcion [1-5]: ";

    if (!(cin >> opcion)) {
      cin.clear();
      cin.ignore(1000, '\n');
      continue;
    }

    if (opcion == 5)
      break;

    limpiarPantalla();
    switch (opcion) {
    case 1:
      ingresarNotas(a);
      break;
    case 2:
      mostrarMatriz(a);
      break;
    case 3:
      cuadroHonor(a);
      break;
    case 4:
      if (exportarActa(a)) {
        cout << "\n[OK] Acta exportada a " << ARCHIVO_ACTAS << "\n";
      } else {
        cout << "\n[ERROR] No se pudo crear el archivo del acta.\n";
      }
      break;
    default:
      cout << "\n[ERROR] Opcion fuera de rango.\n";
      break;
    }

    cout << "\nPresione Enter para continuar...";
    cin.ignore(1000, '\n');
    cin.get();

  } while (opcion != 5);
}
