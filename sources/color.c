/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 04:28:03 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/11/03 04:28:49 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	surface_normal(t_object *object, t_vector intersection)
{
	t_vector	normal;

	normal = (t_vector){0, 0, 0};
	if (object->type == SPHERE)
	{
		normal = vector_subtract(intersection, object->shape.sphere.center);
		normal = normalize_vector(normal.x, normal.y, normal.z);
	}
	else if (object->type == PLANE)
		normal = object->shape.plane.normal;
	else if (object->type == CYLINDER)
		normal = cylinder_normal(object->shape.cylinder, intersection);
	return (normal);
}

int	apply_diffuse_lighting(int o_color, t_light *light, t_vector x, t_object *o)
{
	double		cos_theta;
	t_vector	light_dir;
	t_vector	normal;

	normal = surface_normal(o, x);
	light_dir = vector_subtract(light->origin, x);
	light_dir = normalize_vector(light_dir.x, light_dir.y, light_dir.z);
	cos_theta = dot_product(normal, light_dir);
	if (cos_theta < EPSILON)
		cos_theta = 0;
	return (scale_color(o_color, light->brightness * cos_theta));
}

int	apply_ambient_lighting(t_object *object, t_data *data)
{
	int		ambient_color;
	double	brightness;

	brightness = data->scene.amb_light.brightness;
	if (brightness < 0.01f)
		brightness = 0.01f;
	else if (brightness > 1.0f)
		brightness = 1.0f;
	ambient_color = multiply_colors_with_fallback(object->color,
			data->scene.amb_light.color, 0.1f);
	return (scale_color(ambient_color, brightness));
}

int	in_shadow(t_data *data, t_vector x, t_object *obj, t_light *light)
{
	t_ray			shadow_ray;
	t_intersection	intersection_data;

	shadow_ray.origin = light->origin;
	shadow_ray.direction = vector_subtract(x, light->origin);
	shadow_ray.direction = normalize_vector(shadow_ray.direction.x,
			shadow_ray.direction.y, shadow_ray.direction.z);
	intersection_data = check_intersections(data->scene.objects, shadow_ray);
	if (intersection_data.hit == true)
	{
		if (intersection_data.object != obj)
			return (1);
	}
	return (0);
}

int	get_color(t_data *data, t_vector intersection, t_object *object)
{
	int		final_color;
	int		diffuse_color;
	t_light	*light;

	final_color = apply_ambient_lighting(object, data);
	light = data->scene.lights;
	while (light)
	{
		if (!in_shadow(data, intersection, object, light))
		{
			diffuse_color = apply_diffuse_lighting(object->color,
					light, intersection, object);
			final_color = sum_colors(final_color, diffuse_color);
		}
		light = light->next;
	}
	return (clamp_color(final_color));
}
