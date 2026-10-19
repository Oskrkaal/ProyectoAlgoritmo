#include "registro.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void mostrarMenu() {
  int opcion = 0;

  do {
    system("clear");
    cout << "-----------------------------------------------------" << endl;
    cout << "                  MENU PRINCIPAL                     " << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << " 1. INGRESAR ESTUDIANTES (AL SISTEMA)" << endl;
    cout << " 2. MODIFICAR DATOS DE ESTUDIANTES" << endl;
    cout << " 3. CONSULTAR ESTUDIANTES" << endl;
    cout << " 4. INGRESAR NOTAS" << endl;
    cout << " 5. REPORTES" << endl;
    cout << " 6. FINALIZAR CICLO" << endl;
    cout << " 7. ELIMINAR DEL SISTEMA" << endl;
    cout << " 8. SALIR" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << " Seleccione una opcion [1-8]: ";

    if (!(cin >> opcion)) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "\n[ERROR] Entrada invalida. Ingrese un numero del 1 al 8.\n";
      cout << "\nPresione Enter para continuar...";
      cin.get();
      continue;
    }

    system("clear");
    switch (opcion) {
    case 1:
      ingresarAlumno();
      break;
    case 2:
      editarAlumno();
      break;
    case 3:
      consultarAlumno();
      break;
    case 4:
      cout << "--- INGRESAR NOTAS ---\n";
      break;
    case 5:
      cout << "--- REPORTES ---\n";
      break;
    case 6:
      cout << "--- FINALIZAR CICLO ---\n";
      break;
    case 7:
      cout << "--- ELIMINAR DEL SISTEMA ---\n";
      eliminarAlumno();
      break;
    case 8:
      cout << "\nApagando sistemas...\n";
      break;
    default:
      cout << "\n[ERROR] Opcion fuera de rango.\n";
      break;
    }

    if (opcion != 8) {
      cout << "\nPresione Enter para continuar...";
      cin.ignore(1000, '\n');
      cin.get();
    }
  } while (opcion != 8);
}

int main() {
  // cargarDesdeArchivo(); // Descomentar cuando implementemos la carga inicial
  cargarDesdeArchivo();
  mostrarMenu();
  return 0;
}
