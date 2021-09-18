#include "../includes/philo_bonus.h"

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	my_sleep(long	time)
{
	long	current_time;
	long	new_time;

	current_time = gettime();
	new_time = current_time;
	while (time > new_time - current_time)
	{
		usleep(100);
		new_time = gettime();
	}
}
