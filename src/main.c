
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
	int pipefd[2];
	pid_t pid;
	int 	status;
	
	if (argc != 5)
		ft_error(1, HELPMSG, 1);
	if (pipe(pipefd) == -1)
		ft_error(2,"fallo al crear pipe", 2);
	pid = fork();
	if (pid == -1)
		ft_error(2,"fallo al crear fork", 2);
	if (pid == 0)
		porces_child(argv[1],argv[2], pipefd, env);
	else
	{
		wait(&status);
		ft_printf("aqui empieza porceso padre\n");
		porces_father(argv[4],argv[3],pipefd,env);
		ft_printf("%s %s %s %s \n",argv[1],argv[2],argv[3],argv[4]);
		return (0);
	}
}

void porces_child(char *file, char *cmd, int pipefd[2], char **env)
{
//    int fd_file;
	char *clean_cmd;
//	char **dirt_cmd;
//	if (!ft_strchr(cmd, 32))
//		clean_cmd = cmd;
//	else
//	{
//		dirt_cmd = ft_split(cmd, 32);
//		clean_cmd = dirt_cmd[0];
//	}
	clean_cmd = ft_clean_cmd(cmd);
	close(pipefd[0]);  // Cierra el extremo de lectura no utilizado
    dup2(pipefd[1], STDOUT_FILENO);  // Redirige stdout al extremo de escritura de la tubería
    close(pipefd[1]);  // Ya no se necesita después de dup2

//	pipefd[0] = 0;
//	pipefd[1] = 1;
//	char *fully;

	ft_printf("%d %d \n",pipefd[0],pipefd[1]);
//  fd_file = open(file, O_RDONLY);
//  if (fd_file < 0)
//  ft_error(-1, "errror al abrir el archivo", 2);
//	if (dup2(fd_file, STDIN_FILENO) < 0 || dup2(pipefd[WRITE_END], STDOUT_FILENO) < 0)
//		ft_error(-1 , "error al duplicar entrada o salida", 2);
//	if (close(pipefd[READ_END]) < 0 )
//		ft_error(-1,"erro al cerrar pipe de lectura", 2);
//	if (close( STDOUT_FILENO) < 0 )
//		ft_error(-1,"erro al cerrar pipe de lectura", 2);

	ft_printf("termina el hijo antes del execve\n");
	if (execve(get_full_command(clean_cmd, env), get_second_execve(cmd, file), env) == -1)
		ft_error(2,"fallo al ejecutar execve", 2);
}

void porces_father(char *file, char *cmd, int pipefd[2], char **env)
{

}
