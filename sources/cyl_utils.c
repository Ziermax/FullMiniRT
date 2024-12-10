/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 02:27:20 by atudor            #+#    #+#             */
/*   Updated: 2024/12/10 02:27:22 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	cylinder_normal(t_cylinder cyl, t_vector point)
{
	t_vector	oc;
	t_vector	normal;
	double		projection;
	t_vector	projection_vec;
	t_vector	closest_point;

	oc = sub_vec(point, cyl.center);
	projection = dot_product(oc, cyl.axis);
	if (projection <= 0 + EPSILON)
		return (scl_vec(cyl.axis, -1));
	else if (projection >= cyl.height - EPSILON)
		return (cyl.axis);
	else
	{
		projection_vec = scl_vec(cyl.axis, projection);
		closest_point = add_vec(cyl.center, projection_vec);
		normal = sub_vec(point, closest_point);
		return (normalize_vector(normal.x, normal.y, normal.z));
	}
	return ((t_vector){0, 0, 0});
}

double	quadratic_with_height_limit(double d, double a[3], t_object *o, t_ray r)
{
	double	t1;
	double	t2;
	double	y1;
	double	y2;
	double	h;

	if (d < EPSILON)
		return (INFINITY);
	else
	{
		t1 = (-a[1] - sqrt(d)) / (2 * a[0]);
		t2 = (-a[1] + sqrt(d)) / (2 * a[0]);
		y1 = dot_product(sub_vec(add_vec(r.origin,
						scl_vec(r.direction, t1)),
					o->shape.cylinder.center), o->shape.cylinder.axis);
		y2 = dot_product(sub_vec(add_vec(r.origin,
						scl_vec(r.direction, t2)), o->shape.cylinder.center),
				o->shape.cylinder.axis);
		h = o->shape.cylinder.height;
		if (y1 < -EPSILON || y1 > h + EPSILON)
			t1 = INFINITY;
		if (y2 < -EPSILON || y2 > h + EPSILON)
			t2 = INFINITY;
		return (choose_smaller_t(t1, t2));
	}
}
