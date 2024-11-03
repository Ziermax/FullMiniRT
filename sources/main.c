/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:41:02 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/11/03 04:26:19 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/structs.h" 

//QUITAR ESTO
t_scene	init_scene(void);

void	my_put_pixel(mlx_image_t *img, int x, int y, int color)
{
	int	thck[2];
	int	px[2];

	x *= BPP;
	y *= BPP;
	if (y < 0 || x < 0 || x >= W_WIDTH || y >= W_HEIGHT)
		return ;
	thck[X] = 0;
	while (thck[X] < BPP)
	{
		thck[Y] = 0;
		while (thck[Y] < BPP)
		{
			px[X] = x + thck[X];
			px[Y] = y + thck[Y];
			if (px[X] >= 0 && px[X] < W_WIDTH && px[Y] >= 0 && px[Y] < W_HEIGHT)
				mlx_put_pixel(img, x + thck[X], y + thck[Y], color);
			thck[Y]++;
		}
		thck[X]++;
	}
}

void	destroy_data(t_data *data)
{
	mlx_close_window(data->mlx);
}
//	while (data->scene.lights)
//	{
//		free(data->scene.lights);
//		data->scene.lights = data->scene.lights->next;
//	}
//	while (data->scene.objects)
//	{
//		free(data->scene.objects);
//		data->scene.objects = data->scene.objects->next;
//	}

void	key_events(void *param)
{
	mlx_image_t	*image;
	mlx_t		*mlx;

	mlx = ((t_data *)param)->mlx;
	image = ((t_data *)param)->img;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		destroy_data(param);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)data;
	data.mlx = mlx_init(W_WIDTH, W_HEIGHT, "miniRT", false);
	data.img = mlx_new_image(data.mlx, W_WIDTH, W_HEIGHT);
	data.scene = init_scene();
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_loop_hook(data.mlx, key_events, &data.mlx);
	data.w_height = data.img->height / BPP;
	data.w_width = data.img->width / BPP;
	/*	*
	 *	Aqui va tu funcion ->
	 *	draw_scene(data, data.scene);
	 */
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                Harcoding functions                         */
/* ************************************************************************** */

t_object	*hardcode_plane(void)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (!object)
		return (NULL);
	object->type = PLANE;
	object->shape.plane.center.x = 0.f;
	object->shape.plane.center.z = 0.f;
	object->shape.plane.center.y = -2.f;
	object->shape.plane.normal.x = 0.f;
	object->shape.plane.normal.z = 0.f;
	object->shape.plane.normal.y = 1.f;
	object->color = 0xFF0000ff;
	object->next = NULL;
	return (object);
}

t_object	*hardcode_sphere(void)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (!object)
		return (NULL);
	object->type = SPHERE;
	object->shape.sphere.center.x = 0.f;
	object->shape.sphere.center.z = 20.f;
	object->shape.sphere.center.y = 0.f;
	object->shape.sphere.radius = 10.f;
	object->color = 0x00FF00ff;
	object->next = NULL;
	return (object);
}

t_light	*hardcode_light(void)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->origin.x = 0.f;
	light->origin.z = 0.f;
	light->origin.y = 0.f;
	light->color = 0xffFF;
	light->brightness = 1.f;
	light->next = NULL;
	return (light);
}

t_scene	init_scene(void)
{
	t_scene	scene;

	/*	*
	 *	Camera
	 */
	scene.camera.origin.x = 0.f;
	scene.camera.origin.y = 0.f;
	scene.camera.origin.z = 0.f;
	scene.camera.orientation.x = 0.f;
	scene.camera.orientation.y = 0.f;
	scene.camera.orientation.z = 1.f;
	/*	*
	 *	Lights
	 */
	scene.amb_light.brightness = 1.f;
	scene.amb_light.color = 0x0;
	scene.lights = NULL;
	lst_add_back(&scene.lights, hardcode_light());
	/*	*
	 *	Action
	 */
	scene.objects = NULL;
	lst_add_back(&scene.objects, hardcode_sphere());
	scene.objects->shape.sphere.center.z = 8.19152f;
	scene.objects->shape.sphere.center.x = 5.7357f;
	scene.objects->shape.sphere.radius = 4;
	scene.objects->color = GREEN;
	lst_add_back(&scene.objects, hardcode_sphere());
	scene.objects->next->shape.sphere.center.z = 8.19152f;
	scene.objects->next->shape.sphere.center.x = -5.7357f;
	scene.objects->next->shape.sphere.radius = 4;
	scene.objects->next->color = RED;
	lst_add_back(&scene.objects, hardcode_sphere());
	scene.objects->next->next->shape.sphere.center.z = 50;
	scene.objects->next->next->shape.sphere.radius = 3;
	scene.objects->next->next->color = BLUE;
	return (scene);
}
