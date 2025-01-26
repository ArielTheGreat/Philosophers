#include "../philo.h"

int	ft_atoi(const char *str)
{
	int	z;
	int	p;

	z = 0;
	p = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			p = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		z = z * 10 + (*str - '0');
		str++;
	}
	return (p * z);
}