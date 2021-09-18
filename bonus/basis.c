#include "../includes/philo_bonus.h"

static void	*philoDead(void *arg)
{
	long	curTime;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->table->numberOfMeals != philo->feed)
	{
		curTime = gettime() - philo->table->startTime;
		if (curTime - philo->lastMeal > philo->table->timeToDie)
		{
			sem_wait(philo->deathMessage);
			printf("\e[41m%ldms %d is dead!\e[0m\n", curTime, philo->philoID);
			sem_post(philo->whoDied);
			exit(1);
		}
	}
	return (NULL);
}

static void	*life(t_philo *ph, int i)
{
	pthread_t	lifeTime;

	ph->philoID = i + 1;
	if (ph->philoID % 2)
		usleep(100);
	ph->feed = 0;
	ph->lastMeal = gettime() - ph->table->startTime;
	if (ph->table->countPhilo == 1)
		printf("%ldms %d has taken a fork\n",
			gettime() - ph->table->startTime, ph->philoID);
	if (pthread_create(&lifeTime, NULL, &philoDead, ph))
		ft_error("\e[31mError:\e[0m Pthread create error\n");
	while (ph->table->numberOfMeals != ph ->feed)
	{
		eating(ph);
		sleeping(ph);
		thinking(ph);
	}
	exit(0);
	return (NULL);
}

void	*checkAllSatisfy(void *arg)
{
	int		countPhilo;
	t_philo	*philo;

	philo = (t_philo *)arg;
	countPhilo = philo->table->countPhilo;
	if (philo->table->numberOfMeals > 0)
		while (--countPhilo >= 0)
			sem_wait(philo->philoFeed);
	if (philo->table->numberOfMeals > 0)
	{
		sem_wait(philo->deathMessage);
		printf("\e[41mAll philosophers feed\e[0m\n");
		sem_post(philo->whoDied);
	}
	return (NULL);
}

static void	initSemaphore(t_philo *philo, t_table *table)
{
	sem_unlink("message");
	sem_unlink("forks");
	sem_unlink("takeForks");
	sem_unlink("whoDied");
	sem_unlink("philoFeed");
	philo->deathMessage = sem_open("message", O_CREAT, 0644, 1);
	philo->countForks = sem_open("forks", O_CREAT, 0644, table->countPhilo);
	philo->takeForks = sem_open("takeForks", O_CREAT, 0644, 1);
	philo->whoDied = sem_open("whoDied", O_CREAT, 0644, 0);
	philo->philoFeed = sem_open("philoFeed", O_CREAT, 0644, 0);
	table->startTime = gettime();
	philo->table = table;
}

void	basis(t_philo *philo, t_table *table)
{
	int			i;
	pthread_t	allSatisfy;

	initSemaphore(philo, table);
	if (pthread_create(&allSatisfy, NULL, checkAllSatisfy, philo))
		ft_error("\e[31mError:\e[0m Pthread create error\n");
	if (pthread_detach(allSatisfy))
		ft_error("\e[31mError:\e[0m Detach error\n");
	i = -1;
	while (++i < table->countPhilo)
	{
		philo[i].pid = fork();
		if (!philo[i].pid)
			life(philo, i);
		else if (philo[i].pid < 0)
			ft_error("\e[31mError:\e[0m Fork error\n");
	}
	sem_wait(philo->whoDied);
	table->numberOfMeals = -1;
	i = table->countPhilo;
	while (--i >= 0)
		kill(philo[i].pid, SIGINT);
	sem_post(philo->deathMessage);
	while (++i < table->countPhilo)
		sem_post(philo->philoFeed);
}
