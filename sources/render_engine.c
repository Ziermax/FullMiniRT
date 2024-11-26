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

#include "../includes/minirt.h"
#include <math.h>

t_intersection	check_intersections(t_object *object, t_ray ray)
{
	float		closest_t;
	float		temp;
	t_intersection	intersection_data;
	t_object	*closest_object;


	closest_t = INFINITY;
	while (object)
	{
		if (object->type == SPHERE)
		{
			temp = check_sphere_intersection(object, ray);
			if (temp < closest_t)
			{
				closest_object = object;
				closest_t = temp;
			}
		}
		// if (objects->type == PLANE)
		// {
		// 	temp = check_plane_intersection(data, ray);
		// 	if (temp < closest_t)
		// 		closest_t = temp;
		// }
		// if (objects->type == CYLINDER)
		// {
		// 	temp = check_cylinder_intersection(data, ray);
		// 	if (temp < closest_t)
		// 		closest_t = temp;
		// }
		
		object = object->next;
	}
	if (closest_t == INFINITY)
	{
		intersection_data.hit = false;
		return (intersection_data);
	}
    intersection_data.intersection.x = ray.origin.x + ray.direction.x * closest_t;
    intersection_data.intersection.y = ray.origin.y + ray.direction.y * closest_t;
    intersection_data.intersection.z = ray.origin.z + ray.direction.z * closest_t;
    intersection_data.object = closest_object;
	intersection_data.hit = true;
	return (intersection_data);
}

void	render_engine(t_data *data)
{
	int			x;
	int			y;
	t_ray		ray;
	t_intersection	intersection;
	int			color;
	
	// loop through each pixel in the image
	y = 0;
	while (y < data->w_height)
	{
		x = 0;
		while (x < data->w_width)
		{
			ray = create_ray(data, x, y);
			intersection.hit = false;
			intersection = check_intersections(data->scene.objects, ray);
			if (intersection.hit)
			{
				printf("object color: %x\n", intersection.object->color);
				color = get_color(data, intersection.intersection, intersection.object);
				printf("Official Color at thee end of all calculations: %x\n", color);
				my_put_pixel(data->img, x, y, color);
			}
			else 
				my_put_pixel(data->img, x, y, BLACK);
			x++;
		}
		y++;
	}
}
