#include "registro.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void eliminarAlumno(Academia &a) {
  limpiarPantalla();

  if (a.cantidad == 0) {
    cout << "\n[INFO] No hay alumnos en el sistema. Asegurese de registrarlos "
            "primero.\n";
    return;
  }

  string carreraBuscar, carneBuscar;

  cout << "\n\t\t\t============================================\n";
  cout << "\t\t\t        DAR DE BAJA A UN ESTUDIANTE         \n";
  cout << "\t\t\t============================================\n";
  cout << "+++++++++++++++++++++++++++++ CARRERAS DISPONIBLES "
          "+++++++++++++++++++++++++++++\n"
       << endl;
  cout << "1. Sistemas \t 2. Medicina \t 3. Arquitectura \n 4. Civil \t 5. "
          "Derecho \n\n";

  cout << "Ingrese la Carrera a consultar (escriba el nombre): ";
  if (cin.peek() == '\n')
    cin.ignore();
  getline(cin, carreraBuscar);

  bool hayAlumnos = false;
  cout << "\n================================================================="
          "\n";
  cout << "  CARNE       NOMBRES               APELLIDOS\n";
  cout << "=================================================================\n";

  for (int i = 0; i < a.cantidad; i++) {
    if (a.alumnos[i].carrera == carreraBuscar) {
      cout << "  " << left << setw(10) << a.alumnos[i].carne << "  " << setw(20)
           << a.alumnos[i].nombre << "  " << a.alumnos[i].apellido << "\n";
      hayAlumnos = true;
    }
  }
  cout << "=================================================================\n";

  if (!hayAlumnos) {
    cout << "\n[INFO] No se encontraron estudiantes registrados en la carrera: "
         << carreraBuscar << ".\n";
    return;
  }

  cout
      << "\nIngrese el Carne del estudiante que desea dar de baja (ej. 0001): ";
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
    cout << "\n[ERROR] El carne '" << carneBuscar
         << "' no pertenece a esta carrera o no existe.\n";
    return;
  }

  limpiarPantalla();
  cout << "\n--- ESTUDIANTE ENCONTRADO ---\n";
  cout << "Carne:     " << a.alumnos[idx].carne << "\n";
  cout << "Nombres:   " << a.alumnos[idx].nombre << " "
       << a.alumnos[idx].apellido << "\n";
  cout << "Carrera:   " << a.alumnos[idx].carrera << "\n";

  string confirmacion;
  cout << "\n[ADVERTENCIA CRITICA] Esta absolutamente seguro de ELIMINAR este "
          "registro de forma permanente? (s/n): ";
  cin >> confirmacion;

  if (confirmacion == "s" || confirmacion == "S") {
    // Se desplazan JUNTOS el alumno y TODAS sus filas de la matriz de notas
    // (una por curso), para que las filas del alumno i sigan siendo suyas.
    for (int i = idx; i < a.cantidad - 1; i++) {
      a.alumnos[i] = a.alumnos[i + 1];
      for (int c = 0; c < MAX_CURSOS; c++) {
        int destino = filaNota(i, c);
        int origen = filaNota(i + 1, c);
        for (int j = 0; j < EVAL; j++)
          a.notas[destino][j] = a.notas[origen][j];
        a.conNotas[destino] = a.conNotas[origen];
      }
    }

    // El ultimo alumno queda libre: se limpian sus filas (sin notas fantasma).
    limpiarNotasAlumno(a, a.cantidad - 1);

    a.cantidad--;
    reescribirArchivo(a); // expediente (definida en editarRegistro.cpp)
    exportarActa(a);      // acta de notas (definida en notas.cpp)

    cout << "\n[OK] El estudiante ha sido dado de baja y eliminado "
            "exitosamente del archivo.\n";
  } else {
    cout << "\n[INFO] Operacion cancelada. El registro permanece intacto.\n";
  }
}
