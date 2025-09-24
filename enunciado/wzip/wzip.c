#include <stdio.h>
#include <stdlib.h>

/**
 * Escribe una secuencia comprimida (contador + carácter) al stdout en formato binario
 */
void compress_and_write(char current_char, int count) {
    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&current_char, sizeof(char), 1, stdout);
}

int main(int argc, char *argv[]) {
    /* Validación de argumentos de entrada */
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
    
    /* Variables para implementar el algoritmo RLE */
    char current_char = 0, previous_char = 0;
    int count = 0;
    int first_char = 1;
    
    /* Procesamiento de todos los archivos de entrada */
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }
        
        /* Algoritmo RLE: cuenta caracteres consecutivos iguales */
        while ((current_char = fgetc(fp)) != EOF) {
            if (first_char) {
                previous_char = current_char;
                count = 1;
                first_char = 0;
            } else if (current_char == previous_char) {
                count++;
            } else {
                compress_and_write(previous_char, count);
                previous_char = current_char;
                count = 1;
            }
        }
        
        fclose(fp);
    }
    
    /* Escribir la última secuencia de caracteres */
    if (!first_char) {
        compress_and_write(previous_char, count);
    }
    
    return 0;
}