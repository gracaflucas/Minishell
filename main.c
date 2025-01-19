/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:08:55 by lufiguei          #+#    #+#             */
/*   Updated: 2024/12/04 17:21:28 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO - CHECK_LINE
// execute_with_redirect;
// expand_vars_in_ast
// FINISH FUNCTION chech_file_permission
// TODO - recursively_expand_variables
// TODO - verifiar saidas de erro!
// comentei funcoes em: path utils, handle_heredoc e execution_manager para compilar ***
// leak em bash_exit, still reachable, provavelmente readfile

int	g_signal = 0;

int	main(int argc, char **argv, char **original_env)
{
	t_env	*env;

	(void)argv;
	setup_signal_handlers();
	env = malloc(sizeof(t_env));
	if (!isatty(1) || !isatty(0))
		return (free(env), 0);
	if (argc == 1 && init_environment(env, original_env))
	{
		run_minishell(env);
		cleanup_and_exit_shell(env, 0);
	}
	return (0);
}

/** @brief Main loop to run the minishell.
 * 
 * This function runs the interactive shell, repeatedly prompting 
 * the user for input with a `> ` prompt. 
 * It processes the input by checking if the input is empty or a 
 * newline, tokenizes the input, 
 * parses it into an abstract syntax tree (AST), and then executes
 *  the corresponding commands.
 * The function will continue to loop until the user exits 
 * (e.g., by entering `exit` or providing no input).
 *
 * @param env The environment structure containing environment 
 * 								variables and shell state.*/
void	run_minishell(t_env *env)
{
	char		*input;
	//int			status;
	t_token		*tokens;
	t_ast_node	*ast;

	while (1)
	{
		//status = 0;
		input = readline("Minishell: ");
		if (!input)
			break ;
		if (check_line(&input))
			continue ;
		add_history(input);
		tokens = process_to_tokenize_input(input);
		if (!tokens)
			return ; // retornei um erro qualquer
			//status = ast->shell->exit_status;
		ast = parse_tokens(&tokens);
		if (ast)
			// command_executer(ast, env, &env->shell->exit_status);
			execute(ast->args[0], ast->args, env); // executa comandos simples
		free_ast(&ast);
		//ast->shell->exit_status = status;
		//update_env_status
	}
}
