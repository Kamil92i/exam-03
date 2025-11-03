#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(len + 1);
	if (!join)
	{
		perror("Error");
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	free(s1);
	return (join);
}

char	*stout(void)
{
	char	*line;
	int		fd;
	char	buf[BUFFER_SIZE + 1];

	line = NULL;
	fd = read(0, buf, BUFFER_SIZE);
	while (fd > 0)
	{
		buf[fd] = '\0';
		line = ft_strjoin(line, buf);
		if (!line)
		{
			perror("Error");
			return (NULL);
		}
		fd = read(0, buf, BUFFER_SIZE);
	}
	if (fd == -1)
	{
		perror("Error");
		return (NULL);
	}
	return (line);
}

int	valid(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1 && s2 && s1[i])
	{
		j = 0;
		while (s1[0 + j] == s2[j])
			j++;
		if (s2[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*filter(char *str, char *remove)
{
	int	i;
	int	len_rem = 0;
	int	decrease = 0;

	i = 0;
	len_rem = ft_strlen(remove);
	decrease = len_rem;
	if (!remove || remove[0] == '\0')
		return (str);
	while (str[i])
	{
		if (valid(&str[i], remove))
		{
			while (decrease > 0)
			{
				str[i] = '*';
				i++;
				decrease--;
			}
		}
		else
			i++;
		decrease = len_rem;
	}
	return (str);
}

int	main(int ac, char **av)
{
	char *text;

	if (ac != 2 || !av[1] || av[1][0] == '\0')
		return (1);
	text = stout();
	if (!text)
		return (1);
	filter(text, av[1]);
	printf("%s\n", text);
	free(text);
	return (0);
}
