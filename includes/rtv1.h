/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 04:43:13 by fcecilie          #+#    #+#             */
/*   Updated: 2017/08/16 17:40:00 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/includes/libft.h"
# include "../minilibx/mlx.h"
# include <math.h>
# include <fcntl.h>

typedef struct	s_space
{
	double	x;
	double	y;
	double	z;
}				t_space;

typedef struct	s_object
{
	int				id;
	int				type;
	double			ray;
	t_space			color;
	t_space			origin;
	t_space			rotation;
	t_space			translation;
	struct s_object	*next;
}				t_object;

typedef struct	s_light
{
	int				id;
	int				type;
	t_space			color;
	t_space			origin;
	t_space			translation;
	struct s_light	*next;
}				t_light;

typedef struct	s_view_plane
{
	double	x_indent;
	double	y_indent;
	t_space vec_dir;
	t_space vec_dir_right;
	t_space vec_dir_up;
	t_space view_plane_size;
	t_space view_plane_up_left;
}				t_view_plane;

typedef struct	s_rt
{
	void		*mlx;
	void		*win;
	void		*img;

	int			*add;
	int			bpp;
	int			bpl;
	int			edn;

	int			actual;
	t_object	*obj;
	t_light		*lux;

	t_space		cam_pos;
	t_space		rotation;
	t_space		translation;
	t_space		point;
	t_space		rotated_point;

	double		dist;
	int			id;
	t_space		color;
	int			nb_light;
}				t_rt;

int				display(t_rt *r);
int				parsing(t_rt *r, char *argv);
int				parsing_camera(t_rt *r, char *file);
int				parsing_objects(t_rt *r, char *file);
int				parsing_lights(t_rt *r, char *file);
int				attribution(t_rt *r, t_view_plane *p);
int				heart(t_rt *r, t_view_plane *p);
int				dist_camera_obj(t_rt *r, t_space dir);
int				dist_camera_lux(t_rt *r);
double			plan(t_rt *r, t_space dir);
double			sphere(t_rt *r, t_space dir);
double			cone(t_rt *r, t_space dir);
double			cylindre(t_rt *r, t_space dir);
double			plan_lux(t_rt *r, t_space dir);
double			sphere_lux(t_rt *r, t_space dir);
double			cone_lux(t_rt *r, t_space dir);
double			cylindre_lux(t_rt *r, t_space dir);
int				plan_vector(t_rt *r, t_space *vector);
int				sphere_vector(t_rt *r, t_space *vector);
int				cone_vector(t_rt *r, t_space *vector);
int				cylindre_vector(t_rt *r, t_space *vector);
int				hub(int keycode, void *param);
int				leave_window(void);
int				matrice_x(t_space *m, double angle);
int				matrice_y(t_space *m, double angle);
int				matrice_z(t_space *m, double angle);
t_space			obj_rotate(t_space rot, t_space vec);
int				point_space(t_space *n, double x, double y, double z);
int				catch_value(char *str, int nb);
double			delta(double a, double b, double c);
t_space			vec_unit(t_space origin, t_space ending);
int				get_t_space(char *interval, t_space *space, char *start);
int				get_file_to_string(int fd, char **file);
int				brackets(char *str);
int				get_string_interval(char *str, char *start, char end,
		char **interval);
int				get_objects_informations(t_object *new, char *interval);
int				get_lights_informations(t_light *new, char *interval);

#endif
