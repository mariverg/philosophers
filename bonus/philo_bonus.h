#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_data {
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_count;
    long start_time;
    sem_t *forks;
    sem_t *print_sem;
    sem_t *death_sem;
    pid_t *pids;
} t_data;

typedef struct s_philo {
    int id;
    int meals_eaten;
    long last_meal;
    t_data *data;
    pthread_t death_thread;
} t_philo;

// utils.c
long    get_time(void);
void    precise_sleep(int ms);
void    print_status(t_data *data, int id, char *status);
int     init_semaphores(t_data *data);
void    clean_semaphores(t_data *data);

// init.c
int     init_data(t_data *data, int argc, char **argv);
void    clean_all(t_data *data);
int	    ft_atoi(const char *str);

// routine.c
void    *check_death(void *arg);
void    philosopher_routine(t_philo *philo);

#endif
