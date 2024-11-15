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

#include "../includes/minirt.h"
#include "../includes/structs.h"

t_vector	calculate_direction(t_vector camera_dir, double ndc_x, double ndc_y)
{
	t_vector	direction;
	t_vector	right;
	t_vector	up;

    // Calculate the right vector using a fixed up vector (assumes camera_dir is normalized)
	right = vector_cross_product(camera_dir, (t_vector){0, 1, 0});
	right = normalize_vector(right.x, right.y, right.z);
	up = vector_cross_product(right, camera_dir);
	up = normalize_vector(up.x, up.y, up.z);

    // Scale the right and up vectors by ndc_x and ndc_y
	right = vector_scalar(right, ndc_x);
	up = vector_scalar(up, ndc_y);

    // Combine the camera direction with the scaled right and up vectors
	direction = vector_add(camera_dir, right);
	direction = vector_add(direction, up);

    // Normalize the resulting direction vector
	direction = normalize_vector(direction.x, direction.y, direction.z);
	return (direction);
}


t_ray	create_ray(t_data *data, int x, int y)
{
	double	ndc_x;
	double	ndc_y;
	t_ray	ray;
	double	aspect_ratio;

	aspect_ratio = (double)data->w_width / (double)data->w_height;
	ndc_x = normal_dev_coordinates(x, data, 0) * aspect_ratio * tan(data->scene.camera.fov * 0.5 * M_PI / 180);
	ndc_y = normal_dev_coordinates(y, data, 1) * tan(data->scene.camera.fov * 0.5 * M_PI / 180);
	ray.origin = data->scene.camera.origin;
	ray.direction = calculate_direction(data->scene.camera.orientation, ndc_x, ndc_y);
	ray.direction = normalize_vector(ray.direction.x, ray.direction.y, ray.direction.z);
    return (ray);
}