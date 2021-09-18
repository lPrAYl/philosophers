#include "../includes/philo.h"

static int	philo_dead(t_philo *philo, int *allfeed)
{
	long	current_time;

	current_time = gettime() - philo->table->start_time;
	if (philo->feed == philo->table->numberOfMeals)
		(*allfeed) = 1;
	else if (current_time - philo->lastMeal > philo->table->timeToDie)
	{
		current_time = gettime() - philo->table->start_time;
		pthread_mutex_lock(philo->deathMessage);
		printf("\e[41m%ldms %d is dead!\e[0m\n", current_time, philo->philoID);
		philo->table->isDead = 1;
		return (1);
	}
	else
		(*allfeed) = 0;
	return (0);
}

static void	*death(void *arg)
{
	int		i;
	int		allfeed;
	t_philo	*philo;

	allfeed = 0;
	philo = (t_philo *)arg;
	while (1)
	{
		i = -1;
		while (++i < philo->table->countPhilo)
			if (philo_dead(&philo[i], &allfeed))
				return (NULL);
		if (allfeed == 1)
		{
			printf("\e[41mAll philosophers feed\e[0m\n");
			break ;
		}
	}
	return (NULL);
}

static void	*life(void *arg)
{
	int		i;
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->philoID % 2)
		usleep(100);
	i = -1;
	if (ph->table->countPhilo == 1)
		printf("%ldms %d has taken a fork\n",
			gettime() - ph->table->start_time, ph->philoID);
	while (((ph->table->numberOfMeals) == -1
			|| ++i != (ph->table->numberOfMeals)) && ph->table->isDead != 1)
	{
		eating(ph);
		sleeping(ph);
		thinking(ph);
	}
	return (NULL);
}

static void	initPhilosopher(t_philo *philosopher, t_table *table, int i)
{
	philosopher->table = table;
	philosopher->philoID = i + 1;
	philosopher->feed = 0;
	philosopher->lastMeal = gettime() - table->start_time;
	philosopher->left_fork = &table->forks[i];
	philosopher->right_fork = &table->forks[(i + 1) % table->countPhilo];
	philosopher->deathMessage = &table->message;
}

void	basis(t_philo *philo, t_table *table)
{
	int			i;
	pthread_t	dead;

	i = -1;
	while (++i < table->countPhilo)
		if (pthread_mutex_init(&table->forks[i], NULL))
			ft_error("\e[31mError:\e[0m Mutex init error\n");
	if (pthread_mutex_init(&table->message, NULL))
		ft_error("\e[31mError:\e[0m Mutex init error\n");
	i = -1;
	table->start_time = gettime();
	while (++i < table->countPhilo)
		initPhilosopher(&philo[i], table, i);
	i = -1;
	while (++i < table->countPhilo)
		if (pthread_create(&philo[i].threadID, NULL, life, &philo[i]))
			ft_error("\e[31mError:\e[0m Create error\n");
	if (pthread_create(&dead, NULL, death, philo))
		ft_error("\e[31mError:\e[0m Pthread create error\n");
	i = -1;
	while (++i < table->countPhilo)
		if (pthread_detach(philo[i].threadID))
			ft_error("\e[31mError:\e[0m Detach error\n");
	pthread_join(dead, NULL);
}
