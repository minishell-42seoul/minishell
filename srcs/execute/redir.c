/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghan <sanghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:19:50 by sanghan           #+#    #+#             */
/*   Updated: 2023/01/11 17:26:50 by sanghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_redir(t_parser_token *parser_token, t_env *env_list)
{
	t_list	*in;
	t_list	*out;

	in = parser_token->in;
	while (in != NULL)
	{
		set_redir_in(in->content, in->next->content);
		in = in->next->next;
	}
	out = parser_token->out;
	while (out != NULL)
	{
		set_redir_out(out->content, out->next->content);
		out = out->next->next;
	}
	(void)env_list;
}

char	*replace_env_heredoc(char *str, t_env *env_list)
{
	char	*key;
	char	*key_end;
	char	*temp;

	while (ft_strchr(str, '$'))
	{
		key = ft_strchr(str, '$');
		key_end = key + 1;
		while (ft_isalnum(*key_end))
			key_end++;
		key = ft_substr(key, 1, (int)(key_end - key - 1));
		temp = join_env(str, get_env_value(env_list, key), key_end);
		free(str);
		str = temp;
		free(key);
	}
	return (str);
}

void	set_redir_in(char *redir_sign, char *filename)
{
	int	fd;

	fd = -1;
	if (ft_strncmp(redir_sign, "<", 2) == 0)
		fd = open(filename, O_RDONLY);
	else if (ft_strncmp(redir_sign, "<<", 3) == 0)
		fd = open(".here_doc_temp", O_RDONLY);
	if (fd == -1)
		error_exit("open error\n", 1);
	if (dup2(fd, STDIN_FILENO) == -1)
		error_exit("dup2 error\n", 1);
	close(fd);
}

void	set_redir_out(char *redir_sign, char *filename)
{
	int	fd;

	fd = -1;
	if (ft_strncmp(redir_sign, ">", 2) == 0)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strncmp(redir_sign, ">>", 3) == 0)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		error_exit("open error\n", 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		error_exit("dup2 error\n", 1);
	close(fd);
}
