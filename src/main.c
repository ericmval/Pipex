
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

int	main(int argc, char **argv)
{
	int pipefd[2];
	pid_t pid;
	int 	status;
	

	if (argc != 5)
		ft_error(1, HELPMSG, 1);
//	ft_printf("%s  \n",env[5]);
	if (pipe(pipefd) == -1)
		ft_error(2,"fallo al crear pipe", 2);
	pid = fork();
	if (pid == -1)
		ft_error(2,"fallo al crear fork", 2);
	if (pid >= 0)
	{
		porces_child(argv[1],argv[2], pipefd);
		ft_printf("aqui empieza porceso hijo\n");
		status = 0;
	}
	else
	{
		wait(&status);
		ft_printf("aqui empieza porceso padre\n");
	}
	printf("%d\n",pid);
	
	ft_printf("%s %s %s %s \n",argv[1],argv[2],argv[3],argv[4]);
//	ft_printf("%s  \n",env[3]);
	return (0);
}

int porces_child(char *file, char *cmd, int pipefd[2])
{
    int fd_file;
	char *binary = "/usr/bin/cat";
	

	ft_printf("%s  \n",cmd);
    fd_file = open(file, O_RDONLY);
	char *cmds[3] = {binary, file, NULL};
 //   if (fd_file < 0)
 //   	ft_error(-1, "errror al abrir el archivo", 2);
	if (dup2(fd_file, STDIN_FILENO) < 0 || dup2(pipefd[WRITE_END], STDOUT_FILENO) < 0)
		ft_error(-1 , "error al duplicar entrada o salida", 2);
	if (close(pipefd[READ_END]) < 0 )
		ft_error(-1,"erro al cerrar pipe de lectura", 2);
//	cmds = ft_split(cmd, ' ');
//	if (!cmds)
//		ft_error(-1, "error al reservar memoria", 2);
//	ft_printf("%s  \n",cmds);
    execve(binary, cmds, NULL);
    return (0);
}