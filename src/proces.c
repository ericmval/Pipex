
#include "../inc/pipex.h"

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

char	*check_access(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (cmd);
	else if (access(cmd, F_OK) == 0)
		exit (126);
	return (NULL);
}
