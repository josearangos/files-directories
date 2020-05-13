#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
/* Función para devolver un error en caso de que ocurra */
void error(const char *s);
/* Función que hace algo con un archivo */
void procesoArchivo(char *archivo);


int main(int argc, char *argv[])
{
  /* Con un puntero a DIR abriremos el directorio */
  DIR *dir;
  /* en *ent habrá información sobre el archivo que se está "sacando" a cada momento */
  struct dirent *ent;
  struct stat info;
  struct passwd *pwuser;
  struct group *grpnam;
  /* Empezaremos a leer en el directorio actual */
  dir = opendir (".");

  /* Miramos que no haya error */
  if (dir == NULL)
    error("No puedo abrir el directorio");
 
  /* Una vez nos aseguramos de que no hay error, ¡vamos a jugar! */
  /* Leyendo uno a uno todos los archivos que hay */
  while ((ent = readdir (dir)) != NULL)
    {
      /* Nos devolverá el directorio actual (.) y el anterior (..), como hace ls */
      if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) )
      {
      /* Una vez tenemos el archivo, lo pasamos a una función para procesarlo. */
      procesoArchivo(ent->d_name);
        if(argc == 2){
          if(strcmp(argv[1], "-l")==0){
              if (-1 == stat(ent->d_name,&info))
              {
                  perror("stat()");
                  exit(EXIT_FAILURE);
              }
              if (NULL == (pwuser = getpwuid(info.st_uid)))
              {
                  perror("getpwuid()");
                  exit(EXIT_FAILURE);
              }

              if (NULL == (grpnam = getgrgid(info.st_gid)))
              {
                  perror("getgrgid()");
                  exit(EXIT_FAILURE);
              }
          printf("\tinode: %ld\n", info.st_ino);
          printf("\towner: %u (%s)\n", info.st_uid, pwuser->pw_name);
          printf("\tgroup: %u (%s)\n", info.st_gid, grpnam->gr_name);
          printf("\tperms: %o\n", info.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
          printf("\tlinks: %ld\n", info.st_nlink);
          printf("\tsize: %ld\n", info.st_size); /* you may use %lld */
          printf("\tatime: %s", ctime(&info.st_atim.tv_sec));
          printf("\tmtime: %s", ctime(&info.st_mtim.tv_sec));
          printf("\tctime: %s", ctime(&info.st_ctim.tv_sec));
          printf("\n");
          }
        }
      }
    }
  closedir (dir);

  return EXIT_SUCCESS;
}

void error(const char *s)
{
  /* perror() devuelve la cadena S y el error (en cadena de caracteres) que tenga errno */
  perror (s);
  exit(EXIT_FAILURE);
}

void procesoArchivo(char *archivo)
{
  /* Para "procesar", o al menos, hacer algo con el archivo, vamos a decir su tamaño en bytes */
  /* para ello haremos lo que vemos aquí: https://poesiabinaria.net/2010/04/tamano-de-un-fichero-en-c/ */
  FILE *fich;
  long ftam;

  fich=fopen(archivo, "r");
  if (fich)
    {
      fseek(fich, 0L, SEEK_END);
      ftam=ftell(fich);
      fclose(fich);
      /* Si todo va bien, decimos el tamaño */
      printf ("\t%s (%ld bytes)\n", archivo, ftam);
    }
  else
    /* Si ha pasado algo, sólo decimos el nombre */
    printf ("%s (No info.)\n", archivo);
}