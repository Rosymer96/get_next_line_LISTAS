#include "get_next_line.h"
#include <stdio.h>
int main(void)
{
    t_list *lst;
    t_list *aux;
    char *text;

    text = malloc(sizeof(char) * 15);
    lst = NULL;
    int i = 0;
    while (i < 15)
    {
        text[i] = "Hola mi\nmundo"[i];
        i++;
    }
    text[15] = '\0';
    add_list(&lst, text);
    aux = lst;
    while(aux)
    {
        printf("%s\n",lst->content);
        aux = aux->next;
    }

    int res = found_new_line(lst);
    printf("%d\n", res);
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