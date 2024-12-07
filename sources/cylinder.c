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

t_vector	cylinder_normal(t_cylinder cyl, t_vector point)
{
	t_vector	oc;
	t_vector	axis;
	float		projection;

	oc = vector_subtract(point, cyl.center);
	axis = normalize_vector(cyl.axis.x, cyl.axis.y, cyl.axis.z);
	projection = dot_product(oc, axis);
    if (projection > 0 && projection < cyl.height)
    {
        t_vector projection_vec = vector_scalar(axis, projection);
        t_vector normal = vector_subtract(oc, projection_vec);
        return normalize_vector(normal.x, normal.y, normal.z);
    }
	if (projection <= 0)
		return (vector_scalar(axis, -1));
	if (projection >= cyl.height)
		return (axis);
    return (t_vector){0, 0, 0};
}

float	quadratic_with_height_limit(float discriminant, float a, float b, t_object *object, t_ray ray)
{
	float t1;
	float t2;
	float y1;
	float y2;
	float h;

	if (discriminant < EPSILON)
		return (INFINITY);
	else
	{
		t1 = (-b - sqrt(discriminant)) / (2 * a);
		t2 = (-b + sqrt(discriminant)) / (2 * a);
		y1 = dot_product(vector_subtract(vector_add(ray.origin, vector_scalar(ray.direction, t1)), object->shape.cylinder.center), object->shape.cylinder.axis);
		y2 = dot_product(vector_subtract(vector_add(ray.origin, vector_scalar(ray.direction, t2)), object->shape.cylinder.center), object->shape.cylinder.axis);
		h = object->shape.cylinder.height;
		if (y1 < -EPSILON || y1 > h + EPSILON)
			t1 = INFINITY;
		if (y2 < -EPSILON || y2 > h + EPSILON)
			t2 = INFINITY;
		return (choose_smaller_t(t1, t2));
	}
}


float	check_round_part(t_object *object, t_ray ray)
{
	t_vector	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	oc = vector_subtract(ray.origin, object->shape.sphere.center);
	a = (dot_product(ray.direction, ray.direction) - pow(dot_product(ray.direction, object->shape.cylinder.axis), 2));
	b = 2 * (dot_product(oc, ray.direction) - dot_product(oc, object->shape.cylinder.axis) * dot_product(ray.direction, object->shape.cylinder.axis));
	c = dot_product(oc, oc) - pow(dot_product(oc, object->shape.cylinder.axis), 2) - pow(object->shape.cylinder.radius, 2);
	discriminant = b * b - 4 * a * c;
	return (quadratic_with_height_limit(discriminant, a, b, object, ray));
}

float	check_cylinder_cap_intersection(t_ray ray, t_cylinder cylinder)
{
	float		denom;
	float		t;
	float		distance_squared;
	t_vector	point;
	t_vector	oc;

	denom = dot_product(ray.direction, cylinder.axis);
	if (fabs(denom) > EPSILON)
	{
		oc = vector_subtract(cylinder.center, ray.origin);
		t = dot_product(oc, cylinder.axis) / denom;
		if (t >= EPSILON)
		{
			point = vector_add(ray.origin, vector_scalar(ray.direction, t));
			distance_squared = vector_length(vector_subtract(point,
				cylinder.center));
			distance_squared = distance_squared * distance_squared;
			if (distance_squared <= cylinder.radius * cylinder.radius)
				return (t);
		}
	}
	return (INFINITY);
}

float	check_cylinder_intersection(t_object *object, t_ray ray)
{
	float	t_round;
	float	t_caps;

	t_round = check_round_part(object, ray);
	t_caps = check_cylinder_cap_intersection(ray, object->shape.cylinder);
	return (choose_smaller_t(t_round, t_caps));
}
