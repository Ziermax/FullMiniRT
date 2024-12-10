/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                          :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:47:02 by atudor            #+#    #+#             */
/*   Updated: 2024/10/20 14:47:03 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	check_round_part(t_object *object, t_ray ray)
{
	t_vector	axis;
	t_vector	oc;
	double		abc[3];
	double		discriminant;

	axis = object->shape.cylinder.axis;
	oc = sub_vec(ray.origin, object->shape.cylinder.center);
	abc[0] = dot_product(ray.direction, ray.direction)
		- pow(dot_product(ray.direction, axis), 2);
	abc[1] = 2 * (dot_product(oc, ray.direction)
			- dot_product(oc, axis) * dot_product(ray.direction, axis));
	abc[2] = dot_product(oc, oc) - pow(dot_product(oc, axis), 2)
		- pow(object->shape.cylinder.radius, 2);
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	return (quadratic_with_height_limit(discriminant, abc, object, ray));
}

double	check_t_for_caps(t_ray ray, double t, t_plane cap, t_cylinder cyl)
{
	t_vector		intersection_point;

	if (t != INFINITY)
	{
		intersection_point = add_vec(ray.origin, scl_vec(ray.direction, t));
		if (vector_length(sub_vec(intersection_point, cap.center))
			> cyl.radius + EPSILON)
			return (INFINITY);
	}
	return (t);
}

double	check_if_within_radius(t_ray ray, t_plane btm, t_plane tp, t_cylinder c)
{
	double			t_base;
	double			t_top;
	t_object		base_cap;
	t_object		top_cap;

	base_cap.shape.plane = btm;
	t_base = check_plane_intersection(&base_cap, ray);
	t_base = check_t_for_caps(ray, t_base, btm, c);
	top_cap.shape.plane = tp;
	t_top = check_plane_intersection(&top_cap, ray);
	t_top = check_t_for_caps(ray, t_top, tp, c);
	return (choose_smaller_t(t_base, t_top));
}

double	check_cylinder_cap_intersection(t_ray ray, t_cylinder cylinder)
{
	t_plane		base_cap;
	t_plane		top_cap;
	t_vector	axis;

	axis = cylinder.axis;
	base_cap.center = cylinder.center;
	base_cap.normal = axis;
	top_cap.center = add_vec(cylinder.center,
			scl_vec(axis, cylinder.height));
	top_cap.normal = axis;
	return (check_if_within_radius(ray, base_cap, top_cap, cylinder));
}

double	check_cylinder_intersection(t_object *object, t_ray ray)
{
	double	t_round;
	double	t_caps;

	t_round = check_round_part(object, ray);
	t_caps = check_cylinder_cap_intersection(ray, object->shape.cylinder);
	return (choose_smaller_t(t_round, t_caps));
}
