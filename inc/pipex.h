
#ifndef PIPEX_H
# define PIPEX_H

//Para open, close, read, write, unlink, access, dup , dup2 fork pipe ecexve
# include <unistd.h>
# include <fcntl.h>
//Para malloc, free exit
# include <stdlib.h>
//Para perror
# include <stdio.h>
//Para strerror
# include <string.h>
//Para acceder a los codigos de error de strerror
# include <errno.h>
//Para wait wait pid
# include <sys/wait.h>
# include "../libs/otherproject/libft/libft.h"
# include "../libs/otherproject/printf/ft_printf.h"

# define HELPMSG "los argumentos tienen que ser 4 \n\
ejemplo de uso:\npipex archivo1 comando1 comando2 archivo2\n"

# define READ_END 0
# define WRITE_END 1

void  ft_error(int status, char *str, int exit);
void porces_child(char *file, char *cmd, int pipefd[2], char **env);
char	*take_string(char **split, char *cmd);
char	*get_full_command(char *cmd, char *env[]);
char	*check_access(char *cmd);

#endif