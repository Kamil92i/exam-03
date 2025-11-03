#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	check_dup(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[i] == str[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}


void	sorted(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[i] > str[j])
			{
				tmp = str[i];
				str[i] = str[j];
				str[j] = str[i];
			}
			j++;
		}
		i++;
	}
}

void	generate(char *str, char *result, int *used, int len, int depth)
{
	int	i;

	if (depth == len) // Si on a placé len caractères, on a formé une permutation complète
	{
		write(1, result, len);
		write(1, "\n", 1);
		return ;
	}
	i = 0;
	while (i < len)
	{
		// Si le caractère str[i] n'a pas encore été utilisé dans la permutation
		if (!used[i])
		{
			used[i] = 1; // On marque ce caractère comme utilisé
			result[depth] = str[i]; // On le place à la position 'depth' de la permutation
			generate(str, result, used, len, depth + 1); // On poursuit avec le caractère suivant
			used[i] = 0; // On "désutilise" le caractère pour les prochaines permutations
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int		len;
	char	*result;
	int		*used;

	if (ac != 2 || check_dup(av[1]))
		return (1);
	len = ft_strlen(av[1]);
	result = malloc(len + 1);
	used = calloc(len, sizeof(int));
	if (!result || !used)
		return (1);
	sorted(av[1]);
	generate(av[1], result, used, len, 0);
	free(result);
	free(used);
	return (0);
}

/* depth = 0
│
├── 'a' choisi → depth = 1
│   │
│   ├── 'b' choisi → depth = 2
│   │   │
│   │   └── 'c' choisi → depth = 3 → affiche "abc"
│   │
│   └── 'c' choisi → depth = 2
│       │
│       └── 'b' choisi → depth = 3 → affiche "acb"
│
├── 'b' choisi → depth = 1
│   │
│   ├── 'a' choisi → depth = 2
│   │   │
│   │   └── 'c' choisi → depth = 3 → affiche "bac"
│   │
│   └── 'c' choisi → depth = 2
│       │
│       └── 'a' choisi → depth = 3 → affiche "bca"
│
└── 'c' choisi → depth = 1
    │
    ├── 'a' choisi → depth = 2
    │   │
    │   └── 'b' choisi → depth = 3 → affiche "cab"
    │
    └── 'b' choisi → depth = 2
        │
        └── 'a' choisi → depth = 3 → affiche "cba" */