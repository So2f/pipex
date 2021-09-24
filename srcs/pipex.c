/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-kar <soel-kar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 20:55:22 by soel-kar          #+#    #+#             */
/*   Updated: 2021/09/23 22:27:57 by soel-kar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_cmd1(t_pipex *p)
{
	dup2(p->file1, 0);
	dup2(p->fd[1], 1);
	close(p->fd[1]);
	close(p->fd[0]);
	execve(p->cmd1, p->cmd_arg1, p->env);
}

void	execute_cmd2(t_pipex *p)
{
	dup2(p->file2, 1);
	dup2(p->fd[0], 0);
	close(p->fd[0]);
	execve(p->cmd2, p->cmd_arg2, p->env);
}

void	pipex(t_pipex *p)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		show_error("Error: Something went wrong with fork()", 1);
	else if (pid == 0)
		execute_cmd1(p);
	close(p->fd[1]);
	pid = fork();
	if (pid == 0)
		execute_cmd2(p);
	close(p->fd[0]);
	waitpid(p->fd[0], &(p->fd_pid), 0);
	waitpid(p->fd[1], &(p->fd_pid), 0);
}

void	get_cmd(t_pipex **p)
{
	if ((*p)->file1 < 0)
	   show_error("Error: failed to open file 1.",1 );
	if ((*p)->file2 < 0)
	    show_error("Error: failed to open file 2.",1);
	(*p)->cmd_arg1 = ft_split((*p)->cmd1, ' ');
	get_cmd_path(p, 1);
	(*p)->cmd_arg2 = ft_split((*p)->cmd2, ' ');
	get_cmd_path(p, 2);
}

int	main(int argc, char *argv[], char **env)
{
	t_pipex	*p;

	p = NULL;
    if (argc == 5)
    {
        p = (t_pipex *)malloc(sizeof(t_pipex));
        if ((pipe(p->fd) == -1))
            show_error("Error: Something went wrong with pipe.", 1);
		p->file1 = open(argv[1], O_RDONLY);
		p->file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		p->env = env;
		p->cmd1 = argv[2];
		p->cmd2 = argv[3];
		get_cmd(&p);
		pipex(p);
		close(p->file1);
		close(p->file2);
    }
	else
		show_error("ERROR: Usage ->./pipex file1 cmd1 cmd2 file2'.", 1);
	if (WIFEXITED(p->fd_pid))
		return (WEXITSTATUS(p->fd_pid));
	return (0);
}