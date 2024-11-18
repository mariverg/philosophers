#include "philosophers.h"

void	eating(t_philo *philo)
{
    t_data	*data;

    data = philo->data;
    pthread_mutex_lock(&data->forks[philo->left_fork]);
    print_status(data, philo->id, "has taken a fork");
    pthread_mutex_lock(&data->forks[philo->right_fork]);
    print_status(data, philo->id, "has taken a fork");
    print_status(data, philo->id, "is eating");
    pthread_mutex_lock(&data->dead_mutex);
    philo->last_meal = get_time();
    philo->eat_count++;
    pthread_mutex_unlock(&data->dead_mutex);
    smart_sleep(data->time_to_eat, data);
    pthread_mutex_unlock(&data->forks[philo->left_fork]);
    pthread_mutex_unlock(&data->forks[philo->right_fork]);
}

void	*philosopher(void *arg)
{
    t_philo	*philo;
    t_data	*data;

    philo = (t_philo *)arg;
    data = philo->data;
    if (data->num_philos == 1)
    {
        handle_single_philosopher(philo);
        return (NULL);
    }
    if (philo->id % 2)
        usleep(15000);
    while (!check_death(data, philo))
    {
        eating(philo);
        if (data->must_eat_count != -1 && 
            philo->eat_count >= data->must_eat_count)
            break;
        print_status(data, philo->id, "is sleeping");
        smart_sleep(data->time_to_sleep, data);
        print_status(data, philo->id, "is thinking");
    }
    return (NULL);
}

void handle_single_philosopher(t_philo *philo)
{
    t_data *data;

    data = philo->data;
    pthread_mutex_lock(&data->forks[philo->left_fork]);
    print_status(data, philo->id, "has taken a fork");
    smart_sleep(data->time_to_die, data);
  /*   pthread_mutex_unlock(&data->forks[philo->left_fork]);
    print_status(data, philo->id, "died"); */
}
