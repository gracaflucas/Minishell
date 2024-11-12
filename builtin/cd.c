/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:22:23 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/06 11:55:14 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *get_env_ptr(char *var, char **envp);
int	ft_cd(char *path, t_shell *shell)
{
	char	*old_pwd;
	char	*new_pwd;

	if (path == NULL)
	{
		path = get_env_ptr("HOME", shell->envp);
		if (path == NULL)
			return (printf("Error: HOME unset\n"), 1);
	}
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		path = get_env_ptr("OLDPWD", shell->envp);
		if (path == NULL)
			return (printf("Error: OLDPWD unset\n"), 1);
	}
	old_pwd = get_env_ptr("PWD", shell->envp);
	if (chdir(path) != 0)
		return (printf("cd: %s: %s\n", path, strerror(errno)), 1);
	new_pwd = ft_pwd();
	if (!new_pwd)
		return (1);
	if (old_pwd != NULL)
		ft_setenv("OLDPWD", old_pwd, shell, 1);
	ft_setenv("PWD", new_pwd, shell, 1);
	return (free (new_pwd), 0);
}

static char *get_env_ptr(char *var, char **envp)
{
	int	index;

	index = find_env(envp, var);
    if (index == -1)
		return (NULL);
	return (envp[index] + ft_strlen(var) + 1);
}
