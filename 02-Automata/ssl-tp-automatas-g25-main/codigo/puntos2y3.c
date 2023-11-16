#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>


// Automata Decimal
int automataDecimal(char* cadena){

    //TT
    size_t estados[][4] = {
    //   -,     0,    [1-9],   $
        {3,     1,      2,     4},//0
        {4,     4,      4,     0},//1
        {4,     2,      2,     0},//2
        {4,     4,      2,     4},//3
        {4,     4,      4,     4} //4
    };

    size_t estado_final = 0;

    size_t estadoInicial = 0;

    size_t estado = estadoInicial;
    int i = 0;
    char c;
    int largo_cadena = strlen(cadena);
    for(i=0;i<largo_cadena;i++){
        //Caracter donde está parado
        c=cadena[i];
        //Hace la transición respecto a cuál caracter del alfabeto se está procesando
        if(c=='-') estado = estados[estado][0];
        else if(c == '0') estado = estados[estado] [1];
        else if(c >= '1' && c <='9') estado = estados[estado][2];
        else if(c == '$') estado = estados[estado][3];
        //Si no pertenece al alfabeto va directo a estado de rechazo
        else estado = 4;

        //Si se rechaza, ya salimos del autómata y lo declaramos inválido
        if(estado == 4) return -1;
    }

    //Si no acabó en un estado final, el autómata se rechaza por estar incompleto
    if(estado == estado_final) return 0;
    else return -1;

}


// Función para verificar si un carácter es un operador válido
int esOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Función para obtener la precedencia de un operador
int precedencia(char operador) {
    switch (operador) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0; // Operador no válido
    }
}

/*Punto 2 - Pasar UN caracter numérico a un entero*/
int caracterNumericoAEntero (const char caracter)
{
    if (caracter >= '0' && caracter <='9')
    return caracter - '0';//Recalibra el desplazamiento de la tabla ascii
    else return -1;//Al solo tomar caracteres numéricos y no el signo, el número negativo nos informaría de un error.
};

/*Función que Formatea la operación para el autómata del punto 1, quién la analiza y valida*/
int expresionValida (const char *expresion) {
    char *cadena=malloc(sizeof(cadena));
    strcpy(cadena, expresion);
    strcat(cadena,"$");//Ponemos '$' al final de la cadena para que la valide el autómata
    int longitud = strlen(cadena);
    /*Reemplazamos todos los operadores por '$' */
    for (int i = 0; i < longitud; i++) {
        if (cadena[i] == '+' || cadena[i] == '-' || cadena[i] == '*' || cadena[i] == '/') {
            cadena[i] = '$';
        }
    }
    /*Retornamos la cadena formateada procesada por el autómata*/
    return automataDecimal(cadena);
};



// Función para evaluar una expresión dada en notación infija sin paréntesis
int evaluarExpresion(const char *expresion) {
    int longitud = strlen(expresion);
    int numeros[100]; // Suponemos que la expresión no tiene más de 100 números
    char operadores[100]; // Suponemos que la expresión no tiene más de 100 operadores
    int top_num = -1; // Inicializamos el índice del arreglo de números
    int top_op = -1; // Inicializamos el índice del arreglo de operadores

    for (int i = 0; i < longitud; i++) {
        if (isdigit(expresion[i])) {
            // Si el carácter es un dígito, se convierte en un número y se guarda en la pila
            int numero = 0;
            while (i < longitud && isdigit(expresion[i])) { 
                numero = numero * 10 + caracterNumericoAEntero(expresion[i]); 
                i++;
            }
            numeros[++top_num] = numero;
            i--; // Retroceder el índice para evitar perder el siguiente carácter
        } else if (esOperador(expresion[i])) {
            // Si el carácter es un operador, maneja la precedencia
            while (top_op >= 0 && precedencia(operadores[top_op]) >= precedencia(expresion[i])) {
                char operador = operadores[top_op--];
                int segundoNumero = numeros[top_num--];
                int primerNumero = numeros[top_num--];

                // Realiza la operación y guarda el resultado en el arreglo de números
                switch (operador) {
                    case '+':
                        numeros[++top_num] = primerNumero + segundoNumero;
                        break;
                    case '-':
                        numeros[++top_num] = primerNumero - segundoNumero;
                        break;
                    case '*':
                        numeros[++top_num] = primerNumero * segundoNumero;
                        break;
                    case '/':
                        if (segundoNumero != 0) {
                            numeros[++top_num] = primerNumero / segundoNumero;
                        } else {
                            printf("Error: División por cero\n");
                            exit(1);
                        }
                        break;
                }
            }
            operadores[++top_op] = expresion[i];
        } else return errno;
    }

    // Realiza las operaciones restantes en la pila de operadores
    while (top_op >= 0) {
        char operador = operadores[top_op--];
        int segundoNumero = numeros[top_num--];
        int primerNumero = numeros[top_num--];

        // Realiza la operación y guarda el resultado en el arreglo de números
        switch (operador) {
            case '+':
                numeros[++top_num] = primerNumero + segundoNumero;
                break;
            case '-':
                numeros[++top_num] = primerNumero - segundoNumero;
                break;
            case '*':
                numeros[++top_num] = primerNumero * segundoNumero;
                break;
            case '/':
                if (segundoNumero != 0) {
                    numeros[++top_num] = primerNumero / segundoNumero;
                } else {
                    printf("Error: División por cero\n");
                    exit(1);
                }
                break;
        }
    }

    // El resultado final estará en la parte superior de la pila de números
    return numeros[top_num];
}

int main() {
    char expresion[100];//Se pueden realizar operaciones de hasta 100 caracteres
    
    /*El programa se mantendrá activo hasta ingresar una expresión errónea*/
    while(1){
    printf("Ingrese una expresión matemática sin paréntesis: ");
    scanf("%s", expresion);
    if (expresionValida(expresion) == -1)
    {
        printf("Cadena invalida para este formato. ");
        return 0;
    }
    else {
    int resultado = evaluarExpresion(expresion);
    printf("El resultado es: %d\n", resultado);
    }
    }
    return 0;
}
