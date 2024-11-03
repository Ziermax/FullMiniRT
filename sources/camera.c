/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:37:38 by atudor            #+#    #+#             */
/*   Updated: 2024/09/19 01:37:40 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_camera *create_camera(void)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		exit(1);
	init_vector(&camera->origin, 0.f, 0.f, 0.f);
	init_vector(&camera->orientation, 0.f, 0.f, 1.f);
	camera->fov = 60.f;
	return (camera);
}