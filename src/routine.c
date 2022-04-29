#include "philosopher.h"

int ft_action(t_phi *p, int right, int left)
{
    t_data *d;

    d = p->d;
    pthread_mutex_lock(&d->forks_m[right]);
    ft_display(p, right, "has taken a fork");
    pthread_mutex_lock(&d->forks_m[left]);
    ft_display(p, right, "has taken a fork");
    ft_display(p, right, "is eating");
    pthread_mutex_lock(&p->d->last_meal);
    *p->last_meal = ft_get_time();
    pthread_mutex_unlock(&p->d->last_meal);
    ft_sleep(d->tte);
    pthread_mutex_unlock(&d->forks_m[right]);
    pthread_mutex_unlock(&d->forks_m[left]);
    if (*p->meal_count != -1)
        *p->meal_count += 1;
    ft_display(p, right, "is sleeping");
    ft_sleep(d->tts);
    ft_display(p, right, "is thinking");
    return (0);
}

void    *ft_routine(void *philo)
{
    t_phi   *p;
    t_data  *data;
    int     id;

    p = (t_phi *)philo;
    data = p->d;
    id = *p->id;
    if (id % 2)
        usleep(1000);
    while (p->d->meal_to_eat == -1 || p->d->meal_to_eat != *p->meal_count)
    {
        pthread_mutex_lock(&data->death);
        if (*p->d->pmort != -1)
        {
            pthread_mutex_unlock(&data->death);
            return (NULL);
        }
        pthread_mutex_unlock(&p->d->death);
        usleep(1000);
        if (id == (data->number_philo - 1))
            ft_action(p, id, 0);
        else 
            ft_action(p, id, id + 1);
    }
    return (NULL);
}

void    *one_philo(void *philo)
{
    t_phi *p;

    p = (t_phi *)philo;
    pthread_mutex_lock(&p->d->forks_m[0]);
    ft_display(p, 0, "has taken a fork");
    pthread_mutex_unlock(&p->d->forks_m[0]);
    ft_sleep(p->d->ttd);
    return (NULL);
}