/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungchoi <jungchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:28:40 by hajeong           #+#    #+#             */
/*   Updated: 2023/01/10 20:25:09 by jungchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char *cmd;
	int len;
	t_exec_token	*token;

	(void)argv;
	if (argc != 1)
		return (error_return("argument error\n"));
	g_info.env_list = init_env_list(envp);
	g_info.exit_status = 0;
	while (1)
	{
		printf("==================exit status : %d\n", g_info.exit_status);
		cmd = read_cmd();	
		if (ft_strlen(cmd) >= 1)
			add_history(cmd);
		if (make_token(&token, cmd, &len) != 0)
			continue ;
		if (token->parser_token->cmd == NULL)
			continue ;
		exec_cmd(token, g_info.env_list, len);
		free_all_token(token, token->parser_token, len);
		free(cmd);
	}
}

t_exec_token	*make_exec_token(t_parser_token *parser_token, t_exec_token **exec_token, int len)
{
	int	i;

	*exec_token = (t_exec_token *)malloc(sizeof(t_exec_token) * len);
	if (*exec_token == NULL)
		return NULL;
	i = 0;
	while (i < len)
	{
		(*exec_token)[i].parser_token = &(parser_token[i]);
		(*exec_token)[i].cmd = make_2d_array(parser_token[i].cmd);
		i++;
	}
	return (*exec_token);
}

char	**make_2d_array(t_list *cmd_list)
{
	int		i;
	char	**cmd;
	t_list	*temp;

	cmd = (char **)malloc(sizeof(char *) * (ft_lstsize(cmd_list) + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	temp = cmd_list;
	while (temp != NULL)
	{
		cmd[i] = temp->content;
		i++;
		temp = temp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	free_all_token(t_exec_token *exec_token, t_parser_token *parser_token, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (exec_token[i].cmd != NULL)
			free(exec_token[i].cmd);
		i++;
	}
	free_parser_token(parser_token, len);
	free(exec_token);
}
