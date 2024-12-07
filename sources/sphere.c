/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:46:38 by atudor            #+#    #+#             */
/*   Updated: 2024/10/20 14:46:40 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	choose_smaller_t(float t1, float t2)
{
	if (t1 > EPSILON && (t1 < t2 || t2 <= EPSILON))
		return (t1);
	if (t2 > EPSILON)
		return (t2);
	return (INFINITY);
}

float	quadratic_formula(float a, float b, float discriminant)
{
	float	t1;
	float	t2;
	float	sqrt_discriminant;	

	if (discriminant < EPSILON)
		return (INFINITY);
	else
	{
		sqrt_discriminant = sqrt(discriminant);
		t1 = (-b - sqrt_discriminant) / (2 * a);
		t2 = (-b + sqrt_discriminant) / (2 * a);
		return (choose_smaller_t(t1, t2));
	}
}

float	check_sphere_intersection(t_object *object, t_ray ray)
{
	t_vector	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	oc = vector_subtract(ray.origin, object->shape.sphere.center);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(oc, ray.direction);
	c = dot_product(oc, oc) - (object->shape.sphere.radius
			* object->shape.sphere.radius);
	discriminant = b * b - 4 * a * c;
	return (quadratic_formula(a, b, discriminant));
}
