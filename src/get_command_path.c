
#include "../inc/pipex.h"

static int get_cmd_hijo(const char *comand, int *pipefd);

char *get_command_path(const char *command, char *result)
{
    int pipefd[2];
    pid_t pid;
//    char *result = NULL;
    int status;
    char buffer[1024];
    size_t numread;

    if (pipe(pipefd) == -1)
        ft_error(2,"fallo al crear pipe", 2);
    pid =fork();
    if (pid == -1)
        ft_error(2,"fallo al crear fork", 2);
    if (pid == 0)
    status = get_cmd_hijo(command, pipefd);
    else
    {
        wait(&status);
        numread = read(pipefd[0], buffer, 1023);
        if (numread > 0)
        {
            buffer[numread] = '\0';
            result = ft_strdup(buffer);
        }
        else
            ft_error(2, "no se encuentra el comando", 2);
    }
    return (result);
}

static int get_cmd_hijo(const char *comand, int *pipefd)
{
    char *commands[3]; 
    commands[0] = "which";
    commands  [1] = (char *) comand ;
    commands [2] = NULL;

    if (!comand)
        ft_error(2, "no se ha añadido ningun comando", 2);
    close(pipefd[0]);
    if (dup2(pipefd[1],STDOUT_FILENO) < 0)
        ft_error(2, "error al duplicar", 2);
    close (pipefd[1]);
    if (execve("/usr/bin/which", commands, NULL) < 0)
        ft_error(2, "error al ejecutar which",2);
    return (0);    
}

void  ft_error(int status, char *str, int Nexit)
{
	
	if (Nexit == 1)
	{
		ft_printf("%s",str);
		exit(status);
	}
	if (Nexit == 2)
	{
		perror(str);
		exit(status);
	}

}