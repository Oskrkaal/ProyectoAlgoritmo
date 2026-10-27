#include "registro.h"
#include <cctype>
#include <fstream>
#include <iomanip> // Necesario para mantener las columnas ordenadas
#include <iostream>
#include <string>

using namespace std;

void reescribirArchivo(const Academia &a) {
  ofstream archivo(ARCHIVO);
  if (!archivo.is_open()) {
    cout << "[ERROR] No se pudo abrir el archivo para guardar.\n";
    return;
  }

  archivo << "Carne\tNombres\tApellidos\tCarrera\tTelefono\tDireccion\tSemestre"
             "\tCursos\tFecha/Hora\n";

  for (int i = 0; i < a.cantidad; i++) {
    archivo << a.alumnos[i].carne << "\t" << a.alumnos[i].nombre << "\t"
            << a.alumnos[i].apellido << "\t" << a.alumnos[i].carrera << "\t"
            << a.alumnos[i].telefono << "\t" << a.alumnos[i].direccion << "\t"
            << a.alumnos[i].semestre << "\t" << a.alumnos[i].cursosAsignados
            << "\t" << a.alumnos[i].fechaHora << "\n";
  }
  archivo.close();
}

static bool validarTelefono(string &tel) {
  tel.clear();
  bool valido = false;

  while (!valido) {
    cout << "Nuevo telefono (8 digitos): ";
    cin >> tel;

    if (tel.length() != 8) {
      cout << "[ERROR] Debe tener exactamente 8 digitos.\n";
      continue;
    }

    bool soloNumeros = true;
    for (size_t i = 0; i < tel.length(); i++) {
      if (!isdigit(tel[i])) {
        soloNumeros = false;
        break;
      }
    }

    if (!soloNumeros) {
      cout << "[ERROR] Solo numeros permitidos.\n";
    } else {
      valido = true;
    }
  }
  return valido;
}

void editarAlumno(Academia &a) {
  limpiarPantalla();

  if (a.cantidad == 0) {
    cout << "\n[INFO] No hay alumnos en el sistema. Asegurese de registrarlos "
            "primero.\n";
    return;
  }

  string carreraBuscar, carneBuscar;

  // --- INTERFAZ DE USUARIO INTEGRADA ---
  cout << "\n\t\t\t============================================\n";
  cout << "\t\t\t      BUSQUEDA DE ESTUDIANTE A EDITAR       \n";
  cout << "\t\t\t============================================\n";
  cout << "+++++++++++++++++++++++++++++ CARRERAS DISPONIBLES "
          "+++++++++++++++++++++++++++++\n"
       << endl;
  cout << "1. Sistemas \t 2. Medicina \t 3. Arquitectura \t4. Civil \t 5. "
          "Derecho\n\n"
       << endl;

  cout << "Ingrese la Carrera a consultar (escriba el nombre): ";
  if (cin.peek() == '\n')
    cin.ignore();
  getline(cin, carreraBuscar);

  // --- FILTRADO POR CARRERA CON INFORMACIÓN COMPLETA ---
  bool hayAlumnos = false;
  cout << "\n=================================================================="
          "======================================================\n";
  cout << "  CARNE       NOMBRES               APELLIDOS             TELEFONO  "
          "   DIRECCION               FECHA/HORA\n";
  cout << "===================================================================="
          "====================================================\n";

  for (int i = 0; i < a.cantidad; i++) {
    if (a.alumnos[i].carrera == carreraBuscar) {
      cout << "  " << left << setw(10) << a.alumnos[i].carne << "  " << setw(20)
           << a.alumnos[i].nombre << "  " << setw(20) << a.alumnos[i].apellido
           << "  " << setw(11)
           << a.alumnos[i].telefono
           // Substr evita que direcciones muy largas rompan la alineación de la
           // tabla
           << "  " << setw(22) << a.alumnos[i].direccion.substr(0, 21) << "  "
           << a.alumnos[i].fechaHora << "\n";
      hayAlumnos = true;
    }
  }
  cout << "===================================================================="
          "====================================================\n";

  if (!hayAlumnos) {
    cout << "\n[INFO] No se encontraron estudiantes en la carrera: "
         << carreraBuscar << ".\n";
    return;
  }

  // --- SELECCIÓN DE CARNÉ EXACTO ---
  cout << "\nIngrese el Carne del estudiante que desea editar: ";
  cin >> carneBuscar;

  int idx = -1;
  for (int i = 0; i < a.cantidad; i++) {
    if (a.alumnos[i].carne == carneBuscar &&
        a.alumnos[i].carrera == carreraBuscar) {
      idx = i;
      break;
    }
  }

  if (idx == -1) {
    cout << "\n[ERROR] No se encontro ningun estudiante con Carne: "
         << carneBuscar << " en la carrera: " << carreraBuscar << ".\n";
    return;
  }

  // --- EDICIÓN DEL REGISTRO ---
  limpiarPantalla();
  cout << "\n--- DATOS ENCONTRADOS ---\n";
  cout << "Carne:     " << a.alumnos[idx].carne << "\n";
  cout << "Nombres:   " << a.alumnos[idx].nombre << "\n";
  cout << "Apellidos: " << a.alumnos[idx].apellido << "\n";
  cout << "Carrera:   " << a.alumnos[idx].carrera << "\n";
  cout << "Telefono:  " << a.alumnos[idx].telefono << "\n";
  cout << "Direccion: " << a.alumnos[idx].direccion << "\n";
  cout << "Fecha:     " << a.alumnos[idx].fechaHora << "\n";

  int opcion;
  do {
    cout << "\n--- ELIGE QUE CAMBIAR ---\n";
    cout << "1. Nombres\n2. Apellidos\n3. Carrera\n4. Telefono\n5. "
            "Direccion\n6. Guardar y volver al menu\nOpcion: ";
    if (!(cin >> opcion)) {
      cin.clear();
      cin.ignore(1000, '\n');
      opcion = 0;
    }

    switch (opcion) {
    case 1:
      cout << "Nuevo nombre: ";
      cin.ignore();
      getline(cin, a.alumnos[idx].nombre);
      break;
    case 2:
      cout << "Nuevo apellido: ";
      cin.ignore();
      getline(cin, a.alumnos[idx].apellido);
      break;
    case 3:
      cout << "Nueva carrera: ";
      cin.ignore();
      getline(cin, a.alumnos[idx].carrera);
      // Al cambiar de carrera cambian los cursos: se pide el semestre, se
      // reasignan los cursos y se descartan las notas de los cursos anteriores.
      pedirSemestreYCursos(a.alumnos[idx]);
      limpiarNotasAlumno(a, idx);
      cout << "[AVISO] Cursos reasignados. Se borraron las notas anteriores "
              "del alumno.\n";
      break;
    case 4:
      validarTelefono(a.alumnos[idx].telefono);
      break;
    case 5:
      cout << "Nueva direccion: ";
      cin.ignore();
      getline(cin, a.alumnos[idx].direccion);
      break;
    case 6:
      reescribirArchivo(a);
      exportarActa(a); // por si cambio la carrera y se limpiaron notas
      cout << "\n[OK] Cambios guardados exitosamente.\n";
      break;
    default:
      cout << "[ERROR] Opcion invalida.\n";
    }
  } while (opcion != 6);
}
