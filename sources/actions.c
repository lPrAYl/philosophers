#include "../includes/philo.h"

void	eating(t_philo *philo)
{
	long	currentTime;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->deathMessage);
	currentTime = gettime() - philo->table->start_time;
	if (philo->table->isDead)
		return ;
	printf("%ldms %d has taken left fork\n", currentTime, philo->philoID);
	printf("%ldms %d has taken right fork\n", currentTime, philo->philoID);
	printf("%ldms %d is eating\n", currentTime, philo->philoID);
	philo->lastMeal = gettime() - philo->table->start_time;
	pthread_mutex_unlock(philo->deathMessage);
	usleep(50);
	my_sleep(philo->table->timeToEat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	long	currentTime;

	pthread_mutex_lock(philo->deathMessage);
	currentTime = gettime() - philo->table->start_time;
	if (!philo->table->isDead)
		printf("%ldms %d is sleeping\n", currentTime, philo->philoID);
	pthread_mutex_unlock(philo->deathMessage);
	my_sleep(philo->table->timeToSleep);
}

void	thinking(t_philo *philo)
{
	long	currentTime;

	pthread_mutex_lock(philo->deathMessage);
	currentTime = gettime() - philo->table->start_time;
	if (!philo->table->isDead)
		printf("%ldms %d is thinking\n", currentTime, philo->philoID);
	pthread_mutex_unlock(philo->deathMessage);
	philo->feed++;
}
