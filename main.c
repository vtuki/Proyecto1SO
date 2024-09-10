# include <stdio.h> 
# include <stdlib.h> 
# include <errno.h> 
# include <string.h> 
#include "shell.h"
#include "source.h"
#include "parser.h"
#include "executor.h"

int main(int argc, char **argv) {
 char *cmd; 
 do { 
     print_prompt1(); 
     cmd = read_cmd(); 
     if (!cmd) { 
        exit(EXIT_SUCCESS); 
     } 
     if (cmd[0] == '\0' || strcmp(cmd, "\n") == 0) { 
           free(cmd); 
           continue; 
     } 
     if (strcmp(cmd, "exit\n") == 0) { 
           free(cmd); 
           break; 
     }
     // Verificar si el comando no es "favs" antes de aregarlo a favoritos
     if (strncmp(cmd, "favs", 4) != 0) {
        add_fav_command(cmd);
     }
     // Aquí añadimos el manejo de comandos `favs` 
     if (strncmp(cmd, "favs", 4) == 0) {
         if (strstr(cmd, "crear")) { 
            char *path = strtok(cmd + 6, " "); 
            save_fav_commands(path); 
         } else if (strstr(cmd, "mostrar")) { 
            show_fav_commands(); 
         } else if (strstr(cmd, "eliminar")) { 
            char *nums = strtok(cmd + 9, ","); 
            while (nums != NULL) { 
                  int num = atoi(nums); 
                  remove_fav_command(num); 
                  nums = strtok(NULL, ","); 
            } 
         } else if (strstr(cmd, "buscar")) { 
            char *search_term = strtok(cmd + 7, " "); 
            search_fav_command(search_term); 
         } else if (strstr(cmd, "borrar")) { 
           clear_fav_commands(); 
         } else if (strstr(cmd, "guardar")) { 
           save_fav_commands("ruta/misfavoritos.txt"); 
         } else if (strstr(cmd, "cargar")) { 
           load_fav_commands("ruta/misfavoritos.txt"); 
         } else if (strstr(cmd, "ejecutar")) { 
           int num = atoi(cmd + 8); execute_fav_command(num); 
         } 
      } else { 
         // Procesa los comandos normales 
         struct source_s src; 
         src.buffer = cmd; 
         src.bufsize = strlen(cmd); 
         src.curpos = INIT_SRC_POS; 
         parse_and_execute(&src); 
      } free(cmd); 
   } while (1); 
   exit(EXIT_SUCCESS); 
}


char *read_cmd(void) {
    char buf[1024];
    char *ptr = NULL;
    size_t ptrlen = 0;

    while (fgets(buf, sizeof(buf), stdin)) {
        int buflen = strlen(buf);

        if (!ptr) {
            ptr = malloc(buflen + 1);
        } else {
            char *ptr2 = realloc(ptr, ptrlen + buflen + 1);
            if (ptr2) {
                ptr = ptr2;
            } else {
                free(ptr);
                ptr = NULL;
            }
        }

        if (!ptr) {
            fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
            return NULL;
        }

        strcpy(ptr + ptrlen, buf);

        if (buf[buflen - 1] == '\n') {
            if (buflen == 1 || buf[buflen - 2] != '\\') {
                return ptr;
            }
            ptr[ptrlen + buflen - 2] = '\0';
            buflen -= 2;
            print_prompt2();
        }

        ptrlen += buflen;
    }

    return ptr;
}

int parse_and_execute(struct source_s *src)
{
    skip_white_spaces(src);

    struct token_s *tok = tokenize(src);

    if(tok == &eof_token)
    {
        return 0;
    }

    while(tok && tok != &eof_token)
    {
        struct node_s *cmd = parse_simple_command(tok);

        if(!cmd)
        {
            break;
        }

        do_simple_command(cmd);
        free_node_tree(cmd);
        tok = tokenize(src);
    }

    return 1;
}

