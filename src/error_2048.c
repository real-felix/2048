#include "game_2048.h"

int						size_error(t_2048 *datas)
{
	datas->err_size = 1;
	mvprintw(0, 0, "Size up window !");
	refresh();
	return (0);
	(void)datas;
}
