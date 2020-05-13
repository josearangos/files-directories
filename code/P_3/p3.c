#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>




int main(int argc, char* argv[]){   

    FILE *file;
    
    if(argc !=3){
        printf("Error, indique fichero y número de lineas a leer.");
        exit(0);
    }
    int n_lines = abs(atoi(argv[1]));
    printf("-----------------------------------------------------------------------\n");    
    if(n_lines == 0){
        printf("Error, minimo debe ser 1 linea");
        exit(0);
    }

    file = fopen(argv[2], "r");
    if(file == NULL){
        printf("Error el archivo no se pudo leer");
        exit(0);
    }

    fseek(file,0,SEEK_END);
    unsigned int posicion = ftell(file);
    int i =0;
    char p;
    while(i < n_lines){
        
        fseek(file,--posicion,SEEK_SET);
        p = fgetc(file);
        if(p == '\n' || p == EOF){
            i++;
        }       
    }

    while( i > 0){
        fseek(file,posicion++, SEEK_SET);
        p = fgetc(file);
        printf("%c",p);
        if(p == '\n'){
            i--;
        }      
    }

    fseek(file,-1, SEEK_END);
    p = fgetc(file);
    printf("%c \n",p);
    printf("-----------------------------------------------------------------------\n");    

    return 0;
}