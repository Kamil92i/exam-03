/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberraho <kberraho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:52:59 by kberraho          #+#    #+#             */
/*   Updated: 2025/11/02 16:51:42 by kberraho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	check_int(char **str, int ac)
{
	int	j;
	int	i;

	j = 1;
	while (j < ac)
	{
		i = 0;
		if (str[j][i] == '-' || str[j][i] == '+')
			i++;
		while (str[j][i])
		{
			if (str[j][i] < '0' || str[j][i] > '9')
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

void	solve(int *nums, int size, int target, int *subset, int index,
		int sub_size, int curr_sum)
{
	if (index == size)
	{
		if (curr_sum == target)
		{
			for (int i = 0; i < sub_size; i++)
			{
				printf("%d", subset[i]);
				if (i != sub_size - 1)
					printf(" ");
			}
			printf("\n");
		}
		return ;
	}
	solve(nums, size, target, subset, index + 1, sub_size, curr_sum);
	subset[sub_size] = nums[index];
	solve(nums, size, target, subset, index + 1, sub_size + 1, curr_sum
		+ nums[index]);
}

int	main(int ac, char **av)
{
	int	target;
	int	*nums;
		int subset[(ac - 2)];

	if (ac > 3 || check_int(av, ac))
	{
		target = atoi(av[1]);
		nums = malloc(sizeof(int) * (ac - 2));
		for (int i = 0; i < ac - 2; i++)
		{
			nums[i] = atoi(av[i + 2]);
		}
		solve(nums, (ac - 2), target, subset, 0, 0, 0);
		free(nums);
		return (0);
	}
	return (1);
}


























#include <stdlib.h>
#include <stdio.h>

/* ------------------------------- utils ----------------------------------- */

static void	*ps_xmalloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
		exit(1);
	return (p);
}

static void	ps_print_line(const int *buf, int size)
{
	int	i;

	if (size <= 0)
		return ;
	i = 0;
	while (i < size)
	{
		if (i > 0)
			printf(" ");
		printf("%d", buf[i]);
		i++;
	}
	printf("\n");
}

/* ------------------------------- solver ---------------------------------- */

typedef struct s_ctx
{
	int	*arr;
	int	len;
	int	target;
}	t_ctx;

static void	ps_dfs(const t_ctx *ctx, int idx, long sum, int *buf, int bsz)
{
	if (idx == ctx->len)
	{
		if (bsz > 0 && sum == (long)ctx->target)
			ps_print_line(buf, bsz);
		return ;
	}
	buf[bsz] = ctx->arr[idx];
	ps_dfs(ctx, idx + 1, sum + (long)ctx->arr[idx], buf, bsz + 1);
	ps_dfs(ctx, idx + 1, sum, buf, bsz);
}

static void	ps_solve(const t_ctx *ctx)
{
	int	*buf;

	if (ctx->len <= 0)
		return ;
	buf = (int *)ps_xmalloc(sizeof(int) * ctx->len);
	ps_dfs(ctx, 0, 0, buf, 0);
	free(buf);
}

/* ------------------------------- parsing --------------------------------- */

static int	ps_parse_args(int ac, char **av, t_ctx *ctx)
{
	int	i;

	if (ac < 2)
		return (0);
	ctx->target = atoi(av[1]);
	ctx->len = ac - 2;
	if (ctx->len <= 0)
	{
		ctx->arr = NULL;
		return (1);
	}
	ctx->arr = (int *)ps_xmalloc(sizeof(int) * ctx->len);
	i = 0;
	while (i < ctx->len)
	{
		ctx->arr[i] = atoi(av[i + 2]);
		i++;
	}
	return (1);
}

/* -------------------------------- main ----------------------------------- */

int	main(int ac, char **av)
{
	t_ctx	ctx;

	if (!ps_parse_args(ac, av, &ctx))
		return (0);
	ps_solve(&ctx);
	free(ctx.arr);
	return (0);
}
