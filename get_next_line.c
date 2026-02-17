/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosvela <rosvela@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:43:59 by rosvela           #+#    #+#             */
/*   Updated: 2026/02/16 11:44:38 by rosvela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void read_text(int fd, t_list **lst)
{
    int     bytes;
    char    *text;

    while(!found_new_line(*lst))
    {
        text = malloc(sizeof(char) * BUFFER_SIZE + 1);
        if (!text)
            return;
        bytes = read(fd, text, BUFFER_SIZE);
        if (bytes <= 0)
        {   
            free(text);
            return;
        }        
        text[bytes] = '\0';
        add_list(lst, text); 
    }
}

static char *create_line(t_list *lst, size_t len)
{
    char *new_line;
    size_t  i;
    size_t  j;
    
    if (!lst || len == 0)
        return (NULL);
    new_line = malloc(sizeof(char) * (len + 1));
    if (!new_line)
    return (NULL);
    j = 0;
    while (lst && j < len)
    {
        i = 0;
        while(lst->content[i] && j < len)
        {
            new_line[j] = lst->content[i];
            j++;
            i++;
            if (new_line[j - 1] == '\n')
                break;
        }
        lst = lst->next;
    }
    new_line[j] = '\0';
    return (new_line);
}
static void    free_list(t_list *lst)
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
static void clean_lst(t_list **lst)
{
    t_list  *last;
    t_list   *clean_node;
    char    *new_content;
    size_t     i;
    size_t     j;

    new_content = malloc(BUFFER_SIZE + 1);
    if (!new_content)
    {
        free_list(*lst);
        *lst = NULL;
        return;
    }
    clean_node = malloc(sizeof(t_list));
    if (!clean_node)
    {
        free(new_content);
        free_list(*lst);
        *lst = NULL;
        return ;
    }
    last = get_lst_last(*lst);
    if (!last)
        return;
    i = 0;
    j = 0;
    while (last->content[i] && last->content[i] != '\n')
        i++;
    if (last->content[i] && last->content[i] == '\n')
        i++;
    while (last->content[i])
        new_content[j++] = last->content[i++];
    new_content[j] = '\0';
    if (j == 0)
    {
        free(new_content);
        free(clean_node);
        free_list(*lst);
        *lst = NULL;
    }
    else
    {
        clean_node->content =  new_content;
        clean_node->next = NULL;
        free_list(*lst);
        *lst = clean_node;
    }
}

char *get_next_line(int fd)
{
    static t_list  *lst;
    char    *line;
    size_t  len;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
    {
        free_list(lst);
        lst = NULL;
        return (NULL);
    }
    read_text(fd, &lst);
    if (!lst)
        return (NULL);
    len = get_len_line(lst);
    line = create_line(lst, len);
    if (!line)
    {
        free_list(lst);
        lst = NULL;
        return (NULL);
    }
    clean_lst(&lst);
    return (line);
}
