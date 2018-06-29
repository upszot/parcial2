#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#include "genericas.h"

typedef struct{
    //(Nombre, Edad, Legajo, Sexo)
    char Nombre[30];
    int Edad;
    int Legajo;
    char Sexo;
}EAlumno;


EAlumno* nuevo(void);
int Muestra1Record(EAlumno * record);
int compara_elementos_Estructura(void* pElementA,void* pElementB);

int al_MuestraElemento_desde_hasta(ArrayList *this,char *Titulo,int (*pFunc)(void*) ,int desde,int hasta,int paginado);
ArrayList* clonaOrdenado(ArrayList *this,int (*pFunc)(void* ,void*),int orden);
