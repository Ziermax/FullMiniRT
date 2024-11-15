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
    if (t1 > 0 && (t1 < t2 || t2 <= 0)) {
        return t1;
    }
    if (t2 > 0) {
        return t2;
    }
    return INFINITY; // No valid positive intersection
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
	c = dot_product(oc, oc) - ( object->shape.sphere.radius
									*  object->shape.sphere.radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)	
		return (INFINITY);
	else {
        float sqrt_discriminant = sqrt(discriminant);
        float t1 = (-b - sqrt_discriminant) / (2 * a);
        float t2 = (-b + sqrt_discriminant) / (2 * a);
        return choose_smaller_t(t1, t2); // Return the closest positive intersection
    }
}

// void	setup_spheres(t_scene *scene, int num_spheres)
// {
// 	if (num_spheres < 1)
// 		scene->spheres = NULL;
// 	else
// 	{
// 		scene->spheres = malloc(sizeof(t_sphere) * num_spheres);
// 		if (!scene->spheres)
// 			exit(1);
// 		while (num_spheres > 0)
// 		{
// 			scene->spheres[num_spheres - 1] = create_sphere(scene);
// 			num_spheres--;
// 		}
// 	}
// }

// t_sphere	*create_sphere(t_scene *scene)
// {
// 	t_sphere	*sphere;

// 	(void)scene;
// 	sphere = malloc(sizeof(t_sphere));
// 	if (!sphere)
// 		exit(1);
// 	init_vector(&sphere->center, 100.f, -50.f, 200.f);
// 	sphere->radius = 50.f;
// 	init_vector(&sphere->color, 255.f, 0.f, 0.f);
// 	return (sphere);
// }

