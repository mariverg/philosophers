#include "philosophers.h"

long long	get_time(void)
{
    struct timeval	tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_data *data, int id, char *status)
{
    pthread_mutex_lock(&data->write_mutex);
    if (!data->dead || !strcmp(status, "died"))
        printf("%lld %d %s\n", get_time() - data->start_time, id, status);
    pthread_mutex_unlock(&data->write_mutex);
}

void	smart_sleep(long long time, t_data *data)
{
    long long	start;

    start = get_time();
    while (!data->dead)
    {
        if (get_time() - start >= time)
            break ;
        usleep(100);
    }
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
