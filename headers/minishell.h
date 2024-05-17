/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:01:32 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/16 22:34:02 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

# define TRUE 1
# define FLASE 0

typedef enum s_type
{
	WORD = 0,
	PIPE = 1,
	HERDOC = 2,
	BIGGER = 3,
	LESS = 4,
	DBIGGER = 5,
	DLESS = 6,
	ERROR = 7
}					t_type;

typedef struct s_tokenizer
{
	char			*name;
	t_type			*type;
}					t_tokenizer;

typedef struct s_cmd
{
	struct s_cmd	*prev;
	char			*cmd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_minishell
{
	char			**env;
	char			*line;
	int				status;
}					t_minishell;

// enum t_token
// {
//     PIPE = 1;
//     false = 0;
// }

#endif