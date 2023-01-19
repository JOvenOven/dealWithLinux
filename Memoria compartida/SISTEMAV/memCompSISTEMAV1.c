#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define SHMKEY 75
/*
Instruciones de ejecución:
Compilar: gcc memCompSISTEMAV1.c -o prog1
Ejecutar: ./prog1
*/
int main()
{
    int shmid; 
    char *addr, *turno;
    //Creamos la región de memoria y obtenemos la dirección
    shmid = shmget(SHMKEY, 10, 0777 | IPC_CREAT);
    //Validamos posibles errores al crear memoria compartida
    if (shmid == -1)
    {
        printf("ERROR: al crear la memoria compartida");
        exit(EXIT_FAILURE);
    }
    //Enlazar región al espacio de direccionamiento del proceso
    addr = shmat(shmid, 0, 0);
    //Comprobar errores
    if (addr == (void *)-1)
    {
        printf("ERROR: al ejecutar shmat\n");
        exit(EXIT_FAILURE);
    }
    turno = (char *)addr; //Reservar addr
    
    //Código de sincronización
    sleep(10); //Mientras se ejecuta el segundo programa
    (*turno) = 0;
    while(1)
    {
        
        while(*turno!=0);
        printf("Entra programa 1 con pid: %d\n", getppid());
        sleep(5);
        (*turno) = 1;
        
    }
    //Separar la región del espacio de direccionamiento del proceso
    if (shmdt(addr) == -1)
    {
        printf("ERROR: al ejecutar shmdt\n");
        exit(EXIT_FAILURE);

    }
    
    //ELiminar la región de memoria compartida
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        printf("shmctl(IPC_RMID) falla\n");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}