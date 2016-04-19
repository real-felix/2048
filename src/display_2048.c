#include "game_2048.h"

#include <stdio.h>

static inline unsigned	ft_nbrlen(int64_t nbr, const size_t base)
{
	unsigned			n;

	n = (nbr < 0 ? 2 : 1);
	while (nbr /= (int)base)
		++n;
	return (n);
}

static inline int		ft_log2(int nbr)
{
	int					i;

	if (!nbr)
		return (0);
	i = 1;
	while (!((nbr >>= 1) & 1))
		++i;
	return (i);
}

static void				disp_numbers_ftn(t_2048 *datas, int r, int c)
{
	if (!datas->grid[r][c])
		return ;
	attron(A_BOLD);
	mvprintw(r * datas->row_gap + datas->row_gap / 2 + 1,
			c * datas->col_gap +
			(datas->col_gap - ft_nbrlen(datas->grid[r][c], 10)) / 2,
			"%d", datas->grid[r][c]);
	attroff(A_BOLD);
}

static void				disp_numbers(t_2048 *datas)
{
	int					log;

	for (int c = 0 ; c < datas->grid_size ; ++c)
	{
		for (int r = 0 ; r < datas->grid_size ; ++r)
		{
			log = ft_log2(datas->grid[r][c]);
			attron(COLOR_PAIR(log));
			for (int i = 1 ; i < datas->col_gap ; i++)
			{
				for (int j = 1 ; j < datas->row_gap ; j++)
					mvprintw(r * datas->row_gap + j + 1,
							c * datas->col_gap + i, " ");
			}
			disp_numbers_ftn(datas, r, c);
			attroff(COLOR_PAIR(log));
		}
	}
}

static void				display_2048_ftn(t_2048 *datas)
{
	char				buff[1024];
	int					size;

	if (datas->grid_status > SWP_RUNNING)
		sprintf(buff, "Menu: <ESC> | Score: %u | You already won :)",
				datas->score);
	else
		sprintf(buff, "Menu: <ESC> | Score: %u | Reach %d to win",
				datas->score, datas->win_value);
	attron(COLOR_PAIR(34));
	size = datas->grid_size * datas->col_gap + 1;
	mvprintw(0, 0, "%-*.*s", size, size, buff);
	attroff(COLOR_PAIR(34));
	disp_numbers(datas);
}

int						display_2048(t_2048 *datas)
{
	clear();
	if ((4 * datas->grid_size + 2 > datas->rows) ||
			(6 * datas->grid_size + 1 > datas->cols))
		return (size_error(datas));
	datas->err_size = 0;
	display_2048_ftn(datas);
	attron(COLOR_PAIR(32));
	for (int i = 0 ; i < datas->grid_size + 1 ; ++i)
	{
		move(i * datas->row_gap + 1, 0);
		for (int j = 0 ; j < datas->col_gap * datas->grid_size +
					(datas->cols % datas->col_gap ? 1 : 2) ; ++j)
			printw(".");
	}
	for (int i = 0 ; i < datas->grid_size + 1 ; ++i)
	{
		for (int j = 1 ; j < datas->row_gap * datas->grid_size + 1 ; ++j)
			mvprintw(j, i * datas->col_gap, ".");
	}
	attroff(COLOR_PAIR(32));
	refresh();
	return (0);
}
