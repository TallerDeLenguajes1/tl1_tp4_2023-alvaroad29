#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct
{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
}Nodo;

//------------------------- Declaracion de funciones ----------------------------
Nodo* crearListaVacia();

Nodo* crearNodo(Tarea tarea);

void insertarNodo(Nodo **start,Tarea tarea);

/*void insertarAlFinal(Nodo *start,Tarea tarea);*/

//Nodo* buscarNodoPorId(Nodo *start,int idBuscado);

void moverTareas(Nodo **startPendientes,Nodo **startRealizadas);

void borrarNodo(Nodo **start,int idBorrar);

Tarea ingresarTareas(int i);

void mostrarTarea(Tarea tarea);

void mostrarTareas(Nodo *startPendientes);

//_-----------------------------

Nodo* BuscarTareaPorPalabra(Nodo*startPendientes,Nodo *startRealizadas,char *palabraBuscada);

Nodo* BuscarTareaPorId(Nodo*startPendientes,Nodo *startRealizadas,int idBuscado);

void menu(Nodo*startPendientes,Nodo *startRealizadas);



/*------------------------------------ MAIN -------------------------------*/

int main(int argc, char const *argv[])
{
    Nodo *startPendientes = crearListaVacia(); // cabeza de la lista, start no tiene reserva de memoria, solo es un puntero
    Nodo *startRealizadas = crearListaVacia(); //es un puntero de tipo Nodo que tendra la D.M. del primer nodo o NULL si esta vacia la lista

    // carga de tareas
    int opcion=1,opcion2=0;
    int prueba;
    Tarea tarea;
    Nodo *resultadoBusqueda; //nodo que guardara el resultado de la busqueda

    int i=0;
    do
    {
        printf("<><><><><><><><><><><><> MENU <><><><><><><><><><><><><>\n");
        printf("Seleccione una opcion: \n");
        printf("0-Salir\n");
        printf("1-Cargar tareas\n");
        printf("2-Mostrar tareas pendientes\n");
        printf("3-Marcar tareas a realizadas\n");
        printf("4-Mostrar tareas realizadas\n");
        printf("5-Buscar tarea \n");
        scanf("%d",&opcion2);
        switch (opcion2)
        {
        case 1:
            do
            {
                i++;
                tarea = ingresarTareas(i);
                //mostrarTarea(tarea);
                insertarNodo(&startPendientes,tarea);
                printf("Desea crear otra tarea ( Si (1) / No (0) ): ");
                scanf("%d",&opcion);
            } while (opcion != 0);
            break;

        case 2:
            mostrarTareas(startPendientes);
            break;

        case 3:
            moverTareas(&startPendientes,&startRealizadas);
            break;

        case 4:
            mostrarTareas(startRealizadas);
            break;

        case 5:
            menu(startPendientes,startRealizadas);
            break;

        }

        
    } while (opcion2 != 0);


    return 0;
}








//------------------------- Funciones  ----------------------------

Nodo* crearListaVacia() //lista vacia
{
    return NULL;
}

Nodo* crearNodo(Tarea tarea)
{
    Nodo* nuevoNodo = malloc(sizeof(Nodo)); //crea el nodo
    nuevoNodo->T = tarea; //asigno el contenido
    nuevoNodo->Siguiente = NULL; //apunto a NULL
    return nuevoNodo; //devuelvo
}

void insertarNodo(Nodo **start,Tarea tarea) //**start es la direccion de memoria  de start, si solo mandara *start seria la direccion a la que apunta start osea el primer nodo, No me sirve ya que necesito reescribirlo a start
{
    Nodo* nuevoNodo = crearNodo(tarea); //crea el nodo
    nuevoNodo->T = tarea;
    nuevoNodo->Siguiente = *start; //nodo apunta a lo que apuntaba la cabecera(*start es el contenido de **start que seria la direccion de memoria de start)
    *start = nuevoNodo; //la cabezara apunta al nuevo nodo
}

/*
void insertarAlFinal(Nodo *start,Tarea tarea) //no es necesario el *start porque start no se ve modificado
{
    Nodo* nuevoNodo = crearNodo(tarea); //creo el nodo
    Nodo* aux = start; // nodo aux con la direccion que apunta start
    while (aux->Siguiente) // itera hasta llegar a NULL (antes del ultimo)
    {
        aux = aux->Siguiente; //va a guardar la direccion de
    }
    aux->Siguiente = nuevoNodo; // o seria *(aux)->siguiente = nuevoNodo??
}
*/

Nodo* buscarNodoPorId(Nodo *start,int idBuscado)
{
    Nodo* aux = start;
    while (aux && aux->T.TareaID != idBuscado) //mientras aux no sea NULL y no encuentre el id
    {
        aux = aux->Siguiente;
    }
    return aux;
}



Tarea ingresarTareas(int i)
{
    Tarea tarea;
    fflush(stdin);
    printf("\n==============MENU DE CARGA DE TAREAS=================\n");
    char *Buff; //variable auxiliar
    Buff= (char *) malloc(500*sizeof(char)); // asigno dinamicamente 

    //scanf("%d",&(*tarea[i]).Duracion);
    tarea.TareaID = i; // operador flecha porque accedo a los miembros de la estructura a traves de un puntero a un puntero de la estructura
    printf("---------TAREA[%d]---------\n",i);
    printf("Duracion de la tarea: ");
    scanf("%d",&tarea.Duracion);
    fflush(stdin);
    printf("Descripcion de la tarea: ");
    gets(Buff);
    tarea.Descripcion = (char *)malloc(sizeof(char) * (strlen(Buff)+1)); // tercera reserva
    strcpy(tarea.Descripcion,Buff);

    free(Buff);

    return tarea;
}

void mostrarTarea(Tarea tarea)
{
    printf("ID: %d\n",tarea.TareaID);
    printf("Duracion: %d\n",tarea.Duracion);
    printf("Descripcion: %s\n",tarea.Descripcion);
}

void mostrarTareas(Nodo *startPendientes)
{
    Nodo* aux = startPendientes; //puntero aux para evitar reescribir el puntero cabeza, tmb necesito asignarlo aqui 
    //como esta dentro de una funcion parece no ser necesario declarar un nodo auxiliar??
    while (aux!= NULL)
    {
        mostrarTarea(aux->T);
        aux = aux->Siguiente;
        printf("------------------\n");
    }
}

void borrarNodo(Nodo **start,int idBorrar)
{
    Nodo* auxActual = *start; //Direccion del primer elemento de la lista(si fuera auxActual=start seria la direccion de la cabeza)
    Nodo* auxAnterior = NULL;
    while (auxActual != NULL && auxActual->T.TareaID != idBorrar) //itera hasta llegar al final(o q la lista se vacia) o hasta que encuentre el dato
    {
        auxAnterior = auxActual; // va guardando la ubicacion anterior
        auxActual = auxActual->Siguiente;
    }

    //en caso de que la lista sea vacia aux sera == NULL
    //sino encontro el dato iterara hasta el final y tamb aux sera == NULL
    //si encontro el nodo q contiene el dato (nodo que quiero borrar) la direccion de memoria de este estara en auxAnterior

    if (auxActual == NULL) //==NULL significa que la lista esta vacia o no encontro el dato e itero hasta el final
    {
        //no hago nada
    }else
    {
        if (*start == auxActual) //el caso en que la lista tenga un solo elemento ya que auxActual nunca se actualizo porque no entro en el while
        {
            *start = auxActual->Siguiente; // *start (la cabeza) pasaria a apuntar a NULL
            //en este caso auxActual seguiria apuntando al primer nodo, dsp lo libero
        }else
        {
            //auxActual apunta al nodo que quiero borrar
            //auxAnterior apunta al nodo antes de ese
            auxAnterior->Siguiente = auxActual->Siguiente;
            //auxAnterior->Siguiente seria el "espacio" del nodo al cual estaria apuntando auxAnterior que contiene el dato del sig nodo
            //osea reescribo auxAnterior->Siguiente
            //auxActual->Siguiente seria el "espacio" del nodo(nodo que quiero borrar pero necesito saber a que esta apuntando) al cual estaria apuntando auxActual que contiene el dato del sig nodo
        }
        //free(auxActual->T.Descripcion); // libero la asigDinamica de la descripcion ANTES de liberar el puntero al nodo
        //no la libero si no pierdo la asig dinamica y en tareasRealizadas ya no se mostraria(muestra simbolo raros :C )
        free(auxActual);//libero el puntero al nodo
    }
}

void moverTareas(Nodo **startPendientes,Nodo **startRealizadas)
{
    int eleccion=0; 
    Nodo *aux = *startPendientes;
    puts("--------- INDIQUE QUE TAREAS REALIZO -----------");
    while (aux != NULL)
    {
        puts("Realizo la siguiente tarea: ??? ");
        mostrarTarea(aux->T);
        puts("1-Si / 0-No");
        scanf("%d",&eleccion);
        if (eleccion)
        {
            //startRealizadas contiene la direccion de memoria de startRealizadas(lo q necesito mandar)
            //*startRealizadas contendria el contenido del puntero que seria la direccion de memoria del primer nodo(o NULL)
            insertarNodo(startRealizadas,aux->T); 
            borrarNodo(startPendientes,aux->T.TareaID);
        }
        aux = aux->Siguiente;
    }
}



/* DESCARTADA-------------------
void moverTareas(Nodo *startPendientes,Nodo **startRealizadas)
{
    int eleccion;
    puts("--------- INDIQUE QUE TAREAS REALIZO -----------");
    Nodo *aux = startPendientes;
    while (aux->Siguiente != NULL)
    {
        puts("Realizo la siguiente tarea: ??? ");
        mostrarTarea(*startPendientes->T);
        puts("1-Si / 0-No");
        scanf("%d",&eleccion);
        
            if (eleccion)
            {
                
            }
        
    }
}
*/


Nodo* BuscarTareaPorPalabra(Nodo*startPendientes,Nodo *startRealizadas,char *palabraBuscada)
{
    Nodo* auxPendiente=startPendientes;
    Nodo* auxRealizadas=startRealizadas;

    //strstr no encuentra coincidencia devuelve NULL que seria considerado falso
    //no es necesario strstr(...) != NULL

    while (auxPendiente != NULL)
    {
        if ( strstr(auxPendiente->T.Descripcion,palabraBuscada) )
        {
            puts("\n<<<<<<<< Tarea en estado PENDIENTE >>>>>>>>>>\n");
            return auxPendiente;
        }
        auxPendiente = auxPendiente->Siguiente;
    }

    while (auxRealizadas != NULL)
    {
        if (strstr(auxRealizadas->T.Descripcion,palabraBuscada))
        {
            puts("\n<<<<<<<< Tarea en estado REALIZADA >>>>>>>>>>\n");
            return auxRealizadas;
        }
        auxRealizadas = auxRealizadas->Siguiente;
    }

    //si no hay coincidencias
    //Nodo *aux;
    //aux->T.TareaID = -1;
    //return aux;
    return NULL;
}

Nodo* BuscarTareaPorId(Nodo*startPendientes,Nodo *startRealizadas,int idBuscado)
{

    Nodo* auxPendiente=startPendientes;
    Nodo* auxRealizadas=startRealizadas;
    while (auxPendiente != NULL)
    {
        if (auxPendiente->T.TareaID == idBuscado)
        {
            puts("\n<<<<<<<< Tarea en estado PENDIENTE >>>>>>>>>>\n");
            return auxPendiente;
        }
        auxPendiente = auxPendiente->Siguiente;
    }
    
    while (auxRealizadas != NULL)
    {
        if (auxRealizadas->T.TareaID == idBuscado)
        {
            puts("\n<<<<<<<< Tarea en estado REALIZADA >>>>>>>>>>\n");
            return auxRealizadas;
        }
        auxRealizadas = auxRealizadas->Siguiente;
    }

    //si no hay coincidencias
    //Nodo *aux;
    //aux->T.TareaID = -1;
    //return aux;
    return NULL;
}

void menu(Nodo*startPendientes,Nodo *startRealizadas)
{
    puts("{#}{#}{#}{#}{#}{#} MENU DE BUSQUEDA {#}{#}{#}{#}{#}{#}");
    int op1=1,idBuscado;
    Nodo *resultadoBusqueda; //nodo que guardara el resultado de la busqueda
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
            resultadoBusqueda = BuscarTareaPorId(startPendientes,startRealizadas,idBuscado);
            if (resultadoBusqueda)
            {
                mostrarTarea(resultadoBusqueda->T);
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
            resultadoBusqueda = BuscarTareaPorPalabra(startPendientes,startRealizadas,palabraBuscada);
            if (resultadoBusqueda)
            {
                mostrarTarea(resultadoBusqueda->T);
            }else
            {
                printf("\n<<<<<<<< No se encontro la tarea >>>>>>>>>>\n");
            }
            break;
        }
    }
    free(palabraBuscada);
}
