// ============================================================================
//  menu.cpp - RF11: menu principal y punto de entrada (main)
//  Aqui se crea la UNICA instancia de Academia y se pasa por referencia a
//  cada modulo. No hay variables globales (RNF03).
// ============================================================================
#include "registro.h"
#include <cstdlib>
#include <iostream>

using namespace std;

// Crea la carpeta "files" si no existe (el expediente y las actas van ahi)
static void asegurarCarpetaDatos() {
#ifdef _WIN32
  system("if not exist files mkdir files");
#else
  system("mkdir -p files");
#endif
}

void mostrarMenu(Academia &a) {
  int opcion = 0;

  do {
    limpiarPantalla();
    cout << "-----------------------------------------------------" << endl;
    cout << "           MENU PRINCIPAL / SisUniversidad           " << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << " 1. INGRESAR ESTUDIANTES (AL SISTEMA)" << endl;
    cout << " 2. MODIFICAR DATOS DE ESTUDIANTES" << endl;
    cout << " 3. CONSULTAR ESTUDIANTES" << endl;
    cout << " 4. INGRESAR NOTAS" << endl;
    cout << " 5. REPORTES" << endl;
    cout << " 6. FINALIZAR CICLO (REINICIAR NOTAS)" << endl;
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

    limpiarPantalla();
    switch (opcion) {
    case 1:
      ingresarAlumno(a);
      break;
    case 2:
      editarAlumno(a);
      break;
    case 3:
      consultarAlumno(a);
      break;
    case 4:
      menuNotas(a); // Modulo 2: ingreso de notas (RF08, RF09, RF06)
      break;
    case 5:
      reportes(a); // Matriz de notas + cuadro de honor (RF10, RF12, RF13)
      break;
    case 6:
      reiniciarMatrizNotasCiclo(a); // RF15 (reinicio.cpp)
      break;
    case 7:
      cout << "--- ELIMINAR DEL SISTEMA ---\n";
      eliminarAlumno(a);
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
  Academia academia;         // unico estado del sistema (local a main)
  iniciarAcademia(academia); // alumnos = 0, matriz de notas en 0
  asegurarCarpetaDatos();

  cargarDesdeArchivo(academia); // RF07: expediente de estudiantes
  cargarActas(academia);        // RF07: actas (requiere alumnos ya cargados)

  mostrarMenu(academia);
  return 0;
}
