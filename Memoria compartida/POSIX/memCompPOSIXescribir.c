/*
   Escribe en un objeto de memoria creado previamente "/myMemoryObj"
   para compilar agregue "-lrt"
   Compilar: gcc memCompPOSIXescribir.c -o escribir -lrt
   Ejecutar: ./escribir
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* Para constantes de modo */
#include <fcntl.h>           /* Para constantes O_* */
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
 
#define SMOBJ_NAME  "/myMemoryObj"

int main(void)
{
   int fd;
   char buf[] = "1";
   char *ptr;
   
   fd = shm_open (SMOBJ_NAME,  O_RDWR  , 00200); /* crea objeto s.m*/
   if(fd == -1)
   {
       printf("Error: 'file descriptor' shm_open %s\n", strerror(errno));
      exit(1);
   }
   
   ptr = mmap(NULL, sizeof(buf), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
   if(ptr == MAP_FAILED)
   {
      printf("Error: el mapeo de memoria en proceso de escritura falló %s\n", strerror(errno));
      exit(1);
   }

   sleep(10); //Mientras se ejecuta el segundo programa
   memcpy(ptr,"0", sizeof(buf)); 
   while(1)
   {     
      while(atoi(ptr)!=0);
      printf("Entra programa escribir con pid: %d\n", getppid());
      sleep(5);
      memcpy(ptr,buf, sizeof(buf)); 
   }

   close(fd);
   
   return 0;
}