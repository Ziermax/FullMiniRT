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

t_intersection	get_intersection_data(t_object *object, t_ray ray, double t)
{
	t_intersection	intersection_data;

	intersection_data.intersection.x = ray.origin.x + ray.direction.x * t;
	intersection_data.intersection.y = ray.origin.y + ray.direction.y * t;
	intersection_data.intersection.z = ray.origin.z + ray.direction.z * t;
	intersection_data.object = object;
	intersection_data.hit = true;
	return (intersection_data);
}

double	get_closest_t(t_object *object, t_ray ray, t_object **closest_object)
{
	double	closest_t;
	double	temp;

	closest_t = INFINITY;
	while (object)
	{
		if (object->type == SPHERE)
			temp = check_sphere_intersection(object, ray);
		else if (object->type == PLANE)
			temp = check_plane_intersection(object, ray);
		else if (object->type == CYLINDER)
			temp = check_cylinder_intersection(object, ray);
		if (temp < closest_t)
		{
			*closest_object = object;
			closest_t = temp;
		}
		object = object->next;
	}
	return (closest_t);
}

t_intersection	check_intersections(t_object *object, t_ray ray)
{
	double			closest_t;
	t_intersection	intersection_data;
	t_object		*closest_object;

	closest_object = NULL;
	closest_t = get_closest_t(object, ray, &closest_object);
	if (closest_t == INFINITY)
	{
		intersection_data.hit = false;
		return (intersection_data);
	}
	intersection_data = get_intersection_data(closest_object, ray, closest_t);
	return (intersection_data);
}

void	draw_on_img(t_data *data, int x, int y, t_intersection intersection)
{
	int	color;

	if (intersection.hit)
	{
		color = intersection.object->color;
		color = get_color(data, intersection.intersection,
				intersection.object);
		my_put_pixel(data->img, x, y, color);
	}
	else
		my_put_pixel(data->img, x, y, BLACK);
}

void	render_engine(t_data *data)
{
	int				x;
	int				y;
	t_ray			ray;
	t_intersection	intersection;

	y = 0;
	while (y < data->w_height)
	{
		x = 0;
		while (x < data->w_width)
		{
			ray = create_ray(data, x, y);
			intersection.hit = false;
			intersection = check_intersections(data->scene.objects, ray);
			draw_on_img(data, x, y, intersection);
			x++;
		}
		y++;
	}
}
