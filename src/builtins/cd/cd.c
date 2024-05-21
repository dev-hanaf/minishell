/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:23:55 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/20 22:47:52 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// https://linuxize.com/post/linux-cd-command/
//cd ==> ~

int find_pwd_env(void)
{
    size_t     i;

    i = 0;
    if (g_minishell.env)
    {
        while(ft_strncmp(g_minishell.env[i], "PWD=", 4))
            i++;
        return (i);
    }
    return (-1);
}

void	_cd(char *path)
{
    // char *new_path;
    size_t i = 0;
    
    i = find_pwd_env();
    if (i >= 0)
    {
        // int j = 0;
        if (ft_strlen(path) == 2 /*OR strcmp(arg, "~")*/)
        {
            path = getenv("HOME");
            // printf("getenv %s\n", path);
            // chnage oldpath to this path 
            chdir(path);
            // printf("getenv %s\n", getenv("PWD"));
        }   
    }
    

}