/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-kar <soel-kar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 21:43:24 by soel-kar          #+#    #+#             */
/*   Updated: 2021/09/23 22:38:20 by soel-kar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_env_path(char **env)
{
	int		i;
	char	*new_path;

	i = 0;
	new_path = NULL;
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			new_path = ft_strdup(ft_strrchr(env[i], '=') + 1);
			break ;
		}
		i++;
	}
	return (new_path);
}

int	concatenate_paths(char *path, char **cmd_new, char *arg)
{
	char	*cmd;
	char	*tmp;

	cmd = ft_strjoin(path, "/");
	tmp = cmd;
	cmd = ft_strjoin(cmd, arg);
	free(tmp);
	if (open(cmd, O_RDONLY) > 0)
	{
		*cmd_new = ft_strdup(cmd);
		free(cmd);
		return (1);
	}
	free(cmd);
	return (0);
}

void	get_cmd_path(t_pipex **p, int cmd_new)
{
	int		i;
	char	*new_path;
	char	**split_path;
	int		check;

	check = 0;
	new_path = get_env_path((*p)->env);
	split_path = ft_split(new_path, ':');
	i = 0;
	while (split_path[i] && !check)
	{
		if (cmd_new == 1)
			check = concatenate_paths(split_path[i++], &(*p)->cmd1,
					(*p)->cmd_arg1[0]);
		else if (cmd_new == 2)
			check = concatenate_paths(split_path[i++], &(*p)->cmd2,
					(*p)->cmd_arg2[0]);
	}
	free(new_path);
	i = 0;
	while (split_path[i])
		free(split_path[i++]);
	free(split_path);
	if (!check)
		show_error("Command not found.", 127);
}

void	ft_putendl(char const *s)
{
	int		i;

	i = 0;
	if (s)
		while (s[i])
			write(1, &s[i++], 1);
	write(1, "\n", 1);
}

void	show_error(char *str, int err)
{
	ft_putendl(str);
	exit(err);
}

