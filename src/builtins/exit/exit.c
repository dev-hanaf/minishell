/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 05:16:00 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/08 06:01:01 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if (!arg) exit(get_ms()->status)

// if arg[0] == alpha and arg[1] == numeric  (exit(2)bash: exit: sdf: numeric argument required)

// else if arg[0] == numeric and arg[1] == alpha (exit\nbash: exit: too many arguments) return (1)
// else if arg[0] == numeric and arg[1] == numeric (exit\nbash: exit: too many arguments) return (1)


//else if arg[0] == alpha (exit(2))

void	init_vars(int *is_ok, long *result, int *signe, int *i)
{
	*is_ok = 0;
	*result = 0;
	*signe = 1;
	*i = 0;
}

int	atoi_exit(char *str, int *valid, int *is_ok)
{
	long	result;
	int		signe;
	int		i;
	
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
	}
	if (str[i] != '\0')
		*valid = 0;
	return ((int)result * signe);
}

int  map_to_255_range(int x)
{
    return (x % 256 + 256) % 256;
}

void print_and_free_digit(int e)
{
	ft_putstr_fd("exit\n",2);
	_free_env();
	_free();
	exit(e);
}

void print_and_free_alpha(int e, char *str, char *str2, char *str3)
{
	ft_putstr_fd("exit\n",2);
	ft_putstr_fd(str ,2);
	ft_putstr_fd(str2 ,2);
	ft_putstr_fd(str3 ,2);
	_free_env();
	_free();
	exit(e);
}

void multiple_arguments(char **args, int num)
{
	int is_ok;
	int valid;
	int is_ok2;
	int valid2;
	int num2;
	
	num = atoi_exit(args[0], &valid, &is_ok);
	num2 = atoi_exit(args[1], &valid2, &is_ok2);
	if ((!valid || !is_ok) && (valid2 && is_ok2))
		print_and_free_alpha(2, "bash: exit: ", args[0],": numeric argument required\n");
	else if ((!valid || !is_ok) && (!valid2 && !is_ok2))
		print_and_free_alpha(2, "bash: exit: ", args[0],": numeric argument required\n");
	else
	{
		ft_putstr_fd("exit\n",2);
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		get_ms()->status = 1;
	}
}

void    __exit(char **args)
{
	int num;
	int len;
	int valid;
	int is_ok;
	
	num = 0;
	if (!args)
		print_and_free_digit(get_ms()->status);
	len = ft_strlen_2d_array(args);
	if (len == 1)
	{
		num = atoi_exit(args[0], &valid, &is_ok);
		if (valid && is_ok)
			print_and_free_digit(map_to_255_range(num));
		else
			print_and_free_alpha(2, "bash: exit: ", args[0],": numeric argument required\n");
	}
	else
		multiple_arguments(args, num);
}
