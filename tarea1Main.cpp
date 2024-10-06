/* Universidad de La Frontera
 * Ingeniería Civil Electrónica/Telemática
 *
 * IIE-344 ESTRUCTURA DE DATOS Y ALGORITMOS
 *
 * Tarea 1
 *
 * Autor 1: Benjamín Fuentes ; b.fuentes10@ufromail.cl
 * Autor 2: Maximiliano Ortúzar ; m.ortuzar01@ufromail.cl;
 *
 * Fecha: 06/10/2024
 *
 * Descripción general del programa:
 *      Este programa permite deserializar y serializar
 *      comandos en formato de protocolo RESP 2.0, ademas de poder almacenar cada comando con una ID correspondiente.
 *
 */

// Importamos Librerias correspondientes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicion de constantes
#define NOMBRE_DE_ARCHIVO "comandosRESP2.0.txt" // Nombre por defecto del archivo base de datos
#define MAX_SIZE 1024                           // Máximo largo para los datos tipo "char"

// Declaracion de Prototipos de funciones
void sacar_r_n(char *comando);
void deserializar_comando(char *comando);
void serializar_comando(char *comando, char *tipo);
void guardarComando(char *id, char *comandoAGuardar);
void obtenerComando(char *id);

// Definicion de las funciones

/* Descripcion
 * Nombre de la función: sacar_r_n().
 * Tipo de función: void.
 * Parámetros: "comando" puntero* de tipo char.
 * Dato de retorno: Sin valor de retorno;
 * Descripción de la función:Busca los bytes CRLFy los elimina del mensaje.
 *
 */
void sacar_r_n(char *comando)
{
    for (int i = 0; i < strlen(comando); i++)
    {
        if (comando[i] == 92 && comando[i + 1] == 'r' && comando[i + 2] == 92 && comando[i + 3] == 'n')
        {
            comando[i] = '\0';
        }
    }
}

/* Descripcion
 * Nombre de la función: deserializar_comando().
 * Tipo de función: void.
 * Parámetros: "comando" puntero* de tipo char.
 * Dato de retorno: Sin valor de retorno.
 * Descripción de la función: Lee el primer byte y determina que tipo de dato es, para luego imprimir el mensaje con su tipo.
 *                            Luego pregunta si quiere guardar el comando con una ID
 *
 */
void deserializar_comando(char *comando)
{
    sacar_r_n(comando);
    if (comando[0] == '+')
    {
        printf("comando: %s | Tipo de dato: Simple String \n", comando + 1);
    }
    else if (comando[0] == '-')
    {
        printf("comando: %s | Tipo de dato: Simple Error\n", comando + 1);
    }
    else if (comando[0] == ':')
    {
        printf("comando: %s | Tipo de dato: integer\n", comando + 1);
    }
    else if (comando[0] == '*')
    {
        printf("comando: %s | Tipo de dato: Array\n", comando + 1);
    }
    else if (comando[0] == '$')
    {
        int len;
        sscanf(comando + 1, "%d\r\n", &len);
        char *bulk = strstr(comando, "\r\n") + 2;
        printf("comando: %s | Tipo de dato: Bulk String\n", bulk);
    }
    else
    {
        printf("Formato incorrecto");
    }

    // Preguntando si quiere Guardar el comando
    int opcionPregunta;
    char idDeGuardado[9];
    printf("\n¿Guardar comando?\n");
    printf("1. Si 2.no :  ");
    scanf("%d", &opcionPregunta);
    getchar(); // Limpiar el buffer
    if (opcionPregunta == 1)
    {
        printf("\nIngrese ID de guardado (max 8 caracteres): \n");
        scanf("%8s", idDeGuardado);
        guardarComando(idDeGuardado, comando);
        return;
    }
    else if (opcionPregunta == 2)
    {
        return;
    }
}

/* Descripcion
 * Nombre de la función: serializar_comando().
 * Tipo de función: void.
 * Parámetros: "comando" puntero* de tipo char.
 * Dato de retorno: Sin valor de retorno.
 * Descripción de la función: Pregunta que mensaje se quiere serializar y de que tipo, luego imprime el comando en el formato correcto.
 *
 */
void serializar_comando(char *comando)
{
    int opcionDeSerializado = 0;
    printf("\nIngrese opcion de serializado: \n");
    printf("1.simple string\n2.simple error\n3.bulk string\n");
    printf("Tu opcion: ");
    scanf("%d", &opcionDeSerializado);

    if (opcionDeSerializado == 1)
    {
        printf("+%s\\r\\n", comando);
    }
    else if (opcionDeSerializado == 2)
    {
        printf("-%s\\r\\n ", comando);
    }
    else if (opcionDeSerializado == 3)
    {
        printf("$%d\\r%s\\r\\n", strlen(comando), comando);
    }
    else
    {
        printf("Tipo de dato incorrecto.\n");
    }
}

/* Descripcion
 * Nombre de la función: guardarComando().
 * Tipo de función: void.
 * Parámetros: puntero de id tipo char y puntero comandoAGuardar tipo char
 * Dato de retorno: Sin valor de retorno.
 * Descripción de la función: abre un archivo en forma append para imprimirle el mensaje y la key.
 *
 */
void guardarComando(char *id, char *comandoAGuardar)
{
    FILE *archivoDataBase = fopen(NOMBRE_DE_ARCHIVO, "a");
    if (archivoDataBase == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }
    fprintf(archivoDataBase, "%s|%s\n", id, comandoAGuardar);
    fclose(archivoDataBase);
}

/* Descripcion
 * Nombre de la función: obtenerComando().
 * Tipo de función: void.
 * Parámetros: puntero idDelUsuario tipo char.
 * Dato de retorno: Sin valor de retorno;
 * Descripción de la función: abre el archivo donde se almacenanllos comandos y lasID's luego compara cada ID
 *                            con la ID solicitada por el usuario, si coincide con una se imprime el mensaje asociado por pantalla.
 *
 */

void obtenerComando(char *idDelUsuario)
{
    char lecturaDeLinea[MAX_SIZE];
    char idLeido[9];
    FILE *archivoDataBase = fopen(NOMBRE_DE_ARCHIVO, "r");
    if (archivoDataBase == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }
    while (fgets(lecturaDeLinea, MAX_SIZE, archivoDataBase))
    {
        sscanf(lecturaDeLinea, "%8[^|]", idLeido); // Leer hasta el delimitador '|'
        if (strcmp(idLeido, idDelUsuario) == 0)
        {
            char *comandoObtenido = strchr(lecturaDeLinea, '|'); // Encontrar el delimitador '|'
            if (comandoObtenido != NULL)
            {
                comandoObtenido++; // Saltar el carácter '|'
                printf("comando obtenido: %s", comandoObtenido);
                fclose(archivoDataBase);

                // Preguntar si quiere serializar el mensaje Obtenido
                int opcionPreguntaDeSerializacion = 0;
                printf("\n¿Serializar comando?\n");
                printf("1. Si 2. No : \n");
                scanf("%d", &opcionPreguntaDeSerializacion);
                if (opcionPreguntaDeSerializacion == 1)
                {
                    serializar_comando(comandoObtenido);
                }
                else
                {
                    return;
                }
            }
            fclose(archivoDataBase);
            return;
        }
    }
    // Si no se encontró la ID
    printf("No se encontró el comando con la ID %s.\n", idDelUsuario);
    fclose(archivoDataBase);
}

/* Descripcion
 * Nombre de la función: menu().
 * Tipo de función: void.
 * Parámetros: sin parámetros.
 * Dato de retorno: Sin valor de retorno.
 * Descripción de la función: es un switch en el que escanea la opción que dió el usuario y selecciona las distintas opciones.
 *
 */

void menu()
{
    int opcion;
    char comando[MAX_SIZE];
    char idDebusqueda[9];

    do
    {
        printf("\n----- Menu -----\n");
        printf("1. Deserializar comando \n");
        printf("2. Serializar comando \n");
        printf("3. Recuperar comando con clave  \n");
        printf("4. Salir \n");
        printf("Seleccione opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            // Pedimos el comando
            printf("Ingrese comando: ");
            fgets(comando, MAX_SIZE, stdin);
            deserializar_comando(comando);
            break;
        case 2:
            printf("\nIngrese mensaje: ");
            fgets(comando, MAX_SIZE, stdin);
            serializar_comando(comando);
            break;
        case 3:
            printf("ingrese la id del comando: ");
            scanf("%8s", idDebusqueda);
            obtenerComando(idDebusqueda);
            break;
        }

    } while (opcion != 4);
}

// Funcion principal
int main()
{
    menu(); // Iniciamos Todo
    return 0;
}