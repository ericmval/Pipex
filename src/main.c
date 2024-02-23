
#include "../inc/pipex.h"

/*
hace un primer checheo,luego hace un fork , en el primer fork
hace el proceso hijo y luego espera a que termine.
Luego empieza el porceso padre y cuando termina borra el archivo aux
*/
int	main(int argc, char **argv, char *env[])
{
	pid_t pid;
	int 	status;
	
	first_checker(argc,argv);
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
		wait(&status);
		unlink("aux");
		return (0);
	}
}
/*
crea un archivo aux  donde guardar el resultado de execve a traves
de un duplicado de standart out con un dup2
*/
void porces_child(char *file, char *cmd, char **env)
{
    int fd_file;
	char *clean_cmd;

	fd_file = open("aux", O_WRONLY | O_CREAT, 0644);
	if (fd_file == -1)
		ft_error(1,"error al abrir archivo", 2);
	clean_cmd = ft_clean_cmd(cmd);
    dup2(fd_file, STDOUT_FILENO);
	if (execve(get_full_command(clean_cmd, env), get_second_execve(cmd, file), NULL) == -1)
		ft_error(2,"fallo al ejecutar execve", 2);
	exit(0);
}
/*
se crea un archivo (si no existe se crea) con el nombre de la ultima 
variable de entrada y se duplica la salida standart out que da el execve
que se le hace al archivo aux creado en proces_child
*/
void porces_father(char *file, char *cmd, char **env, char *endfile)
{
	char *clean_cmd;
	int fd_file;

	clean_cmd = ft_clean_cmd(cmd);
	fd_file = open(endfile, O_WRONLY | O_CREAT, 0644);
	if (fd_file == -1)
		ft_error(1,"error al abrir archivo", 2);
	dup2(fd_file, STDOUT_FILENO);
	if (execve(get_full_command(clean_cmd, env), get_second_execve(cmd, file), NULL) == -1)
		ft_error(2,"fallo al ejecutar execve", 2);
}
/*
chequea que hay el numero de argumentos exacto al iniciar el programa
tambien chechea si se puede abrir el primer archivo*/
void first_checker(int argc, char **argv)
{
	if (argc != 5)
		ft_error(1, HELPMSG, 1);
	if (access(argv[1],R_OK) != 0 )
		ft_error(126, "No se puede abrir el primer archivo ", 2);
	

}
