/*Librerias a utilizar*/
#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

/*Cabe destacar que este codigo se puede optimizar aun mas*/

#define MAXPOINT 100 /*Numeros de puntos que se mostraran en pantalla*/
                     /*Se puede cambiar la cantidad y aun asi funcionaria el algoritmo (Cabe destacar que en este caso a mayor puntos tardara mas el algoritmo)*/
                     /*A excepcion que se dieran numeros menores de 3*/

typedef struct
{
    int x;
    int y;
}Point;              /*Una estructura de tipo punto para un mayor entendimiento del codigo*/

void inicializar(void);             /*Funcion para inicializar el modo grafico*/
bool CCW(Point a, Point b, Point c);/*Funcion para saber si un punto va con las manesillas del reloj o encontra*/
                                    /*Tambien puede indicar si un punto esta a la derecha de una linea, colineal o la izquierda de esta*/

void quicksort(Point Puntos[MAXPOINT],int Primero,int Ultimo);

void main (void)
{
    Point Puntos[MAXPOINT],PuntoEn[MAXPOINT],PuntoSu[MAXPOINT],PuntoIn[MAXPOINT],PuntoIz,PuntoDer; /*Declaracion de variables del tipo punto*/
    int i = 0, j = 0, TotalPunSup=0,TotalPunInf=0, Cant=0; /*Variables de interaccion*/
    char Men[50]; /*Posible mensaje que se guardara en esta variable*/

    inicializar();

    srand((unsigned int)time(NULL));/* Funcion para cambiar la funcion random en cada ejecucion de codigo*/

    for(i=0;i<MAXPOINT;i++) /*Establecimiento de puntos*/
    {
        /*Se indica la posicion de los puntos a traves de la funcion random, estos puntos tendran cierto limites en pantalla*/

        Puntos[i].x =100 +(rand() % 440) ;  
        Puntos[i].y =100 +(rand() % 280) ;  
    }

    /*Bucle para mostrar los puntos en pantalla y obtener el punto que se encuentra mas a la izquierda*/

    for(i=0;i<MAXPOINT;i++)
    {
        putpixel(Puntos[i].x,Puntos[i].y,WHITE);

        if(i==0)
        {
            PuntoIz=Puntos[i];
            PuntoDer=Puntos[i];
        }
        else 
        {
            if(PuntoIz.x>=Puntos[i].x)
                PuntoIz=Puntos[i];
            if(PuntoDer.x<=Puntos[i].x)
                PuntoDer=Puntos[i];
        }
    }

    setcolor(WHITE);
    line(PuntoIz.x,PuntoIz.y,PuntoDer.x,PuntoDer.y);

    PuntoEn[0] = PuntoIz;
    PuntoEn[1] = PuntoDer;

    for(i = 0; i<MAXPOINT; i++)
    {
        if(CCW(PuntoIz,PuntoDer,Puntos[i]))
        {
            PuntoSu[TotalPunSup]=Puntos[i];
            TotalPunSup++;
            putpixel(Puntos[i].x,Puntos[i].y,YELLOW);
        }
        else if(CCW(PuntoDer,PuntoIz,Puntos[i]))
        {
            PuntoIn[TotalPunInf]=Puntos[i];
            TotalPunInf++;
            putpixel(Puntos[i].x,Puntos[i].y,BLUE);
        }
    }

    



    
    
    /*Este es el algoritmo mas eficiente de ordenacion
    quicksort(Puntos,0,MAXPOINT-1);*/



    



    setcolor(WHITE);
    outtextxy(50,20,"Pulse cualquier boton para Salir");
    getch();
    closegraph();
}

bool CCW(Point a, Point b, Point c) /*Funcion para obtener la ubicacion de un punto respecto a un recta*/
{
    long int q = (long)(c.y-a.y)*(long)(b.x-a.x); 
    long int w = (long)(b.y-a.y)*(long)(c.x-a.x);
    
    /*
    Para saber si un punto se encuentra al lado izquierdo de una recta o al lado derecho, existe una manera
    que es obtener el area del triangulo que se forma al obtener esos puntos, si el area es positiva ese punto
    se encuentra a la derecha, si el area es negativa ese punto e encuentra a la izquierda de ese segmento, y si el 
    area es 0, quiere decir que ese punto es colineal.
    
    area = |(long)(b.x-a.x)*(long)(c.y-a.y)| - |(long)(b.y-a.y)*(long)(c.x-a.x)| ;
                        q                                   w

    Es una formla del area que se obtiene a partir de unicamente sus puntos
    
    En este caso se utilizo de tal manera que solamente se compara las dos partes de esa formula, pero el resultado es el mismo
    */

    if( q >= w ) /*Si el punto esta ubicado a la derecha o es colineal*/

        return false;
   
    return true;   /*Si esta ubicado a la izquierda*/
}
/*
void quicksort(Point Puntos[MAXPOINT],int Primero,int Ultimo)
{
    int i, j, pivot;
    Point temp;

   if(Primero<Ultimo)
   {
      pivot=Primero;
      i=Primero;
      j=Ultimo;

      while(i<j)
      {
         while(Puntos[i].x <= Puntos[pivot].x && i<Ultimo)
            i++;
         while(Puntos[j].x > Puntos[pivot].x)
            j--;
         if(i<j)
         {
            temp=Puntos[i];
            Puntos[i]=Puntos[j];
            Puntos[j]=temp;
         }
      }

      temp=Puntos[pivot];
      Puntos[pivot]=Puntos[j];
      Puntos[j]=temp;
      quicksort(Puntos,Primero,j-1);
      quicksort(Puntos,j+1,Ultimo);
   }
}*/

void inicializar(void)
{
	int drive=DETECT,modo;
	initgraph(&drive,&modo,"c:\\tc20\\bin");
}