#include "registro.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

// Definición de las variables globales
Estudiante registrar[TAM];
int contadorAlumnos = 0;
const string ARCHIVO = "files/ExpedienteEstudiante.txt";

void agregarAlArchivo() {
  ofstream archivo(ARCHIVO, ios::app);
  if (!archivo.is_open()) {
    archivo.open(ARCHIVO);
    archivo << "Carne\tNombres\tApellidos\tCarrera\tTelefono\tDireccion\tFecha/"
               "Hora\n";
  } else {
    archivo.seekp(0, ios::end);
    if (archivo.tellp() == 0) {
      archivo << "Carne\tNombres\tApellidos\tCarrera\tTelefono\tDireccion\tFech"
                 "a/Hora\n";
    }
  }

  int idx = contadorAlumnos - 1;
  archivo << registrar[idx].carne << "\t" << registrar[idx].nombre << "\t"
          << registrar[idx].apellido << "\t" << registrar[idx].carrera << "\t"
          << registrar[idx].telefono << "\t" << registrar[idx].direccion << "\t"
          << registrar[idx].fechaHora << "\n";

  archivo.close();
}

void cargarDesdeArchivo() {
  ifstream archivo(ARCHIVO);
  if (!archivo.is_open())
    return;

  string linea;
  getline(archivo, linea); // Saltar el encabezado de las columnas

  contadorAlumnos = 0;
  while (getline(archivo, linea)) {
    if (linea.empty())
      continue;

    istringstream ss(linea);
    string carne, nombres, apellidos, carrera, telefono, direccion, fecha;

    getline(ss, carne, '\t');
    getline(ss, nombres, '\t');
    getline(ss, apellidos, '\t');
    getline(ss, carrera, '\t');
    getline(ss, telefono, '\t');
    getline(ss, direccion, '\t');
    getline(ss, fecha);

    if (contadorAlumnos >= TAM)
      break;

    registrar[contadorAlumnos].carne = carne;
    registrar[contadorAlumnos].nombre = nombres;
    registrar[contadorAlumnos].apellido = apellidos;
    registrar[contadorAlumnos].carrera = carrera;
    registrar[contadorAlumnos].telefono = telefono;
    registrar[contadorAlumnos].direccion = direccion;
    registrar[contadorAlumnos].fechaHora = fecha;
    contadorAlumnos++;
  }
  archivo.close();
}

void ingresarAlumno() {
  string opcion;

  do {
    system("clear");
    if (contadorAlumnos >= TAM) {
      cout << "\n[ERROR] El sistema esta lleno. Maximo de alumnos alcanzado.\n";
      break;
    }

    cout << "\n++++++++++++++++++++++++++++++ NUEVO REGISTRO "
            "++++++++++++++++++++++++++++++ \n"
         << endl;
    cout << "+++++++++++++++++++++++++++++ CARRERAS DISPONIBLES "
            "+++++++++++++++++++++++++++++"
         << endl;

    cout << "1. Sistemas \t 2. Medicina \t 3. "
            "Arquitectura \t 4. Civil \t 5. Derecho\n\n"
         << endl;
    // Generación automática del carné (0001, 0002, etc.)
    ostringstream autoCarne;
    autoCarne << setfill('0') << setw(4) << (contadorAlumnos + 1);
    registrar[contadorAlumnos].carne = autoCarne.str();

    cout << "[SISTEMA] Carne asignado automaticamente: "
         << registrar[contadorAlumnos].carne << "\n";

    cout << "Nombres: ";
    if (contadorAlumnos == 0 || cin.peek() == '\n')
      cin.ignore();
    getline(cin, registrar[contadorAlumnos].nombre);

    cout << "Apellidos: ";
    getline(cin, registrar[contadorAlumnos].apellido);

    cout << "Carrera: ";
    getline(cin, registrar[contadorAlumnos].carrera);

    string telTemporal;
    bool telefonoValido = false;

    while (!telefonoValido) {
      cout << "Telefono (8 digitos): ";
      cin >> telTemporal;

      if (telTemporal.length() != 8) {
        cout << "[ERROR] El telefono debe tener exactamente 8 digitos.\n";
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
    registrar[contadorAlumnos].telefono = telTemporal;

    cout << "Direccion: ";
    cin.ignore();
    getline(cin, registrar[contadorAlumnos].direccion);

    time_t tiempoActual = time(0);
    tm *fechaInfo = localtime(&tiempoActual);
    char bufferFecha[30];
    strftime(bufferFecha, sizeof(bufferFecha), "%d/%m/%Y %H:%M:%S", fechaInfo);
    registrar[contadorAlumnos].fechaHora = string(bufferFecha);

    contadorAlumnos++;
    agregarAlArchivo();

    system("clear");
    cout << "\n======================================================\n";
    cout << "          ESTUDIANTE REGISTRADO EXITOSAMENTE          \n";
    cout << "======================================================\n";
    cout << "Carne:      " << registrar[contadorAlumnos - 1].carne << "\n";
    cout << "Nombre:     " << registrar[contadorAlumnos - 1].nombre << " "
         << registrar[contadorAlumnos - 1].apellido << "\n";
    cout << "Carrera:    " << registrar[contadorAlumnos - 1].carrera << "\n";
    cout << "Telefono:   " << registrar[contadorAlumnos - 1].telefono << "\n";
    cout << "Direccion:  " << registrar[contadorAlumnos - 1].direccion << "\n";
    cout << "Fecha/Hora: " << registrar[contadorAlumnos - 1].fechaHora << "\n";
    cout << "======================================================\n";

    cout << "\n¿Desea registrar otro alumno? (s/n): ";
    cin >> opcion;

  } while (opcion == "s" || opcion == "S");
}
