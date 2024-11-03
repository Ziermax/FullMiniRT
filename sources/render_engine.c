/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_engine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:11:30 by atudor            #+#    #+#             */
/*   Updated: 2024/10/20 16:11:33 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include <math.h>

t_vector	*check_intersections(t_data *data, t_ray ray)
{
	float		t_sphere;
	// float		t_plane;
	// float		t_cylinder;
	float		closest_t;
	t_vector	*intersection;

	closest_t = INFINITY;
	t_sphere = check_sphere_intersection(data, ray);
	// t_plane = check_plane_intersection(data, ray);
	// t_cylinder = check_cylinder_intersection(data, ray);
	closest_t = t_sphere;
	// if (t_plane < closest_t)
	// 	closest_t = t_plane;
	// if (t_cylinder < closest_t)
	// 	closest_t = t_cylinder;
	if (closest_t == INFINITY)
		return (NULL);
	intersection = malloc(sizeof(t_vector));
	intersection->x = ray.origin.x + ray.direction.x * closest_t;
	intersection->y = ray.origin.y + ray.direction.y * closest_t;
	intersection->z = ray.origin.z + ray.direction.z * closest_t;
	return (intersection);
}

void	render_engine(t_data *data)
{
	unsigned int	x;
	unsigned int	y;
	t_ray	ray;
	t_vector	*intersection;
	
	// loop through each pixel in the image
	y = 0;
	while (y < data->img->height)
	{
		x = 0;
		while (x < data->img->width)
		{
			ray = create_ray(data, x, y);
			intersection = check_intersections(data, ray);
			if (intersection)
			{
				mlx_put_pixel(data->img, x, y, 0xFF0000);
				// get color
				// put pixel on image
				free(intersection);
			}
			else 
				mlx_put_pixel(data->img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}
