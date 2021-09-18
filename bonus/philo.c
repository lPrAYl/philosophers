#include "../includes/philo_bonus.h"

static void	validate_arg(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc > 6)
		ft_error("\e[31mError:\e[0m Too many arguments\n");
	if (argc < 5)
		ft_error("\e[31mError:\e[0m Not enough arguments\n");
	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				ft_error("\e[31mError:\e[0m Wrong arguments\n");
	}
}

static void	init_table(t_table *table, int argc, char **argv)
{
	table->countPhilo = ft_atoi(argv[1]);
	table->timeToDie = ft_atoi(argv[2]);
	table->timeToEat = ft_atoi(argv[3]);
	table->timeToSleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->numberOfMeals = ft_atoi(argv[5]);
	else
		table->numberOfMeals = -1;
	if (!table->countPhilo || !table->timeToDie || !table->timeToEat
		|| !table->timeToSleep || !table->numberOfMeals)
		ft_error("\e[31mError:\e[0m Parameters can't be zero\n");
}

static void	memoryFree(t_philo *philo, t_table *table)
{
	if (sem_unlink("message") || sem_unlink("forks") || sem_unlink("takeForks")
		|| sem_unlink("whoDied") || sem_unlink("philoFeed"))
		ft_error("\e[31mError:\e[0m Error sem_unlink\n");
	if (sem_close(philo->deathMessage) || sem_close(philo->countForks)
		|| sem_close(philo->takeForks) || sem_close(philo->whoDied)
		|| sem_close(philo->philoFeed))
		ft_error("\e[31mError:\e[0m Error sem_close\n");
	free(philo);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philosophers;

	validate_arg(argc, argv);
	init_table(&table, argc, argv);
	philosophers = malloc(sizeof(*philosophers) * table.countPhilo);
	if (!philosophers)
		ft_error("\e[31mError:\e[0m Memory allocate error\n");
	basis(philosophers, &table);
	memoryFree(philosophers, &table);
	return (0);
}
