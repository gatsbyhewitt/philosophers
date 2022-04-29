#include "philosopher.h"

void    join_threads(pthread_t *t, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        if (pthread_join(t[i], NULL) != 0)
        {
            write(2, "Error\nProblem joining threads\n", 31);
            return ;
        }
        i++;
    }
}

int	ft_init_and_verify(pthread_t *th, t_phi *p, int nb, t_data *d)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		ft_init_philo(&p[i], i, d);
		i++;
	}
	if (pthread_create(th, NULL, ft_verify, p) != 0)
		return (0);
	return (1);
}

void    ft_create_threads(pthread_t *t, t_phi *p, int n, t_data *d)
{
    int             i;
    pthread_t   th;

    i = 0;
    if (!ft_init_and_verify(&th, p, n, d))
		return ;
    if (d->number_philo == 1)
	{
		if (pthread_create(&t[0], NULL, &one_philo, &p[0]) != 0)
			return ;
	}
    else
    {
        while (i < n)
        {
            if (pthread_create(&t[i], NULL, &ft_routine, &p[i]) != 0)
            {
                write(2, "Error\nProblem in creating threads\n", 31);
                return ;
            }
            i++;
        }
    }
    pthread_detach(th);
}

void    *ft_death(t_phi *p, t_data *data, int i)
{
    pthread_mutex_lock(&data->death);
    if (*data->pmort == -1)
        *data->pmort = *p[i].id;
    pthread_mutex_unlock(&data->death);
    printf("%lu %i died 💀\n", (ft_get_time() - *data->time), i + 1);
    return (NULL);
}

void    *ft_verify(void *philo)
{
    t_phi *p;
    t_data *data;
    int i;

    p = (t_phi *)philo;
    data = p->d;
    i = 0;
    while (*p[i].meal_count == -1 || *p[i].meal_count != data->meal_to_eat)
    {
        pthread_mutex_lock(&data->last_meal);
        if ((ft_get_time() - *p[i].last_meal) >= (size_t)data->ttd)
        {
            pthread_mutex_unlock(&p->d->last_meal);
            ft_death(p, data, i);
            return (NULL);
        }
        pthread_mutex_unlock(&data->last_meal);
        if (i == data->number_philo - 1)
            i = 0;
        else
            i++;
    }
    return (NULL);
}