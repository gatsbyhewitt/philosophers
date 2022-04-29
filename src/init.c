#include "philosopher.h"

void    ft_exit(t_phi *p, pthread_t *t)
{
    int i;

    i = 0;
    pthread_mutex_destroy(&p->d->display);
    pthread_mutex_destroy(&p->d->last_meal);
    while (i < p->d->number_philo)
    {
        pthread_mutex_destroy(&p->d->forks_m[i]);
        free(p[i].id);
        free(p[i].last_meal);
        free(p[i].meal_count);
        i++;
    }
    free(p->d->forks_m);
    free(p->d->time);
    free(p->d->pmort);
    free(t);
}

int ft_init_mutex(t_data *d)
{
    int i;

    i = 0;
    while (i < d->number_philo)
    {
        pthread_mutex_init(&d->forks_m[i], NULL);
        i++;
    }
    pthread_mutex_init(&d->display, NULL);
    pthread_mutex_init(&d->death, NULL);
    pthread_mutex_init(&d->last_meal, NULL);
    return (0);
}

int ft_init_philo(t_phi *p, int i, t_data *d)
{
    p->id = malloc(sizeof(int));
    p->last_meal = malloc(sizeof(size_t));
    p->meal_count = malloc(sizeof(int));
    if (!p->id || !p->last_meal || !p->meal_count)
    {
        write(2, "Error\nProblem with malloc philo (./init.c)", 43);
        return (1);
    }
    *p->id = i;
    *p->last_meal = ft_get_time();
    p->d = d;
    if (d->meal_to_eat != -1)
        *p->meal_count = 0;
    else 
        *p->meal_count = -1;
    return (0);
}

int ft_init_data(t_data *d, int argc, char **argv)
{
    d->number_philo = ft_atoi(argv[1]);
    d->ttd = ft_atoi(argv[2]);
    d->tte = ft_atoi(argv[3]);
    d->tts = ft_atoi(argv[4]);
    if (argc == 6)
        d->meal_to_eat = ft_atoi(argv[5]);
    else 
        d->meal_to_eat = -1;
    if (d->meal_to_eat == 0)
        return (1);
    d->forks_m = malloc(sizeof(pthread_mutex_t) * d->number_philo);
    d->time = malloc(sizeof(size_t));
    *d->time = ft_get_time();
    d->pmort = malloc(sizeof(int));
    if (!d->forks_m || !d->time || !d->pmort)
    {
        write(2, "Error\nProblem with malloc data (./init.c)", 42);
        return (1);
    }
    *d->pmort = -1;
    return (0);
}
