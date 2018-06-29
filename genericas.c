#include "genericas.h"


//#------------- Genericas -------------#
void menu(char *opciones)
{
    system("cls");
    printf("%s \n",opciones);
    printf("\n0.  Salir \n");
    printf("\n\tIngrese Opcion: ");
}

void sms_error(int mensaje,int Error)
{
    system("cls");
    printf("\n\n");
    switch(mensaje)
    {
        case -1:
            printf("ERROR-COD: %d -- Inicializar listado",Error);
            break;
        case 1:
            printf("ERROR-COD: %d -- TRAMITE URGENTE",Error);
            break;
        case 2:
            printf("ERROR-COD: %d -- TRAMITE REGULAR",Error);
            break;
        case 3:
            if(Error!=100)
            {
                printf("ERROR-COD: %d -- PROXIMO CLIENTE",Error);
            }
            else
            {
                printf("\n\n NO HAY MAS GENTE QUE ATENDER \n\n");
            }

            break;
        case 4:
            printf("ERROR-COD: %d -- LISTAR",Error);
            break;
        case 5:
            printf("ERROR-COD: %d -- INFORMAR",Error);
            break;
        case -2:
            printf("ERROR-COD: %d -- Opcion de menu Invalida",Error);
            break;
        default:
            printf("Se produjo un Error Inesperado...");
            break;
    }
    printf("\n\n");
    system("pause");
}

char *get_char(char *sms,int LongitudCadena)
{
    char *PTexto= (char *) malloc (sizeof(char)*LongitudCadena);
    char *TextoLibre=(char *) malloc (sizeof(char)*LongitudCadena+4);

    int flag;
    do
    {
        flag=0;
        printf("%s ",sms);
        fflush(stdin);
        fgets(TextoLibre,LongitudCadena+3,stdin); //Trunco la lectura del buffer en 3 mas de mi longitud
        fflush(stdin);
        strncpy(PTexto, TextoLibre, LongitudCadena); // Copio la cantidad de caracteres hasta 1 menos de la longitud
        PTexto[sizeof(PTexto) -1] = '\0';        //agrego retorno de carro

        //printf("\nL:%s T:%s Dif:%d TAM:%d ultimo:[%c] Overflow:[%c] \n",TextoLibre,PTexto,strcmp(PTexto,TextoLibre),sizeof(PTexto),PTexto[LongitudCadena-1],PTexto[sizeof(PTexto)]);
        //system("pause");

        if(strlen(PTexto) >= LongitudCadena) //el strlen funciona para atras... en estos casos asique no sirve..
        //if(strcmp(PTexto,TextoLibre)<0)
        {//overflow
            flag=1;
            //flag=0;// si lleno mucho el buffer se boludea igual....
            fflush(stdin);
            *PTexto=' ';
            printf("\n Error Overflow: La longitud maxima del campo es: %d \n",LongitudCadena);
            system("pause");
            system("cls");
        }
    }while(flag!=0);

    strcpy(PTexto,strtok(TextoLibre, "\n"));
    return PTexto;
}

int get_int_Rango(char *sms,int desde,int hasta)
{
    int aux;
    int flag=0;
    do
    {
        if(flag==1)
        {
            printf("\n Valor fuera de Rango Debe ser: (%d< X <%d)  \n",desde-1,hasta+1);
            system("pause");
            system("cls");
        }
        fflush(stdin);
        printf("%s",sms);
        scanf("%d",&aux);
        flag=1;
    }while( (aux<desde) || (aux>hasta) );

    return aux;
}

