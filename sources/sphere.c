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

double	choose_smaller_t(double t1, double t2)
{
	if (t1 > EPSILON && (t1 < t2 || t2 <= EPSILON))
		return (t1);
	if (t2 > EPSILON)
		return (t2);
	return (INFINITY);
}

double	quadratic_formula(double a, double b, double discriminant)
{
	double	t1;
	double	t2;
	double	sqrt_discriminant;	

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

double	check_sphere_intersection(t_object *object, t_ray ray)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	oc = sub_vec(ray.origin, object->shape.sphere.center);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(oc, ray.direction);
	c = dot_product(oc, oc) - (object->shape.sphere.radius
			* object->shape.sphere.radius);
	discriminant = b * b - 4 * a * c;
	return (quadratic_formula(a, b, discriminant));
}
