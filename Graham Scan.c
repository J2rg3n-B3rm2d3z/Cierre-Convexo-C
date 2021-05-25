/*Librerias a utilizar*/
#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define MAXPOINT 20 /*Numeros de puntos que se mostraran en pantalla*/
                     /*Se puede cambiar la cantidad y aun asi funcionaria el algoritmo*/
                     /*A excepcion que se dieran numeros menores de 3*/

typedef struct
{
    int x;
    int y;
}Point;              /*Una estructura de tipo punto para un mayor entendimiento del codigo*/

void inicializar(void);             /*Funcion para inicializar el modo grafico*/
bool CCW(Point a, Point b, Point c);/*Funcion para saber si un punto va con las manesillas del reloj o encontra*/
                                    /*Tambien puede indicar si un punto esta a la derecha de una linea, colineal o la izquierda de esta*/

void main (void)
{
    Point Puntos[MAXPOINT],PuntoEnSup[MAXPOINT],PuntoEnInf[MAXPOINT],Punto0,PuntoAux; /*Declaracion de variables del tipo punto*/
    int i = 0, j = 0, pasada =0, Cant=0; /*Variables de interaccion*/
    char Men[50];

    inicializar();

    /*srand((unsigned int)time(NULL)); Funcion para cambiar la funcion random en cada ejecucion de codigo*/

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
    }


	for( pasada=1;pasada<MAXPOINT;pasada++)
		for( i =0; i<MAXPOINT-1;i++)
			if(Puntos[i].x>=Puntos[i+1].x)
			{
				PuntoAux = Puntos[i];
				Puntos[i] = Puntos[i+1];
				Puntos[i+1] = PuntoAux;
			}

    for(i=0;i<MAXPOINT;i++)
    {
        putpixel(Puntos[i].x,Puntos[i].y,YELLOW);
        sprintf(Men,"%d",i);
        outtextxy(Puntos[i].x,Puntos[i].y,Men);
        delay(500);
    }

    PuntoEnSup[0] = Puntos[0];
    PuntoEnSup[1] = Puntos[1];
    Cant = 2;

    for(i = 2; i<MAXPOINT; i++)
    {
        PuntoEnSup[Cant]=Puntos[i];
        Cant++;

        while( (Cant > 2) && !CCW(PuntoEnSup[Cant-1],PuntoEnSup[Cant-2],PuntoEnSup[Cant-3]))
        {
            /*setcolor(BLACK);
            line(PuntoEnSup[Cant-3].x,PuntoEnSup[Cant-3].y,PuntoEnSup[Cant-2].x,PuntoEnSup[Cant-2].y);*/
            PuntoEnSup[Cant-2] = PuntoEnSup[Cant-1];
            Cant--;
            delay(500);
        }

        setcolor(WHITE);
        if(Cant > 2)
            line(PuntoEnSup[Cant-3].x,PuntoEnSup[Cant-3].y,PuntoEnSup[Cant-2].x,PuntoEnSup[Cant-2].y);
        
        delay(500);
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

void inicializar(void)
{
	int drive=DETECT,modo;
	initgraph(&drive,&modo,"c:\\tc20\\bin");
}

