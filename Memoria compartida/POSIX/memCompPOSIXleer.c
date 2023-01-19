/*
   Lee en un objeto de memoria creado previamente "/myMemoryObj"
   para compilar agregue "-lrt"
   Compilar: gcc memCompPOSIXleer.c -o leer -lrt
   Ejecutar: ./leer
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
   char *ptr;
   char buf[] = "0";
   struct stat shmobj_st;
   
   fd = shm_open (SMOBJ_NAME,  O_RDWR  , 00200); /* crea objeto s.m*/
   if(fd == -1)
   {
       printf("Error: 'file descriptor' shm_open %s\n", strerror(errno));
	   exit(1);
   }
   
   if(fstat(fd, &shmobj_st) == -1)
   {
       printf(" error fstat \n");
	   exit(1);
   }
   ptr = mmap(NULL, shmobj_st.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
   if(ptr == MAP_FAILED)
   {
      printf("Error: el mapeo de memoria en proceso de lectura falló %s\n", strerror(errno));
      exit(1);
   }
   
   while(1)
   {     
      while(atoi(ptr)!=1);
      printf("Entra programa leer con pid: %d\n", getppid());
      sleep(5);
      memcpy(ptr,buf, sizeof(buf));   
   }

   close(fd);
   
   return 0;
}