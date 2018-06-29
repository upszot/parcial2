#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ArrayList.h"
//#include "Estructura.h"
#include "genericas.h"


#define NOMBRE_ARCHIVO "alumnos.csv"

#define TAMLista 10
#define PAGINADO 5


/*
1. Crear el archivo alumnos.csv que va a contener la informacion de 10 alumnos (Nombre, Edad, Legajo, Sexo),
  los cuales deben ser creados de manera dinamica y almacenados en un ArrayList.

2. Listar los alumnos del ArrayList ordenados por Edad.


*/

int main()
{
    ArrayList *ListAlumno;
    ListAlumno= al_newArrayList();


    char seguir='s';
    int opcion=0;
    int Error=-9;

    if(ListAlumno!=NULL)
    {
        Error=0;
    }

    if(Error==0)
    {
        do
        {
            menu(   "\n 1. Parse del archivo CVS"
                    "\n 2. Lista Ordenados por Edad"
                    //"\n 3. PROXIMO CLIENTE"
                    //"\n 4. LISTAR"
                    //"\n 5. INFORMAR:"
                );

            scanf("%d",&opcion);
            switch(opcion)
            {
                case 1:
                    Error = cargarDesdeArchivo(NOMBRE_ARCHIVO, ListAlumno);
                    break;
                case 2:

                    break;
                case 3://PROXIMO CLIENTE

                    break;
                case 4:

                    break;
                case 5:


                    break;
                case 0:
                    seguir = 'n';
                    Error=0;
                    break;
                default:
                    Error=-1;
                    opcion=-2;
                    break;
            }//FIN switch(opcion)
            if(Error!=0)
            {
                sms_error(opcion,Error);
                Error=0;
            }
        }while(seguir=='s');
    }
    else
    {
        sms_error(-1,Error);
    }//FIN if(Error==0)

    return Error;
}//int main()
