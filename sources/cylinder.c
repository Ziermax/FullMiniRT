/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:47:02 by atudor            #+#    #+#             */
/*   Updated: 2024/10/20 14:47:03 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	setup_cylinders(t_scene *scene, int num_cylinders)
{
	if (num_cylinders < 1)
		scene->cylinders = NULL;
	else
	{
		scene->cylinders = malloc(sizeof(t_cylinder) * num_cylinders);
		if (!scene->cylinders)
			exit(1);
		while (num_cylinders > 0)
		{
			scene->cylinders[num_cylinders - 1] = create_cylinder(scene);
			num_cylinders--;
		}
	}
}

t_cylinder	*create_cylinder(t_scene *scene)
{
	t_cylinder	*cylinder;

	(void)scene;
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		exit(1);
	init_vector(&cylinder->center, -100.f, -100.f, 300.f);
	init_vector(&cylinder->axis, 0.f, 1.f, 0.f);
	cylinder->radius = 30.f;
	cylinder->height = 200.f;
	init_vector(&cylinder->color, 0.f, 0.f, 255.f);
	return (cylinder);
}

