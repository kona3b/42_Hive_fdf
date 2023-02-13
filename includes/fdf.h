/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaittola <kaittola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:44:55 by kaittola          #+#    #+#             */
/*   Updated: 2022/10/19 17:45:16 by kaittola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

# include "mlx.h"
# include "libft.h"

# define WIN_H 960
# define WIN_W 1280
# define WIN_N "fdf-kaittola"

# define INT_MAX 2147483647
# define INT_MIN -2147483647

# define RETURN_SUCCESS 1
# define RETURN_ERROR 0

# define TRUE 1
# define FALSE 0

# define EXIT_ERROR 1
# define EXIT_SUCCESS 0

# define SPACING 2
# define DO_SWAP 1
# define NO_SWAP 0

# define POINT_0 0
# define POINT_1 1

# define LOWEST ((double)0.3)
# define HIGHEST ((double)1.0)

# define TXT 0xEAEAEA

# define EXIT_WINDOW "Window closed, successful exit!\n"
# define EXIT_USAGE "usage: ./fdf <filename>.fdf\n"
# define EXIT_MAP_SIZE "Map temp size < 0 error!\n"
# define EXIT_MAP_MALLOC "Map lines malloc error!\n"
# define EXIT_LINES_0 "Line length not equal error!\n"
# define EXIT_LINES_1 "Line length temp < 0 error!\n"
# define EXIT_LINES_2 "Line length lines malloc error!\n"
# define EXIT_SPLIT "ft_strsplit returned NULL error!\n"
# define EXIT_OPEN "File open error!\n"
# define EXIT_GNL "GNL error!\n"
# define EXIT_MAP_LINES "Map without lines error!\n"
# define EXIT_MAP_LINES2 "Map numbers error!\n"
# define EXIT_CLOSE "File close error!\n"
# define EXIT_MLX_1 "mlx init failure error!\n"
# define EXIT_MLX_2 "mlx win pointer NULL error!\n"
# define EXIT_ESC "Esc pressed, successfull exit!\n"

typedef struct s_point
{
	int		row;
	int		col;
}	t_point;

typedef struct s_minmax
{
	int		min;
	int		max;
}	t_minmax;

typedef struct s_segment
{
	t_point	*b;
	t_point	*e;
}	t_segment;

typedef struct s_double_coord
{
	double	row;
	double	col;
}	t_double_coord;

typedef struct s_row
{
	int		*line;
	int		point_count;
	int		size;
}	t_row;

typedef struct s_map
{
	t_row		*lines;
	int			line_count;
	int			size;
	int			max_point_count;
	t_minmax	height;
}	t_map;

typedef struct s_mouse
{
	t_point	prev;
	t_point	curr;
	t_point	diff;
	char	isdown;
}	t_mouse;

typedef struct s_fdf
{
	t_point		origin;
	t_point		offset;
	double		height;
	int			zoom;
	int			proj;
	int			color_theme;
	t_map		map;
}	t_fdf;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_mlx;

typedef struct s_program
{
	t_mlx	*mlx;
	t_fdf	*fdf;
	t_mouse	*mouse;
}	t_program;

enum e_event
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum e_key
{
	KEY_C = 8,
	KEY_P = 35,
	KEY_ESC = 53,
	UP_KEY = 126,
	DOWN_KEY = 125
};

enum e_mouse
{
	MOVE = 0,
	LEFT_CLICK = 1,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5
};

enum e_projection
{
	PROJ_PARALLEL = 0,
	PROJ_ISOMETRIC = 30,
	DIFF_ISO_MIL = 15,
	PROJ_MILITARY = 45
};

enum e_zoom
{
	ZOOM_IN = 1,
	ZOOM_OUT = -1
};

enum e_color_theme
{
	BLUE = 0,
	GREEN = 8,
	RED = 16
};

void	exit_message(const char *msg, int v);
int		exit_success(void);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	change_colors(t_program *program);
void	change_projection(t_program *program);
void	check_lines(t_map *map);
void	parse(char *filename, t_map *map);
void	init_req(t_program *program);
void	init_img(t_mlx *mlx, t_fdf *fdf);
void	init_offset(t_fdf *fdf);
void	init_origin(t_fdf *fdf);
int		mouse_handler(int button, int x, int y, t_program *program);
int		keys_handler(int key, t_program *program);
int		mouse_action_down(int button, int x, int y, t_program *program);
int		mouse_action_move(int x, int y, t_program *program);
int		mouse_action_up(int button, int x, int y, t_program *program);
int		zoomer(int dir, int zoom);
void	pan(t_program *program);
void	offsetter(t_point *mouse, t_program *program, int prev_zoom);
void	stick_zoom(unsigned int *zoom);
void	draw(t_mlx *mlx, t_fdf *fdf);
double	max(double d0, double d1);
int		abs_max(int i0, int i1);
int		in_range(int lowest, int value, int max);
int		get_height(int height, t_fdf *fdf);
void	projection(t_point *dst, t_point *scr, t_fdf *fdf);
int		get_color(double percent, t_segment *points, t_fdf *fdf);
void	print_menu(t_mlx *mlx);
void	check_nbrs(char **numerals);

#endif
