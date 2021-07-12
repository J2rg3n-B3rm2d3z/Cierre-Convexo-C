#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

/*
Nota: Este algoritmo no es tan eficiente en comparacion a otros, 
este fue un codigo que se encontro en internet en otro lenguaje, solamente fue "Traducido" a lenguaje C

En este codigo se crea el diagrama de voronoi a partir de un barrido de toda la pantalla, 
asi como por ejemplo, al momento de cargar una imagen bmp.

*/

#define MAXPOINT 10 /*Maximo de puntos en pantalla, se recomienda trabajar con pocos puntos para que de esta forma no dilate tanto el programa*/
                    /*Mientras mas puntos mas lento sera el proceso se recomienda usar menos de 10*/
typedef struct /*Estructura para los puntos*/
{
    int x;
    int y;
} Point;

double distancia(int x1, int x2, int y1, int y2); /*Funcion para obtener la distancia entre 2 puntos*/
void inicializar(void);                           /*Funcion para iniciar el modo grafico*/

void main(void)
{

    int c, x, y, i;         /*Variables de interaccion*/
    Point Puntos[MAXPOINT]; /*Maximo de puntos en pantalla*/

    inicializar();

    srand((unsigned int)time(NULL));

    /*Obtencion de puntos*/

    for (i = 0; i < MAXPOINT; i++)
    {
        Puntos[i].x = 50 + (rand() % 540);
        Puntos[i].y = 50 + (rand() % 380);
    }

    /*Barrido para mostrar en pantalla el diagrama*/

    for (x = 0; x < getmaxx(); x++)
    {
        for (y = 0; y < getmaxy(); y++)
        {
            c = 0;/*Se inicializa la variable para el color que indica en que poligono se encuentra*/

            /*Se entra en bucle para verificar punto por punto el menor de la distancia que hay entre X y Y, en cada iteraccion
             y de esa manera verificar la distancia mas proxima, para de esa manera asignarle un color a cada poligono
            */

            for (i = 0; i < MAXPOINT; i++)
            {
                if (distancia(Puntos[i].x, x, Puntos[i].y, y) < distancia(Puntos[c].x, x, Puntos[c].y, y))
                {
                    c = i;
                }
            }

            putpixel(x, y, c);/*Se pinta pixel a pixel*/
        }
    }

    /*Se muestran los puntos en pantalla ya teniendo el diagrama*/

    for (i = 0; i < MAXPOINT; i++)
    {
        if (getpixel(Puntos[i].x, Puntos[i].y) != 15)
        {
            setcolor(15);
            setfillstyle(1, 15);
            circle(Puntos[i].x, Puntos[i].y, 3);
            floodfill(Puntos[i].x, Puntos[i].y, 15);
        }
        else
        {
            setcolor(0);
            setfillstyle(1, 0);
            circle(Puntos[i].x, Puntos[i].y, 3);
            floodfill(Puntos[i].x, Puntos[i].y, 0);
        }
    }

    getch();
}

double distancia(int x1, int x2, int y1, int y2)
{
    double d;
    d = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
    return d;
}

void inicializar(void)
{
    int drive = DETECT, modo;
    initgraph(&drive, &modo, "c:\\tc20\\bin");
}