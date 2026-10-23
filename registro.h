#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>

using namespace std;

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

// Declaración de variables globales para compartir entre archivos
const int TAM = 50;
extern Estudiante registrar[TAM];
extern int contadorAlumnos;
extern const string ARCHIVO;

void ingresarAlumno();
void editarAlumno();
void eliminarAlumno();
void consultarAlumno();
void reescribirArchivo();
void cargarDesdeArchivo(); // Agregado para poder usarlo en el main

#endif
