#include "../includes/philo.h"

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
	table->isDead = 0;
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

static int	memoryFree(t_philo *philosophers, t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->countPhilo)
		if (pthread_mutex_destroy(&table->forks[i]))
			return (1);
	if (pthread_mutex_destroy(&table->message))
		return (1);
	free(table->forks);
	free(philosophers);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philosophers;

	validate_arg(argc, argv);
	init_table(&table, argc, argv);
	philosophers = malloc(sizeof(t_philo) * table.countPhilo);
	if (!philosophers)
		ft_error("\e[31mError:\e[0m Memory allocate error\n");
	table.forks = malloc(sizeof(pthread_mutex_t) * table.countPhilo);
	if (!table.forks)
		ft_error("\e[31mError:\e[0m Memory allocate error\n");
	basis(philosophers, &table);
	return (memoryFree(philosophers, &table));
}
