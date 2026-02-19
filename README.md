*Este proyecto ha sido creado como parte del currículo de 42 por rosvela.*

## Descripción
El objetivo de este proyecto es programar una función que devuelva una línea leída de un descriptor de archivo (file descriptor). Este reto introduce el concepto de **variables estáticas** en C y la gestión eficiente de memoria mediante **listas enlazadas** para manejar el buffer de lectura de manera dinámica.

La función `get_next_line` permite leer el contenido de un archivo línea a línea (hasta encontrar un salto de línea `\n` o el final del archivo `EOF`), lo cual es mucho más eficiente que leer el archivo completo en memoria, especialmente cuando se trabaja con archivos de gran tamaño.

## Instrucciones

### Compilación
El proyecto debe compilarse con los indicadores habituales y el flag `-D BUFFER_SIZE=n`, que define el tamaño del buffer:

Para la versión obligatoria:

```bash
cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

Para la versión bonus (soporte para múltiples FD):

```bash
cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c
```

### Ejecución

Para utilizar la función en tu propio código, incluye la cabecera correspondiente:

#include "get_next_line.h" 

o

#include "get_next_line_bonus.h"

## Algoritmo y Decisiones Técnicas

Se utiliza una lista enlazada (t_list) para almacenar fragmentos de texto leídos del archivo.

- Cada nodo contiene hasta BUFFER_SIZE bytes.
- Permite leer líneas de cualquier longitud, incluso mayores que BUFFER_SIZE.
- Mantiene contenido sobrante para la próxima llamada.

En la versión bonus, se usa un array de listas estáticas (lst[FD_MAX]) para manejar múltiples file descriptors simultáneamente sin interferencia.

### Flujo del algoritmo

1. Validación inicial: se comprueba que el fd es válido y BUFFER_SIZE > 0. En bonus, además que fd < FD_MAX.
2. Lectura del archivo (read_text): se leen bloques de tamaño BUFFER_SIZE hasta encontrar un \n o EOF. Cada bloque se almacena en la lista.
3. Construcción de la línea (create_line): se recorren los nodos concatenando caracteres hasta el primer \n.
4. Limpieza de la lista (clean_lst): se extrae cualquier contenido que quede después del \n del último nodo, se liberan los nodos antiguos, y se guarda el sobrante en un nuevo nodo si existe.
5. Devolución de la línea: la línea construida se devuelve y la lista queda lista para la siguiente llamada.

### Manejo de casos especiales

- Archivo vacío → devuelve NULL.
- Línea sin \n al final → se devuelve al final del archivo y la lista se limpia.
- Múltiples saltos de línea seguidos → cada llamada devuelve una línea, incluso vacía.
- BUFFER_SIZE pequeño → múltiples nodos permiten leer la línea fragmentada sin perder información.

### Justificación técnica

- La lista enlazada permite almacenar fragmentos dinámicos sin limitar la longitud de la línea.
- Guardar el sobrante en el último nodo asegura que no se pierda información entre llamadas.
- El array de listas en el bonus permite lectura simultánea de varios archivos.
- La liberación de memoria en errores y EOF evita memory leaks y dangling pointers.

## Recursos

### Documentación Oficial
- [Manual de C (man pages)](https://man7.org/linux/man-pages/man3/).
- [Documentación de funciones estáticas](https://www.geeksforgeeks.org/c/static-variables-in-c/).
- Subject oficial (42).

### Uso de IA en este Proyecto

La IA se utilizó en las siguientes tareas:

- Sugerencias de casos límite y testing

- Consulta de documentación

- Mejora de redacción del README

Toda la lógica e implementación del código fue desarrollada manualmente.

## Autor

- **rosvela** - Estudiante de 42 Madrid

---
