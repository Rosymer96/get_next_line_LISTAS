/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosvela <rosvela@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:50:42 by rosvela           #+#    #+#             */
/*   Updated: 2026/02/16 11:50:46 by rosvela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*get_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	add_list(t_list **lst, char *text)
{
    t_list  *new_node;
    t_list  *last;

    new_node = malloc(sizeof(t_list));
    if (!new_node)
        return;
    new_node->content = text;
    new_node->next = NULL;
	if (!*lst)
        *lst = new_node;
    else
    {
        last = get_lstlast(*lst);
        last->next = new_node;
    }
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int found_new_line(t_list *lst)
{
    int i;
    
    if (!lst)
    {
        return (0);
    }
    while (lst)
    {
        i = 0;
        while (lst->content[i])
        {
            if (lst->content[i] == '\n')
                return (1);
            i++;
        }
        lst = lst->next;
    }
    return (0);
}



