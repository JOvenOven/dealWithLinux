#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define SHMKEY 75
/*
Instruciones de ejecución:
Compilar: gcc memCompSISTEMAV2.c -o prog2
Ejecutar: ./prog2
*/
int main()
{
    int shmid;
    char *addr, *turno;
    /*OBTENER DIRECCION DE LA REGION DE MEMORIA */
    shmid = shmget (SHMKEY,10,0777);
    //Validamos posibles errores al crear memoria compartida
    if (shmid == -1)
    {
        printf("Fallo al crear la memoria compartida");
        exit(EXIT_FAILURE);
    }
    /*Enlazar region al espacio de direcciòn del proceso*/
    addr = shmat(shmid,0,0);
    //Comprobar errores
    if (addr == (void *)-1)
    {
        printf("ERROR: al ejecutar shmat\n");
        exit(EXIT_FAILURE);
    }
    turno = (char *) addr; /*Reservar addr*/
    //ALternancia estricta
    while(1)
    {
        while(*turno!=1);
        printf("Entra programa 2 con pid: %d\n", getppid());
        sleep(5);
        (*turno) = 0;
    }
    /*Separar la regiòn del espacio de direccionamiento del proceso*/
    if (shmdt(addr) == -1)
    {
        printf("ERROR: al ejecutar shmdt\n");
        exit(EXIT_FAILURE);

    }
    return 0;
}