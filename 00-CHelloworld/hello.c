#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE* archivo = freopen("output.txt","w",stdout);

    printf("Hello world");

    fclose(archivo);
return 0;
}