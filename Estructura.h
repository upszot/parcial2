#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#include "genericas.h"

#define MASACARA_ARCHIVO "%[^,],%[^,],%[^,],%[^\n]\n"
#define CANTIDAD_CAMPOS_ARCHIVO 4
#define TIENE_ENCABEZADO_ARCHIVO 0

typedef struct{
    //(Nombre, Edad, Legajo, Sexo)
    char Nombre[30];
    int Edad;
    int Legajo;
    char Sexo[1];
    //int  (*get_Edad) () ;

}EAlumno;

int charToint(char* charInt);
EAlumno* nuevo(void);
int Muestra1Record(EAlumno * record);
int compara_elementos_Estructura(void* pElementA,void* pElementB);

int al_MuestraElemento_desde_hasta(ArrayList *this,char *Titulo,int (*pFunc)(void*) ,int desde,int hasta,int paginado);
ArrayList* clonaOrdenado(ArrayList *this,int (*pFunc)(void* ,void*),int orden);

int cargarDesdeArchivo(const char* nombreArchivo, ArrayList* this);

int parserEstructura(FILE* pFile, ArrayList* this);
int Alumno_setEdad(EAlumno* this, int dato);
int Alumno_setLegajo(EAlumno* this, int dato);
//int Alumno_setSexo(EAlumno* this, char dato);
int Alumno_setSexo(EAlumno* this,  char *dato);
int Alumno_setName(EAlumno* this, const char* name);

ArrayList* al_filter(ArrayList* listIn , int (*functionFilter)(void*));
int funcionQueFiltra(void* item);
