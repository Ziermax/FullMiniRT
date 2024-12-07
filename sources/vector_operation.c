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
#include <math.h>

t_vector	add_vec(t_vector vec1, t_vector vec2)
{
	vec1.x = vec1.x + vec2.x;
	vec1.y = vec1.y + vec2.y;
	vec1.z = vec1.z + vec2.z;
	return (vec1);
}

t_vector	sub_vec(t_vector vec1, t_vector vec2)
{
	vec1.x = vec1.x - vec2.x;
	vec1.y = vec1.y - vec2.y;
	vec1.z = vec1.z - vec2.z;
	return (vec1);
}

t_vector	scl_vec(t_vector vec, float scale)
{
	vec.x *= scale;
	vec.y *= scale;
	vec.z *= scale;
	return (vec);
}

float	dot_product(t_vector vec1, t_vector vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
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
	if (magnitude == 0)
	{
		vector.x = 0;
		vector.y = 0;
		vector.z = 0;
	}
	else
	{
		vector.x /= magnitude;
		vector.y /= magnitude;
		vector.z /= magnitude;
	}
	return (vector);
}
