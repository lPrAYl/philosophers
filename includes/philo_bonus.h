#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_table
{
	int		countPhilo;
	int		numberOfMeals;
	long	timeToDie;
	long	timeToEat;
	long	timeToSleep;
	long	startTime;
}				t_table;

typedef struct s_philo
{
	int		philoID;
	int		feed;
	long	lastMeal;
	pid_t	pid;
	sem_t	*whoDied;
	sem_t	*countForks;
	sem_t	*takeForks;
	sem_t	*philoFeed;
	sem_t	*deathMessage;
	t_table	*table;
}				t_philo;

int			ft_isdigit(int c);
int			ft_atoi(char *str);
void		ft_error(char *s);

long		gettime(void);
void		my_sleep(long time);

void		basis(t_philo *philosophers, t_table *table);

void		eating(t_philo *philosophers);
void		sleeping(t_philo *philosophers);
void		thinking(t_philo *philosophers);

#endif