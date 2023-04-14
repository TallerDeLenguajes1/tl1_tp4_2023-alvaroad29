#include <stdio.h>
#include <time.h> // permite usar la funcion time()
#include <stdlib.h> //permite usar la funcion rand() y malloc
#include <string.h>

struct Tarea
{
    int TareaID; // lo obtengo del ciclo
    char *Descripcion;
    int Duracion; // entre 10 - 100
}typedef tarea;

void inicializarPunteros(tarea **tareas,int cant);
void ingresarTareas(tarea **tareas,int cant);
void listarTareas(tarea **tareas,tarea **tareasRealizadas,int cant);
void mostrarTareas(tarea **tareas,int cant);
int main(int argc, char const *argv[])
{
    tarea **tareasPendientes;
    tarea **tareasRealizadas;
    int cant;

    // punto 1
    printf("Cantidad de tareas que va a realizar: ");
    scanf("%d",&cant);
    tareasPendientes = (tarea**) malloc(sizeof(tarea*) * cant); //primera reserva
    tareasRealizadas = (tarea**) malloc(sizeof(tarea*) * cant);
    //con tarea* digo que reserve la memoria de un puntero que va a a puntar a una struct, si solo fuera sizeof(tarea) va a devolver el tamaño de la structura. tarea* devuelve el tamaño de un puntero (4bytes o depende)


    inicializarPunteros(tareasPendientes,cant);
    inicializarPunteros(tareasRealizadas,cant);
    ingresarTareas(tareasPendientes,cant);
    listarTareas(tareasPendientes,tareasRealizadas,cant);
    mostrarTareas(tareasPendientes,cant);
    mostrarTareas(tareasRealizadas,cant);


    for (int i = 0; i < cant; i++)
    {
            free(tareasPendientes[i];)
            free(tareasRealizadas[i];)
    }
    free(tareasPendientes);
    free(tareasRealizadas);

    return 0;
}

void inicializarPunteros(tarea **tareas,int cant)
{
    for (int i = 0; i < cant; i++)
    {
        tareas[i] = NULL;
    }
}

void ingresarTareas(tarea **tareas,int cant)
{
    fflush(stdin);
    printf("\n==============MENU DE CARGA DE TAREAS=================\n");
    char *Buff; //variable auxiliar
    Buff= (char *) malloc(500*sizeof(char)); // asigno dinamicamente 
    for (int i = 0; i < cant; i++)
    {
        //scanf("%d",&(*tarea[i]).Duracion);
        tareas[i] = malloc(sizeof(tarea)); // segunda tarea. si no lo pongo intento guardar a algo q no existe
        tareas[i]->TareaID = i+1; // operador flecha porque accedo a los miembros de la estructura a traves de un puntero a un puntero de la estructura
        printf("---------TAREA[%d]---------\n",i+1);
        printf("Duracion de la tarea: \n");
        scanf("%d",&tareas[i]->Duracion);
        fflush(stdin);
        printf("Descripcion de la tarea: \n");
        gets(Buff);
        tareas[i]->Descripcion = (char *)malloc(sizeof(char) * (strlen(Buff)+1)); // tercera reserva
        strcpy(tareas[i]->Descripcion,Buff);
        //puts(tareas[i]->Descripcion);
    }
    free(Buff);
}

//a la hora de liberar, hago el proceso inverso, primero libero descripcion,despues tareas[i] y dsp tareas

void listarTareas(tarea **tareas,tarea **tareasRealizadas,int cant)
{
    int eleccion,j=0;
    for (int i = 0; i < cant; i++)
    {
        printf("Realizo la tarea de ID: %d  (1 = SI , 0 = NO)",tareas[i]->TareaID);
        scanf("%d",&eleccion);
        if (eleccion)
        {
            tareasRealizadas[j] = tareas[i]; // si tengo un solo subindice, si pongo NO, no guardara nada en esa posicion y como tareaRealizada estaba inicializada en NULL entonces qdaria con huecos tareaRealizada
            tareas[i] = NULL;
            j++;
        }
    }
}
void mostrarTareas(tarea **tareas,int cant)
{
    for (int i = 0; i < cant; i++)
    {
        if (tareas[i] != NULL)
        {
            printf("ID: %d\n",tareas[i]->TareaID);
            printf("Duracion: %d\n",tareas[i]->Duracion);
            printf("%s\n",tareas[i]->Descripcion);
        }
    }
}