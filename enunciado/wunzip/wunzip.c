#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    /* Validación de argumentos de entrada */
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }
    
    /* Variables para la descompresión RLE */
    int count;
    char character;
    
    /* Procesamiento de todos los archivos de entrada */
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wunzip: cannot open file\n");
            exit(1);
        }
        
        /* Algoritmo de descompresión: lee pares de contador-carácter y expande */
        while (fread(&count, sizeof(int), 1, fp) == 1 && 
               fread(&character, sizeof(char), 1, fp) == 1) {
            
            /* Escribir el carácter 'count' veces */
            for (int i = 0; i < count; i++) {
                putchar(character);
            }
        }
        
        fclose(fp);
    }
    
    return 0;
}