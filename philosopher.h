#ifndef PHILO
# define PHILO

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data {
    int     number_philo;
    int     ttd;
    int     tte;
    int     tts;
    int     meal_to_eat;
    int     *pmort;
    size_t  *time;
    pthread_mutex_t *forks_m;
    pthread_mutex_t display;
    pthread_mutex_t death;
    pthread_mutex_t last_meal; 
}       t_data;

typedef struct s_phi {
    int     *id;
    size_t  *last_meal;
    int     *meal_count;
    t_data  *d;
}       t_phi;

int ft_atoi(char *nptr);
int ft_only_digit(char *str);
int ft_check_args(int argc, char **argv);

void    ft_exit(t_phi *p, pthread_t *t);
int ft_init_mutex(t_data *d);
int ft_init_philo(t_phi *p, int i, t_data *d);
int ft_init_data(t_data *d, int argc, char **argv);

int ft_action(t_phi *p, int left, int right);
void    *ft_routine(void *philo);
void    *one_philo(void *philo);
void    *ft_verify(void *philo);

void    *create_tab(int n);
void    join_threads(pthread_t *t, int n);
void    ft_create_threads(pthread_t *t, t_phi *p, int n, t_data *d);

size_t  ft_get_time(void);
void	ft_sleep(size_t time);
void    ft_display(t_phi *p, int i, char *str);

#endif