#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libs/libft/libft.h"

typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}   t_env;

// setting-env
t_env	*init_env_list(char **envp);
t_env	*make_env_node(char *key, char *value);
void	env_list_add_node(t_env **list, t_env *node);

// builtin-function
void	ft_env(t_env *list);

#endif
