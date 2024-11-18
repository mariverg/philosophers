#include "philosophers.h"

int	check_death(t_data *data, t_philo *philo)
{
    pthread_mutex_lock(&data->dead_mutex);
    if (data->dead)
    {
        pthread_mutex_unlock(&data->dead_mutex);
        return (1);
    }
    if (get_time() - philo->last_meal > data->time_to_die)
    {
        data->dead = 1;
        pthread_mutex_unlock(&data->dead_mutex);
        print_status(data, philo->id, "died");
        return (1);
    }
    pthread_mutex_unlock(&data->dead_mutex);
    return (0);
}

void	monitor(t_data *data)
{
    int	i;
    int	all_ate;

    while (!data->dead)
    {
        i = -1;
        all_ate = 1;
        while (++i < data->num_philos)
        {
            if (check_death(data, &data->philos[i]))
                return ;
            if (data->must_eat_count != -1 && 
                data->philos[i].eat_count < data->must_eat_count)
                all_ate = 0;
        }
        if (data->must_eat_count != -1 && all_ate)
        {
            pthread_mutex_lock(&data->dead_mutex);
            data->dead = 1;
            pthread_mutex_unlock(&data->dead_mutex);
            return ;
        }
        usleep(1000);
    }
}

int	start_simulation(t_data *data)
{
    int	i;

    data->start_time = get_time();
    i = -1;
    while (++i < data->num_philos)
    {
        data->philos[i].last_meal = get_time();
        if (pthread_create(&data->philos[i].thread, NULL, 
            philosopher, &data->philos[i]))
            return (1);
    }
    monitor(data);
    i = -1;
    while (++i < data->num_philos)
        pthread_join(data->philos[i].thread, NULL);
    return (0);
}

int	main(int argc, char **argv)
{
    t_data	data;

    if (argc != 5 && argc != 6)
    {
        printf("Error: wrong number of arguments\n");
        return (1);
    }
    if (init_data(&data, argc, argv))
        return (1);
    if (init_mutex(&data))
        return (1);
    if (init_philos(&data))
        return (1);
    if (start_simulation(&data))
        return (1);
    return (0);
}