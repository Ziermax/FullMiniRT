/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:11:41 by atudor            #+#    #+#             */
/*   Updated: 2024/10/20 16:11:43 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	vector_add(t_vector a, t_vector b)
{
	t_vector	vector;

	vector.x = a.x + b.x;
	vector.y = a.y + b.y;
	vector.z = a.z + b.z;
	return (vector);
}

t_vector	vector_subtract(t_vector a, t_vector b)
{
	t_vector	vector;

	vector.x = a.x - b.x;
	vector.y = a.y - b.y;
	vector.z = a.z - b.z;
	return (vector);
}

float	vector_length(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	vector_scalar(t_vector a, double scalar)
{
	t_vector	vector;

	vector.x = a.x * scalar;
	vector.y = a.y * scalar;
	vector.z = a.z * scalar;
	return (vector);
}

t_vector	vector_cross_product(t_vector a, t_vector b)
{
	t_vector	vector;

	vector.x = a.y * b.z - a.z * b.y;
	vector.y = a.z * b.x - a.x * b.z;
	vector.z = a.x * b.y - a.y * b.x;
	return (vector);
}

