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

#include "../inc/minirt.h"

float	choose_smaller_t(float t1, float t2)
{
	if (t1 < t2)
		return (t1);
	return (t2);
}

float	check_single_sphere_intersection(t_data *data, t_ray ray, int i)
{
	t_vector	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	oc = vector_subtract(ray.origin, data->scene->spheres[i]->center);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(oc, ray.direction);
	c = dot_product(oc, oc) - (data->scene->spheres[i]->radius
									* data->scene->spheres[i]->radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (INFINITY);
	else if (discriminant == 0) // one intersection, tangent
		return (-b / (2 * a));
	else
		return (choose_smaller_t((-b + sqrt(discriminant))
					/ (2 * a), (-b - sqrt(discriminant)) / (2 * a)));
}

float	check_sphere_intersection(t_data *data, t_ray ray)
{
	float		closest_t;
	int			num_spheres;
	int			i;
	float		t;

	t = INFINITY;
	closest_t = INFINITY;
	num_spheres = data->scene->num_spheres;
	i = 0;
	while (num_spheres > 0)
	{
		t = check_single_sphere_intersection(data, ray, i);
		if (t < closest_t && t > 0)
			closest_t = t;
		i++;
		num_spheres--;
	}
	return (closest_t);
}

void	setup_spheres(t_scene *scene, int num_spheres)
{
	if (num_spheres < 1)
		scene->spheres = NULL;
	else
	{
		scene->spheres = malloc(sizeof(t_sphere) * num_spheres);
		if (!scene->spheres)
			exit(1);
		while (num_spheres > 0)
		{
			scene->spheres[num_spheres - 1] = create_sphere(scene);
			num_spheres--;
		}
	}
}

t_sphere	*create_sphere(t_scene *scene)
{
	t_sphere	*sphere;

	(void)scene;
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		exit(1);
	init_vector(&sphere->center, 100.f, -50.f, 200.f);
	sphere->radius = 50.f;
	init_vector(&sphere->color, 255.f, 0.f, 0.f);
	return (sphere);
}

