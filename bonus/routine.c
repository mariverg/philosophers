#include "philo_bonus.h"

void *check_death(void *arg)
{
    t_philo *philo;
    long current_time;
    
    philo = (t_philo *)arg;
    while (1)
    {
        current_time = get_time();
        if (current_time - philo->last_meal > philo->data->time_to_die)
        {
            sem_wait(philo->data->print_sem);
            printf("%ld %d died\n", current_time - philo->data->start_time, philo->id);
            sem_post(philo->data->death_sem);
            exit(1);
        }
        precise_sleep(1);
    }
    return (NULL);
}

static void eat(t_philo *philo)
{
    sem_wait(philo->data->forks);
    print_status(philo->data, philo->id, "has taken a fork");
    sem_wait(philo->data->forks);
    print_status(philo->data, philo->id, "has taken a fork");
    
    print_status(philo->data, philo->id, "is eating");
    philo->last_meal = get_time();
    precise_sleep(philo->data->time_to_eat);
    philo->meals_eaten++;
    
    sem_post(philo->data->forks);
    sem_post(philo->data->forks);
}

void philosopher_routine(t_philo *philo)
{
    pthread_create(&philo->death_thread, NULL, check_death, philo);
    pthread_detach(philo->death_thread);
    
    if (philo->id % 2 == 0)
        precise_sleep(philo->data->time_to_eat / 2);
        
    while (philo->data->must_eat_count == -1 || 
           philo->meals_eaten < philo->data->must_eat_count)
    {
        eat(philo);
        print_status(philo->data, philo->id, "is sleeping");
        precise_sleep(philo->data->time_to_sleep);
        print_status(philo->data, philo->id, "is thinking");
    }
    exit(0);
}
