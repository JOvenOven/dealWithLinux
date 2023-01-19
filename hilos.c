#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
typedef struct datos_hilo{
	int valor_hilo;
	char nombre_hilo[50];
} datos_hilo;
void retardo(int segundos, int nanosegundos);
void *rutina_hilo1(void *arg)
{
    datos_hilo *h1datos=(datos_hilo *)arg;

    while (1)
    {
        printf("Soy el hilo 1: %s del proceso 1 con pid: %d\n", h1datos->nombre_hilo,getpid());
        //retardo(3,20);
        

    }
}

void *rutina_hilo2(void *arg)
{
    datos_hilo *h2datos=(datos_hilo *)arg;

    while (1)
    {
        printf("Soy el hilo 2: %s del proceso 1 con pid: %d\n", h2datos->nombre_hilo,getpid());
        //retardo(3,20);
        

    }
}
void *rutina_hilo3(void *arg)
{
    datos_hilo *h3datos=(datos_hilo *)arg;

    while (1)
    {
        printf("Soy el hilo 3: %s del proceso 2 con pid: %d\n", h3datos->nombre_hilo,getpid());
        //retardo(3,20);
        

    }
}
void *rutina_hilo4(void *arg)
{
    datos_hilo *h4datos=(datos_hilo *)arg;

    while (1)
    {
        printf("Soy el hilo 4: %s del proceso 2 con pid: %d\n", h4datos->nombre_hilo,getpid());
        //retardo(3,20);
        

    }
}
void retardo(int segundos, int nanosegundos)
{
    struct timespec ts = {segundos, nanosegundos};
    nanosleep(&ts,NULL);
}

int main(int argc, char *argv[])
{
    pthread_t id_hilo1; /*Identificador de hilo1*/
    pthread_t id_hilo2; /*Identificador de hilo2*/
    pthread_t id_hilo3; /*Identificador de hilo3*/
    pthread_t id_hilo4; /*Identificador de hilo4*/
    
    datos_hilo h1datos; //datos del hilo 1
    datos_hilo h2datos; //datos del hilo 2
    datos_hilo h3datos; //datos del hilo 3
    datos_hilo h4datos; //datos del hilo 4
  

    
    pid_t pid_hijo; //variable para almacenar el identificador de proceso (pid) hijo
    pid_hijo=fork(); //se crea ahora un nuevo proceso
    if(pid_hijo >=0)//fork tuvo éxito
    {
    	if(pid_hijo==0)//este es el proceso hijo
    	{
	    		    /* prototipo de funcion pthread_create (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);*/
	    if (0 != pthread_create(&id_hilo1, NULL, rutina_hilo1, (void *)&h1datos))
		return -1;

	    if (0 != pthread_create(&id_hilo2, NULL, rutina_hilo2, (void *)&h2datos))
		return -1;
    	}else{//fork() regresa nuevo 'pid' al proceso padre
    		    

	    if (0 != pthread_create(&id_hilo3, NULL, rutina_hilo3, (void *)&h3datos))
		return -1;

	    if (0 != pthread_create(&id_hilo4, NULL, rutina_hilo4, (void *)&h4datos))
		return -1;
    	}
    	
    }else{
    	perror("fork");//despliega mensaje de error
    	exit(0);
    }
   
    
    if(argc > 4){
 
    	strcpy(h1datos.nombre_hilo, argv[1]);
    	strcpy(h2datos.nombre_hilo, argv[2]);
    	strcpy(h3datos.nombre_hilo, argv[3]);
    	strcpy(h4datos.nombre_hilo, argv[4]);
    }else{
    	printf("Faltan argumentos de entrada");
    	exit(0);
    }


    pthread_join(id_hilo4, NULL);
    pthread_join(id_hilo3, NULL);
    pthread_join(id_hilo2, NULL);
    pthread_join(id_hilo1, NULL);

    return 0;
}