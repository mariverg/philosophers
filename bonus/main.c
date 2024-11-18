#include "philo_bonus.h"

static void wait_children(t_data *data)
{
    int status;
    int i;
    
    i = 0;
    while (i < data->num_philos)
    {
        waitpid(-1, &status, 0);
        if (WEXITSTATUS(status) == 1)
        {
            i = 0;
            while (i < data->num_philos)
            {
                if (data->pids[i] != 0)
                    kill(data->pids[i], SIGTERM);
                i++;
            }
            break;
        }
        i++;
    }
}

static void create_philosophers(t_data *data)
{
    t_philo philo;
    int i;
    
    i = 0;
    while (i < data->num_philos)
    {
        philo.id = i + 1;
        philo.meals_eaten = 0;
        philo.data = data;
        philo.last_meal = get_time();
        
        data->pids[i] = fork();
        if (data->pids[i] == 0)
        {
            philosopher_routine(&philo);
            exit(0);
        }
        i++;
    }
    wait_children(data);
}

int main(int argc, char **argv)
{
    t_data data;
    
    if (argc != 5 && argc != 6)
    {
        printf("Error: wrong number of arguments\n");
        return (1);
    }
    if (init_data(&data, argc, argv) != 0)
        return (1);
        
    if (init_semaphores(&data) != 0)
    {
        clean_all(&data);
        return (1);
    }
    create_philosophers(&data);
    clean_all(&data);
    return (0);
}
