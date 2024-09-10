#ifndef SHELL_H
#define SHELL_H

#include "source.h"
#include <stddef.h>
int parse_and_execute(struct source_s *src);

typedef struct fav_command {
 int id;
 char command[256]; //cadena para el comando
 struct fav_command *next; //lista enlazada
} fav_command_t;

void print_prompt1(void);
void print_prompt2(void);
char *read_cmd(void);
void add_fav_command(const char *cmd);
void show_fav_commands(); 
void remove_fav_command(int num); 
void search_fav_command(const char *substr); 
void execute_fav_command(int num); 
void save_fav_commands(const char *path); 
void load_fav_commands(const char *path); 
void clear_fav_commands();

#endif /* SHELL_H */

