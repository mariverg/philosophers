#include "philo_bonus.h"

static int validate_args(int argc, char **argv)
{
    int i;
    int j;
    
    i = 1;
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

  int init_data(t_data *data, int argc, char **argv)
{
    if (validate_args(argc, argv))
        return (1);
        
    data->num_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        data->must_eat_count = ft_atoi(argv[5]);
    else
        data->must_eat_count = -1;
    data->start_time = get_time();

    if (data->num_philos < 1 || data->time_to_die < 0 || 
        data->time_to_eat < 0 || data->time_to_sleep < 0 || 
        (argc == 6 && data->must_eat_count < 0))
        return (1);
        
    data->pids = malloc(sizeof(pid_t) * data->num_philos);
    if (!data->pids)
        return (1);
        
    return (0);
}


void clean_all(t_data *data)
{
    free(data->pids);
    clean_semaphores(data);
}
