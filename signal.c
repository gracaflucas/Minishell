/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:09:44 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/06 17:09:53 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int signal)
{
	if (signal == SIGINT)
	{
		write (STDOUT_FILENO, "\nPrompt > ", 10);
		//rl_replace_line("", 0);
		//rl_on_new_line();
		//rl_redisplay();
	}
}

// write (STDOUT_FILENO, "\nPrompt > ", 10);
