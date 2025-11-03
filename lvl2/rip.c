#include <stdio.h>

int	check(char *str)
{
	int	i;
	int	opened;
	int	closed;

	opened = 0;
	closed = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			opened++;
		else if (str[i] == ')')
		{
			if (opened > 0)
				opened--;
			else
				closed++;
		}
		i++;
	}
	return (opened + closed);
}

void	rip(char *str, int must_fix, int n_fix, int pos)
{
	int		i;
	char	c;

	// Si on a supprimé le bon nombre de parenthèses
	// et que la chaîne est valide → on affiche
	if (must_fix == n_fix && !check(str))
	{
		puts(str);
		return ;
	}
	i = pos;
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
		{
			c = str[i];                       // sauvegarde le caractère
			str[i] = ' ';                     // le "supprime"
			rip(str, must_fix, n_fix + 1, i); // appel récursif
			str[i] = c;                       // le restaure (backtracking)
		}
		i++;
	}
}

int	main(int ac, char **ag)
{
	if (ac < 2)
		return (1);

	int	m_fix;
	m_fix = check(ag[1]);
	if (m_fix == 0)
	{
		puts(ag[1]);
		return (0);
	}
	rip(ag[1], m_fix, 0, 0);
	return 0;
}

