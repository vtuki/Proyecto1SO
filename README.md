# Proyecto 1: Shell Básica con Comando de Favoritos (`favs`)

Este proyecto implementa una shell básica en C que permite ejecutar comandos de manera interactiva. Además, incluye un comando especial llamado `favs`, que facilita la gestión de comandos favoritos, permitiendo al usuario añadir, eliminar, modificar, buscar y ejecutar comandos almacenados previamente.

## Funcionalidades

### Shell Básica
- Ejecuta comandos ingresados por el usuario a través de un prompt interactivo.
- Permite gestionar procesos usando `fork()` y `exec()` para ejecutar comandos en paralelo.
- Soporta argumentos indeterminados y comunicación mediante pipes.

### Comando `favs`
- **Agregar** un nuevo comando a la lista de favoritos.
- **Mostrar** todos los comandos favoritos guardados.
- **Eliminar** un comando de la lista usando su ID.
- **Buscar** comandos en la lista usando subcadenas.
- **Ejecutar** un comando favorito por su ID.
- **Guardar** los comandos favoritos en un archivo.
- **Cargar** comandos favoritos desde un archivo previamente guardado.
- **Limpiar** toda la lista de comandos favoritos.

## Compilación y Ejecución

### 1. Compilación

Para compilar el proyecto, abre una terminal y navega hasta el directorio del proyecto. Luego, ejecuta el siguiente comando:

```bash
gcc -o shell main.c source.c scanner.c parser.c node.c executor.c prompt.c shell_favs.c

```bash
./shell
