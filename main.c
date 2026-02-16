#include "get_next_line.h"
#include <stdio.h>
int main(void)
{
    t_list *lst;
    char *text;

    text = malloc(sizeof(char) * 30);
    lst = NULL;
    int i = 0;
    while (i < 30)
    {
        text[i] = "Hola mi mundo."[i];
        i++;
    }
    text[15] = '\0';
    add_list(&lst, text);
    while(lst)
    {
        printf("%s",lst->content);
        lst = lst->next;
    }

    int res = found_new_line(&lst);
    t_list *tmp;
    while (lst)
    {
        tmp = lst->next;
        free(lst-> content);
        free(lst);
        lst =tmp;
    }
    return (0);
}