/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:21:10 by atudor            #+#    #+#             */
/*   Updated: 2024/10/20 17:21:12 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/structs.h"

t_vector	calculate_direction(t_vector camera_o, double ndc_x, double ndc_y, t_data *data)
{
	t_vector	direction;
	t_vector	right;
	t_vector	up;	

	right = vector_cross_product(camera_o, (t_vector){0, 1, 0});
	right = normalize_vector(right.x, right.y, right.z);
	up = vector_cross_product(right, camera_o);
	right = vector_scalar(right, ndc_x * data->scale);
	up = vector_scalar(up, ndc_y * data->scale);
	direction = vector_add(camera_o, right);
	direction = vector_add(direction, up);
	return (direction);
}

t_ray	create_ray(t_data *data, int x, int y)
{
	double	ndc_x;
	double	ndc_y;
	t_vector	camera_o;
	t_ray	ray;

	camera_o = data->scene->camera->orientation;
	ndc_x = normal_dev_coordinates(x, data, data->aspect_ratio, 0) * data->scale;
	ndc_y = normal_dev_coordinates(y, data, data->aspect_ratio, 1) * data->scale;
	ray.direction = calculate_direction(camera_o, ndc_x, ndc_y, data);
	ray.direction = normalize_vector(ray.direction.x, ray.direction.y, ray.direction.z);
	return (ray);
}