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

t_vector	*check_intersections(t_object *object, t_ray ray)
{
	float		closest_t;
	float		temp;
	t_vector	*intersection;


	closest_t = INFINITY;
	while (object)
	{
		if (object->type == SPHERE)
		{
			printf("Checking sphere\n");
			temp = check_sphere_intersection(object, ray);
			if (temp < closest_t)
			{
				printf("Sphere intersection found, t = %f\n", temp);
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
		printf("No intersection found\n");
		return (NULL);
	}
	intersection = malloc(sizeof(t_vector));
	intersection->x = ray.origin.x + ray.direction.x * closest_t;
	intersection->y = ray.origin.y + ray.direction.y * closest_t;
	intersection->z = ray.origin.z + ray.direction.z * closest_t;
	return (intersection);
}

void	render_engine(t_data *data)
{
	int	x;
	int	y;
	t_ray	ray;
	t_vector	*intersection;
	
	// loop through each pixel in the image
	y = 0;
	while (y < data->w_height)
	{
		x = 0;
		while (x < data->w_width)
		{
			ray = create_ray(data, x, y);
			intersection = check_intersections(data->scene.objects, ray);
			if (intersection)
			{
				my_put_pixel(data->img, x, y, GREEN);
				// get color
				// put pixel on image
				free(intersection);
			}
			else 
				my_put_pixel(data->img, x, y, RED);
			x++;
		}
		y++;
	}
}
