#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#include "Employee.h"
#include "parser.h"
#include "../../Programacion-I/pattie/Funciones/funciones.h"

#define NOMBRE_ARCHIVO_EMPLEADOS "data.csv"


/****************************************************
    Menu:
        1. Parse del archivo data.csv
        2. Listar Empleados
        3. Ordenar por nombre
        4. Agregar un elemento
        5. Elimina un elemento
        6. Listar Empleados (Desde/Hasta)
*****************************************************/


int main()
{
    ArrayList* arrayEmpleados = al_newArrayList();
    int parseoEmpleados;
    char seguir = 's';
    int opcion;
    int listaEmpleados;
    int cargaEmpleado;
    int ordenaLista;
    int cantidadElementosLista;
    int borraEmpleado;
    int indiceDesde;
    int indiceHasta;

    if(arrayEmpleados != NULL)
    {
        while(seguir == 's')
        {
            system("cls");

            printf("1. Parse del archivo data.csv\n");
            printf("2. Listar Empleados\n");
            printf("3. Ordenar por nombre\n");
            printf("4. Agregar un elemento\n");
            printf("5. Elimina un elemento\n");
            printf("6. Listar Empleados (Desde/Hasta)\n\n");
            printf("7. Salir\n");

            scanf("%d", &opcion);

            switch(opcion)
            {
            case 1:
                parseoEmpleados = employee_cargarDesdeArchivo(NOMBRE_ARCHIVO_EMPLEADOS, arrayEmpleados);
                if(parseoEmpleados == 1)
                {
                    printf("Parse del archivo OK\n");
                }
                else
                {
                    printf("ERROR en Parse\n");
                }
                break;

            case 2:
                listaEmpleados = employee_listar(arrayEmpleados, -1, -1);
                if(listaEmpleados < 1)
                {
                    printf("No hay Empleados cargados\n");
                }
                break;

            case 3:
                cantidadElementosLista = al_len(arrayEmpleados);
                if(cantidadElementosLista > 0)
                {
                    ordenaLista = al_sort(arrayEmpleados, employee_compare, 1);
                    if(ordenaLista == 0)
                    {
                        printf("Ordenamiento OK\n");
                    }
                    else
                    {
                        printf("ERROR en ordenamiento\n");
                    }
                }
                else
                {
                    printf("No hay Empleados cargados\n");
                }
                break;

            case 4:
                cargaEmpleado = employee_agregar(arrayEmpleados);
                if(cargaEmpleado == 1)
                {
                    printf("Alta de Empleado OK\n");
                }
                else
                {
                    printf("Error al cargar empleado\n");
                }
                break;

            case 5:
                listaEmpleados = employee_listar(arrayEmpleados, -1, -1);
                if(listaEmpleados < 1)
                {
                    printf("No hay Empleados cargados\n");
                }
                else
                {
                    borraEmpleado = employee_borrar(arrayEmpleados);
                    if(borraEmpleado == 1)
                    {
                        printf("Baja de Empleado OK\n");
                    }
                    else
                    {
                        printf("Error al borrar empleado\n");
                    }
                }
                break;

            case 6:
                do
                {
                    indiceDesde = pedirEnteroSinValidar("Ingrese indice desde el cual listar Empleados: ");
                    if(indiceDesde < 0)
                    {
                        printf("El indice desde el cual listar no puede ser negativo\n");
                    }
                } while(indiceDesde < 0);

                do
                {
                    indiceHasta = pedirEnteroSinValidar("Ingrese indice hasta el cual listar Empleados: ");
                    if(indiceHasta < 0)
                    {
                        printf("El indice hasta el cual listar no puede ser negativo\n");
                    }
                } while(indiceHasta < 0);

                if(indiceDesde <= indiceHasta)
                {
                    listaEmpleados = employee_listar(arrayEmpleados, indiceDesde, indiceHasta);
                    if(listaEmpleados < 1)
                    {
                        printf("No hay Empleados cargados\n");
                    }
                }
                else
                {
                    printf("El indice desde no puede ser mayor al indice hasta\n");
                }
                break;

            case 7:
                seguir = 'n';
                break;

            default:
                printf("Opcion incorrecta, opciones validas desde 1 hasta 7\n");
            }

            if(seguir == 's')
            {
                system("pause");
            }
        }

    }
    else
    {
        printf("ERROR. No se puede crear la lista de Empleados en memoria\n");
    }

    return 0;
}
