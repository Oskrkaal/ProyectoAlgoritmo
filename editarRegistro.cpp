#include "registro.h"
#include <cctype>
#include <fstream>
#include <iomanip> // Necesario para mantener las columnas ordenadas
#include <iostream>
#include <string>

using namespace std;

void reescribirArchivo() {
  ofstream archivo(ARCHIVO);
  if (!archivo.is_open()) {
    cout << "[ERROR] No se pudo abrir el archivo para guardar.\n";
    return;
  }

  archivo << "Carne\tNombres\tApellidos\tCarrera\tTelefono\tDireccion\tFecha/"
             "Hora\n";

  for (int i = 0; i < contadorAlumnos; i++) {
    archivo << registrar[i].carne << "\t" << registrar[i].nombre << "\t"
            << registrar[i].apellido << "\t" << registrar[i].carrera << "\t"
            << registrar[i].telefono << "\t" << registrar[i].direccion << "\t"
            << registrar[i].fechaHora << "\n";
  }
  archivo.close();
}

bool validarTelefono(string &tel) {
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

void editarAlumno() {
  system("clear");

  if (contadorAlumnos == 0) {
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

  for (int i = 0; i < contadorAlumnos; i++) {
    if (registrar[i].carrera == carreraBuscar) {
      cout << "  " << left << setw(10) << registrar[i].carne << "  " << setw(20)
           << registrar[i].nombre << "  " << setw(20) << registrar[i].apellido
           << "  " << setw(11)
           << registrar[i].telefono
           // Substr evita que direcciones muy largas rompan la alineación de la
           // tabla
           << "  " << setw(22) << registrar[i].direccion.substr(0, 21) << "  "
           << registrar[i].fechaHora << "\n";
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
  for (int i = 0; i < contadorAlumnos; i++) {
    if (registrar[i].carne == carneBuscar &&
        registrar[i].carrera == carreraBuscar) {
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
  system("clear");
  cout << "\n--- DATOS ENCONTRADOS ---\n";
  cout << "Carne:     " << registrar[idx].carne << "\n";
  cout << "Nombres:   " << registrar[idx].nombre << "\n";
  cout << "Apellidos: " << registrar[idx].apellido << "\n";
  cout << "Carrera:   " << registrar[idx].carrera << "\n";
  cout << "Telefono:  " << registrar[idx].telefono << "\n";
  cout << "Direccion: " << registrar[idx].direccion << "\n";
  cout << "Fecha:     " << registrar[idx].fechaHora << "\n";

  int opcion;
  do {
    cout << "\n--- ELIGE QUE CAMBIAR ---\n";
    cout << "1. Nombres\n2. Apellidos\n3. Carrera\n4. Telefono\n5. "
            "Direccion\n6. Guardar y volver al menu\nOpcion: ";
    cin >> opcion;

    switch (opcion) {
    case 1:
      cout << "Nuevo nombre: ";
      cin.ignore();
      getline(cin, registrar[idx].nombre);
      break;
    case 2:
      cout << "Nuevo apellido: ";
      cin.ignore();
      getline(cin, registrar[idx].apellido);
      break;
    case 3:
      cout << "Nueva carrera: ";
      cin.ignore();
      getline(cin, registrar[idx].carrera);
      break;
    case 4:
      validarTelefono(registrar[idx].telefono);
      break;
    case 5:
      cout << "Nueva direccion: ";
      cin.ignore();
      getline(cin, registrar[idx].direccion);
      break;
    case 6:
      reescribirArchivo();
      cout << "\n[OK] Cambios guardados exitosamente.\n";
      break;
    default:
      cout << "[ERROR] Opcion invalida.\n";
    }
  } while (opcion != 6);
}
