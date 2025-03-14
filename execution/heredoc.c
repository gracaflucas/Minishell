/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alawrence <alawrence@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:24:12 by ana-lda-          #+#    #+#             */
/*   Updated: 2025/03/14 11:47:19 by alawrence        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	str_compare(char *s1, char *s2, int max)
{
	int	i;

	i = 0;
	while (i < max && *s1 && *s2 && s1[i] == s2[i])
		i++;
	if (sizeof_str(s1, '\0') == i && i == max)
		return (1);
	return (0);
}

/** @brief Handles a signal interrupt during heredoc processing.
 * Outputs a newline and exits the child process.
 *
 * @param n Signal number (ignored in this implementation).*/
void	quit_heredoc(int n)
{
	(void)n;
	write(1, "\n", 1);
	exit(0);
}

/** @brief Checks if a string contains quotes.
 * Determines whether a string has double (`"`) or single (`'`) quotes.
 *
 * @param s The string to check.
 * @return 0 if the string contains quotes, 1 otherwise.*/
int	have_quotes(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			return (0);
		i++;
	}
	return (1);
}

/** @brief Reads input and writes to a file descriptor until
 * a limiter is encountered.
 * Processes heredoc input, optionally expanding environment variables
 * if the limiter has no quotes.
 *
 * @param pipe_state Pipe state containing the current output file descriptor.
 * @param limiter The string that terminates heredoc input.
 * @param env Environment variables for variable expansion.
 * @param is_expandable Flag indicating whether variable expansion
 * is enabled.*/
void	read_and_write(int std_out, char *limiter, t_env *env, int is_expandable)
{
	char	*buf;
	int		f_arr[3];

	limiter = remove_quotes_from_str(limiter, 0, 0, 0);
	while (1)
	{
		buf = readline(">> ");
		if (!buf || str_compare(limiter, buf, sizeof_str(buf, '\n')))
		{
			free(buf);
			break ;
		}
		if (is_expandable)
		{
			buf[sizeof_str(buf, '\n')] = '\0';
			ft_memset(f_arr, 0, 3 * sizeof(int));
			buf = recursively_expand_vars(buf, env, 0, f_arr);
			ft_memset(f_arr, 0, 3 * sizeof(int));
			buf = recursively_expand_vars(buf, env, 1, f_arr);
		}
		write(std_out, buf, sizeof_str(buf, '\0'));
		write(std_out, "\n", 1);
		free(buf);
	}
	free(limiter);
}

/** @brief Executes a heredoc operation.
 * Creates a subprocess to read heredoc input until the limiter is encountered.
 * Handles variable expansion, writes input to a pipe,
 * and sets pipe state for further execution.
 *
 * @param limiter The delimiter string that terminates heredoc input.
 * @param pipe_state Pipe state to manage heredoc input and output descriptors.
 * @param env Environment variables for variable expansion.
 * @return 0 if heredoc was processed successfully, non-zero on error.*/
/* int	exec_here_doc(char *limiter, t_pipe_state *pipe_state, t_env *env)
{
	pid_t	pid;
	int		out_fd[2];

	pipe(out_fd);
	pid = fork();
	printf("entrou no heredoc %i", env->exit_status);
	signal(SIGINT, SIG_IGN);
	if (!pid)
	{
		signal(SIGINT, quit_heredoc);
		safe_close(out_fd[0]);
		read_and_write(out_fd[1], limiter, env, have_quotes(limiter));
		exit(1);
	}
	waitpid(pid, &env->exit_status, 0);
	safe_close(out_fd[1]);
	pipe_state->current_input_fd = out_fd[0];
	pipe_state->heredoc_status = (WEXITSTATUS(env->exit_status)) - 1;
	if (pipe_state->heredoc_status < 0)
		pipe_state->heredoc_status += 2;
	pipe_state->second_heredoc_status = env->exit_status;
	return (pipe_state->heredoc_status);
} */
int exec_here_doc(char *limiter, t_pipe_state *pipe_state, t_env *env)
{
    pid_t pid;
    int out_fd[2];

    pipe(out_fd);
    pid = fork();
    signal(SIGINT, SIG_IGN);
    if (!pid)
    {
        signal(SIGINT, quit_heredoc);
        safe_close(out_fd[0]);
        read_and_write(out_fd[1], limiter, env, have_quotes(limiter));
        exit(1);
    }
    waitpid(pid, &env->exit_status, 0);
    safe_close(out_fd[1]);
    pipe_state->current_input_fd = out_fd[0];
    pipe_state->heredoc_status = (WEXITSTATUS(env->exit_status)) - 1;
    if (pipe_state->heredoc_status < 0)
        pipe_state->heredoc_status += 2;
    pipe_state->second_heredoc_status = env->exit_status;
    return (pipe_state->heredoc_status);
}

