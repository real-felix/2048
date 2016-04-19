#include "game_2048.h"

#include <stdlib.h>

#define EXAMPLE_2048	0

static void				example_color(t_2048 *datas)
{
	datas->grid[0][0] = 2;
	datas->grid[0][1] = 4;
	datas->grid[0][2] = 8;
	datas->grid[0][3] = 16;
	datas->grid[0][4] = 32;
	datas->grid[1][0] = 64;
	datas->grid[1][1] = 128;
	datas->grid[1][2] = 256;
	datas->grid[1][3] = 512;
	datas->grid[1][4] = 1024;
	datas->grid[2][0] = 2048;
	datas->grid[2][1] = 4096;
	datas->grid[2][2] = 8192;
	datas->grid[2][3] = 16384;
	datas->grid[2][4] = 32768;
	datas->grid[3][0] = 65536;
}

static void				init_game(t_2048 *datas)
{
	srand(time(0));
	datas->grid_size = 4;
	if (IS_SQUARE(WIN_VALUE))
		datas->win_value = WIN_VALUE;
	else
		datas->win_value = 2048;
	datas->grid_nb_init = 2;
	datas->grid_max_rand = 4;
	datas->grid_max_rand_nb = 1;
	datas->already_won = 0;
	if (EXAMPLE_2048)
		example_color(datas);
	else
		grid_init(datas);
	resize_2048(datas);
	display_2048(datas);
	datas->key = 0;
}

static void				game_check_status(t_2048 *datas)
{
	int					ch;
	int					size;

	size = datas->grid_size * datas->col_gap + 1;
	if (datas->grid_status == SWP_RUNNING_WIN)
	{
		datas->already_won = 1;
		mvprintw(0, 0, "%-*s", size, "You won ! Continue anyway ?");
		ch = get_choice(datas, 2, 2, "Yes", "No", NULL);
		if (ch)
			(void)grid_init(datas);
	}
	else
	{
		if (datas->grid_status == SWP_GAME_OVER)
			mvprintw(0, 0, "%-*s", size, "You lose (press <ENTER>)");
		else if (datas->grid_status == SWP_WIN)
			mvprintw(0, 0, "%-*s", size, "No more move (press <ENTER>)");
		while (getch() != 10)
			;
		grid_init(datas);
	}
}

static int				game_keys(t_2048 *datas)
{
	int					ret;

	ret = 0;
	timeout(-1);
	if ((datas->key = getch()) == 'A')
		ret = swipe(datas, UP);
	else if (datas->key == 'B')
		ret = swipe(datas, DOWN);
	else if (datas->key == 'C')
		ret = swipe(datas, RIGHT);
	else if (datas->key == 'D')
		ret = swipe(datas, LEFT);
	if ((datas->grid_status == SWP_RUNNING)
			|| (datas->already_won && (datas->grid_status == SWP_RUNNING_WIN)))
		return (ret);
	display_2048(datas);
	attron(COLOR_PAIR(33));
	game_check_status(datas);
	attroff(COLOR_PAIR(33));
	return (1);
}

void					game_2048(t_2048 *datas)
{
	init_game(datas);
	while (42)
	{
		if (datas->key == KEY_RESIZE)
		{
			resize_2048(datas);
			display_2048(datas);
			display_2048(datas);
		}
		if (((datas->key = getch()) == 033) && (!datas->err_size))
		{
			timeout(0);
			if (getch() < 0)
			{
				if (menu_2048(datas) < 0)
					break ;
				display_2048(datas);
			}
			else if (game_keys(datas))
				display_2048(datas);
		}
	}
}
