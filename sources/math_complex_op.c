/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_complex_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 04:09:34 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/11/03 04:50:10 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/math_complex_op.h"
#include <math.h>

float	distance_of_points(t_vector vec1, t_vector vec2)
{
	float	x;
	float	y;
	float	z;

	x = vec1.x - vec2.x;
	y = vec1.y - vec2.y;
	z = vec1.z - vec2.z;
	return (sqrtf(x * x + y * y + z * z));
}

float	angle_between_vectors(t_vector vec1, t_vector vec2)
{
	float	quotient;
	float	divident;

	divident = sqrtf(dot_product(vec1, vec1) * dot_product(vec2, vec2));
	if (!divident)
		return (M_PI_2);
	quotient = dot_product(vec1, vec2);
	return (acosf(quotient / divident));
}

int	quadratic_formula(float a, float b, float c, float *result)
{
	float	half_b;
	float	discriminant;
	
	if (!result || a == 0.f)
		return (1);
	half_b = -b / 2;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (1);
	discriminant = sqrt(discriminant);
	result[0] = (half_b + discriminant) / a;
	result[1] = (half_b - discriminant) / a;
	return (0);
}
