/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:38:29 by atudor            #+#    #+#             */
/*   Updated: 2024/09/19 01:38:32 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	init_vector(t_vector *vector, double x, double y, double z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
}

void	create_scene(t_scene *scene)
{
	int num_spheres = 1;
	int num_planes = 2;
	int num_cylinders = 0;
	int num_lights = 1;

	scene->camera = create_camera();
	setup_spheres(scene, num_spheres);
	setup_planes(scene, num_planes);
	setup_cylinders(scene, num_cylinders);
	setup_lights(scene, num_lights);
}

