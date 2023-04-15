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


//----------------------------FUNCIONES---------------------------

void inicializarPunteros(tarea **tareas,int cant);

void ingresarTareas(tarea **tareas,int cant);

void moverTareas(tarea **tareasPendientes,tarea **tareasRealizadas,int cant);

void mostrarTareas(tarea **tareas,int cant);

void mostrarTarea(tarea tarea);

tarea BuscarTareaPorId(tarea **tareasPendientes,tarea **tareasRealizadas,int cant,int idBuscado);

tarea BuscarTareaPorPalabra(tarea **tareasPendientes,tarea **tareasRealizadas,int cant,char *palabraBuscada);

void menu(tarea **tareasPendientes,tarea **tareasRealizadas,int cant);


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


    //INICIALIZO EN NULL
    inicializarPunteros(tareasPendientes,cant);
    inicializarPunteros(tareasRealizadas,cant);

    //INGRESO TAREAS EN tareasPendientes
    ingresarTareas(tareasPendientes,cant);

    //MUESTRO TAREAS PENDIENTES
    puts("<>-<>-<>-<> Tareas pendientes <>-<>-<>-<>");
    mostrarTareas(tareasPendientes,cant);

    //MENU PARA MOVER TAREAS desde tareasPendientes a tareasRealizadas
    moverTareas(tareasPendientes,tareasRealizadas,cant);

    //MUESTRO TAREAS REALIZADAS
    puts("<>-<>-<>-<> Tareas realizadas <>-<>-<>-<>");
    mostrarTareas(tareasRealizadas,cant);

    //MENU DE BUSQUEDA
    menu(tareasPendientes,tareasRealizadas,cant);

    //LIBERACION DE MEMORIA
    for (int i = 0; i < cant; i++)
    {
            free(tareasPendientes[i]);
            free(tareasRealizadas[i]);
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

void moverTareas(tarea **tareasPendientes,tarea **tareasRealizadas,int cant)
{
    int eleccion,j=0;
    puts("--------- INDIQUE QUE TAREAS REALIZO -----------");
    for (int i = 0; i < cant; i++)
    {
        puts("Realizo la siguiente tarea: ??? ");
        mostrarTarea(*tareasPendientes[i]);
        puts("1-Si / 0-No");
        scanf("%d",&eleccion);
        if (eleccion)
        {
            tareasRealizadas[j] = tareasPendientes[i]; // si tengo un solo subindice, si pongo NO, no guardara nada en esa posicion y como tareaRealizada estaba inicializada en NULL entonces qdaria con huecos tareaRealizada
            tareasPendientes[i] = NULL;
            j++;
        }
    }
}


void mostrarTarea(tarea tarea)
{
    printf("ID: %d\n",tarea.TareaID);
    printf("Duracion: %d\n",tarea.Duracion);
    printf("Descripcion: %s\n",tarea.Descripcion);
}

void mostrarTareas(tarea **tareas,int cant)
{
    for (int i = 0; i < cant; i++)
    {
        if (tareas[i] != NULL)
        {
            mostrarTarea(*tareas[i]); // le mando la struct, si mando tareas[i] seria un puntero entonces mostrarTarea quedaria void mostrarTarea(tarea *tarea) y tendria que usar el operador flecha
            printf("---------------------------\n");
        }
    }
}

tarea BuscarTareaPorPalabra(tarea **tareasPendientes,tarea **tareasRealizadas,int cant,char *palabraBuscada)
{
    for (int i = 0; i < cant; i++)
    {
        if (tareasPendientes[i] != NULL && strstr(tareasPendientes[i]->Descripcion,palabraBuscada))
        {
            return *tareasPendientes[i];
        }
        if (tareasRealizadas[i]!=NULL && strstr(tareasRealizadas[i]->Descripcion,palabraBuscada))
        {
            return *tareasRealizadas[i];
        }
    }
    //si no hay coincidencias
    tarea aux;
    aux.TareaID = -1;
    return aux;
}

tarea BuscarTareaPorId(tarea **tareasPendientes,tarea **tareasRealizadas,int cant,int idBuscado)
{

    for (int i = 0; i < cant; i++)
    {
        /*
            es necesario la verificacion de != NULL, si no se intentaria acceder a la struct y daria error
            incluso si creo una tarea de un solo elemento, buscara en dos conjuntos de tareas y si o si uno estara
            con NULL
        */
        if (tareasPendientes[i] != NULL && tareasPendientes[i]->TareaID == idBuscado)
        {
            return *tareasPendientes[i]; //devuelvo el struct (contenido) NO el puntero, si mandara el puntero tendria que cambiar la definicion de la funcion a tarea* Buscar...
        }

        if (tareasRealizadas[i]!=NULL && tareasRealizadas[i]->TareaID == idBuscado)
        {
            return *tareasRealizadas[i];
        }
    }
    //si no hay coincidencias
    tarea aux;
    aux.TareaID = -1;
    return aux;
}


void menu(tarea **tareasPendientes,tarea **tareasRealizadas,int cant)
{
    puts("{#}{#}{#}{#} MENU DE BUSQUEDA {#}{#}{#}{#}");
    int op1=1,idBuscado;
    tarea aux;
    char *palabraBuscada;
    palabraBuscada= (char *) malloc(100*sizeof(char));
    while (op1 != 0)
    {
        printf("\n");
        puts("[0 - Salir]");
        puts("[1 - Busqueda por ID]");
        puts("[2 - Busqueda por palabra]");
        printf("\n");
        scanf("%d",&op1);
        switch (op1)
        {
        case 1:
            puts("-----BUSQUEDA POR ID----");
            fflush(stdin);
            printf("Ingrese el id de la tarea que desea buscar: ");
            scanf("%d",&idBuscado);
            aux = BuscarTareaPorId(tareasPendientes,tareasRealizadas,cant,idBuscado);
            if (aux.TareaID != -1)
            {
                printf("\n<<<<<<<< Resultado obtenido: >>>>>>>>>>\n");
                mostrarTarea(aux);
            }else
            {
                printf("\n<<<<<<<< No se encontro la tarea >>>>>>>>>>\n");
            }
            break;

        case 2:
            puts("-----BUSQUEDA POR PALABRA----");
            fflush(stdin);
            printf("Ingrese la palabra que desea buscar: ");
            gets(palabraBuscada);
            aux = BuscarTareaPorPalabra(tareasPendientes,tareasRealizadas,cant,palabraBuscada);
            if (aux.TareaID != -1)
            {
                printf("\n<<<<<<<< Resultado obtenido: >>>>>>>>>>\n");
                mostrarTarea(aux);
            }else
            {
                printf("\n<<<<<<<< No se encontro la tarea >>>>>>>>>>\n");
            }
            break;
        }
    }
    free(palabraBuscada);
}