#include "../includes/philo.h"

int	main()
{
		struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("%ld\n",tv.tv_sec * 1000 + tv.tv_usec / 1000);
	sleep(10);
	printf("%ld\n", tv.tv_sec * 1000 + tv.tv_usec / 1000);
	//return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}