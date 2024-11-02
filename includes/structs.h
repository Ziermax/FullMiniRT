/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:55:37 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/11/02 23:51:01 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../MLX42/include/MLX42/MLX42.h"

# define W_WIDTH 1000
# define W_HEIGHT 1000

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
	t_vector origin;
	t_vector direction;
}	t_ray;

typedef struct s_sphere
{
	t_vector	center;
	float		radius;
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
	float		radius;
	float		height;
	t_vector	color;
}	t_cylinder;

typedef struct s_paraboloid
{
	t_vector	center;
	t_vector	direction;
	float		radius;
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
//	t_sphere	**spheres;
//	t_plane		**planes;
//	t_cylinder	**cylinders;
//	int			num_spheres;
//	int			num_planes;
//	int			num_cylinders;
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
//	int			aspect_ratio;
//	double		scale;
}	t_data;

#endif
