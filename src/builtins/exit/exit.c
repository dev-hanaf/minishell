/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 05:16:00 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/15 00:05:50 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_and_free_alpha(int e, char *str, char *str2, char *str3)
{
	if (get_ms()->pexit)
		ft_putstr_fd("exit\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	_free_env();
	_free();
	exit(e);
}

size_t	atoi_exit(char *str, int *valid, int *is_ok, int i)
{
	size_t	result;
	int		signe;

	*valid = 1;
	init_vars(is_ok, &result, &signe, &i);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		*is_ok = 1;
		result = result * 10 + (str[i++] - 48);
		if ((result > 9223372036854775807ULL && signe == 1)
			|| ((result > 9223372036854775808ULL && signe == -1)))
			print_and_free_alpha(2, "bash: exit: ", str,
				" numeric argument required\n");
	}
	if (str[i] != '\0')
		*valid = 0;
	return ((int)result * signe);
}

void	print_and_free_digit(int e)
{
	if (get_ms()->pexit)
		ft_putstr_fd("exit\n", 2);
	_free_env();
	_free();
	exit(e);
}

void	multiple_arguments(char **args)
{
	int	is_ok;
	int	valid;
	int	is_ok2;
	int	valid2;

	atoi_exit(args[0], &valid, &is_ok, 0);
	atoi_exit(args[1], &valid2, &is_ok2, 0);
	if ((!valid || !is_ok) && (valid2 && is_ok2))
		print_and_free_alpha(2, "bash: exit: ", args[0],
			": numeric argument required\n");
	else if ((!valid || !is_ok) && (!valid2 && !is_ok2))
		print_and_free_alpha(2, "bash: exit: ", args[0],
			": numeric argument required\n");
	else
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		get_ms()->status = 1;
	}
}

void	__exit(char **args)
{
	unsigned char	num;
	int				len;
	int				valid;
	int				is_ok;

	num = 0;
	if (!args || !*args)
		print_and_free_digit(get_ms()->status);
	len = ft_strlen_2d_array(args);
	if (len == 1)
	{
		num = atoi_exit(args[0], &valid, &is_ok, 0);
		if (valid && is_ok)
			print_and_free_digit(num);
		else
			print_and_free_alpha(2, "bash: exit: ", args[0],
				": numeric argument required\n");
	}
	else
		multiple_arguments(args);
}
