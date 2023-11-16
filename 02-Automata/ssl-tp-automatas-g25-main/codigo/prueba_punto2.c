#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

/*Punto 2 - Pasar UN caracter numérico a un entero*/
int caracterNumericoAEntero (const char caracter)
{
    if (caracter >= '0' && caracter <='9')
    return caracter - '0';//Recalibra el desplazamiento de la tabla ascii
    else return -1;//Al solo tomar caracteres numéricos y no el signo, el número negativo nos informaría de un error.
};

int main() {
    char carNumerico;//Se pueden realizar operaciones de hasta 100 caracteres
    int nro=0;
    /*El programa se mantendrá activo hasta ingresar una expresión errónea*/
    printf("Ingrese un caracter numérico: ");
    scanf("%c", &carNumerico);
    nro=caracterNumericoAEntero(carNumerico);
    ( nro != -1) ? printf("\n%d\n",nro) : printf("\nError\n");
    return 0;
}