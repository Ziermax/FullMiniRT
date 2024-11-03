/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:37:33 by atudor            #+#    #+#             */
/*   Updated: 2024/09/18 09:37:36 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "structs.h"

// void draw_image(t_img img);
// void render_scene(t_mlx mlx);


// camera functions
t_camera *create_camera(void);

// light functions
void	setup_lights(t_scene *scene, int num_lights);
t_light	*create_light(t_scene *scene);

// sphere functions
float	check_sphere_intersection(t_data *data, t_ray ray);
void	setup_spheres(t_scene *scene, int num_spheres);
t_sphere	*create_sphere(t_scene *scene);

// plane functions
void	setup_planes(t_scene *scene, int num_planes);
t_plane	*create_plane(t_scene *scene);

// cylinder functions
void	setup_cylinders(t_scene *scene, int num_cylinders);
t_cylinder	*create_cylinder(t_scene *scene);

// inits
void	init_vector(t_vector *vector, double x, double y, double z);
void	create_scene(t_scene *scene);

// render engine
void	render_engine(t_data *data);

// math functions
t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_scalar(t_vector a, double scalar);
t_vector	vector_cross_product(t_vector a, t_vector b);
double		normal_dev_coordinates(int coord, t_data *data, int ratio, int b);
t_vector	normalize_vector(double x, double y, double z);
t_vector	vector_subtract(t_vector a, t_vector b);
float	dot_product(t_vector a, t_vector b);

// ray functions
t_vector	calculate_direction(t_vector camera_o, double ndc_x, double ndc_y, t_data *data);
t_ray	create_ray(t_data *data, int x, int y);


#endif