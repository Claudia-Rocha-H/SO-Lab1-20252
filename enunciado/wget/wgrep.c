#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    /* Validación de argumentos de entrada */
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    
    char *search_term = argv[1];
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    
    /* Si no hay archivos especificados, leer desde stdin */
    if (argc == 2) {
        while ((read = getline(&line, &len, stdin)) != -1) {
            if (strstr(line, search_term) != NULL) {
                printf("%s", line);
            }
        }
    } else {
        /* Procesamiento de archivos múltiples */
        for (int i = 2; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("wgrep: cannot open file\n");
                exit(1);
            }
            
            /* Buscar el patrón en cada línea del archivo */
            while ((read = getline(&line, &len, fp)) != -1) {
                if (strstr(line, search_term) != NULL) {
                    /* Si hay múltiples archivos, mostrar nombre del archivo */
                    if (argc > 3) {
                        printf("%s:%s", argv[i], line);
                    } else {
                        printf("%s", line);
                    }
                }
            }
            
            fclose(fp);
        }
    }
    
    /* Liberar memoria allocada por getline */
    if (line) {
        free(line);
    }
    
    return 0;
}