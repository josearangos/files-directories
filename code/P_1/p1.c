#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

char *timeConvert(time_t time);
char *typeFile(struct stat info_file);
void printBasicInfo(struct stat info_file);
void printPermissions(struct stat info_file);

int main(int argc, char const *argv[]){
    
    struct stat info_file;
    char *type; 

    //validamos argumentos
    if(argc >2){
        printf("Número de parametros invalidos\n... solo son 2 parametros");
        return 2;
    }

    
    ///validamos que el archivo se le pueda aplicar stat
    if(stat(argv[1],&info_file) < 0){
        printf("Error while reading file \n");
        return 4;
    }
    
    type= typeFile(info_file);
    
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------FILE NAME : %s ---------------------------------------------------\n", argv[1]);
    printBasicInfo(info_file); 
    printf("------------------------------------FILE PERMISSIONS-------------------------------------------------\n");
    printPermissions(info_file);
    printf("\n");
    printf("-----------------------------------------------------------------------------------------------------\n");
        
    
    return 0;
}


char *typeFile(struct stat info_file){
   char *type; 
   if (S_ISDIR(info_file.st_mode)) {
      type = "Directory";
    } else if (S_ISLNK(info_file.st_mode)) {
      type =  "Symbolic Link";
    } else {
      type = "File";
    }
    return type;
}


char *timeConvert(time_t time){
    return  ctime(&time);   
}


void printPermissions(struct stat info_file){

    printf("\n");
    printf((S_ISDIR(info_file.st_mode)) ? "d" : "-");
    printf( (info_file.st_mode & S_IRUSR) ? "r" : "-");
    printf( (info_file.st_mode & S_IWUSR) ? "w" : "-");
    printf( (info_file.st_mode & S_IXUSR) ? "x" : "-");
    printf( (info_file.st_mode & S_IRGRP) ? "r" : "-");
    printf( (info_file.st_mode & S_IWGRP) ? "w" : "-");
    printf( (info_file.st_mode & S_IXGRP) ? "x" : "-");
    printf( (info_file.st_mode & S_IROTH) ? "r" : "-");
    printf( (info_file.st_mode & S_IWOTH) ? "w" : "-");
    printf( (info_file.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

void printBasicInfo(struct stat info_file){
    
    printf("Size : %ld bytes\n",info_file.st_size);
    printf("N_links: %ld\n",info_file.st_nlink);
    printf("Last access: \t\t\t\t%s", timeConvert(info_file.st_atime));
    printf("Last modification: \t\t\t%s\n", timeConvert(info_file.st_atime));
    printf("N_Blocks: %ld\n",info_file.st_blocks);
    printf("Block size: %ld\n",info_file.st_blksize);
    printf("User_Id: %d\n",info_file.st_uid);    

}