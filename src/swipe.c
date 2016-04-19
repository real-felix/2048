#include "game_2048.h"

static int	out_of_boundary(int grid_size, int x, int y)
{
	if (x < 0 || x >= grid_size)
		return (1);
	if (y < 0 || y >= grid_size)
		return (1);
	return (0);
}

static void	dir_to_xy(t_move direction, int *x, int *y, char type)
{
	int x_factor;
	int y_factor;

	x_factor = 0;
	y_factor = 0;
	if (direction == LEFT || direction == RIGHT)
		x_factor = (direction == LEFT) ? 1 : -1;
	if (direction == UP || direction == DOWN)
		y_factor = (direction == UP) ? 1 : -1;
	if (type == REV_NORMAL)
	{
		*x += x_factor;
		*y += y_factor;
	}
	else if (type == REV_SWIPE_XY)
	{
		*x += (y_factor) ? 1 : 0;
		*y += (x_factor) ? 1 : 0;
	}
	else if (type == REV_INVERT)
	{
		*x -= x_factor;
		*y -= y_factor;
	}
}

static int	grid_merge(t_2048 *grid, int *next_xy, int x, int y)
{
	if (grid->grid[next_xy[1]][next_xy[0]] == (grid->grid)[y][x])
		if (grid->grid_last_merged[0] != next_xy[0] || \
				grid->grid_last_merged[1] != next_xy[1])
		{
			(grid->grid)[next_xy[1]][next_xy[0]] += (grid->grid)[y][x];
			(grid->grid)[y][x] = 0;
			grid->grid_last_merged[0] = next_xy[0];
			grid->grid_last_merged[1] = next_xy[1];
			return (1);
		}
	return (0);
}

static int	swipe_scroll(t_2048 *grid, int x, int y, t_move direction)
{
	int		next_xy[2];
	int		ret;

	ret = 0;
	if ((grid->grid)[y][x] == 0)
		return (0);
	next_xy[0] = x;
	next_xy[1] = y;
	dir_to_xy(direction, next_xy, next_xy + 1, REV_INVERT);
	while (!out_of_boundary(grid->grid_size, next_xy[0], next_xy[1]))
	{
		if ((grid->grid)[next_xy[1]][next_xy[0]] != 0)
			return (ret + grid_merge(grid, next_xy, x, y));
		(grid->grid)[next_xy[1]][next_xy[0]] = (grid->grid)[y][x];
		(grid->grid)[y][x] = 0;
		x = next_xy[0];
		y = next_xy[1];
		ret++;
		dir_to_xy(direction, next_xy, next_xy + 1, REV_INVERT);
	}
	return (ret);
}

int			swipe(t_2048 *grid, t_move direction)
{
	int		xy[2];
	int		sub_xy[2];
	int		ret;

	ret = 0;
	grid->grid_last_merged[0] = -1;
	grid->grid_last_merged[1] = -1;
	xy[0] = (direction == RIGHT) ? grid->grid_size - 1 : 0;
	xy[1] = (direction == DOWN) ? grid->grid_size - 1 : 0;
	while (!out_of_boundary(grid->grid_size, xy[0], xy[1]))
	{
		sub_xy[0] = xy[0];
		sub_xy[1] = xy[1];
		dir_to_xy(direction, (sub_xy), (sub_xy + 1), REV_NORMAL);
		while (!out_of_boundary(grid->grid_size, sub_xy[0], sub_xy[1]))
		{
			ret += swipe_scroll(grid, sub_xy[0], sub_xy[1], direction);
			dir_to_xy(direction, (sub_xy), (sub_xy + 1), REV_NORMAL);
		}
		dir_to_xy(direction, (xy), (xy + 1), REV_SWIPE_XY);
	}
	if (ret)
		ret += grid_rand(grid, grid->grid_max_rand_nb);
	grid->grid_status = game_status(grid);
	return (ret);
}
