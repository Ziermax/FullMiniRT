/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:46:54 by atudor            #+#    #+#             */
/*   Updated: 2024/10/20 14:46:56 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	setup_lights(t_scene *scene, int num_lights)
{
	if (num_lights < 1)
		scene->lights = NULL;
	else
	{
		scene->lights = malloc(sizeof(t_light) * num_lights);
		if (!scene->lights)
			exit(1);
		while (num_lights > 0)
		{
			scene->lights[num_lights - 1] = create_light(scene);
			num_lights--;
		}
	}
}

t_light	*create_light(t_scene *scene)
{
	t_light	*light;

	(void)scene;
	light = malloc(sizeof(t_light));
	if (!light)
		exit(1);
	init_vector(&light->origin, -600.f, 10.f, 1050.f);
	init_vector(&light->color, 0.f, 255.f, 0.f);
	light->brightness = 1.f;
	return (light);
}
