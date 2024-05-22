/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:35:13 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/22 05:11:22 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int _pwd(void)
{
    char *cwd;
    
    cwd = getcwd(NULL, 0);     
    if (!cwd)
    {
        perror("");
        return(-1);
    }   
    printf("%s\n", cwd);   
    free(cwd);
    g_minishell.status = 0;
    return (0);
}
