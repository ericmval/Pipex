
#include "../inc/pipex.h"

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

int	main(int argc, char **argv, char *env[])
{
	pid_t pid;
	int 	status;
	
	if (argc != 5)
		ft_error(1, HELPMSG, 1);
	pid = fork();
	if (pid == -1)
		ft_error(2,"fallo al crear fork", 2);
	if (pid == 0)
		porces_child(argv[1],argv[2], env);
	else
	{
		wait(&status);
		pid = fork();
		if (pid == -1)
			ft_error(2,"fallo al crear fork", 2);
		if (pid == 0)
			porces_father("aux",argv[3], env, argv[4]);
		else
		{
			wait(&status);
			unlink("aux");
		}
		return (0);
	}
}

void porces_child(char *file, char *cmd, char **env)
{
    int fd_file;
	char *clean_cmd;

	fd_file = open("aux", O_WRONLY | O_CREAT, 0644);
	clean_cmd = ft_clean_cmd(cmd);
    dup2(fd_file, STDOUT_FILENO);
	if (execve(get_full_command(clean_cmd, env), get_second_execve(cmd, file), env) == -1)
		ft_error(2,"fallo al ejecutar execve", 2);
	exit(0);
}

void porces_father(char *file, char *cmd, char **env, char *endfile)
{
	char *clean_cmd;
	int fd_file;

	clean_cmd = ft_clean_cmd(cmd);
	fd_file = open(endfile, O_WRONLY | O_CREAT, 0644);
	dup2(fd_file, STDOUT_FILENO);
	if (execve(get_full_command(clean_cmd, env), get_second_execve(cmd, file), env) == -1)
		ft_error(2,"fallo al ejecutar execve", 2);
}
