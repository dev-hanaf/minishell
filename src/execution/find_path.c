#include "minishell.h"
void clean_exit(int e)
{
    exit(e);
}
void	ms_error(char *str, int e)
{
	if (e == 127)
	{
		ft_putstr_fd("ms: ", 2);
		ft_putstr_fd(str, 2);
		if (ft_strchr(str, '/'))
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found \n", 2);
	}
	else if (e == 1026)
	{
		ft_putstr_fd("ms: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory \n", 2);
		e = 126;
	}
	else
	{
		ft_putstr_fd("ms: ", 2);
		perror(str);
	}
	clean_exit(e);
}

void	free_data(char **data, char *cmd)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
	free(cmd);
}

char	*ft_look_in_path(char *cmd, char *path)
{
	char	*cmd_path;
	char	**paths;
	char	*cmd2;
	int		i;

	i = -1;
	if (!cmd || !path)
		ms_error(cmd, 127);
	paths = ft_split(path + 5, ':');
	cmd2 = ft_strjoin("/", cmd);
	if (!paths || !cmd2)
		ms_error("split", 1);
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], cmd2);
		if (!access(cmd_path, F_OK))
		{
			if (!access(cmd_path, X_OK))
				return (free_data(paths, cmd2), cmd_path);
			else
				ms_error(cmd_path, 126);
		}
		free(cmd_path);
	}
	return (free_data(paths, cmd2), ms_error(cmd, 127), NULL);
}

void	check_dir(char *cmd)
{
	int	fd;

	fd = open(cmd, __O_DIRECTORY);
	if (fd != -1)
		ms_error(cmd, 1026);
	close(fd);
}

char	*get_cmd_path(char *cmd, char **env)
{
	char	*path;

	path = NULL;
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
			path = *env;
		env++;
	}
	if (!cmd || !*cmd)
		clean_exit(0);
	if (ft_strchr(cmd, '/') || !path)
	{
		if (!access(cmd, F_OK))
		{
			check_dir(cmd);
			if (!access(cmd, X_OK))
				return (cmd);
			else
				ms_error(cmd, 126);
		}
		ms_error(cmd, 127);
	}
	return (ft_look_in_path(cmd, path));
}
