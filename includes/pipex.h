/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-kar <soel-kar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 20:55:47 by soel-kar          #+#    #+#             */
/*   Updated: 2021/09/23 22:40:42 by soel-kar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

typedef struct s_pipex
{
    char    *cmd1;
    char    *cmd2;
    char	**cmd_arg1;
	char	**cmd_arg2;
    char    **env;
    int     file1;
    int     file2;
    int     fd[2];
    int     fd_pid;
}				t_pipex;

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s1);

void	pipex(t_pipex *p);
void	execute_cmd1(t_pipex *p);
void	execute_cmd2(t_pipex *p);
void	check_pipex(t_pipex **p);
void	get_cmd_path(t_pipex **p, int cmd_new);
char	*get_env_path(char **env);
int		concatenate_paths(char *path, char **cmd_new, char *arg);
void	show_error(char *str, int error);
void	ft_putendl(char const *s);

#endif