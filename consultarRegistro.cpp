#include "registro.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void consultarAlumno() {
  int opcion;

  do {
    system("clear");
    cout << "\n\t\t\t============================================\n";
    cout << "\t\t\t            MODULO DE CONSULTAS             \n";
    cout << "\t\t\t============================================\n";
    cout << " 1. Buscar estudiante por Nombre o Apellido (RF04)\n";
    cout << " 2. Mostrar listado general de matriculados (RF05)\n";
    cout << " 3. Volver al menu principal\n";
    cout << "----------------------------------------------------\n";
    cout << " Seleccione una opcion [1-3]: ";

    if (!(cin >> opcion)) {
      cin.clear();
      cin.ignore(1000, '\n');
      continue;
    }

    if (opcion == 3)
      break;

    if (contadorAlumnos == 0) {
      cout << "\n[INFO] La base de datos esta vacia. No hay alumnos "
              "registrados.\n";
      cout << "Presione Enter para continuar...";
      cin.ignore();
      cin.get();
      continue;
    }

    system("clear");

    if (opcion == 1) {
      string nombreBuscar;
      cout << "\n================ BUSQUEDA DE ESTUDIANTE ================\n";
      cout << "Ingrese el nombre o apellido a buscar (puede ser parcial): ";
      if (cin.peek() == '\n')
        cin.ignore();
      getline(cin, nombreBuscar);

      bool encontrado = false;
      cout << "\n=============================================================="
              "==========================================================\n";
      cout << "  CARNE       NOMBRES               APELLIDOS             "
              "CARRERA        SEM   TELEFONO     CURSOS ASIGNADOS\n";
      cout << "================================================================"
              "========================================================\n";

      for (int i = 0; i < contadorAlumnos; i++) {
        if (registrar[i].nombre.find(nombreBuscar) != string::npos ||
            registrar[i].apellido.find(nombreBuscar) != string::npos) {

          cout << "  " << left << setw(10) << registrar[i].carne << "  "
               << setw(20) << registrar[i].nombre << "  " << setw(20)
               << registrar[i].apellido << "  " << setw(13)
               << registrar[i].carrera << "  " << setw(4)
               << registrar[i].semestre << "  " << setw(11)
               << registrar[i].telefono << "  "
               << registrar[i].cursosAsignados.substr(0, 30)
               << "...\n"; // Se recorta a 30 caracteres para no romper la tabla
          encontrado = true;
        }
      }
      cout << "================================================================"
              "========================================================\n";

      if (!encontrado) {
        cout << "\n[INFO] No se encontraron resultados que coincidan con: '"
             << nombreBuscar << "'.\n";
      }

    } else if (opcion == 2) {
      cout << "\n\t\t\t============================================\n";
      cout << "\t\t\t         LISTADO GENERAL DE ALUMNOS         \n";
      cout << "\t\t\t============================================\n";
      cout << "\n=============================================================="
              "==========================================================\n";
      cout << "  CARNE       NOMBRES               APELLIDOS             "
              "CARRERA        SEM   TELEFONO     CURSOS ASIGNADOS\n";
      cout << "================================================================"
              "========================================================\n";

      for (int i = 0; i < contadorAlumnos; i++) {
        cout << "  " << left << setw(10) << registrar[i].carne << "  "
             << setw(20) << registrar[i].nombre << "  " << setw(20)
             << registrar[i].apellido << "  " << setw(13)
             << registrar[i].carrera << "  " << setw(4) << registrar[i].semestre
             << "  " << setw(11) << registrar[i].telefono << "  "
             << registrar[i].cursosAsignados.substr(0, 30) << "...\n";
      }
      cout << "================================================================"
              "========================================================\n";
      cout << "Total de matriculados: " << contadorAlumnos
           << " estudiante(s).\n";
    }

    cout << "\nPresione Enter para continuar...";
    if (cin.peek() == '\n')
      cin.ignore();
    cin.get();

  } while (opcion != 3);
}
