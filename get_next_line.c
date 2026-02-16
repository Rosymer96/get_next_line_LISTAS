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

static void *read_text(int fd, t_list **lst)
{
    int     bytes;
    char    *text;

    text = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!text)
        return NULL;
    while(!found_new_line(lst))
    {
        bytes = read(fd, text, BUFFER_SIZE);
        if (bytes <= 0)
        return (free(text), NULL);
        text[bytes] = '\0';
    }
    add_list(&lst, text);
}

char *get_next_line(int fd)
{
    static t_list  *lst;


}
