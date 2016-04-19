#include "game_2048.h"

void					resize_2048(t_2048 *datas)
{
	t_winsize			ws;

	ioctl(0, TIOCGWINSZ, &ws);
	datas->rows = ws.ws_row;
	datas->cols = ws.ws_col;
	datas->row_gap = (ws.ws_row - 2) / (datas->grid_size + 0);
	datas->col_gap = (ws.ws_col - 1) / (datas->grid_size + 0);
}
