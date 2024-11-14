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
	t_vector vector;

	vector.x = a.y * b.z - a.z * b.y;
	vector.y = a.z * b.x - a.x * b.z;
	vector.z = a.x * b.y - a.y * b.x;
	return (vector);
}

double		normal_dev_coordinates(int coord, t_data *data, int b)
{
    if (b == 0) {
        double ndc_x = (2 * (coord + 0.5) / data->w_width) - 1;
        printf("NDC X for coord %d: %f\n", coord, ndc_x);
        return ndc_x;
    } else {
        double ndc_y = 1 - (2 * (coord + 0.5) / data->w_height);
        printf("NDC Y for coord %d: %f\n", coord, ndc_y);
        return ndc_y;
    }
}

t_vector	normalize_vector(double x, double y, double z)
{
	t_vector	vector;
	double		magnitude;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	magnitude = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
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


