#include "game_2048.h"

static void				init_colors(void)
{
	start_color();
	init_color(100, 900, 800, 800);
	init_color(101, 900, 800, 600);
	init_color(102, 900, 700, 400);
	init_color(103, 900, 500, 500);
	init_color(104, 950, 300, 300);
	init_color(105, 950, 300, 0);
	init_color(106, 950, 600, 0);
	init_color(107, 600, 400, 300);
	init_color(108, 600, 300, 0);
	init_color(109, 500, 500, 0);
	init_color(110, 200, 650, 200);
	init_color(111, 450, 950, 700);
	init_color(112, 200, 200, 650);
	init_color(113, 700, 200, 950);
	init_color(114, 900, 900, 400);
	init_color(115, 600, 600, 600);
	init_color(116, 600, 600, 600);
	init_color(117, 600, 600, 600);
	init_color(118, 600, 600, 600);
	init_color(119, 600, 600, 600);
	init_color(COLOR_BLACK, 0, 0, 0);
}

static void				init_2048(void)
{
	init_colors();
	for (int i = 1 ; i < 21 ; ++i)
		init_pair(i, COLOR_BLACK, 99 + i);
	init_pair(32, 8, COLOR_WHITE);
	init_pair(33, COLOR_WHITE, COLOR_RED);
	init_pair(34, COLOR_WHITE, COLOR_BLUE);
}

int						main(void)
{
	t_2048				datas;

	initscr();
	raw();
	noecho();
	curs_set(0);
	init_2048();
	game_2048(&datas);
	endwin();
	return (0);
}
