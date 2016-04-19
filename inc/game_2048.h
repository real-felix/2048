/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2048.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaudre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/01 16:51:12 by fdaudre-          #+#    #+#             */
/*   Updated: 2015/03/01 22:19:32 by fdaudre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_2048_H
# define GAME_2048_H

# include <ncurses.h>
# include <sys/ioctl.h>
# include <time.h>
# include <stdint.h>

# define IS_SQUARE(x) ((((x & -x) ^ x) == 0)  &&  (x != 0))

typedef struct winsize	t_winsize;

typedef enum			e_const
{
	WIN_VALUE = 2048
}						t_const;

typedef enum			e_move
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}						t_move;

typedef enum			e_reverse_type
{
	REV_NORMAL,
	REV_SWIPE_XY,
	REV_INVERT
}						t_reverse_type;

typedef enum			e_swipe_result
{
	SWP_GAME_OVER = -1,
	SWP_RUNNING,
	SWP_RUNNING_WIN,
	SWP_WIN
}						t_swipe_result;

typedef struct			s_2048
{
	int					rows;
	int					cols;
	int					row_gap;
	int					col_gap;
	int					win_value;
	unsigned int		score;
	t_swipe_result		grid_status;
	int					grid_size;
	int					grid_nb_init;
	int					grid[16][16];
	int					grid_last_merged[2];
	int					grid_max_rand;
	int					grid_max_rand_nb;
	int					key;
	WINDOW				*subw;
	int					tmp[8];
	int					err_size;
	int					already_won;
}						t_2048;

void					game_2048(t_2048 *datas);
void					resize_2048(t_2048 *datas);
int						display_2048(t_2048 *datas);
int						menu_2048(t_2048 *datas);
int						get_choice(t_2048 *datas, int li, int co, ...);
int						size_error(t_2048 *datas);

int						grid_rand(t_2048 *datas, int rand_nb);
int						swipe(t_2048 *datas, t_move direction);
int						game_status(t_2048 *grid);
int						grid_init(t_2048 *datas);

#endif
