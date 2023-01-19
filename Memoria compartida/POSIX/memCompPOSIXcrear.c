/*
    Crea un objeto de memoria "/objMem"
    El objeto puede ser encontrado en /dev/shm
    para compilar use la bandera "-lrt"
    Compilar: gcc memCompPOSIXcrear.c -o crear -lrt
    Ejecutar: ./crear
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* Para constantes de modo */
#include <fcntl.h>           /* Para constantes O_* */
#include <unistd.h>
#include <sys/types.h>

#define SIZEOF_SMOBJ 200
#define SMOBJ_NAME  "/myMemoryObj"

int main(void)
{
   int fd;
   fd = shm_open (SMOBJ_NAME, O_CREAT | O_RDWR  , 00700); /* crea objeto s.m*/
   if(fd == -1)
   {
       printf("Error: 'file descriptor' shm_open \n");
	   exit(1);
   }
   if(-1 == ftruncate(fd, SIZEOF_SMOBJ))
   {
       printf("Error: la memoria compartida no pudo ser redimensionada (ftruncate) \n");
	   exit(1);
   }
   
   close(fd);
   
   return 0;
}