/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:50:07 by evallee-          #+#    #+#             */
/*   Updated: 2023/09/25 15:15:21 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>
# include <stdbool.h>

typedef struct s_minishell
{
	bool	running;
	char	*name;
}	t_minishell;

#endif