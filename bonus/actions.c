#include "../includes/philo_bonus.h"

void	eating(t_philo *philo)
{
	long	currentTime;

	sem_wait(philo->takeForks);
	sem_wait(philo->countForks);
	sem_wait(philo->countForks);
	currentTime = gettime() - philo->table->startTime;
	sem_wait(philo->deathMessage);
	printf("%ldms %d has taken left fork\n", currentTime, philo->philoID);
	printf("%ldms %d has taken right fork\n", currentTime, philo->philoID);
	printf("%ldms %d is eating\n", currentTime, philo->philoID);
	philo->lastMeal = gettime() - philo->table->startTime;
	sem_post(philo->deathMessage);
	sem_post(philo->takeForks);
	my_sleep(philo->table->timeToEat);
	sem_post(philo->countForks);
	sem_post(philo->countForks);
	if (++philo->feed == philo->table->numberOfMeals)
		sem_post(philo->philoFeed);
}

void	sleeping(t_philo *philo)
{
	long	currentTime;

	sem_wait(philo->deathMessage);
	currentTime = gettime() - philo->table->startTime;
	printf("%ldms %d is sleeping\n", currentTime, philo->philoID);
	sem_post(philo->deathMessage);
	my_sleep(philo->table->timeToSleep);
}

void	thinking(t_philo *philo)
{
	long	currentTime;

	sem_wait(philo->deathMessage);
	currentTime = gettime() - philo->table->startTime;
	printf("%ldms %d is thinking\n", currentTime, philo->philoID);
	sem_post(philo->deathMessage);
}
