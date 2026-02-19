/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosvela <rosvela@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:20:52 by rosvela           #+#    #+#             */
/*   Updated: 2026/02/18 14:23:21 by rosvela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	read_text(int fd, t_list **lst)
{
	int		bytes;
	char	*text;

	while (!found_new_line(*lst))
	{
		text = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!text)
			return (free_list(*lst), *lst = NULL, (void)0);
		bytes = read(fd, text, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(text);
			free_list(*lst);
			*lst = NULL;
			return ;
		}
		if (bytes == 0)
			return (free(text), (void)0);
		text[bytes] = '\0';
		add_list(lst, text);
	}
}

static char	*create_line(t_list *lst, size_t len)
{
	char	*new_line;
	size_t	i;
	size_t	j;

	if (!lst || len == 0)
		return (NULL);
	new_line = malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (NULL);
	j = 0;
	while (lst && j < len)
	{
		i = 0;
		while (lst->content[i] && j < len)
		{
			new_line[j] = lst->content[i];
			j++;
			i++;
			if (new_line[j - 1] == '\n')
				break ;
		}
		lst = lst->next;
	}
	new_line[j] = '\0';
	return (new_line);
}

static char	*get_clean_node(char *content)
{
	size_t	i;
	size_t	clean_node_len;
	char	*new_content;

	i = 0;
	while (content[i] && content[i] != '\n')
		i++;
	if (content[i] == '\n')
		i++;
	clean_node_len = 0;
	while (content[i + clean_node_len])
		clean_node_len++;
	if (clean_node_len == 0)
		return (NULL);
	new_content = malloc(clean_node_len + 1);
	if (!new_content)
		return (NULL);
	clean_node_len = 0;
	while (content[i])
		new_content[clean_node_len++] = content[i++];
	new_content[clean_node_len] = '\0';
	return (new_content);
}

static void	clean_lst(t_list **lst)
{
	t_list	*last;
	char	*new_content;

	if (!lst || !*lst)
		return ;
	last = get_lst_last(*lst);
	if (!last)
		return (free_list(*lst), *lst = NULL, (void)0);
	new_content = get_clean_node(last->content);
	free_list(*lst);
	if (!new_content)
	{
		*lst = NULL;
		return ;
	}
	*lst = malloc(sizeof(t_list));
	if (!*lst)
	{
		free(new_content);
		return ;
	}
	(*lst)->content = new_content;
	(*lst)->next = NULL;
}

char	*get_next_line(int fd)
{
	static t_list	*lst[FD_MAX];
	char			*line;
	size_t			len;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
	{
		free_list(lst[fd]);
		lst[fd] = NULL;
		return (NULL);
	}
	read_text(fd, &lst[fd]);
	if (!lst[fd])
		return (NULL);
	len = get_len_line(lst[fd]);
	line = create_line(lst[fd], len);
	if (!line)
	{
		free_list(lst[fd]);
		lst[fd] = NULL;
		return (NULL);
	}
	clean_lst(&lst[fd]);
	return (line);
}
