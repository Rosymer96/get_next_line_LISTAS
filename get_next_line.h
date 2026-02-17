/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosvela <rosvela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:43:08 by rosvela           #+#    #+#             */
/*   Updated: 2026/02/16 11:06:55 by rosvela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

t_list	*get_lst_last(t_list *lst);
void	add_list(t_list **lst, char *text);
size_t get_len_line(t_list *lst);
int found_new_line(t_list *lst);
char *get_next_line(int fd);
void    free_list(t_list *lst);


#endif
