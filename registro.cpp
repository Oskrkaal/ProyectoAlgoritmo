#include "registro.h"
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

// Función para convertir a minúsculas y facilitar la búsqueda de carreras
string aMinusculas(string cadena) {
  string resultado = cadena;
  transform(resultado.begin(), resultado.end(), resultado.begin(), ::tolower);
  return resultado;
}

// Base de datos global de las mallas curriculares por carrera
map<int, vector<string>> obtenerMalla(string carreraSeleccionada) {
  map<int, vector<string>> malla;
  carreraSeleccionada = aMinusculas(carreraSeleccionada);

  if (carreraSeleccionada == "sistemas") {
    malla[1] = {"Contabilidad I", "Desarrollo Humano y Profesional",
                "Introduccion a los Sistemas de Computo", "Logica de Sistemas",
                "Metodologia de la Investigacion"}; //[cite: 1]
    malla[2] = {"Algebra Lineal", "Algoritmos", "Contabilidad II",
                "Matematica Discreta", "Precalculo"}; //[cite: 1]
    malla[3] = {"Calculo I", "Derecho Informatico", "Fisica I",
                "Proceso Administrativo", "Programacion I"}; //[cite: 1]
    malla[4] = {"Calculo II", "Estadistica I", "Fisica II", "Microeconomia",
                "Programacion II"}; //[cite: 1]
    malla[5] = {"Electronica Analogica", "Emprendedores de Negocios",
                "Estadistica II", "Metodos Numericos",
                "Programacion III"}; //[cite: 1]
    malla[6] = {"Automatas y Lenguajes Formales", "Bases de Datos I",
                "Electronica Digital", "Investigacion de Operaciones",
                "Sistemas Operativos I"}; //[cite: 1]
    malla[7] = {"Analisis de Sistemas I", "Arquitectura de Computadoras I",
                "Bases de Datos II", "Compiladores",
                "Sistemas Operativos II"}; //[cite: 1]
    malla[8] = {"Analisis de Sistemas II", "Arquitectura de Computadoras II",
                "Desarrollo Web", "Etica Profesional",
                "Redes de Computadoras I"}; //[cite: 1]
    malla[9] = {"Administracion de Tecnologias de Informacion",
                "Ingenieria de Software", "Inteligencia Artificial",
                "Proyecto de Graduacion I",
                "Redes de Computadoras II"}; //[cite: 1]
    malla[10] = {"Aseguramiento de la Calidad de Software",
                 "Proyecto de Graduacion II",
                 "Seguridad y Auditoria de Sistemas",
                 "Seminario de Tecnologias de Informacion",
                 "Telecomunicaciones"}; //[cite: 1]
  } else if (carreraSeleccionada == "medicina") {
    malla[1] = {"Biologia Celular y Molecular Humana I",
                "Ciencias Exactas en la Salud",
                "Desarrollo Humano y Profesional",
                "Metodologia de la Investigacion",
                "Principios Clinicos",
                "Quimica Inorganica",
                "Salud Mental I Bases Biologicas de la Conducta",
                "Sistemas de Comunicacion"}; //[cite: 2]
    malla[2] = {"Bioestadistica",
                "Biologia Celular y Molecular Humana II",
                "Embriologia",
                "Fisica Medica I",
                "Investigacion I",
                "Propedeutica Medica",
                "Quimica Organica",
                "Salud Mental II Psicologia de la Anormalidad"}; //[cite: 2]
    malla[3] = {"Anatomia I",
                "Bioquimica I",
                "Fisica Medica II",
                "Histologia I",
                "Investigacion II",
                "Realidad Nacional",
                "Salud Mental III Des. Psicolog. del Niño y del Adolescente",
                "Semiologia I"}; //[cite: 2]
    malla[4] = {"Anatomia II",
                "Atencion Primaria en Salud",
                "Bioquimica II",
                "Epidemiologia",
                "Fisiologia I",
                "Histologia II",
                "Salud Mental IV Salud Mental en Atencion Primaria",
                "Semiologia II"}; //[cite: 2]
    malla[5] = {"Anatomia III",  "Bioquimica III",  "Farmacologia I",
                "Fisiologia II", "Microbiologia I", "Patologia I",
                "Salud Publica", "Semiologia III"}; //[cite: 2]
    malla[6] = {"Bioquimica Clinica Aplicada",
                "Farmacologia II",
                "Fisiologia III",
                "Inmunologia",
                "Microbiologia II",
                "Patologia II",
                "Rehabilitacion",
                "Tecnologia Biomolecular"}; //[cite: 2]
    malla[7] = {"Atencion Ambulatoria y Pre-Hospitalaria",
                "Atencion Neurologica",
                "Atencion Oftalmologica",
                "Genetica Humana",
                "Medicina Forense",
                "Medicina Laboral"};                   //[cite: 2]
    malla[8] = {"Bioetica I", "Medicina Interna I"};   //[cite: 2]
    malla[9] = {"Medicina Interna II", "Psiquiatria"}; //[cite: 2]
    malla[10] = {"Gestion y Liderazgo de Servicios de Salud",
                 "Pediatria"}; //[cite: 2]
    malla[11] = {"Cirugia", "Medicina Alternativa",
                 "Trabajo de Graduacion I"}; //[cite: 2]
    malla[12] = {"Ginecologia y Obstetricia",
                 "Trabajo de Graduacion II"}; //[cite: 2]
    malla[13] = {"Antropologia Medica",
                 "Practica Profesional Asistida Rural"}; //[cite: 2]
    malla[14] = {"Bioetica II",
                 "Practica Profesional Asistida Hospitalaria"}; //[cite: 2]
  } else if (carreraSeleccionada == "arquitectura") {
    malla[1] = {"Comunicacion Oral y Escrita",
                "Desarrollo Humano y Profesional",
                "Dibujo Arquitectonico I",
                "Ecologia",
                "Humanistica y Estetica",
                "Matematica I",
                "Metodos y Tecnicas de Diseño",
                "Tecnicas de Expresion Grafica I"}; //[cite: 5]
    malla[2] = {"Computacion I",
                "Dibujo Arquitectonico II",
                "Diseño Arquitectonico I",
                "Matematica II",
                "Materiales de Construccion",
                "Metodos de Investigacion I",
                "Modelos Arquitectonicos",
                "Tecnicas de Expresion Grafica II"}; //[cite: 5]
    malla[3] = {"Computacion II",
                "Control Ambiental I",
                "Diseño Arquitectonico II",
                "Fisica",
                "Geometria",
                "Historia de la Arquitectura I",
                "Introduccion a las Estructuras",
                "Tecnicas de Presentacion de Proyectos"}; //[cite: 5]
    malla[4] = {"Control Ambiental II",
                "Dibujo Constructivo",
                "Diseño Arquitectonico III",
                "Historia de la Arquitectura II",
                "Leyes y Normas de la Construccion y Ambientales",
                "Sistemas Constructivos I",
                "Sistemas Estructurales I",
                "Topografia"}; //[cite: 5]
    malla[5] = {"Administracion de Obras I",
                "Diseño Arquitectonico IV",
                "Historia de la Arquitectura III",
                "Instalaciones I",
                "Psicologia Ambiental",
                "Sistemas Constructivos II",
                "Sistemas Estructurales II"}; //[cite: 5]
    malla[6] = {"Administracion de Obras II",
                "Arquitectura Ambiental",
                "Diseño Arquitectonico V",
                "Historia y Teoria de la Arquitectura",
                "Instalaciones II",
                "Sistemas Estructurales III",
                "Suelos"}; //[cite: 5]
    malla[7] = {"Diseño Arquitectonico VI",
                "Estadistica",
                "Instalaciones III",
                "Sistemas Constructivos III",
                "Sistemas Estructurales IV",
                "Supervision I",
                "Urbanismo I"}; //[cite: 5]
    malla[8] = {"Administracion de Obras III",
                "Diseño Arquitectonico VII",
                "Matematica III",
                "Metodos de Investigacion II",
                "Practica Profesional Supervisada",
                "Sistemas Constructivos IV",
                "Sistemas Estructurales V"}; //[cite: 5]
    malla[9] = {"Anteproyecto de Graduacion",    "Diseño Arquitectonico VIII",
                "Economia y Arquitectura",       "Mercadotecnia",
                "Sociologia de la Arquitectura", "Urbanismo II"}; //[cite: 5]
    malla[10] = {
        "Analisis de Proyectos",    "Conservacion de Monumentos",
        "Diseño Arquitectonico IX", "Etica para Arquitectos",
        "Proyecto de Graduacion",   "Sistemas Constructivos V"}; //[cite: 5]
  } else if (carreraSeleccionada == "civil") {
    malla[1] = {"Algebra Superior", "Desarrollo Humano y Profesional",
                "Dibujo Tecnico", "Geometria Plana y del Espacio",
                "Programacion para la Ciencia e Ingenieria I"}; //[cite: 4]
    malla[2] = {"Calculo I",
                "Dibujo Asistido por Computadora",
                "Historia y Comunicacion Cientifica",
                "Programacion para la Ciencia e Ingenieria II",
                "Quimica Inorganica I",
                "Topografia I"}; //[cite: 4]
    malla[3] = {"Algebra Lineal I", "Calculo II",
                "Dibujo Constructivo y Topografico", "Fisica I",
                "Topografia II"}; //[cite: 4]
    malla[4] = {"Algebra Lineal II",
                "Calculo Vectorial y Multivariable",
                "Fisica II",
                "Geologia I",
                "Legislacion Aplicada a Ingenieria Civil",
                "Topografia III"}; //[cite: 4]
    malla[5] = {"Ecologia y Sostenibilidad Ambiental",
                "Ecuaciones Diferenciales Ordinarias", "Fisica III",
                "Geologia II", "Mecanica de Cuerpos Rigidos I"}; //[cite: 4]
    malla[6] = {"Contabilidad Aplicada a Ingenieria Civil",
                "Ecuaciones Diferenciales Parciales",
                "Estadistica y Probabilidad Aplicada a Ingenieria Civil",
                "Ingenieria de Carreteras I",
                "Mecanica de Cuerpos Rigidos II",
                "Mecanica de Solidos I"}; //[cite: 4]
    malla[7] = {"Analisis Numerico",     "Ingenieria de Carreteras II",
                "Mecanica de Fluidos I", "Mecanica de Solidos II",
                "Mecanica de Suelos I",  "Tipologia Estructural"}; //[cite: 4]
    malla[8] = {
        "Analisis Estructural I", "Hidraulica",
        "Ingenieria Economica y Teoria de Decisiones en Ingenieria Civil",
        "Materiales de Construccion", "Mecanica de Suelos II"}; //[cite: 4]
    malla[9] = {
        "Analisis Estructural II", "Diseño de Estructuras de Concreto I",
        "Diseño de Estructuras de Madera y Mamposteria", "Hidrologia I",
        "Investigacion de Operaciones Aplicado a Ingenieria Civil"}; //[cite: 4]
    malla[10] = {"Costos, Presupuestos y Avaluos",
                 "Diseño de Estructuras de Concreto II", "Hidrologia II",
                 "Ingenieria de Transito y Sistemas de Transporte",
                 "Ingenieria Sanitaria I"}; //[cite: 4]
    malla[11] = {"Cimentaciones", "Diseño de Estructuras de Acero",
                 "Ingenieria Sanitaria II", "Obras Hidraulicas",
                 "Pavimentos"}; //[cite: 4]
  } else if (carreraSeleccionada == "derecho") {
    malla[1] = {"Introduccion al Derecho", "Sociologia de Derecho",
                "Desarrollo Humano y Profesional", "Teoria General del Estado",
                "Lenguaje y Redaccion Tecnica Juridica"}; //[cite: 3]
    malla[2] = {"Tecnicas Basicas de Investigacion",
                "Filosofia",
                "Historia del Derecho",
                "Derecho de Personas y Familia",
                "Derecho de los Bienes y Registral",
                "Derecho Penal (Parte General)"}; //[cite: 3]
    malla[3] = {"Tecnica de Litigacion Oral", "Teoria General del Proceso",
                "Derecho Constitucional I", "Derecho de Sucesiones",
                "Derecho Penal (Parte Especial)"}; //[cite: 3]
    malla[4] = {"Argumentacion Juridica", "Derecho de los Pueblos Indigenas",
                "Derechos Humanos y Ambiental",
                "Derecho de Obligaciones y Negocios Juridicos",
                "Derecho Administrativo I"}; //[cite: 3]
    malla[5] = {"Ciencias Forenses",
                "Metodos Alternos de Resolucion de Conflictos",
                "Derecho Individual del Trabajo",
                "Derecho de Contratos Civiles",
                "Derecho Administrativo II",
                "Derecho Procesal Penal I"}; //[cite: 3]
    malla[6] = {"Derecho Financiero y Tributario",
                "Derecho de Propiedad Intelectual",
                "Derecho Colectivo del Trabajo y de la Seguridad Social",
                "Derecho de Sociedades Mercantiles",
                "Derecho Procesal Administrativo",
                "Derecho Procesal Penal II"}; //[cite: 3]
    malla[7] = {"Derecho Economico",
                "Derecho Cambiario",
                "Derecho Procesal del Trabajo",
                "Derecho Procesal Civil y Mercantil I",
                "Derecho Notarial (Parte General)",
                "Clinica Procesal Penal"}; //[cite: 3]
    malla[8] = {"Metodos y Tecnicas de Investigacion Juridica",
                "Derecho Procesal Constitucional",
                "Clinica Procesal del Trabajo",
                "Derecho Procesal Civil y Mercantil II",
                "Derecho Notarial (Parte Especial)",
                "Derecho de Obligaciones y Contratos Mercantiles"}; //[cite: 3]
    malla[9] = {"Seminario de Trabajo de Graduacion I",
                "Derecho Internacional Publico y Privado",
                "Derecho Bancario y Bursatil",
                "Derecho Procesal Civil y Mercantil III",
                "Derecho Notarial (Jurisdiccion Voluntaria)"}; //[cite: 3]
    malla[10] = {"Seminario de Trabajo de Graduacion II",
                 "Filosofia del Derecho", "Deontologia Juridica",
                 "Clinica Procesal Civil y Mercantil",
                 "Clinica Notarial"}; //[cite: 3]
  }
  return malla;
}

// Definición de las variables globales
Estudiante registrar[TAM];
int contadorAlumnos = 0;
const string ARCHIVO = "files/ExpedienteEstudiante.txt";

void agregarAlArchivo() {
  ofstream archivo(ARCHIVO, ios::app);
  if (!archivo.is_open()) {
    archivo.open(ARCHIVO);
    archivo << "Carne\tNombres\tApellidos\tCarrera\tTelefono\tDireccion\tSemest"
               "re\tCursos\tFecha/Hora\n"; //[cite: 6]
  } else {
    archivo.seekp(0, ios::end);
    if (archivo.tellp() == 0) {
      archivo << "Carne\tNombres\tApellidos\tCarrera\tTelefono\tDireccion\tSeme"
                 "stre\tCursos\tFecha/Hora\n"; //[cite: 6]
    }
  }

  int idx = contadorAlumnos - 1;
  archivo << registrar[idx].carne << "\t" << registrar[idx].nombre << "\t"
          << registrar[idx].apellido << "\t" << registrar[idx].carrera << "\t"
          << registrar[idx].telefono << "\t" << registrar[idx].direccion << "\t"
          << registrar[idx].semestre << "\t" << registrar[idx].cursosAsignados
          << "\t" << registrar[idx].fechaHora << "\n"; //[cite: 6]

  archivo.close();
}

void cargarDesdeArchivo() {
  ifstream archivo(ARCHIVO);
  if (!archivo.is_open())
    return; //[cite: 6]

  string linea;
  getline(archivo, linea); //[cite: 6]

  contadorAlumnos = 0;
  while (getline(archivo, linea)) { //[cite: 6]
    if (linea.empty())
      continue; //[cite: 6]

    istringstream ss(linea);
    string carne, nombres, apellidos, carrera, telefono, direccion, semestreStr,
        cursos, fecha; //[cite: 6]

    getline(ss, carne, '\t');       //[cite: 6]
    getline(ss, nombres, '\t');     //[cite: 6]
    getline(ss, apellidos, '\t');   //[cite: 6]
    getline(ss, carrera, '\t');     //[cite: 6]
    getline(ss, telefono, '\t');    //[cite: 6]
    getline(ss, direccion, '\t');   //[cite: 6]
    getline(ss, semestreStr, '\t'); //[cite: 6]
    getline(ss, cursos, '\t');      //[cite: 6]
    getline(ss, fecha);             //[cite: 6]

    if (contadorAlumnos >= TAM)
      break; //[cite: 6]

    registrar[contadorAlumnos].carne = carne;         //[cite: 6]
    registrar[contadorAlumnos].nombre = nombres;      //[cite: 6]
    registrar[contadorAlumnos].apellido = apellidos;  //[cite: 6]
    registrar[contadorAlumnos].carrera = carrera;     //[cite: 6]
    registrar[contadorAlumnos].telefono = telefono;   //[cite: 6]
    registrar[contadorAlumnos].direccion = direccion; //[cite: 6]
    registrar[contadorAlumnos].semestre =
        semestreStr.empty() ? 0 : stoi(semestreStr);     //[cite: 6]
    registrar[contadorAlumnos].cursosAsignados = cursos; //[cite: 6]
    registrar[contadorAlumnos].fechaHora = fecha;        //[cite: 6]

    contadorAlumnos++;
  }
  archivo.close();
}

void ingresarAlumno() {
  string opcion;

  do {
    system("clear");
    if (contadorAlumnos >= TAM) {
      cout
          << "\n[ERROR] El sistema esta lleno. Maximo de alumnos alcanzado.\n"; //[cite: 6]
      break;
    }

    cout << "\n++++++++++++++++++++++++++++++ NUEVO REGISTRO "
            "++++++++++++++++++++++++++++++ \n"
         << endl; //[cite: 6]
    cout << "+++++++++++++++++++++++++++++ CARRERAS DISPONIBLES "
            "+++++++++++++++++++++++++++++"
         << endl; //[cite: 6]
    cout << "Sistemas \t Medicina \t Arquitectura \t Civil \t Derecho\n\n"
         << endl;

    // Generación automática del carné
    ostringstream autoCarne;
    autoCarne << setfill('0') << setw(4) << (contadorAlumnos + 1); //[cite: 6]
    registrar[contadorAlumnos].carne = autoCarne.str();            //[cite: 6]

    cout << "[SISTEMA] Carne asignado automaticamente: "
         << registrar[contadorAlumnos].carne << "\n"; //[cite: 6]

    cout << "Nombres: "; //[cite: 6]
    if (contadorAlumnos == 0 || cin.peek() == '\n')
      cin.ignore();                                  //[cite: 6]
    getline(cin, registrar[contadorAlumnos].nombre); //[cite: 6]

    cout << "Apellidos: ";                             //[cite: 6]
    getline(cin, registrar[contadorAlumnos].apellido); //[cite: 6]

    cout << "Carrera (escriba el nombre de las opciones de arriba): ";
    getline(cin, registrar[contadorAlumnos].carrera);

    // Determinamos la duración máxima de la carrera para la validación
    string carreraMinuscula = aMinusculas(registrar[contadorAlumnos].carrera);
    int maxSemestres = 10; // Duración base para Sistemas, Arquitectura, Derecho
    if (carreraMinuscula == "medicina") {
      maxSemestres = 14;
    } else if (carreraMinuscula == "civil") {
      maxSemestres = 11;
    }

    // --- ASIGNACIÓN DE SEMESTRE Y CURSOS ---
    int semestreIngresado;
    cout << "Semestre a inscribir (1-" << maxSemestres << "): ";
    while (!(cin >> semestreIngresado) || semestreIngresado < 1 ||
           semestreIngresado > maxSemestres) {
      cout << "[ERROR] Semestre no valido para "
           << registrar[contadorAlumnos].carrera
           << ". Ingrese un valor entre 1 y " << maxSemestres
           << ": ";                                        //[cite: 6]
      cin.clear();                                         //[cite: 6]
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); //[cite: 6]
    }
    registrar[contadorAlumnos].semestre = semestreIngresado; //[cite: 6]

    // Obtener la malla según la carrera escrita
    map<int, vector<string>> mallaActiva =
        obtenerMalla(registrar[contadorAlumnos].carrera);

    // Procesar cursos a un solo string para guardarlo en el archivo .txt
    string cursosCadena = "";
    if (mallaActiva.find(semestreIngresado) != mallaActiva.end()) { //[cite: 6]
      vector<string> cursos = mallaActiva[semestreIngresado];
      for (size_t i = 0; i < cursos.size(); ++i) { //[cite: 6]
        cursosCadena += cursos[i];                 //[cite: 6]
        if (i < cursos.size() - 1)
          cursosCadena += ", "; //[cite: 6]
      }
    } else {
      cursosCadena = "Pendiente de asignar (Carrera o Semestre no mapeados)";
    }
    registrar[contadorAlumnos].cursosAsignados = cursosCadena; //[cite: 6]
    // ----------------------------------------

    string telTemporal;
    bool telefonoValido = false;

    while (!telefonoValido) {           //[cite: 6]
      cout << "Telefono (8 digitos): "; //[cite: 6]
      cin >> telTemporal;               //[cite: 6]

      if (telTemporal.length() != 8) { //[cite: 6]
        cout << "[ERROR] El telefono debe tener exactamente 8 digitos.\n"; //[cite:
                                                                           //6]
        continue;
      }

      bool soloNumeros = true;
      for (size_t i = 0; i < telTemporal.length(); i++) { //[cite: 6]
        if (!isdigit(telTemporal[i])) {                   //[cite: 6]
          soloNumeros = false;                            //[cite: 6]
          break;
        }
      }

      if (!soloNumeros) {                          //[cite: 6]
        cout << "[ERROR] Ingrese solo numeros.\n"; //[cite: 6]
      } else {
        telefonoValido = true; //[cite: 6]
      }
    }
    registrar[contadorAlumnos].telefono = telTemporal; //[cite: 6]

    cout << "Direccion: ";                              //[cite: 6]
    cin.ignore();                                       //[cite: 6]
    getline(cin, registrar[contadorAlumnos].direccion); //[cite: 6]

    time_t tiempoActual = time(0);            //[cite: 6]
    tm *fechaInfo = localtime(&tiempoActual); //[cite: 6]
    char bufferFecha[30];                     //[cite: 6]
    strftime(bufferFecha, sizeof(bufferFecha), "%d/%m/%Y %H:%M:%S",
             fechaInfo);                                        //[cite: 6]
    registrar[contadorAlumnos].fechaHora = string(bufferFecha); //[cite: 6]

    contadorAlumnos++;  //[cite: 6]
    agregarAlArchivo(); //[cite: 6]

    system("clear");
    cout << "\n======================================================\n"; //[cite:
                                                                          //6]
    cout << "          ESTUDIANTE REGISTRADO EXITOSAMENTE          \n"; //[cite:
                                                                        //6]
    cout << "======================================================\n"; //[cite:
                                                                        //6]
    cout << "Carne:      " << registrar[contadorAlumnos - 1].carne
         << "\n"; //[cite: 6]
    cout << "Nombre:     " << registrar[contadorAlumnos - 1].nombre << " "
         << registrar[contadorAlumnos - 1].apellido << "\n"; //[cite: 6]
    cout << "Carrera:    " << registrar[contadorAlumnos - 1].carrera
         << "\n"; //[cite: 6]
    cout << "Semestre:   " << registrar[contadorAlumnos - 1].semestre
         << "\n"; //[cite: 6]
    cout << "Cursos:     " << registrar[contadorAlumnos - 1].cursosAsignados
         << "\n"; //[cite: 6]
    cout << "Telefono:   " << registrar[contadorAlumnos - 1].telefono
         << "\n"; //[cite: 6]
    cout << "Direccion:  " << registrar[contadorAlumnos - 1].direccion
         << "\n"; //[cite: 6]
    cout << "Fecha/Hora: " << registrar[contadorAlumnos - 1].fechaHora
         << "\n"; //[cite: 6]
    cout << "======================================================\n"; //[cite:
                                                                        //6]

    cout << "\n¿Desea registrar otro alumno? (s/n): "; //[cite: 6]
    cin >> opcion;                                     //[cite: 6]

  } while (opcion == "s" || opcion == "S"); //[cite: 6]
}
