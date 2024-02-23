
#include "../inc/pipex.h"
/*
entra como primer parametro una lista con las posibles rutas
extraidas de PATH,le añade a cada posible ruta el comando 
introducido por el usuario , si esta se puede ejecutar la terorna
como salida de funcion
*/
char	*take_string(char **split, char *cmd)
{
	int		i;
	char	*t1;
	char	*t2;

	i = -1;
	t1 = NULL;
	t2 = NULL;
	if (!split)
		ft_error(1,"error indeterminado", 2);
	while (split[++i])
	{
		t1 = ft_strjoin(split[i], "/");
		if (!t1)
			ft_error(1,"al usar malloc", 2);
		t2 = ft_strjoin(t1, cmd);
		if (!t2)
			ft_error(1,"al usar malloc", 2);
		free(t1);
		if (check_access(t2))
			return (t2);
		free(t2);
	}
	ft_error(1,"comando no encontrado", 2);
	return (NULL);
}
/*
comprueba si el comando empieza por / (ruta absoluta) y 
verifica si es  ejecutable.
comprueba si el comando empieza por ./ (ruta relativa) y
verifica si es ejecutable.
Busca entre todas la variables de entorno si 
alguna empieza por PATH, cuando la emcuentra crea un string
con la rutas de PATH y lo convierte en una lista de las posibles
rutas y lo pasa a la funcion  take_string
*/
char	*get_full_command(char *cmd, char *env[])
{
	int		i;
	char	*tmp;
	char	**split;

	i = -1;
	split = NULL;
	if (cmd[0] == '/')
		return (check_access(cmd));
	else if (cmd[0] == '.' && cmd[1] == '/')
		return (check_access(cmd + 2));
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
		{
			tmp = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			if (!tmp)
				ft_error(1,"al usar malloc", 2);
			split = ft_split(tmp, ':');
			free (tmp);
			break ;
		}
	}
	if (!split)
		ft_error(1,"al usar malloc", 2);
	return (take_string(split, cmd));
}
/*
verifica que el comando que se introduce se puede ejecutar.
Si se puede retorna el comando para ser usado
Si no  se puede retorna mensaje de error y sale del programa
*/
char	*check_access(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (cmd);
	else if (access(cmd, F_OK) == 0)
		exit (126);
	return (NULL);
}
/*
esta funcion se usa para crear una lista de el argumento
en primer lugar y luego los difrentes flags que tenga.
Es necesario en el segundo argumento de la funcion execve
*/
char	**get_second_execve(char *cmd, char *file)
{
	char	*str_mid;
	char	*str_mid2;
	char	**out;

	str_mid = ft_strjoin(cmd, " ");
	str_mid2 = ft_strjoin(str_mid, file);
	out = ft_split(str_mid2, 32);
	free (str_mid);
	free (str_mid2);
	return(out);
}
/*
comprueba si el comando introducido esta solo para
poder usarse como primer argumento de la funcion get_full_command
si no esta solo hace un split y retorna el primer elemento que 
corresponte al comando, ya que el resto son flags
 */
char	*ft_clean_cmd(char *cmd)
{
	char **dirt_cmd;
	char *clean_cmd;

	if (!ft_strchr(cmd, 32))
		return(cmd);
	else
	{
		dirt_cmd = ft_split(cmd, 32);
		clean_cmd = dirt_cmd[0];
		free (dirt_cmd);
		return (clean_cmd);
	}
}
/*
gestiona varias salidas de error para ahorrar espacio
si el ultimo parametro de la funcion es 1:
imprime solo el texto del parametro str
si el ultimo parametro de la funcion es 2:
imprime  el texto del parametro str y el mensaje de error predeterminado
*/
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