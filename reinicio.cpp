// ============================================================================
//  reinicio.cpp - Modulo 3: Reportes y Menu (RF12 - RF15)
//  RF12: redondeos y porcentajes (cmath)
//  RF13: fecha/hora de emision (ctime)
//  RF14: validacion de rango de notas
//  RF15: reiniciar la matriz de notas para un nuevo ciclo
// ============================================================================
#include "registro.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

// ---------------------------------------------------------------------------
// RF12 - Redondear y calcular porcentajes con <cmath>
// ---------------------------------------------------------------------------

// Redondea al numero de decimales pedido (0 = entero mas cercano, como la
// version original). La nota final se muestra con redondearNota(x, 2).
double redondearNota(double nota, int decimales) {
  double factor = pow(10.0, decimales);
  return round(nota * factor) / factor;
}

// Porcentaje redondeado al entero mas cercano; protege la division entre cero.
double calcularPorcentaje(double parcial, double total) {
  if (total <= 0)
    return 0.0;
  return redondearNota((parcial / total) * 100.0);
}

// ---------------------------------------------------------------------------
// RF13 - Fecha y hora con <ctime>
// ---------------------------------------------------------------------------

// Devuelve la fecha/hora actual con el formato indicado (por defecto
// DD/MM/AAAA HH:MM:SS). La usan el acta (notas.cpp) y el respaldo del ciclo.
string fechaHoraActual(const char *formato) {
  time_t tiempoActual = time(0);
  tm *infoTiempo = localtime(&tiempoActual);

  char buffer[80];
  strftime(buffer, sizeof(buffer), formato, infoTiempo);
  return string(buffer);
}

void mostrarFechaHoraEmision() {
  cout << "\n Fecha y Hora de Emision del Reporte: " << fechaHoraActual()
       << "\n";
}

// ---------------------------------------------------------------------------
// RF14 - Validar que la nota este entre 0 y el maximo permitido.
// Por defecto el maximo es 100; notas.cpp lo usa con el tope de cada
// evaluacion (15, 15, 35, 35).
// ---------------------------------------------------------------------------
bool validarRangoNota(double nota, double maximo) {
  if (nota >= 0.0 && nota <= maximo)
    return true;

  cout << "  [ERROR] Nota invalida (" << nota << "). Debe estar entre 0 y "
       << maximo << " puntos.\n";
  return false;
}

// ---------------------------------------------------------------------------
// RF15 - Reiniciar la matriz de notas para un nuevo ciclo
// Recibe la Academia POR REFERENCIA, asi que modifica la matriz real del
// sistema (no una copia).
// ---------------------------------------------------------------------------
void reiniciarMatrizNotasCiclo(Academia &a) {
  limpiarPantalla();
  cout << "\n====================================================\n";
  cout << "          REINICIAR MATRIZ DE NOTAS (CICLO)         \n";
  cout << "====================================================\n";

  if (a.cantidad == 0) {
    cout << "\n[INFO] No hay estudiantes registrados en el sistema "
            "actualmente.\n";
    return;
  }

  bool hayNotas = false;
  for (int i = 0; i < FILAS; i++) {
    if (a.conNotas[i]) {
      hayNotas = true;
      break;
    }
  }
  if (!hayNotas) {
    cout << "\n[INFO] La matriz ya esta vacia: ningun alumno tiene notas.\n";
    return;
  }

  string confirmacion;
  cout << "\n[ADVERTENCIA] Esta accion pondra todas las notas de la matriz "
          "en cero (0).\n";
  cout << "Se guardara un respaldo del acta antes de borrar.\n";
  cout << "Desea proceder con el reinicio para el nuevo ciclo? (s/n): ";
  cin >> confirmacion;

  if (confirmacion != "s" && confirmacion != "S") {
    cout << "\n[INFO] Operacion cancelada por el usuario. Las notas no se "
            "modificaron.\n";
    return;
  }

  // 1) Respaldo del acta del ciclo que termina. Si falla, NO se borra nada.
  string respaldo =
      "files/ActaNotas_" + fechaHoraActual("%Y%m%d_%H%M%S") + ".txt";
  if (!exportarActaA(a, respaldo)) {
    cout << "\n[ERROR] No se pudo crear el respaldo (" << respaldo
         << "). Las notas NO fueron borradas.\n";
    return;
  }

  // 2) Se limpia toda la matriz (se recorren las FILAS completas, no solo los
  //    alumnos activos, para no dejar filas residuales).
  for (int i = 0; i < FILAS; i++) {
    a.conNotas[i] = false;
    for (int j = 0; j < EVAL; j++)
      a.notas[i][j] = 0.0f;
  }

  // 3) Se actualiza el acta permanente para que el reinicio persista.
  exportarActa(a);

  cout << "\n[OK] La matriz de notas ha sido reiniciada exitosamente para el "
          "nuevo ciclo.\n";
  cout << "[OK] Respaldo del ciclo anterior: " << respaldo << "\n";
}
