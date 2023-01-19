/*include*/
#include <unistd.h>    /*Constantes simbólicas*/
#include <sys/types.h> /* Tipos de datos del sistema primitivos*/
#include <errno.h>     /*Errores*/
#include <stdio.h>     /*Input/Output*/
#include <sys/wait.h>  /*Espera por la terminación del proceso */
#include <stdlib.h>    /*Utilerias en General*/
#include <string.h>
#include <pwd.h>       //Provee una definicion de la estructura passwd, que, entre otras cosas, incluye el nombre de usuario
// Declaración de funciones
int suma_primos(int N);
// PROGRAMA PRINCIPAL
int main(int argc, char **argv)
{
    pid_t childpid, nietopid; // variable para almacenar el identificador de proceso del proceso (pid) hijo y nieto//
    int p1[2];                // Padre -> Hijo
    int p2[2];                // Hijo -> Nieto
    pipe(p1);                 // Conexión entre el proceso padre y el hijo
    pipe(p2);                 // Conexión entre el hijo y el nieto
    /* solo 1 variable "int" es necesaria debido a que cada proceso tendrá su propia instancia de la variable, 2 variables "int" son usadas por claridad */
    /* se crea ahora un nuevo proceso */
    childpid = fork();
    if (childpid >= 0) // fork tuvo éxito
    {
        if (childpid == 0) // proceso hijo
        {
            //otro fork para obtener al proceso nieto
            nietopid = fork();
            if (nietopid == 0)// proceso nieto
            {
                //Cerramos la escritura de la pipa 2
                close(p2[1]);
                //Variable para almacenar la variable recibida por el nieto
                int y;
                // printf("Proceso nieto con pid %d\n", getpid());
                //RECIBIMOS DEL HIJO
                read(p2[0], &y, sizeof(y));
                printf("\nProceso nieto recibe del hijo: %d", y);
                y *= 3;
                printf("\nNieto. Numero por tres: %d", y);
                //cerramos la lectura
                close(p2[0]);


                // De la librería pwd.h, nos sirve para obtener el nombre de usuario, entre otras cosas
                struct passwd *p = getpwuid(getuid()); 
                printf("\nNombre de usuario: %s\n", p->pw_name);//obtenemos el nombre de usuario
                char *nombre_archivo = p->pw_name;
                // Abrimos el archivo
                FILE *archivo = fopen(p->pw_name, "w");

                char *path = realpath(nombre_archivo, NULL);
                //Verificamos por errores
                if (path == NULL)
                {
                    printf("\nNo se pudo encontrar el archivo: [%s]\n", nombre_archivo);
                }//IMprimimos la ruta del archivo
                else
                {
                    printf("\nRuta del archivo :[%s]\n", path);
                    free(path);
                }
                //Llenamos el archivo
                fprintf(archivo, "Usuario: %s con resultado: %d", p->pw_name, y);
                //FInalmente, cerramos el archivo
                fclose(archivo);

            }
            else
            {// proceso hijo

                close(p1[1]);
                close(p2[0]);
                
                // printf("Proceso hijo con pid %d\n", getpid());
                int x;
                read(p1[0], &x, sizeof(x));
                
                printf("\nProceso hijo recibe del padre: %d\n", x);
                x *= 2;
                printf("\nProceso hijo envia al nieto: %d\n", x);
                write(p2[1], &x, sizeof(x)); // valor enviado al nieto, hijo de este
                
                close(p2[1]);
                close(p1[0]);
                wait(NULL);
            }
        }
        else // proceso padre
        {
            //Leemos N
            int N;
            printf("Ingrese N: ");
            scanf("%d", &N);
            //Cerramos la lectura de la pipa 1, pues solo vamos a aescribir
            close(p1[0]);
            //Obtenemos la suma de numeros primos de 0 a N
            int sumNumPrim = suma_primos(N);
            //Imprimimos informacion
            printf("\nProceso padre. Suma de numeros primos: %d\n", sumNumPrim);

            // printf("%d", sumNumPrim);
            //printf("Proceso padre envía al hijo: %d", sumNumPrim);
            write(p1[1], &sumNumPrim, sizeof(N)); // valor enviado al hijo
            
            // printf("Proceso padre con pid %d\n", getpid());
            //Cerramos, una vez que hemos escrito, la escritura de la pipa 1
            wait(NULL);
            close(p1[1]);
            
        }
    }
    else // fork regresa -1 si falla
    {
        perror("fork"); // despliega mensaje de error
        exit(0);
    }

    return 0;
}
//Funcion para obtener la suma de los numeros primos de 0 a N
int suma_primos(int N)
{
    int sumNumPrim = 0, i = 0;
    //este entero servirá para saber si es primo (0) o si no es primo(1)
    int es_primo = 0;
    //Recorremos de 0 a N
    for (int j = 0; j < N; j++)
    {
        es_primo = 0;
        //Caso Base. Si el número es 0 o 1, no es un número primo
        if (j == 0 || j == 1)
            es_primo  = 1;
        //Empezamos en 2, ya que es el menor número primo, y recordando que un
        //número no puede ser divisible de forma entera por un número mayor a su mitad
        for (i = 2; i <= j / 2; ++i)
        {
            // si j es divisible por i, entonces n no es primo (el menor numero primo es 2)
            if (j % i == 0)
                es_primo  = 1;
        }

        // Si primo nunca fue 1, entonces encontramos un número primo
        if (es_primo  == 0)
        {
            //sumamos los numeros primos
            sumNumPrim += j;
            // printf("\nNumero primo: %d", j);
        }
    }

    return sumNumPrim;
}