/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:46:46 by atudor            #+#    #+#             */
/*   Updated: 2024/10/20 14:46:48 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	check_plane_intersection(t_object *object, t_ray ray)
{
	double		denom;
	double		t;
	t_vector	oc;

	denom = dot_product(ray.direction, object->shape.plane.normal);
	if (denom > EPSILON || denom < -EPSILON)
	{
		oc = vector_subtract(object->shape.plane.center, ray.origin);
		t = dot_product(oc, object->shape.plane.normal) / denom;
		if (t >= EPSILON)
			return (t);
	}
	return (INFINITY);
}
