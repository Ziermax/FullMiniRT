/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:46:46 by atudor            #+#    #+#             */
/*   Updated: 2024/10/20 14:46:48 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"


static t_plane	*create_plane2(t_scene *scene)
{
	t_plane	*plane;

	(void)scene;
	plane = malloc(sizeof(t_plane));
	if (!plane)
		exit(1);
	init_vector(&plane->center, 0.f, 0.f, -100.f);
	init_vector(&plane->normal, 0.f, 0.f, 1.f);
	init_vector(&plane->color, 135.f, 206.f, 235.f);
	return (plane);
}


void	setup_planes(t_scene *scene, int num_planes)
{
	if (num_planes < 1)
		scene->planes = NULL;
	else
	{
		scene->planes = malloc(sizeof(t_plane) * num_planes);
		if (!scene->planes)
			exit(1);
		while (num_planes > 0)
		{
			if (num_planes == 2)
				scene->planes[num_planes - 1] = create_plane(scene);
			else
				scene->planes[num_planes - 1] = create_plane2(scene);
			num_planes--;
		}
	}
}

t_plane	*create_plane(t_scene *scene)
{
	t_plane	*plane;

	(void)scene;
	plane = malloc(sizeof(t_plane));
	if (!plane)
		exit(1);
	init_vector(&plane->center, 0.f, -100.f, 0.f);
	init_vector(&plane->normal, 0.f, 1.f, 0.f);
	init_vector(&plane->color, 255.f, 255.f, 255.f);
	return (plane);
}
