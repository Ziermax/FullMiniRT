/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:55:37 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/11/03 04:29:57 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../MLX42/include/MLX42/MLX42.h"

# define BPP 1
# define X 0
# define Y 1
# define W_WIDTH 1000
# define W_HEIGHT 1000
# define RED 0xFF0000ff
# define GREEN 0x00FF00ff
# define BLUE 0x0000FFff
# define WHITE 0xFFFFFFff
# define BLACK 0x000000ff
# define YELLOW 0xFFFF00ff

#define SHADOW_BIAS 0.001
#define EPSILON 0.00000000000000001

/* ************************************************************************** */
/*                                Geometry structures                         */
/* ************************************************************************** */

typedef enum e_objtype
{
	SPHERE,
	PLANE,
	CYLINDER,
	PARABOLOID
}	t_objtype;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

typedef struct s_sphere
{
	t_vector	center;
	double		radius;
	t_vector	color;
}	t_sphere;

typedef struct s_plane
{
	t_vector	center;
	t_vector	normal;
	t_vector	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	axis;
	double		radius;
	double		height;
	t_vector	color;
}	t_cylinder;

typedef struct s_paraboloid
{
	t_vector	center;
	t_vector	direction;
	double		radius;
	int			color;
}	t_paraboloid;

typedef union u_shape
{
	t_sphere		sphere;
	t_plane			plane;
	t_cylinder		cylinder;
	t_paraboloid	paraboloid;
}	t_shape;

typedef struct s_object	t_object;

struct s_object
{
	t_object	*next;
	t_objtype	type;
	t_shape		shape;
	int			color;
};

/* ************************************************************************** */
/*                                Scene structures                            */
/* ************************************************************************** */


typedef struct s_intersection {
    t_vector intersection;
    t_object *object;
	bool hit;
} t_intersection;

typedef struct s_light	t_light;

struct s_light
{
	t_light		*next;
	t_vector	origin;
	double		brightness;
	int			color;
};

typedef struct s_camera
{
	t_vector	origin;
	t_vector	orientation;
	double		fov;
}	t_camera;

typedef struct s_scene
{
	t_object	*objects;
	t_light		*lights;
	t_light		amb_light;
	t_camera	camera;
//	int			num_lights;
}	t_scene;

/* ************************************************************************** */
/*                               Data structures                              */
/* ************************************************************************** */

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		scene;
	int			aspect_ratio;
	double		scale;
	int			w_height;
	int			w_width;
}	t_data;

int	proportional_color(double percentage, int min_color, int max_color);
int get_color(t_data *data, t_vector intersection, t_object *object);
#endif
