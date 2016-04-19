#include "game_2048.h"

static int	grid_runnable(t_2048 *grid, int x, int y)
{
	int current;

	for (; y < grid->grid_size ; ++y)
	{
		for (; x < grid->grid_size ; ++x)
		{
			current = grid->grid[y][x];
			if (current == 0)
				return (1);
			if (y < grid->grid_size - 1)
				if (current == grid->grid[y + 1][x])
					return (1);
			if (x < grid->grid_size - 1)
				if (current == grid->grid[y][x + 1])
					return (1);
		}
		x = 0;
	}
	return (0);
}

static int	highest_nbr(t_2048 *grid)
{
	int		x;
	int		y;
	int		highest;
	int		current;

	x = 0;
	y = 0;
	highest = 0;
	while (y < grid->grid_size)
	{
		while (x < grid->grid_size)
		{
			current = grid->grid[y][x];
			if (current > highest)
				highest = current;
			x++;
		}
		x = 0;
		y++;
	}
	return (highest);
}

int			game_status(t_2048 *grid)
{
	int		runnable;
	int		win;

	runnable = grid_runnable(grid, 0, 0);
	win = (highest_nbr(grid) >= grid->win_value) ? 1 : 0;
	if (runnable)
	{
		if (win)
			return (SWP_RUNNING_WIN);
		else
			return (SWP_RUNNING);
	}
	else if (win)
		return (SWP_WIN);
	return (SWP_GAME_OVER);
}
