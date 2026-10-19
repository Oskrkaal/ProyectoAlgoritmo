#include "registro.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void eliminarAlumno() {
  system("clear");

  if (contadorAlumnos == 0) {
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

  for (int i = 0; i < contadorAlumnos; i++) {
    if (registrar[i].carrera == carreraBuscar) {
      cout << "  " << left << setw(10) << registrar[i].carne << "  " << setw(20)
           << registrar[i].nombre << "  " << registrar[i].apellido << "\n";
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
  for (int i = 0; i < contadorAlumnos; i++) {
    if (registrar[i].carne == carneBuscar &&
        registrar[i].carrera == carreraBuscar) {
      idx = i;
      break;
    }
  }

  if (idx == -1) {
    cout << "\n[ERROR] El carne '" << carneBuscar
         << "' no pertenece a esta carrera o no existe.\n";
    return;
  }

  system("clear");
  cout << "\n--- ESTUDIANTE ENCONTRADO ---\n";
  cout << "Carne:     " << registrar[idx].carne << "\n";
  cout << "Nombres:   " << registrar[idx].nombre << " "
       << registrar[idx].apellido << "\n";
  cout << "Carrera:   " << registrar[idx].carrera << "\n";

  string confirmacion;
  cout << "\n[ADVERTENCIA CRITICA] ¿Esta absolutamente seguro de ELIMINAR este "
          "registro de forma permanente? (s/n): ";
  cin >> confirmacion;

  if (confirmacion == "s" || confirmacion == "S") {
    for (int i = idx; i < contadorAlumnos - 1; i++) {
      registrar[i] = registrar[i + 1];
    }

    contadorAlumnos--;
    reescribirArchivo(); // <-- LLAMA A LA FUNCIÓN QUE ESTÁ EN
                         // EDITARREGISTRO.CPP

    cout << "\n[OK] El estudiante ha sido dado de baja y eliminado "
            "exitosamente del archivo.\n";
  } else {
    cout << "\n[INFO] Operacion cancelada. El registro permanece intacto.\n";
  }
}
