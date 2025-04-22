#ifndef MAIN_H
#define MAIN_H

/* === Librairies autorisées === */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* === Fonctions utilitaires === */
char **_realloc_args(char **args, int old_size, int new_size);
char *get_path_from_env(char **envp);

/* === Fonctions principales === */
void remove_trailing_newline(char *line);
char **parse_line(char *line);
char *find_full_path(char *command, char **envp);
int execute_command(char *command, char **args, char **envp);
int handle_builtin(char **args, char **envp, char *line);


#endif /* MAIN_H */
