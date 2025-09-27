#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 101

int main(int argc, char *argv[]) {
    FILE *fileIn;
    char buffer[TAM];
for (int i = 1; i < argc; i++) { 
// Abre el archivo en modo lectura

        fileIn = fopen(argv[i], "r");
        if (fileIn == NULL) {
         printf("wcat: cannot open file\n");
     return 1;
           }

// Lee y escribe el contenido del archivo

           while (fgets(buffer, TAM, fileIn) != NULL) {
               printf("%s", buffer);
           }

//cierra el archivo

        fclose(fileIn);
    }

    return 0;
}







