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

t_list	*get_lst_last(t_list *lst)
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
    {
        free(text);
        return;
    }
    new_node->content = text;
    new_node->next = NULL;
	if (!*lst)
        *lst = new_node;
    else
    {
        last = get_lst_last(*lst);
        last->next = new_node;
    }
}

void    free_list(t_list *lst)
{
    t_list  *tmp;
    while (lst)
    {
        tmp = lst->next;
        free(lst->content);
        free(lst);
        lst = tmp;
    }
}

size_t get_len_line(t_list *lst)
{
    size_t  len;
    size_t  i;

    len = 0;
    while (lst)
    {
        i = 0;
        while (lst->content[i])
        {
            len++;
            if (lst->content[i] == '\n')
                return (len);
            i++;
        }
        lst = lst->next;
    }
    return (len);
}


int found_new_line(t_list *lst)
{
    size_t  i;
    
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



