#include "philo_bonus.h"

long get_time(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void precise_sleep(int ms)
{
    long start;
    long current;
    
    start = get_time();
    while (1)
    {
        current = get_time();
        if (current - start >= ms)
            break;
        usleep(100);
    }
}

void print_status(t_data *data, int id, char *status)
{
    sem_wait(data->print_sem);
    printf("%ld %d %s\n", get_time() - data->start_time, id, status);
    sem_post(data->print_sem);
}

int init_semaphores(t_data *data)
{
    sem_unlink("/forks");
    sem_unlink("/print");
    sem_unlink("/death");
    
    data->forks = sem_open("/forks", O_CREAT, 0644, data->num_philos);
    data->print_sem = sem_open("/print", O_CREAT, 0644, 1);
    data->death_sem = sem_open("/death", O_CREAT, 0644, 0);
    
    if (data->forks == SEM_FAILED || data->print_sem == SEM_FAILED || 
        data->death_sem == SEM_FAILED)
        return (1);
    return (0);
}

void clean_semaphores(t_data *data)
{
    sem_close(data->forks);
    sem_close(data->print_sem);
    sem_close(data->death_sem);
    sem_unlink("/forks");
    sem_unlink("/print");
    sem_unlink("/death");
}
int	ft_atoi(const char *str)
{
    int	res;
    int	sign;

    res = 0;
    sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-')
        sign = -1;
    if (*str == '-' || *str == '+')
        str++;
    while (*str >= '0' && *str <= '9')
    {
        res = res * 10 + (*str - '0');
        str++;
    }
    return (res * sign);
}
