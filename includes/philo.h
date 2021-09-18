#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_table
{
	int				countPhilo;
	int				isDead;
	int				numberOfMeals;
	long			timeToDie;
	long			timeToEat;
	long			timeToSleep;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
}				t_table;

typedef struct s_philo
{
	int				philoID;
	int				feed;
	long			lastMeal;
	pthread_t		threadID;
	pthread_mutex_t	*deathMessage;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}				t_philo;

int		ft_isdigit(int c);
int		ft_atoi(char *str);
void	ft_error(char *s);

long	gettime(void);
void	my_sleep(long time);

void	basis(t_philo *philosophers, t_table *table);

void	eating(t_philo *philosophers);
void	sleeping(t_philo *philosophers);
void	thinking(t_philo *philosophers);

#endif