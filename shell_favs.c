#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
 
fav_command_t *fav_list = NULL;
int fav_count = 0;
 
void add_fav_command(const char *cmd) {
    // Verifica si el comando ya existe
    fav_command_t *current = fav_list;
    while (current) {
        if (strcmp(current->command, cmd) == 0) {
            return; // El comando ya está en la lista
        }
        current = current->next;
    }
 
    // Añade el nuevo comando
    fav_command_t *new_fav = (fav_command_t *)malloc(sizeof(fav_command_t));
    new_fav->id = ++fav_count;
    strcpy(new_fav->command, cmd);
    new_fav->next = fav_list;
    fav_list = new_fav;
}
 
void show_fav_commands() {
    fav_command_t *current = fav_list;
    if (!current) {
        printf("No hay comandos favoritos guardados.\n");
        return;
    }
    while (current) {
        printf("%d: %s\n", current->id, current->command);
        current = current->next;
    }
}
 
void remove_fav_command(int num) {
    fav_command_t *current = fav_list;
    fav_command_t *prev = NULL;
 
    while (current) {
        if (current->id == num) {
            if (prev) {
                prev->next = current->next;
            } else {
                fav_list = current->next;
            }
            free(current);
            printf("Comando %d eliminado de los favoritos.\n", num);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Comando número %d no encontrado en favoritos.\n", num);
}
 
void search_fav_command(const char *substr) {
    fav_command_t *current = fav_list;
    int found = 0;
 
    while (current) {
        if (strstr(current->command, substr)) {
            printf("%d: %s\n", current->id, current->command);
            found = 1;
        }
        current = current->next;
    }
 
    if (!found) {
        printf("No se encontraron comandos que contengan '%s'.\n", substr);
    }
}
 
void execute_fav_command(int num) {
    fav_command_t *current = fav_list;
 
    while (current) {
        if (current->id == num) {
            system(current->command);  // Ejecuta el comando
            return;
        }
        current = current->next;
    }
 
    printf("Comando número %d no encontrado en favoritos.\n", num);
}
 
void save_fav_commands(const char *path) {
    FILE *file = fopen(path, "w");
    if (!file) {
        printf("Error al abrir el archivo %s para escribir.\n", path);
        return;
    }
 
    fav_command_t *current = fav_list;
    while (current) {
        fprintf(file, "%d:%s\n", current->id, current->command);
        current = current->next;
    }
 
    fclose(file);
    printf("Favoritos guardados en %s\n", path);
}
 
void load_fav_commands(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("Error al abrir el archivo %s para leer.\n", path);
        return;
    }
 
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *cmd = strchr(line, ':');
        if (cmd) {
            *cmd = '\0';
            int id = atoi(line);
            cmd++;
            cmd[strlen(cmd) - 1] = '\0';  // Elimina el carácter de nueva línea
            add_fav_command(cmd);
            fav_list->id = id;  // Restaura el ID original
        }
    }
 
    fclose(file);
    printf("Favoritos cargados desde %s\n", path);
}
 
void clear_fav_commands() {
    fav_command_t *current = fav_list;
    while (current) {
        fav_command_t *next = current->next;
        free(current);
        current = next;
    }
    fav_list = NULL;
    fav_count = 0;
    printf("Todos los comandos favoritos han sido eliminados.\n");
}

