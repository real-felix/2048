#include "game_2048.h"

static int				choice_size(t_2048 *datas)
{
	int					c;
	int					tmp;

	tmp = datas->tmp[3];
	datas->tmp[3] = 0;
	if ((c = get_choice(datas, 5, 4, "4", "5", "6", "7", "8", NULL)) < 0)
	{
		display_2048(datas);
		datas->tmp[3] = tmp;
		return (-1);
	}
	datas->grid_size = c + 4;
	resize_2048(datas);
	grid_init(datas);
	return (0);
}

static int				choice_win(t_2048 *datas)
{
	int					c;
	int					tmp;

	tmp = datas->tmp[3];
	datas->tmp[3] = 0;
	if ((c = get_choice(datas, 6, 4, "64", "128", "256", "512", "1024",
					"2048", "4096", "8192", "16384", "65536", NULL)) < 0)
	{
		display_2048(datas);
		datas->tmp[3] = tmp;
		return (-1);
	}
	datas->win_value = 1 << (c + 6);
	grid_init(datas);
	return (0);
}

static int				choice_max_rand(t_2048 *datas)
{
	int					c;
	int					tmp;

	tmp = datas->tmp[3];
	datas->tmp[3] = 0;
	if ((c = get_choice(datas, 7, 4, "2", "4", "8", "16", "32", NULL)) < 0)
	{
		display_2048(datas);
		datas->tmp[3] = tmp;
		return (-1);
	}
	datas->grid_max_rand = 1 << (c + 1);
	grid_init(datas);
	return (0);
}

static int				choice_poping(t_2048 *datas)
{
	int					c;
	int					tmp;

	tmp = datas->tmp[3];
	datas->tmp[3] = 0;
	if ((c = get_choice(datas, 8, 4, "1", "2", "3", "4", NULL)) < 0)
	{
		display_2048(datas);
		datas->tmp[3] = tmp;
		return (-1);
	}
	datas->grid_max_rand_nb = c + 1;
	grid_init(datas);
	return (0);
}

int						menu_2048(t_2048 *datas)
{
	datas->tmp[0] = 1;
	while (datas->tmp[0])
	{
		wrefresh(stdscr);
		datas->tmp[1] = get_choice(datas, 2, 2, "New game", "Grid size",
		"Win value", "Max rand", "Nbr of poping nums", "Quit", NULL);
		if (!datas->tmp[1])
			datas->tmp[0] = grid_init(datas);
		else if (datas->tmp[1] == 1)
			datas->tmp[0] = choice_size(datas);
		else if (datas->tmp[1] == 2)
			datas->tmp[0] = choice_win(datas);
		else if (datas->tmp[1] == 3)
			datas->tmp[0] = choice_max_rand(datas);
		else if (datas->tmp[1] == 4)
			datas->tmp[0] = choice_poping(datas);
		else if (datas->tmp[1] == 5)
			return (-1);
		else
			break ;
	}
	datas->tmp[3] = 0;
	timeout(0);
	return (0);
}
