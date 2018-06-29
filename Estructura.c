#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#include "Estructura.h"
#include "genericas.h"

//#define MASACARA_ARCHIVO "%[^,],%[^,],%[^,],%[^\n]\n"




int parserEstructura(FILE* pFile, ArrayList* this)
{
    int retorno = -1;
    int cantidadFilasLeidas = 0;
    int cantidadDatosLeidos;
    int agregoRecord;
    char cabecera[80];
    int guardoDato;

    EAlumno* record;

    char Nombre[30];
    char Edad[3];
    char Legajo[5];
    char Sexo[1];


    if(pFile != NULL)
    {
        retorno = -2;
        if(TIENE_ENCABEZADO_ARCHIVO == 1)
        {
            //descarto la lectura del encabezado
            fgets(cabecera, 80, pFile);
        }

        while(!feof(pFile))
        {
            retorno = 0;
            record = nuevo();
            if(record != NULL)
            {
                cantidadDatosLeidos = fscanf(pFile,MASACARA_ARCHIVO,Nombre,Edad,Legajo,Sexo);
                if(cantidadDatosLeidos == CANTIDAD_CAMPOS_ARCHIVO)
                {

                    guardoDato = Alumno_setName(record,(char*) Nombre);
                    if(guardoDato !=0)
                    {
                        break;
                    }

                    guardoDato = Alumno_setEdad(record, charToint(Edad) );
                    if(guardoDato !=0)
                    {
                        break;
                    }

                    guardoDato = Alumno_setLegajo(record,charToint(Legajo) );
                    if(guardoDato !=0)
                    {
                        break;
                    }

                    guardoDato = Alumno_setSexo(record,(char) Sexo );
                    if(guardoDato !=0)
                    {
                        break;
                    }


                    agregoRecord = al_add(this, record);
                    if(agregoRecord < 0) //Hubo error
                    {
                        break;
                    }

                    cantidadFilasLeidas++;
                }
                else //Fin de archivo u otro error
                {
                    break;
                }
            }
            else //Sin memoria
            {
                break;
            }
        }
    }

    return retorno;
}

int charToint(char* charInt)
{
    int nro;
    nro = atoi(charInt);
    return nro;
}

int Alumno_setEdad(EAlumno* this, int dato)
{
    this->Edad = dato;
    return 0;
}

int Alumno_setLegajo(EAlumno* this, int dato)
{
    this->Legajo = dato;
    return 0;
}

int Alumno_setSexo(EAlumno* this, char dato)
{
    this->Sexo = dato;
    return 0;
}

int Alumno_setName(EAlumno* this, const char* name)
{
    strcpy(this->Nombre, name);
    return 0;
}



EAlumno* nuevo(void)
{
    EAlumno* returnAux;
    returnAux = (EAlumno*)malloc(sizeof(EAlumno));
    return returnAux;
}

int Muestra1Record(EAlumno * record)
{
    int retorno=-1;
    if(record !=NULL)
    {
        retorno=0;
        printf("\n Nombre: %s ",record->Nombre);
        printf("Edad: %d ",record->Edad);
        printf(" Legajo: %d ",record->Legajo);
        printf(" Sexo: %c \n",record->Sexo);
    }
    return retorno;
}

int compara_elementos_Estructura(void* pElementA,void* pElementB)
{
    int retorno;
    EAlumno *tmp_1;
    EAlumno *tmp_2;
    tmp_1=(EAlumno * ) pElementA;
    tmp_2=(EAlumno * ) pElementB;
    //return strcmp(tmp_1->DNI,tmp_2->DNI);
    if(tmp_1->Edad > tmp_2->Edad)
    {
        retorno=1;
    }
    else
    {
        retorno=-1;
        if(tmp_1->Edad == tmp_2->Edad)
        {
            retorno=0;
        }

    }
    return retorno;
}


int al_MuestraElemento_desde_hasta(ArrayList *this,char *Titulo,int (*pFunc)(void*) ,int desde,int hasta,int paginado)
{
    int retorno=-1;
    int cont=0;
    if(this!=NULL && Titulo!=NULL)
    {
        retorno=0;
        system("cls");
        printf("\n\n-------- %s --------\n",Titulo);
        if(this->isEmpty(this)==0)
        {//No esta vacio
            for(int index=desde;index<hasta;index++)
            {
                if(cont!=0 && cont %paginado==0)
                {
                    system("pause");
                    system("cls");
                    printf("\n\n-------- %s --------\n",Titulo);
                }
                pFunc(al_get(this,index));
                cont++;
            }

            if(cont!=0)
            {//pausa la ultima tanda de elementos mostrados
                system("pause");
            }
        }//if(this->isEmpty(this)==0)
        else
        {//o con error o sin datos a mostrar
            printf("\n Sin Datos a Motrar...\n");
            system("pause");
        }
    }//if(this!=NULL && Titulo!=NULL)
    return retorno;
}

int funcionQueFiltra(void* item)
{
    int retorno=0;
    EAlumno *tmp_1;
    tmp_1=(EAlumno * ) item;
    if(tmp_1->get_Edad() > 30 ) //&& (strcpy(tmp_1->profecion,"programador")) )
    {
        retorno=1;
    }
    return retorno ;

}

int get_Edad(void * record)
{
    EAlumno *tmp_1;
    tmp_1=(EAlumno * ) record;
    return tmp_1->Edad;
}

ArrayList* al_filter(ArrayList* listIn , int (*functionFilter)(void*))
{
    ArrayList *ListaTemp=NULL;
    ListaTemp= al_newArrayList();
    if(listIn!=NULL && functionFilter!=NULL && ListaTemp!=NULL)
    {
        for(int i=0;i<listIn->len(listIn);i++)
        {
                if( functionFilter(listIn->get(listIn,i) )==1  )
                {
                    ListaTemp->add(  listIn->get(listIn,i) );
                }
        }
        return ListaTemp;
    }
}

ArrayList* clonaOrdenado(ArrayList *this,int (*pFunc)(void* ,void*),int orden)
{
    ArrayList *ListaOrdenada=NULL;
    if(this!=NULL)
    {
        ListaOrdenada = al_newArrayList();
        ListaOrdenada=al_clone(this);
        if(ListaOrdenada!=NULL)
        {
            //if(ListaOrdenada->sort(ListaOrdenada,compara_elementos_Estructura,1)==-1)
            if(ListaOrdenada->sort(ListaOrdenada,pFunc,1)==-1)
            {
                ListaOrdenada=NULL;
            }
        }
    }
    return ListaOrdenada;
}


int cargarDesdeArchivo(const char* nombreArchivo, ArrayList* this)
{
    FILE* archivo;
    int retorno = -1;
    int parseoArchivo;
    int cerroArchivo;

    archivo = fopen(nombreArchivo, "r");
    if(archivo != NULL)
    {
        retorno = -2;
        if(parserEstructura(archivo, this)==0)
        {
            retorno = -3;
            if(fclose(archivo)==0)
            {
                retorno = 0;
            }
        }
    }//FIN if(archivo != NULL)

    return retorno;
}


