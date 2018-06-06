#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ArrayList.h"
#include "Employee.h"
#include "parser.h"
#include "../../Programacion-I/pattie/Funciones/funciones.h"

int employee_compare(void* pEmployeeA,void* pEmployeeB)
{
    int retorno;
    Employee* empleadoA = (Employee*) pEmployeeA;
    Employee* empleadoB = (Employee*) pEmployeeB;

    if(empleadoA != NULL && empleadoB != NULL)
    {
        retorno = stricmp(empleadoA->name, empleadoB->name);
    }

    return retorno;
}


void employee_print(Employee* this)
{
    printf("%d - %s - %s - %d\n", this->id, this->name, this->lastName, this->isEmpty);
}


Employee* employee_new(void)
{

    Employee* returnAux;

    returnAux = (Employee*)malloc(sizeof(Employee));

    return returnAux;

}

void employee_delete(Employee* this)
{


}

int employee_setId(Employee* this, int id)
{
    this->id = id;

    return 0;
}

int employee_getId(Employee* this)
{
    int id;
    id = this->id;

    return id;
}

int employee_setName(Employee* this, const char* name)
{
    strcpy(this->name, name);

    return 0;
}

char* employee_getName(Employee* this)
{
    char* retorno = NULL;
    strcpy(retorno, this->name);

    return retorno;
}

int employee_setLastName(Employee* this, const char* lastName)
{
    strcpy(this->lastName, lastName);

    return 0;
}

char* employee_getLastName(Employee* this)
{
    char* retorno = NULL;
    strcpy(retorno, this->lastName);

    return retorno;
}

int employee_setIsEmpty(Employee* this, int isEmpty)
{
    int retorno = -1;
    if(isEmpty == 0 || isEmpty == 1)
    {
        this->isEmpty = isEmpty;
        retorno = 0;
    }

    return retorno;
}

int employee_getIsEmpty(Employee* this)
{
    int isEmpty;
    isEmpty = this->isEmpty;

    return isEmpty;
}

int employee_nuevoId(ArrayList* arrayEmpleados)
{
    int i;
    int nuevoId = 0;
    Employee* unEmpleado = NULL;
    int primerElemento = 0;

    for(i = 0; i < al_len(arrayEmpleados); i++)
    {
        unEmpleado = (Employee*)al_get(arrayEmpleados, i);
        if(unEmpleado != NULL)
        {
            if(unEmpleado->id > nuevoId || primerElemento == 0)
            {
                primerElemento = 1;
                nuevoId = unEmpleado->id;
            }
        }
    }

    nuevoId++;

    return nuevoId;
}

int employee_cargarDesdeArchivo(const char* nombreArchivo, ArrayList* arrayEmpleados)
{
    FILE* archivoEmpleados;
    int retorno = 0;
    int parseoArchivo;
    int cerroArchivo;
    int cantidadElementosArray = al_len(arrayEmpleados);
    char continua;
    int limpiaArray;
    int confirmaParseo = 1;

    if(cantidadElementosArray > 0)
    {
        do
        {
            printf("La carga de Empleados desde archivo sobreescribira los Empleados ya cargados. Continua? (S/N): ");
            fflush(stdin);
            scanf("%c", &continua);
            if(toupper(continua) != 'S' && toupper(continua) != 'N')
            {
                printf("Opcion no valida, debe ingresar S o N. Por favor reingrese\n");
            }
        } while(toupper(continua) != 'S' && toupper(continua) != 'N');

        if(toupper(continua) == 'S')
        {
            limpiaArray = al_clear(arrayEmpleados);
            if(limpiaArray < 0)
            {
                printf("Error al limpiar array list\n");
                confirmaParseo = 0; //Error al limpiar arrayList, se cancela
            }
        }
        else
        {
            printf("Parseo cancelado por el usuario\n");
            confirmaParseo = 0; //Cancelado por el usuario
        }
    }
    else if(cantidadElementosArray < 0)
    {
        printf("Array list apunta a NULL\n");
        confirmaParseo = 0; //Cancelado por el usuario
    }

    if(confirmaParseo == 1)
    {
        archivoEmpleados = fopen(nombreArchivo, "r");
        if(archivoEmpleados != NULL)
        {
            parseoArchivo = parserEmployee(archivoEmpleados, arrayEmpleados);
            cerroArchivo = fclose(archivoEmpleados);

            if(parseoArchivo == 1 && cerroArchivo == 0)
            {
                retorno = 1;
            }
        }
    }

    return retorno;
}

int employee_listar(ArrayList* arrayEmpleados)
{
    int i;
    int retorno = 0;
    Employee* unEmpleado = NULL;

    for(i = 0; i < al_len(arrayEmpleados); i++)
    {
        unEmpleado = (Employee*)al_get(arrayEmpleados, i);
        if(unEmpleado != NULL)
        {
            employee_print(unEmpleado);
            retorno = 1;
        }
    }

    return retorno;
}

int employee_agregar(ArrayList* arrayEmpleados)
{
    int retorno = -1;
    int huboError = 0;
    int guardoDato;
    char nombre[TAM_NOMBRE];
    char apellido[TAM_APELLIDO];
    Employee* unEmpleado = employee_new();

    retorno = 0;

    if(huboError == 0)
    {
        pedirString("Ingrese nombre del empleado: ", nombre, TAM_NOMBRE);
        if(strcmp(nombre, "") == 0)
        {
            printf("El dato es obligatorio, por favor reingrese\n");
            huboError = 1;
        }
    }

    if(huboError == 0)
    {
        pedirString("Ingrese apellido del empleado: ", apellido, TAM_APELLIDO);
        if(strcmp(apellido, "") == 0)
        {
            printf("El dato es obligatorio, por favor reingrese\n");
            huboError = 1;
        }
    }

    if(huboError == 0)
    {
        guardoDato = employee_setId(unEmpleado, employee_nuevoId(arrayEmpleados));
        if(guardoDato < 0)
        {
            huboError = 1;
        }

        guardoDato = employee_setName(unEmpleado, nombre);
        if(guardoDato < 0)
        {
            huboError = 1;
        }

        guardoDato = employee_setLastName(unEmpleado, apellido);
        if(guardoDato < 0)
        {
            huboError = 1;
        }

        guardoDato = employee_setIsEmpty(unEmpleado, 0);
        if(guardoDato < 0)
        {
            huboError = 1;
        }

        if(huboError == 0)
        {
            guardoDato = al_add(arrayEmpleados, unEmpleado);
            if(guardoDato < 0) //Hubo error
            {
                huboError = 1;
                printf("Error al guardar los datos en el array list\n");
            }
        }
        else
        {
            printf("Error al guardar los datos en la estructura\n");
        }
    }
    else
    {
        printf("Error de carga de datos, por favor reingrese\n");
    }

    if(huboError == 0)
    {
        retorno = 1;
    }

    return retorno;
}

int employee_borrar(ArrayList* arrayEmpleados)
{
    int retorno = -1;
    int huboError = 0;
    int idParaBorrar;
    char confirma;
    int borroDato;
    int indice;
    int noHayDatos;
    Employee* unEmpleado = NULL;

    retorno = 0;

    noHayDatos = al_isEmpty(arrayEmpleados);
    if(noHayDatos == 0)
    {
        idParaBorrar = pedirEnteroSinValidar("\nIngrese ID de Empleado a borrar: ");
        if(idParaBorrar <= 0)
        {
            printf("El dato debe ser un numero positivo, por favor reingrese\n");
            huboError = 1;
        }

        if(huboError == 0)
        {
            indice = employee_getIndexPorId(arrayEmpleados, idParaBorrar);

            if(indice < 0)
            {
                printf("No se hallo el ID de Empleado especificado\n");
                huboError = 1;
            }
            else
            {
                unEmpleado = (Employee*)al_get(arrayEmpleados, indice);

                do
                {
                    printf("Se va a borrar el Empleado:\n");
                    employee_print(unEmpleado);
                    printf("\nConfirma? (S/N)");
                    fflush(stdin);
                    scanf("%c", &confirma);
                    if(toupper(confirma) != 'S' && toupper(confirma) != 'N')
                    {
                        printf("Opcion no valida, debe ingresar S o N. Por favor reingrese\n");
                    }
                } while(toupper(confirma) != 'S' && toupper(confirma) != 'N');

                if(toupper(confirma) == 'S')
                {
                    borroDato = al_remove(arrayEmpleados, indice);
                    if(borroDato < 0)
                    {
                        huboError = 1;
                    }
                }
                else
                {
                    printf("Accion cancelada por el usuario\n");
                    huboError = 1;
                }
            }
        }
    }
    else
    {
        printf("No hay Empleados cargados\n");
        huboError = 1;
    }

    if(huboError == 0)
    {
        retorno = 1;
    }

    return retorno;
}

int employee_getIndexPorId(ArrayList* arrayEmpleados, int id)
{
    int retorno = -1;
    Employee* unEmpleado = NULL;
    int i;

    for(i = 0; i < al_len(arrayEmpleados); i++)
    {
        unEmpleado = (Employee*)al_get(arrayEmpleados, i);
        if(employee_getId(unEmpleado) == id)
        {
            retorno = i;
            break; //Corto el for
        }
    }

    return retorno;
}
