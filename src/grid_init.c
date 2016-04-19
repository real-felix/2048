#include "game_2048.h"

int			grid_init(t_2048 *grid)
{
	int		x;
	int		y;

	grid->score = 0;
	grid->already_won = 0;
	x = 0;
	y = 0;
	while (y < grid->grid_size)
	{
		while (x < grid->grid_size)
		{
			grid->grid[y][x] = 0;
			x++;
		}
		x = 0;
		y++;
	}
	grid_rand(grid, grid->grid_nb_init);
	return (0);
}
