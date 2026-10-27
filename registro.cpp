#include "registro.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

// Función para convertir a minúsculas y facilitar la búsqueda de carreras
string aMinusculas(string cadena) {
  string resultado = cadena;
  transform(resultado.begin(), resultado.end(), resultado.begin(), ::tolower);
  return resultado;
}

// Base de datos global de las mallas curriculares por carrera
map<int, vector<string>> obtenerMalla(string carreraSeleccionada) {
  map<int, vector<string>> malla;
  carreraSeleccionada = aMinusculas(carreraSeleccionada);

  if (carreraSeleccionada == "sistemas") {
    malla[1] = {"Contabilidad I", "Desarrollo Humano y Profesional",
                "Introduccion a los Sistemas de Computo", "Logica de Sistemas",
                "Metodologia de la Investigacion"};
    malla[2] = {"Algebra Lineal", "Algoritmos", "Contabilidad II",
                "Matematica Discreta", "Precalculo"};
    malla[3] = {"Calculo I", "Derecho Informatico", "Fisica I",
                "Proceso Administrativo", "Programacion I"};
    malla[4] = {"Calculo II", "Estadistica I", "Fisica II", "Microeconomia",
                "Programacion II"};
    malla[5] = {"Electronica Analogica", "Emprendedores de Negocios",
                "Estadistica II", "Metodos Numericos",
                "Programacion III"};
    malla[6] = {"Automatas y Lenguajes Formales", "Bases de Datos I",
                "Electronica Digital", "Investigacion de Operaciones",
                "Sistemas Operativos I"};
    malla[7] = {"Analisis de Sistemas I", "Arquitectura de Computadoras I",
                "Bases de Datos II", "Compiladores",
                "Sistemas Operativos II"};
    malla[8] = {"Analisis de Sistemas II", "Arquitectura de Computadoras II",
                "Desarrollo Web", "Etica Profesional",
                "Redes de Computadoras I"};
    malla[9] = {"Administracion de Tecnologias de Informacion",
                "Ingenieria de Software", "Inteligencia Artificial",
                "Proyecto de Graduacion I",
                "Redes de Computadoras II"};
    malla[10] = {"Aseguramiento de la Calidad de Software",
                 "Proyecto de Graduacion II",
                 "Seguridad y Auditoria de Sistemas",
                 "Seminario de Tecnologias de Informacion",
                 "Telecomunicaciones"};
  } else if (carreraSeleccionada == "medicina") {
    malla[1] = {"Biologia Celular y Molecular Humana I",
                "Ciencias Exactas en la Salud",
                "Desarrollo Humano y Profesional",
                "Metodologia de la Investigacion",
                "Principios Clinicos",
                "Quimica Inorganica",
                "Salud Mental I Bases Biologicas de la Conducta",
                "Sistemas de Comunicacion"};
    malla[2] = {"Bioestadistica",
                "Biologia Celular y Molecular Humana II",
                "Embriologia",
                "Fisica Medica I",
                "Investigacion I",
                "Propedeutica Medica",
                "Quimica Organica",
                "Salud Mental II Psicologia de la Anormalidad"};
    malla[3] = {"Anatomia I",
                "Bioquimica I",
                "Fisica Medica II",
                "Histologia I",
                "Investigacion II",
                "Realidad Nacional",
                "Salud Mental III Des. Psicolog. del Niño y del Adolescente",
                "Semiologia I"};
    malla[4] = {"Anatomia II",
                "Atencion Primaria en Salud",
                "Bioquimica II",
                "Epidemiologia",
                "Fisiologia I",
                "Histologia II",
                "Salud Mental IV Salud Mental en Atencion Primaria",
                "Semiologia II"};
    malla[5] = {"Anatomia III",  "Bioquimica III",  "Farmacologia I",
                "Fisiologia II", "Microbiologia I", "Patologia I",
                "Salud Publica", "Semiologia III"};
    malla[6] = {"Bioquimica Clinica Aplicada",
                "Farmacologia II",
                "Fisiologia III",
                "Inmunologia",
                "Microbiologia II",
                "Patologia II",
                "Rehabilitacion",
                "Tecnologia Biomolecular"};
    malla[7] = {"Atencion Ambulatoria y Pre-Hospitalaria",
                "Atencion Neurologica",
                "Atencion Oftalmologica",
                "Genetica Humana",
                "Medicina Forense",
                "Medicina Laboral"};
    malla[8] = {"Bioetica I", "Medicina Interna I"};
    malla[9] = {"Medicina Interna II", "Psiquiatria"};
    malla[10] = {"Gestion y Liderazgo de Servicios de Salud",
                 "Pediatria"};
    malla[11] = {"Cirugia", "Medicina Alternativa",
                 "Trabajo de Graduacion I"};
    malla[12] = {"Ginecologia y Obstetricia",
                 "Trabajo de Graduacion II"};
    malla[13] = {"Antropologia Medica",
                 "Practica Profesional Asistida Rural"};
    malla[14] = {"Bioetica II",
                 "Practica Profesional Asistida Hospitalaria"};
  } else if (carreraSeleccionada == "arquitectura") {
    malla[1] = {"Comunicacion Oral y Escrita",
                "Desarrollo Humano y Profesional",
                "Dibujo Arquitectonico I",
                "Ecologia",
                "Humanistica y Estetica",
                "Matematica I",
                "Metodos y Tecnicas de Diseño",
                "Tecnicas de Expresion Grafica I"};
    malla[2] = {"Computacion I",
                "Dibujo Arquitectonico II",
                "Diseño Arquitectonico I",
                "Matematica II",
                "Materiales de Construccion",
                "Metodos de Investigacion I",
                "Modelos Arquitectonicos",
                "Tecnicas de Expresion Grafica II"};
    malla[3] = {"Computacion II",
                "Control Ambiental I",
                "Diseño Arquitectonico II",
                "Fisica",
                "Geometria",
                "Historia de la Arquitectura I",
                "Introduccion a las Estructuras",
                "Tecnicas de Presentacion de Proyectos"};
    malla[4] = {"Control Ambiental II",
                "Dibujo Constructivo",
                "Diseño Arquitectonico III",
                "Historia de la Arquitectura II",
                "Leyes y Normas de la Construccion y Ambientales",
                "Sistemas Constructivos I",
                "Sistemas Estructurales I",
                "Topografia"};
    malla[5] = {"Administracion de Obras I",
                "Diseño Arquitectonico IV",
                "Historia de la Arquitectura III",
                "Instalaciones I",
                "Psicologia Ambiental",
                "Sistemas Constructivos II",
                "Sistemas Estructurales II"};
    malla[6] = {"Administracion de Obras II",
                "Arquitectura Ambiental",
                "Diseño Arquitectonico V",
                "Historia y Teoria de la Arquitectura",
                "Instalaciones II",
                "Sistemas Estructurales III",
                "Suelos"};
    malla[7] = {"Diseño Arquitectonico VI",
                "Estadistica",
                "Instalaciones III",
                "Sistemas Constructivos III",
                "Sistemas Estructurales IV",
                "Supervision I",
                "Urbanismo I"};
    malla[8] = {"Administracion de Obras III",
                "Diseño Arquitectonico VII",
                "Matematica III",
                "Metodos de Investigacion II",
                "Practica Profesional Supervisada",
                "Sistemas Constructivos IV",
                "Sistemas Estructurales V"};
    malla[9] = {"Anteproyecto de Graduacion",    "Diseño Arquitectonico VIII",
                "Economia y Arquitectura",       "Mercadotecnia",
                "Sociologia de la Arquitectura", "Urbanismo II"};
    malla[10] = {
        "Analisis de Proyectos",    "Conservacion de Monumentos",
        "Diseño Arquitectonico IX", "Etica para Arquitectos",
        "Proyecto de Graduacion",   "Sistemas Constructivos V"};
  } else if (carreraSeleccionada == "civil") {
    malla[1] = {"Algebra Superior", "Desarrollo Humano y Profesional",
                "Dibujo Tecnico", "Geometria Plana y del Espacio",
                "Programacion para la Ciencia e Ingenieria I"};
    malla[2] = {"Calculo I",
                "Dibujo Asistido por Computadora",
                "Historia y Comunicacion Cientifica",
                "Programacion para la Ciencia e Ingenieria II",
                "Quimica Inorganica I",
                "Topografia I"};
    malla[3] = {"Algebra Lineal I", "Calculo II",
                "Dibujo Constructivo y Topografico", "Fisica I",
                "Topografia II"};
    malla[4] = {"Algebra Lineal II",
                "Calculo Vectorial y Multivariable",
                "Fisica II",
                "Geologia I",
                "Legislacion Aplicada a Ingenieria Civil",
                "Topografia III"};
    malla[5] = {"Ecologia y Sostenibilidad Ambiental",
                "Ecuaciones Diferenciales Ordinarias", "Fisica III",
                "Geologia II", "Mecanica de Cuerpos Rigidos I"};
    malla[6] = {"Contabilidad Aplicada a Ingenieria Civil",
                "Ecuaciones Diferenciales Parciales",
                "Estadistica y Probabilidad Aplicada a Ingenieria Civil",
                "Ingenieria de Carreteras I",
                "Mecanica de Cuerpos Rigidos II",
                "Mecanica de Solidos I"};
    malla[7] = {"Analisis Numerico",     "Ingenieria de Carreteras II",
                "Mecanica de Fluidos I", "Mecanica de Solidos II",
                "Mecanica de Suelos I",  "Tipologia Estructural"};
    malla[8] = {
        "Analisis Estructural I", "Hidraulica",
        "Ingenieria Economica y Teoria de Decisiones en Ingenieria Civil",
        "Materiales de Construccion", "Mecanica de Suelos II"};
    malla[9] = {
        "Analisis Estructural II", "Diseño de Estructuras de Concreto I",
        "Diseño de Estructuras de Madera y Mamposteria", "Hidrologia I",
        "Investigacion de Operaciones Aplicado a Ingenieria Civil"};
    malla[10] = {"Costos, Presupuestos y Avaluos",
                 "Diseño de Estructuras de Concreto II", "Hidrologia II",
                 "Ingenieria de Transito y Sistemas de Transporte",
                 "Ingenieria Sanitaria I"};
    malla[11] = {"Cimentaciones", "Diseño de Estructuras de Acero",
                 "Ingenieria Sanitaria II", "Obras Hidraulicas",
                 "Pavimentos"};
  } else if (carreraSeleccionada == "derecho") {
    malla[1] = {"Introduccion al Derecho", "Sociologia de Derecho",
                "Desarrollo Humano y Profesional", "Teoria General del Estado",
                "Lenguaje y Redaccion Tecnica Juridica"};
    malla[2] = {"Tecnicas Basicas de Investigacion",
                "Filosofia",
                "Historia del Derecho",
                "Derecho de Personas y Familia",
                "Derecho de los Bienes y Registral",
                "Derecho Penal (Parte General)"};
    malla[3] = {"Tecnica de Litigacion Oral", "Teoria General del Proceso",
                "Derecho Constitucional I", "Derecho de Sucesiones",
                "Derecho Penal (Parte Especial)"};
    malla[4] = {"Argumentacion Juridica", "Derecho de los Pueblos Indigenas",
                "Derechos Humanos y Ambiental",
                "Derecho de Obligaciones y Negocios Juridicos",
                "Derecho Administrativo I"};
    malla[5] = {"Ciencias Forenses",
                "Metodos Alternos de Resolucion de Conflictos",
                "Derecho Individual del Trabajo",
                "Derecho de Contratos Civiles",
                "Derecho Administrativo II",
                "Derecho Procesal Penal I"};
    malla[6] = {"Derecho Financiero y Tributario",
                "Derecho de Propiedad Intelectual",
                "Derecho Colectivo del Trabajo y de la Seguridad Social",
                "Derecho de Sociedades Mercantiles",
                "Derecho Procesal Administrativo",
                "Derecho Procesal Penal II"};
    malla[7] = {"Derecho Economico",
                "Derecho Cambiario",
                "Derecho Procesal del Trabajo",
                "Derecho Procesal Civil y Mercantil I",
                "Derecho Notarial (Parte General)",
                "Clinica Procesal Penal"};
    malla[8] = {"Metodos y Tecnicas de Investigacion Juridica",
                "Derecho Procesal Constitucional",
                "Clinica Procesal del Trabajo",
                "Derecho Procesal Civil y Mercantil II",
                "Derecho Notarial (Parte Especial)",
                "Derecho de Obligaciones y Contratos Mercantiles"};
    malla[9] = {"Seminario de Trabajo de Graduacion I",
                "Derecho Internacional Publico y Privado",
                "Derecho Bancario y Bursatil",
                "Derecho Procesal Civil y Mercantil III",
                "Derecho Notarial (Jurisdiccion Voluntaria)"};
    malla[10] = {"Seminario de Trabajo de Graduacion II",
                 "Filosofia del Derecho", "Deontologia Juridica",
                 "Clinica Procesal Civil y Mercantil",
                 "Clinica Notarial"};
  }
  return malla;
}

// ---------------------------------------------------------------------------
// Utilidades compartidas (declaradas en registro.h)
// ---------------------------------------------------------------------------

// Limpia la consola: "cls" en Windows (Dev-C++/MinGW, RNF01) y "clear" en otros.
void limpiarPantalla() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Deja el sistema en estado inicial: sin alumnos y con la matriz de notas en 0.
void iniciarAcademia(Academia &a) {
  a.cantidad = 0;
  for (int i = 0; i < FILAS; i++) {
    a.conNotas[i] = false;
    for (int j = 0; j < EVAL; j++)
      a.notas[i][j] = 0.0f;
  }
}

// Siguiente numero de carne = mayor carne existente + 1 (evita repetidos
// despues de dar de baja a un alumno).
static int siguienteCarneNumero(const Academia &a) {
  int mayor = 0;
  for (int i = 0; i < a.cantidad; i++) {
    int n = atoi(a.alumnos[i].carne.c_str());
    if (n > mayor)
      mayor = n;
  }
  return mayor + 1;
}

// Verdadero si el texto es un entero positivo (solo digitos).
static bool esEntero(const string &texto) {
  if (texto.empty())
    return false;
  for (size_t i = 0; i < texto.length(); i++) {
    if (texto[i] < '0' || texto[i] > '9')
      return false;
  }
  return true;
}

// Duracion de la carrera en semestres (misma regla que ya usaba el registro)
int maxSemestresCarrera(const string &carrera) {
  string c = aMinusculas(carrera);
  if (c == "medicina")
    return 14;
  if (c == "civil")
    return 11;
  return 10; // Sistemas, Arquitectura, Derecho
}

// Une los cursos en una sola cadena "A, B, C" (formato guardado en el archivo)
static string unirCursos(const vector<string> &cursos) {
  string r = "";
  for (size_t i = 0; i < cursos.size(); i++) {
    r += cursos[i];
    if (i + 1 < cursos.size())
      r += ", ";
  }
  return r;
}

// Pide el semestre al usuario (validado contra la duracion de la carrera) y
// asigna los cursos de la malla. La usan ingresarAlumno() y editarAlumno().
void pedirSemestreYCursos(Estudiante &e) {
  int maxSem = maxSemestresCarrera(e.carrera);
  int semestreIngresado;
  cout << "Semestre a inscribir (1-" << maxSem << "): ";
  while (!(cin >> semestreIngresado) || semestreIngresado < 1 ||
         semestreIngresado > maxSem) {
    cout << "[ERROR] Semestre no valido para " << e.carrera
         << ". Ingrese un valor entre 1 y " << maxSem << ": ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  e.semestre = semestreIngresado;

  map<int, vector<string>> malla = obtenerMalla(e.carrera);
  map<int, vector<string>>::iterator it = malla.find(semestreIngresado);
  if (it != malla.end())
    e.cursosAsignados = unirCursos(it->second);
  else
    e.cursosAsignados = "Pendiente de asignar (Carrera o Semestre no mapeados)";
}

// Lista de cursos asignados al alumno (maximo MAX_CURSOS). Se toma de la malla
// cuando coincide con lo guardado; si no, se separa el texto guardado. Un
// alumno "Pendiente de asignar" o de formato antiguo devuelve lista vacia.
vector<string> cursosDeAlumno(const Estudiante &e) {
  vector<string> cursos;

  map<int, vector<string>> malla = obtenerMalla(e.carrera);
  map<int, vector<string>>::iterator it = malla.find(e.semestre);
  if (it != malla.end() && unirCursos(it->second) == e.cursosAsignados)
    cursos = it->second; // evita partir nombres con coma ("Costos, Presupuestos...")

  if (cursos.empty() && !e.cursosAsignados.empty() &&
      e.cursosAsignados.find("Pendiente") == string::npos) {
    string resto = e.cursosAsignados;
    size_t pos;
    while ((pos = resto.find(", ")) != string::npos) {
      cursos.push_back(resto.substr(0, pos));
      resto = resto.substr(pos + 2);
    }
    cursos.push_back(resto);
  }

  if ((int)cursos.size() > MAX_CURSOS)
    cursos.resize(MAX_CURSOS);
  return cursos;
}

static void agregarAlArchivo(const Academia &a) {
  ofstream archivo(ARCHIVO, ios::app);
  if (!archivo.is_open()) {
    archivo.open(ARCHIVO);
    archivo << "Carne\tNombres\tApellidos\tCarrera\tTelefono\tDireccion\tSemest"
               "re\tCursos\tFecha/Hora\n";
  } else {
    archivo.seekp(0, ios::end);
    if (archivo.tellp() == 0) {
      archivo << "Carne\tNombres\tApellidos\tCarrera\tTelefono\tDireccion\tSeme"
                 "stre\tCursos\tFecha/Hora\n";
    }
  }

  int idx = a.cantidad - 1;
  archivo << a.alumnos[idx].carne << "\t" << a.alumnos[idx].nombre << "\t"
          << a.alumnos[idx].apellido << "\t" << a.alumnos[idx].carrera << "\t"
          << a.alumnos[idx].telefono << "\t" << a.alumnos[idx].direccion << "\t"
          << a.alumnos[idx].semestre << "\t" << a.alumnos[idx].cursosAsignados
          << "\t" << a.alumnos[idx].fechaHora << "\n";

  archivo.close();
}

// RF07 (parte 1): carga el expediente de estudiantes al iniciar el sistema.
void cargarDesdeArchivo(Academia &a) {
  ifstream archivo(ARCHIVO.c_str());
  if (!archivo.is_open())
    return;

  string linea;
  getline(archivo, linea); // encabezado

  a.cantidad = 0;
  while (a.cantidad < TAM && getline(archivo, linea)) {
    if (!linea.empty() && linea[linea.size() - 1] == '\r')
      linea.erase(linea.size() - 1);
    if (linea.empty())
      continue;

    istringstream ss(linea);
    string carne, nombres, apellidos, carrera, telefono, direccion, semestreStr,
        cursos, fecha;

    getline(ss, carne, '\t');
    getline(ss, nombres, '\t');
    getline(ss, apellidos, '\t');
    getline(ss, carrera, '\t');
    getline(ss, telefono, '\t');
    getline(ss, direccion, '\t');
    getline(ss, semestreStr, '\t');
    getline(ss, cursos, '\t');
    getline(ss, fecha);

    Estudiante &e = a.alumnos[a.cantidad];
    e.carne = carne;
    e.nombre = nombres;
    e.apellido = apellidos;
    e.carrera = carrera;
    e.telefono = telefono;
    e.direccion = direccion;
    // Si el semestre no es numerico (fila antigua/danada) se usa 0 en lugar
    // de dejar que stoi() lance una excepcion y cierre el programa.
    e.semestre = esEntero(semestreStr) ? atoi(semestreStr.c_str()) : 0;
    e.cursosAsignados = cursos;
    e.fechaHora = fecha;

    a.cantidad++;
  }
  archivo.close();
}
void ingresarAlumno(Academia &a) {
  string opcion;

  do {
    limpiarPantalla();
    if (a.cantidad >= TAM) {
      cout
          << "\n[ERROR] El sistema esta lleno. Maximo de alumnos alcanzado.\n";
      break;
    }

    cout << "\n++++++++++++++++++++++++++++++ NUEVO REGISTRO "
            "++++++++++++++++++++++++++++++ \n"
         << endl;
    cout << "+++++++++++++++++++++++++++++ CARRERAS DISPONIBLES "
            "+++++++++++++++++++++++++++++"
         << endl;
    cout << "Sistemas \t Medicina \t Arquitectura \t Civil \t Derecho\n\n"
         << endl;

    // Generación automática del carné
    ostringstream autoCarne;
    autoCarne << setfill('0') << setw(4) << siguienteCarneNumero(a);
    a.alumnos[a.cantidad].carne = autoCarne.str();

    cout << "[SISTEMA] Carne asignado automaticamente: "
         << a.alumnos[a.cantidad].carne << "\n";

    cout << "Nombres: ";
    if (a.cantidad == 0 || cin.peek() == '\n')
      cin.ignore();
    getline(cin, a.alumnos[a.cantidad].nombre);

    cout << "Apellidos: ";
    getline(cin, a.alumnos[a.cantidad].apellido);

    cout << "Carrera (escriba el nombre de las opciones de arriba): ";
    getline(cin, a.alumnos[a.cantidad].carrera);

    // Semestre y cursos de la malla (valida el rango segun la carrera)
    pedirSemestreYCursos(a.alumnos[a.cantidad]);
    // ----------------------------------------

    string telTemporal;
    bool telefonoValido = false;

    while (!telefonoValido) {
      cout << "Telefono (8 digitos): ";
      cin >> telTemporal;

      if (telTemporal.length() != 8) {
        cout
            << "[ERROR] El telefono debe tener exactamente 8 digitos.\n";
        continue;
      }

      bool soloNumeros = true;
      for (size_t i = 0; i < telTemporal.length(); i++) {
        if (!isdigit(telTemporal[i])) {
          soloNumeros = false;
          break;
        }
      }

      if (!soloNumeros) {
        cout << "[ERROR] Ingrese solo numeros.\n";
      } else {
        telefonoValido = true;
      }
    }
    a.alumnos[a.cantidad].telefono = telTemporal;

    cout << "Direccion: ";
    cin.ignore();
    getline(cin, a.alumnos[a.cantidad].direccion);

    time_t tiempoActual = time(0);
    tm *fechaInfo = localtime(&tiempoActual);
    char bufferFecha[30];
    strftime(bufferFecha, sizeof(bufferFecha), "%d/%m/%Y %H:%M:%S",
             fechaInfo);
    a.alumnos[a.cantidad].fechaHora = string(bufferFecha);

    a.cantidad++;
    agregarAlArchivo(a);

    limpiarPantalla();
    cout
        << "\n======================================================\n";
    cout << "          ESTUDIANTE REGISTRADO EXITOSAMENTE          \n";
    cout << "======================================================\n";
    cout << "Carne:      " << a.alumnos[a.cantidad - 1].carne
         << "\n";
    cout << "Nombre:     " << a.alumnos[a.cantidad - 1].nombre << " "
         << a.alumnos[a.cantidad - 1].apellido << "\n";
    cout << "Carrera:    " << a.alumnos[a.cantidad - 1].carrera
         << "\n";
    cout << "Semestre:   " << a.alumnos[a.cantidad - 1].semestre
         << "\n";
    cout << "Cursos:     " << a.alumnos[a.cantidad - 1].cursosAsignados
         << "\n";
    cout << "Telefono:   " << a.alumnos[a.cantidad - 1].telefono
         << "\n";
    cout << "Direccion:  " << a.alumnos[a.cantidad - 1].direccion
         << "\n";
    cout << "Fecha/Hora: " << a.alumnos[a.cantidad - 1].fechaHora
         << "\n";
    cout << "======================================================\n";

    cout << "\n¿Desea registrar otro alumno? (s/n): ";
    cin >> opcion;

  } while (opcion == "s" || opcion == "S");
}
