#include "philosopher.h"

void    *create_tab(int n)
{
    pthread_t *tab;

    tab = malloc(sizeof(pthread_t) * n);
    if (!tab)
        return (NULL);
    return (tab);
}


int main(int argc, char **argv)
{
    pthread_t   *t;
    t_data      d;
    t_phi       *p;
    int     n;

    if (ft_check_args(argc, argv))
        return (0);
    if (ft_init_data(&d, argc, argv) || ft_init_mutex(&d))
        return (0);
    n = ft_atoi(argv[1]);
    t = (pthread_t *)create_tab(n);
    p = malloc(sizeof(t_phi) * n);
    if (!p)
        return (0);
    ft_create_threads(t, p, n, &d);
    join_threads(t, n);
    ft_exit(p, t);
    free(p);
    return (0);
}