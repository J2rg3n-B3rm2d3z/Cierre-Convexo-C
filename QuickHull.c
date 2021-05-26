/*Librerias a utilizar*/
#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

/*Cabe destacar que este codigo se puede optimizar aun mas*/

#define MAXPOINT 500 /*Numeros de puntos que se mostraran en pantalla*/
                     /*Se puede cambiar la cantidad y aun asi funcionaria el algoritmo*/
                     /*A excepcion que se dieran numeros menores de 3*/

typedef struct
{
    int x;
    int y;
}Point;              /*Una estructura de tipo punto para un mayor entendimiento del codigo*/

Point PuntosEnvSup[MAXPOINT];   /*Arreglo de puntos para la envolvente convexa superior*/
Point PuntosEnvInf[MAXPOINT];   /*Arreglo de puntos para la envolvente convexa inferiors*/

/*Control de la cantidad de puntos en cada arreglo*/

int CantPuntosEn=0;
int CantPuntosEnSu=0;
int CantPuntosEnIn=0;

void inicializar(void);             /*Funcion para inicializar el modo grafico*/
bool CCW(Point a, Point b, Point c);/*Funcion para saber si un punto va con las manesillas del reloj o encontra*/
                                    /*Tambien puede indicar si un punto esta a la derecha de una linea, colineal o la izquierda de esta*/

void FindHull (Point Puntos[MAXPOINT],Point a,Point b, int Cant, bool Arriba);  /*Funcion recursiva para obtener la envolvente convexa basado en el algoritmo Quitsort*/
long Area(Point a,Point b,Point c);                                             /*Funcion para encontrar el area de un triangulo con solo 3 puntos*/
void quicksort(Point Puntos[MAXPOINT],int Primero,int Ultimo);                  /*Funcion para ordenar los puntos de menor a mayor aplicando el algoritmo Quitsort*/

void main (void)
{
    Point Puntos[MAXPOINT],PuntoSu[MAXPOINT],PuntoIn[MAXPOINT],PuntoIz,PuntoDer;    /*Declaracion de variables del tipo punto*/
    int i = 0, j = 0, TotalPunSup=0,TotalPunInf=0;                                  /*Variables de interaccion*/

    inicializar();

    srand((unsigned int)time(NULL));/* Funcion para cambiar la funcion random en cada ejecucion de codigo*/

    for(i=0;i<MAXPOINT;i++) /*Establecimiento de puntos*/
    {
        /*Se indica la posicion de los puntos a traves de la funcion random, estos puntos tendran cierto limites en pantalla*/

        Puntos[i].x =100 +(rand() % 440) ;  
        Puntos[i].y =100 +(rand() % 280) ;  
    }

    /*Bucle para mostrar los puntos en pantalla y obtener el punto que se encuentra mas a la izquierda y mas a la derecha*/

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

    /*

    Esta parte del codigo es para mostrar mas a fondo el funcionamiento del algoritmo
    Solamente dibuja una linea de extremo a extremo para que sea mas visual el algoritmo
    Si lo quiere ver mas el funcionamiento, descomenta esta parte*/

    /*
    setcolor(BLUE);
    line(PuntoIz.x,PuntoIz.y,PuntoDer.x,PuntoDer.y);
    delay(50);*/

    /*Bucle para obtener la cantidad de puntos resultantes del lado izquierdo y derecho de la linea trazada del paso anterior*/
    for(i = 0; i<MAXPOINT; i++)
    {
        if(CCW(PuntoIz,PuntoDer,Puntos[i]))
        {
            PuntoSu[TotalPunSup]=Puntos[i];
            TotalPunSup++;
        }
        else if(CCW(PuntoDer,PuntoIz,Puntos[i]))
        {
            PuntoIn[TotalPunInf]=Puntos[i];
            TotalPunInf++;
        }
    }

    /*Ambos puntos extremos pertenecen a la parte convexa asi que se agregan al arreglo de puntos envolventes inferior y superior*/
    PuntosEnvSup[0]=PuntoIz;
    PuntosEnvSup[1]=PuntoDer;
    PuntosEnvInf[0]=PuntoIz;
    PuntosEnvInf[1]=PuntoDer;

    CantPuntosEn=2; /*La cantidad de punto que contienen por el momento*/

    FindHull(PuntoSu,PuntoIz,PuntoDer,TotalPunSup,true);/*Se llama a la funcion que encuentra los puntos convexo, este llamado es para los puntos superiores*/
    
    quicksort(PuntosEnvSup,0,CantPuntosEn-1);/*Se ordenan los puntos obtenidos de la funcion anterior, es decir los puntos de la envolvente convexa superior*/

    CantPuntosEnSu=CantPuntosEn;/*Se indica la cantidad de puntos existentes en la parte superior*/

    CantPuntosEn=2;/*Se reinicia esta variable para volver a ejecutar la funcion FindHull*/

    FindHull(PuntoIn,PuntoDer,PuntoIz,TotalPunInf,false);/*Se llama a la funcion, pero esta vez para encontrar los puntos de la cadena convexa inferior*/

    quicksort(PuntosEnvInf,0,CantPuntosEn-1);/*Se vuelve a ordenar estos puntos*/
    
    CantPuntosEnIn=CantPuntosEn;/*Se indica la cantidad de puntos de la convexa inferior*/

    /*En esta parte del codigo solo se pinta la envolvente convexa a partir de los puntos obtenidos*/
    setcolor(WHITE);

    for(i=0;i<CantPuntosEnSu-1;i++)
    {
        line(PuntosEnvSup[i].x,PuntosEnvSup[i].y,PuntosEnvSup[i+1].x,PuntosEnvSup[i+1].y);
        delay(100);
    }

    for(i=CantPuntosEnIn-1;i>0;i--)
    {
        line(PuntosEnvInf[i].x,PuntosEnvInf[i].y,PuntosEnvInf[i-1].x,PuntosEnvInf[i-1].y);
        delay(100);
    }

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

long Area(Point a,Point b,Point c)
{
   long area;
   area = (long)(b.x-a.x)*(long)(c.y-a.y);
   area-= (long)(b.y-a.y)*(long)(c.x-a.x);
   return(area);
}

void FindHull (Point Puntos[MAXPOINT],Point a,Point b, int Cant, bool Arriba)
{
    /*A esta funcion se le pasan 5 parametros
     la primera es el arreglo de puntos,
     luego se le pide los extremos de la linea punto a y punto b
     por consiguiente la cantidad de puntos que posee el arreglo
     y por ultimo, una booleana que indica si esos puntos estan en la parte superior de la linea que se creo inicialmente
     o en la parte inferior
    */
    Point PuntoIz[MAXPOINT],PuntoDer[MAXPOINT]; /*Arreglos de puntos resultantes despues de obtener el punto convexo*/
 
    int i=0,TotalPiz=0,TotalPde=0;              /*Variables de iteraccion y variable controladora de puntos de los arreglos anteriores*/
    Point c;                                    /*Creacion de un nuevo punto*/

    if(Cant<1) /*Si la cantidad de puntos existentes es menor a 1 se detiene la funcion y termina la recursividad*/
     return;
    
    for(i = 0; i < Cant; i++) /*Bucle para encontrar el punto mas lejano de la recta dada por los puntos a y b*/
    {
        if(i==0)
            c = Puntos[i];
        else if ((long) Area(a,Puntos[i],b)>(long) Area(a,c,b)) 
        /*Se compara el area del triangulo que conforma los tres puntos,
        al encontrar el area mas grande del triangulo se obtiene el punto mas alejado de esta recta*/
            c = Puntos[i];

    }
    /*Codigo para mostrar su funcionamiento mas a detalle
    Si se quiere ver mas a detalle el funcionamiento del programa en ejecucion descomentaree el siguiente
    codigo
    */

   /*
    setcolor(BLUE);
    line(a.x,a.y,c.x,c.y);
    delay(100);
    line(b.x,b.y,c.x,c.y);
    delay(100);*/

    /*Esta parte del codigo es unicamente para agregar el punto convexo encontrado, al arreglo convexo superior o inferior*/
    if(Arriba) 
        PuntosEnvSup[CantPuntosEn] = c;
    else
        PuntosEnvInf[CantPuntosEn] = c;
        
    CantPuntosEn++;/*Se aumenta la cantidad de puntos*/

    /*Se clasifica los puntos restantes no interiores del triangulo abc
    en si estan a la izquierda de este triangulo o a la derecha y se guarda en un arreglo respectivamente
    */
    for(i = 0; i<Cant; i++)
    {
        if(CCW(a,c,Puntos[i]))
        {
            PuntoIz[TotalPiz]=Puntos[i];
            TotalPiz++;
        }
        else if(CCW(c,b,Puntos[i]))
        {
            PuntoDer[TotalPde]=Puntos[i];
            TotalPde++;
        }
    }

    /*Se vuelve a llamar la funcion recursivamente hasta que no se encuentren ningun punto en algun lado fuera del triangulo abc*/

    FindHull(PuntoIz,a,c,TotalPiz,Arriba);/*Esta funcion se llama para los puntos del lado izquierdo*/
    FindHull(PuntoDer,c,b,TotalPde,Arriba);/*Esta funcion se llama para los puntos del lado derecho*/

}

void quicksort(Point Puntos[MAXPOINT],int Primero,int Ultimo)/*Algoritmo quicksort para ordenar los puntos de izquierda a derecha de manera eficiente*/
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
}

void inicializar(void)
{
	int drive=DETECT,modo;
	initgraph(&drive,&modo,"c:\\tc20\\bin");
}