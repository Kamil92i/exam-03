```c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int    ft_abs(int n)
{
    if (n < 0)
        return (-n);
    return (n);
}

int    is_safe(int *pos, int colonne, int ligne)
{
    int    i;

    i = 0;
    while (i < colonne)
    {
        if (pos[i] == ligne)
            return (0);
        if (ft_abs(pos[i] - ligne) == ft_abs(i - colonne))
            return (0);
        i++;
    }
    return (1);
}

void    solve(int colonne, int *pos, int n)
{
    int    ligne;
    int    i;

    if (colonne == n)
    {
        i = 0;
        while (i < n)
        {
            printf("%d", pos[i]);
            if (i < n - 1)
                printf(" ");
            i++;
        }
        printf ("\n");
        return ;
    }
    ligne = 0;
    while (ligne < n)
    {
        if (is_safe(pos, colonne, ligne))
        {
            pos[colonne] = ligne;
            solve(colonne + 1, pos, n);
        }
        ligne++;
    }
}

#include <stdio.h>
int    main(int ac , char **av)
{
    if (ac == 2 && atoi(av[1]) > 0)
    {
        int    n = atoi(av[1]);
        int    *pos;
        
        pos = malloc(sizeof(int) * n);
        if (!pos)
            return (1);
        solve(0, pos, n);
        free(pos);
        return (0);
    }
    return (1);
}
```
