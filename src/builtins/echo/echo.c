/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:53:51 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/13 13:05:58 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void _echo(char **argumentes) // echo hi heloo NULL
{
    int i;

    i = 1;//TODO why 1, ask lmokhtar
    while(argumentes && argumentes[i])
    {
        printf("%s", argumentes[i]);
        if (argumentes[i + 1] != NULL)
            printf(" ");
        i++;
    }
    printf("\n");
}
