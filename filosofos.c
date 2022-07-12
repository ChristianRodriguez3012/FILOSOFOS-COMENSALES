#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void * filosofo(void * arg);
int numFilosofos;
int comida = 3500;
int estomagos[];
int comio = 0;
int comidaRestaurada = 2;
int derrochandoEnergia = 0;

pthread_mutex_t tenedor[];

int main(void)
{
    printf("FILOSOFOS COMENSALES\n");
    printf("\tFILÓSOFOS:\n");
    printf("DETERMINE LA CANTIDAD DE FILOSOFOS: ");
    scanf("%d", &numFilosofos);
    pthread_t filosofos[numFilosofos];
    int id[numFilosofos];
    int i;

    for (int i = 0; i < numFilosofos; i++)
    {
        pthread_mutex_init(&tenedor[i], NULL);
    }
    for (int i = 0; i < numFilosofos; i++)
    {
        id[i] = i + 1;
        pthread_create(&filosofos[i], NULL, &filosofo, &id[i]);
    }
    for (int i = 0; i < numFilosofos; i++)
    {
        pthread_join(filosofos[i], NULL);
    }

    return 0;
}

// FUNCIÓN: COGER TENEDOR Y SABER CUAL ES

void cogiendotenedor(int a, int b)
{
    pthread_mutex_lock(&tenedor[b]);
    printf("EL FILÓSOFO # %d ESTÁ USANDO EL TENEDOR/ES %d \n", a, b);
}

// FUNCIÓN: SOLTAR TENEDOR Y SABER CUAL ES

void soltartenedores(int s1, int s2)
{tenedor
    pthread_mutex_unlock(&tenedor[s1]);
    pthread_mutex_unlock(&tenedor[s2]);
}

// FUNCIÓN: PENSAR

void piensa(int n)
{
    printf("AL FILÓSOFO# %d SE LE HA ENVIADO A PENSAR\n,", n);
    estomagos[n] -= 10;
    comio -= 10;
    derrochandoEnergia += 10;
    int aleatorio = rand() % 10;
    sleep(aleatorio);
}

// FUNCIÓN DE SECCIÓN CRÍTICA

void comiendo(int arg)
{
    int t1 = arg - 2;
    int t2 = arg - 1;

    if (t1 == -1)
    {
        t1 = t2;
        t2 = numFilosofos - 1;
    }

    // CORRIGIENDO: DEADLOCK

    if (arg == 1)
    {
        sleep(2);
    }

    cogiendotenedor(arg, t1);
    cogiendotenedor(arg, t2);

    printf("FILÓSOFO# %d ESTA COMIENDO \n", arg);
    comida = comida - 250;
    estomagos[arg] += 250;
    comio += 2500;

    // VERIFICACIÓN: RENOVACIÓN DE RECURSOS

    if (comida == 0 && comidaRestaurada > 0)
    {
        printf("COMIDA TOTAL EN LOS ESTÓMAGOS: %d ... \n", comio);
        printf("ENERGIA TOTAL GASTADA: %d ...\n", derrochandoEnergia);
        printf("CANTIDAD CONSUMIDA: %d ...\n", comio + derrochandoEnergia);

        comida = 3500;
        printf("COMIDA RESTUARADA\n");
    }

    printf("COMPROBANDO EL ESTOMAGO DEL FILÓSOFO # %d: %d ... \n", arg, estomagos[arg]);
    printf("COMIDA RESTANTE: %d ... \n", comida);
    soltartenedores(t1, t2);
}

void *filosofo(void *arg)
{
    int arg2 = *((int *)arg);
    while (comida > 0)
    {
        piensa(arg2);
        comiendo(arg2);
    }
    return NULL;
}