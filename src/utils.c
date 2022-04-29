#include "philosopher.h"

size_t  ft_get_time(void)
{
    struct timeval  time;

    gettimeofday(&time, NULL);
    return ((size_t)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	ft_sleep(size_t time)
{
	size_t	t;

	t = ft_get_time() + time;
	while (ft_get_time() < t)
		usleep(10);
}

void    ft_display(t_phi *p, int i, char *str)
{
    pthread_mutex_lock(&p->d->display);
    pthread_mutex_lock(&p->d->death);
    if (*p->d->pmort == -1)
        printf("%lu %i %s\n", (ft_get_time() - *p->d->time), i + 1, str);
    pthread_mutex_unlock(&p->d->death);
    pthread_mutex_unlock(&p->d->display);
}