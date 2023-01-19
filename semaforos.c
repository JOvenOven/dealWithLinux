//¿Què es?
//-Mecanismo de sincronizaciòn 
//Protegen acceso a la "secciòn critica"//fragmento del codigo que es compartido por varios hilos o procesos
//Funciones:
/*int sem_init (sem_t *sem, int pshared, unsigned int value); INICIALIZARLO
int sem_wait(sem_t *sem); DECREMENTAR UNA UNIDAD AL SEMAFORO O BLOQUEAR EL ACCESO AL RECURSO COMPARTIDOPOR OTRO HILO
int sem_post(sem_t *sem); INCREMENTAR UNA UNIDAD AL SEMAFORO O BLOQUEAR EL ACCESO AL RECURSO COMPARTIDO*/
/*gcc semaforos.c -pthread para compilar con hilos //./a.out */
//Sin semaforos no dara e resultado de cero porque no esta protegida la zona critica

#include <pthread.h> //hilos
#include <semaphore.h> //semaforos
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define NR_LOOP 100 //CONSTANTE NUMERO DE INTERACCIONES
static void * thread_1_function (void* arg); //DECLARACION DE PROTOTIPO DE LA FUNCION
static void * thread_2_function (void* arg);  //DECLARACION DE PROTOTIPO DE LA FUNCION
static void * thread_3_function (void* arg);
static void * thread_4_function (void* arg);

static int counter =0; //Recurso ompartido 
sem_t sem_nombre1; //DECLARACION DEL SEMAFORO
sem_t sem_nombre2; 
sem_t sem_nombre3; 
sem_t sem_nombre4; 

int main (int argc, char *argv[])
{
    char * valor_hilo1 = (char*)argv[1];
    char * valor_hilo2 = (char*)argv[2];
    char * valor_hilo3 = (char*)argv[3];
    char * valor_hilo4 = (char*)argv[4];

    pthread_t thread_1,thread_2,thread_3,thread_4; //CREACION DE DOS HILOS
    sem_init (&sem_nombre1, 0, 1); /* INICIALIZACOND EL SEMAFORO, &sem1 REFERENCIA AL SEMAFORO, 0 SEMAFORO ES 
    COMPARTIDO ENTRE PROCESOS , VALOR DE INCIALIZACION A 0 PORQUE ES DE SINCRONIZACION*/
    /*SE INICIALIZA A 0 PARA QUE NO TENGA TICKETS, PARA QUE UN PROCESO QUE LLAME A DOWN SE QUEDE BLOQUEADO HASTA 
    QUE OTRO LO DESPIERTE*/
    /*SOLO 1 HILO ACCEDERA A NUESTRA VARIABLE*/
    sem_init (&sem_nombre2, 0, 0);
    sem_init (&sem_nombre3, 0, 0);
    sem_init (&sem_nombre4, 0, 0);
    pthread_create(&thread_1, NULL, *thread_1_function, (void *)valor_hilo1); /* &thread_1 REFERENCIA AL HILO, 
    NULL ATRIBUTOS POR DEFECTO, *thread_1_function FUNCION QUE VA A EJECUTARSE AL CREARSE EL HILO, 
    PRIMER PARÁMETRO COMO ARGUMENTO DE ENTRADA A LA FUNCION*/
    pthread_create(&thread_2, NULL, *thread_2_function, (void *)valor_hilo2);
    pthread_create(&thread_3, NULL, *thread_3_function, (void *)valor_hilo3);
    pthread_create(&thread_4, NULL, *thread_4_function, (void *)valor_hilo4);



    pthread_join(thread_1,NULL); //ESPERA A QUE LOS HILOS TERMINEN
    pthread_join(thread_2,NULL); //MAIN ESPERARA A QUE EL HILO 1 ACABE Y A QUE EL HILO 2 ACABE
    pthread_join(thread_3,NULL);
    pthread_join(thread_4,NULL);
    //printf(" valor counter %d \n", counter);

    return (0);

}

void retardo(int segundos, int nanosegundos) //FUNCIÓN QUE PAUSA LA EJECUCIÓN DEL PROGRAMA
{
    struct timespec ts = {segundos, nanosegundos};
    nanosleep(&ts,NULL);
}

static void * thread_1_function (void* arg)
{
    char * nombre1 = (char*)arg;

    for (int i = 0; i < NR_LOOP; i++)
    {
    	sem_wait(&sem_nombre1); //DEJA QUE IMPRIMA NOMBRE1 PORQUE EL SEMÁFORO FUE INICIALIZADO CON 1
    	printf("\n %s, ", nombre1 );
    	sem_post(&sem_nombre2); //AVISA A SEMAFORO NOMBRE2 QUE CONTINUE
    }
    return (0);
}

static void * thread_2_function (void* arg)
{
    char * nombre2 = (char*)arg;

    for (int i = 0; i < NR_LOOP; i++)
    {
    	sem_wait(&sem_nombre2);
    	printf("%s, ", nombre2 );
    	sem_post(&sem_nombre3); //AVISA A SEMAFORO NOMBRE3 QUE CONTINUE
    }
    return (0);
    
}

static void * thread_3_function (void* arg)
{
    char * nombre3 = (char*)arg;

    for (int i = 0; i < NR_LOOP; i++)
    {
    	sem_wait(&sem_nombre3);
    	printf("%s, ", nombre3 );
    	sem_post(&sem_nombre4); //AVISA A SEMAFORO NOMBRE4 QUE CONTINUE
    }
    return (0);
    
}

static void * thread_4_function (void* arg)
{
    char * nombre4 = (char*)arg;
    
    for (int i = 0; i < NR_LOOP; i++)
    {
    	sem_wait(&sem_nombre4);
    	printf("%s", nombre4 );
	retardo(1,0);
    	sem_post(&sem_nombre1); //REINICIA EL CICLO
    }
    return (0);
    
}