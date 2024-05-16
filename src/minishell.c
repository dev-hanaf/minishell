/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:53:01 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/16 22:26:09 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    (void)ac,
    (void)av;
    (void)env;
    /*     if (ac == 1)
    {
        ft_putstr("ne");
        return (0);
    } */
    // char *redline;
    // redline = redline("minishell-5$");
    // while(TRUE)
    // {
        
    // }
    write(1,"hello world", 11);
    return (0);
}