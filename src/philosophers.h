#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
#include <string.h>


typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data
{
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat_count;
    int             dead;
    long long       start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t write_mutex;
    pthread_mutex_t dead_mutex;
    t_philo         *philos;
};

struct s_philo
{
    int             id;
    int             left_fork;
    int             right_fork;
    int             eat_count;
    long long       last_meal;
    pthread_t       thread;
    t_data          *data;
};

// utils.c
long long	get_time(void);
void		print_status(t_data *data, int id, char *status);
void		smart_sleep(long long time, t_data *data);
int			check_death(t_data *data, t_philo *philo);

// init.c
int			init_data(t_data *data, int argc, char **argv);
int			init_mutex(t_data *data);
int			init_philos(t_data *data);
int	        ft_atoi(const char *str);

// actions.c
void		*philosopher(void *arg);
void		eating(t_philo *philo);
void        handle_single_philosopher(t_philo *philo);

#endif