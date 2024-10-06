# Tarea 1 - Estructura de Datos y Algoritmos

## Descripción General

Este programa fue desarrollado como parte de la asignatura IIE-344: Estructura de Datos y Algoritmos en la **Universidad de La Frontera**. Su objetivo es permitir la serialización y deserialización de comandos en el formato de protocolo **RESP 2.0** (REdis Serialization Protocol). Además, ofrece la funcionalidad de almacenar y recuperar comandos utilizando una clave única para cada uno.

## Autores

- **Benjamín Fuentes** (b.fuentes10@ufromail.cl)
- **Maximiliano Ortúzar** (m.ortuzar01@ufromail.cl)

## Fecha

06/10/2024

## Funcionalidades

1. **Deserializar Comando**: 
   - Interpreta el tipo de dato de un comando en formato RESP 2.0 (`Simple String`, `Error`, `Integer`, `Array`, `Bulk String`) y lo muestra en pantalla.
   - Pregunta al usuario si desea guardar el comando con una clave identificadora.

2. **Serializar Comando**:
   - Convierte una cadena ingresada por el usuario a uno de los tipos de datos del protocolo RESP (`Simple String`, `Error`, `Bulk String`).

3. **Almacenar Comando**:
   - Permite guardar un comando serializado junto con una clave en un archivo de base de datos.

4. **Recuperar Comando por Clave**:
   - Busca en la base de datos un comando usando una clave proporcionada por el usuario. Si se encuentra, se muestra y se da la opción de serializarlo nuevamente.

5. **Menú Interactivo**:
   - Un menú en consola que permite al usuario seleccionar la operación que desea realizar: deserializar, serializar, guardar o recuperar comandos.

## Estructura del Código

- **sacar_r_n()**: Elimina los caracteres CRLF (`\r\n`) de los comandos.
- **deserializar_comando()**: Deserializa un comando RESP 2.0 y determina su tipo de dato.
- **serializar_comando()**: Serializa un comando ingresado por el usuario en formato RESP.
- **guardarComando()**: Guarda un comando serializado con una clave en un archivo.
- **obtenerComando()**: Recupera un comando almacenado usando una clave y da la opción de serializarlo.
- **menu()**: Menú interactivo que permite la ejecución de las distintas funciones del programa.

## Archivos

- **comandosRESP2.0.txt**: Archivo donde se almacenan los comandos serializados junto con su clave.

## Cómo ejecutar

Compilar el programa utilizando un compilador de C++ como `g++`:

```bash
g++ -o tarea1Main tarea1Main.cpp
