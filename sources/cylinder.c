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

t_vector cylinder_normal(t_cylinder cyl, t_vector point)
{
    t_vector oc;              // Vector from cylinder base to point
    t_vector axis;            // Cylinder's axis (normalized)
    double projection;        // Projection of 'oc' onto the cylinder axis

    // Calculate oc (vector from base to point) and normalize the axis
    oc = vector_subtract(point, cyl.center);
    axis = normalize_vector(cyl.axis.x, cyl.axis.y, cyl.axis.z);

    // Projection of 'oc' onto the axis
    projection = dot_product(oc, axis);

    // Check if point is on the curved surface of the cylinder
    if (projection > 0 && projection < cyl.height)
    {
        // Calculate the normal for the curved surface
        t_vector projection_vec = vector_scalar(axis, projection);
        t_vector normal = vector_subtract(oc, projection_vec);
        return normalize_vector(normal.x, normal.y, normal.z);
    }

    // Handle the bottom cap
	if (projection <= 0 + EPSILON)
		return vector_scalar(axis, -1); // Bottom cap normal
	if (projection >= cyl.height - EPSILON)
		return axis; // Top cap normal

    // Default case (unlikely to happen)
    return (t_vector){0, 0, 0};
}


double	quadratic_with_height_limit(double discriminant, double a, double b, t_object *object, t_ray ray)
{
	double t1;
	double t2;
	double y1;
	double y2;
	double h;

	if (discriminant < EPSILON)
		return (INFINITY);
	else
	{
		t1 = (-b - sqrt(discriminant)) / (2 * a);
		t2 = (-b + sqrt(discriminant)) / (2 * a);
		y1 = dot_product(vector_subtract(vector_add(ray.origin,
			vector_scalar(ray.direction, t1)), object->shape.cylinder.center),
				object->shape.cylinder.axis);
		y2 = dot_product(vector_subtract(vector_add(ray.origin,
			vector_scalar(ray.direction, t2)), object->shape.cylinder.center),
				object->shape.cylinder.axis);
		h = object->shape.cylinder.height;
		if (y1 < -EPSILON || y1 > h + EPSILON)
			t1 = INFINITY;
		if (y2 < -EPSILON || y2 > h + EPSILON)
			t2 = INFINITY;
		return (choose_smaller_t(t1, t2));
	}
}

double	check_round_part(t_object *object, t_ray ray)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	oc = vector_subtract(ray.origin, object->shape.sphere.center);
	a = (dot_product(ray.direction, ray.direction) - pow(dot_product(ray.direction, object->shape.cylinder.axis), 2));
	b = 2 * (dot_product(oc, ray.direction) - dot_product(oc, object->shape.cylinder.axis) * dot_product(ray.direction, object->shape.cylinder.axis));
	c = dot_product(oc, oc) - pow(dot_product(oc, object->shape.cylinder.axis), 2) - pow(object->shape.cylinder.radius, 2);
	discriminant = b * b - 4 * a * c;
	return (quadratic_with_height_limit(discriminant, a, b, object, ray));
}

double check_if_within_radius(t_ray ray, t_plane base_cap, t_plane top_cap, t_cylinder cylinder)
{
	t_vector	intersection_point;
	double		t_base;
	double		t_top;

	t_base = check_plane_intersection(&(t_object){.shape.plane = base_cap}, ray);
	if (t_base != INFINITY)
	{
		intersection_point = vector_add(ray.origin, vector_scalar(ray.direction, t_base));
	if (vector_length(vector_subtract(intersection_point, base_cap.center)) > cylinder.radius + EPSILON)
		t_base = INFINITY;
	}
	t_top = check_plane_intersection(&(t_object){.shape.plane = top_cap}, ray);
	if (t_top != INFINITY)
	{
		intersection_point = vector_add(ray.origin, vector_scalar(ray.direction, t_top));
		if (vector_length(vector_subtract(intersection_point, top_cap.center)) > cylinder.radius + EPSILON)
			t_top = INFINITY;
	}
	return (choose_smaller_t(t_base, t_top));
}

double	check_cylinder_cap_intersection(t_ray ray, t_cylinder cylinder)
{
	t_plane		base_cap;
	t_plane		top_cap;

	base_cap.center = cylinder.center;
	base_cap.normal = cylinder.axis;
	top_cap.center = vector_add(cylinder.center, vector_scalar(cylinder.axis, cylinder.height));
	top_cap.normal = vector_scalar(cylinder.axis, -1);
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
