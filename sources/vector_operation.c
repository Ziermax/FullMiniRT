/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 04:06:01 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/11/03 04:13:29 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structs.h"
#include <stdio.h>
#include <math.h>

t_vector	scl_vec(t_vector vec, double scale)
{
	vec.x *= scale;
	vec.y *= scale;
	vec.z *= scale;
	return (vec);
}

double	dot_product(t_vector vec1, t_vector vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

void	init_vector(t_vector *vector, double x, double y, double z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
}

t_vector	normalize_vector(double x, double y, double z)
{
	t_vector	vector;
	double		magnitude;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	magnitude = sqrt(vector.x * vector.x + vector.y
			* vector.y + vector.z * vector.z);
	if (magnitude < EPSILON)
		return (vector);
	vector.x /= magnitude;
	vector.y /= magnitude;
	vector.z /= magnitude;
	return (vector);
}

double	normal_dev_coordinates(int coord, t_data *data, int b)
{
	double	ndc_x;
	double	ndc_y;

	if (b == 0)
	{
		ndc_x = (2 * (coord + 0.5) / data->w_width) - 1;
		return (ndc_x);
	}
	else
	{
		ndc_y = 1 - (2 * (coord + 0.5) / data->w_height);
		return (ndc_y);
	}
}
