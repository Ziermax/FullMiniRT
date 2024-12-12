/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:37:33 by atudor            #+#    #+#             */
/*   Updated: 2024/12/12 15:21:24 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "structs.h"

// camera functions
t_camera		create_camera(void);

// light functions
void			setup_lights(t_scene *scene, int num_lights);
t_light			*create_light(t_scene *scene);

// sphere functions
double			choose_smaller_t(double t1, double t2);
double			check_sphere_intersection(t_object *object, t_ray ray);

// plane functions
double			check_plane_intersection(t_object *object, t_ray ray);

// cylinder functions
double			check_round_part(t_object *object, t_ray ray);
double			check_cylinder_cap_intersection(t_ray ray, t_cylinder cylinder);
double			check_cylinder_intersection(t_object *object, t_ray ray);
t_vector		cylinder_normal(t_cylinder cyl, t_vector point);
double			quadratic_with_height_limit(double d,
					double a[3], t_object *o, t_ray r);

// inits
t_scene			get_scene(char *file);
void			free_scene(t_scene *scene);
void			init_vector(t_vector *vector, double x, double y, double z);
void			create_scene(t_scene *scene);

// render engine
t_intersection	check_intersections(t_object *object, t_ray ray);
void			render_engine(t_data *data);

// math functions
t_vector		add_vec(t_vector a, t_vector b);
t_vector		scl_vec(t_vector a, double scalar);
t_vector		vector_cross_product(t_vector a, t_vector b);
double			normal_dev_coordinates(int coord, t_data *data, int b);
t_vector		normalize_vector(double x, double y, double z);
t_vector		sub_vec(t_vector a, t_vector b);
double			dot_product(t_vector a, t_vector b);
double			vector_length(t_vector v);

// ray functions
t_vector		calculate_direction(t_vector camera_dir,
					double ndc_x, double ndc_y);
t_ray			create_ray(t_data *data, int x, int y);

//color utils

int				get_color(t_data *data, t_vector intersection,
					t_object *object);
void			clamp_rgba(int *red, int *green, int *blue, int *alpha);
int				sum_colors(int color1, int color2);
int				scale_color(int base_color, double brightness_factor);
int				clamp_color(int color);
int				multiply_colors_with_fallback(int color1,
					int color2, double fallback_factor);

void			my_put_pixel(mlx_image_t *img, int x, int y, int color);

#endif
