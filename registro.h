#ifndef REGISTRO_H
#define REGISTRO_H

// ============================================================================
//  Dev-Academy - Sistema de Control Academico (Seccion C)
//  Header comun. NO declara variables globales: todo el estado del sistema
//  vive en un unico objeto 'Academia' creado en main() y se comparte entre
//  modulos pasandolo POR REFERENCIA (&).  Solo hay constantes (const).
// ============================================================================

#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------- Constantes
const int TAM = 50;  // maximo de alumnos (filas de la matriz de notas)
const int EVAL = 4;  // columnas: 0=Parcial 1, 1=Parcial 2, 2=Actividades, 3=Examen
const int MAX_CURSOS = 8;        // maximo de cursos por semestre (Medicina/Arq.)
const int FILAS = TAM * MAX_CURSOS; // filas de la matriz: una por (alumno, curso)
const string ARCHIVO = "files/ExpedienteEstudiante.txt";
const string ARCHIVO_ACTAS = "files/ActaNotas.txt";

// ------------------------------------------------------------------- Structs
struct Estudiante {
  string carne;
  string nombre;
  string apellido;
  string carrera;
  string telefono;
  string direccion;
  string fechaHora;
  int semestre;
  string cursosAsignados;
};

// Contenedor de todo el estado del sistema (reemplaza a las globales).
//   alumnos[i]  -> datos personales del alumno i
//   notas[f][j] -> matriz 2D (Alumno-Curso) x Evaluaciones
//   conNotas[f] -> true si esa fila (alumno, curso) ya tiene notas
// La fila de la matriz para el curso c del alumno i es:  f = i * MAX_CURSOS + c
// (ver filaNota() en notas.cpp).
struct Academia {
  Estudiante alumnos[TAM];
  int cantidad;
  float notas[FILAS][EVAL];
  bool conNotas[FILAS];
};

// ----------------------------------------------- Utilidades (registro.cpp)
string aMinusculas(string cadena);
void limpiarPantalla();
void iniciarAcademia(Academia &a);
int maxSemestresCarrera(const string &carrera);
void pedirSemestreYCursos(Estudiante &e);
vector<string> cursosDeAlumno(const Estudiante &e);

// ------------------------------------------ Modulo 1: Alumnos (RF01 - RF05)
void ingresarAlumno(Academia &a);
void editarAlumno(Academia &a);
void eliminarAlumno(Academia &a);
void consultarAlumno(const Academia &a);
void reescribirArchivo(const Academia &a);
void cargarDesdeArchivo(Academia &a);

// ------------------------------------- Modulo 2: Notas y archivos (RF06-RF10)
int filaNota(int alumno, int curso);
void limpiarNotasAlumno(Academia &a, int alumno);
void calcularNotaFinal(float parcial1, float parcial2, float actividades,
                       float examen, float &zona, float &notaFinal);
bool exportarActaA(const Academia &a, const string &ruta);
bool exportarActa(const Academia &a);
bool cargarActas(Academia &a);
void mostrarMatriz(const Academia &a);
void cuadroHonor(const Academia &a);
void reportes(const Academia &a);
void menuNotas(Academia &a);

// ------------------------------------- Modulo 3: Reportes y menu (RF11-RF15)
double redondearNota(double nota, int decimales = 0);
double calcularPorcentaje(double parcial, double total);
string fechaHoraActual(const char *formato = "%d/%m/%Y %H:%M:%S");
void mostrarFechaHoraEmision();
bool validarRangoNota(double nota, double maximo = 100.0);
void reiniciarMatrizNotasCiclo(Academia &a);

#endif
