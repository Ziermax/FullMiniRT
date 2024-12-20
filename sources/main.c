/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:41:02 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/12/12 21:29:39 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/structs.h"
#include "../includes/minirt.h"

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
	free_scene(&data->scene);
}

void	key_events(void *param)
{
	mlx_t		*mlx;

	mlx = ((t_data *)param)->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		destroy_data(param);
}

void	print_scene(t_scene scene);

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)data;
	if (argc != 2)
		return (1);
	data.scene = get_scene(argv[1]);
	if (!data.scene.objects)
		return (2);
	print_scene(data.scene);
	data.mlx = mlx_init(W_WIDTH, W_HEIGHT, "miniRT", false);
	data.img = mlx_new_image(data.mlx, W_WIDTH, W_HEIGHT);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_loop_hook(data.mlx, key_events, &data.mlx);
	data.w_height = data.img->height / BPP;
	data.w_width = data.img->width / BPP;
	data.aspect_ratio = data.w_width / data.w_height;
	data.scale = tan(data.scene.camera.fov * 0.5 * M_PI / 180);
	render_engine(&data);
	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.img);
	mlx_terminate(data.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                Harcoding functions                         */
/* ************************************************************************** */
/*
t_object	*hardcode_plane(void)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (!object)
		return (NULL);
	object->type = PLANE;
	object->shape.plane.center.x = 0.f;
	object->shape.plane.center.z = 20.f;
	object->shape.plane.center.y = -2.f;
	object->shape.plane.normal.x = 0.f;
	object->shape.plane.normal.z = 1.f;
	object->shape.plane.normal.y = 0.2f;
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
	light->origin.z = -20.f;
	light->origin.y = 0.f;
	light->color = WHITE;
	light->brightness = 0.5f;
	light->next = NULL;
	return (light);
}

t_object *hardcode_cylinder(void)
{
    t_object *object = malloc(sizeof(t_object));
    if (!object)
        return NULL;

    object->type = CYLINDER;
    object->shape.cylinder.center = (t_vector){0, 10, 150};
    object->shape.cylinder.axis = (t_vector){0, -1, -0.2};
    //object->shape.cylinder.axis = (t_vector){0, 0.2, 0.2}; // Vertical axis
    object->shape.cylinder.radius = 100.0f;
    object->shape.cylinder.height = 10.0f;
    object->color = YELLOW;
    object->next = NULL;

    return object;
}

t_scene	init_scene(void)
{
	t_object *new_object;
	t_scene	scene;

	scene.camera.origin.x = 0.f;
	scene.camera.origin.y = 0.f;
	scene.camera.origin.z = -20.f;
	scene.camera.orientation.x = 0.0f;
	scene.camera.orientation.y = 0.f;
	scene.camera.orientation.z = 1.0f;
	scene.camera.fov = 60.f;
	scene.amb_light.brightness = 0.1f;
	scene.amb_light.color = WHITE;
	scene.lights = NULL;
	lst_add_back(&scene.lights, hardcode_light());

	scene.objects = NULL;
	// Add first sphere
	new_object = hardcode_sphere();
	new_object->shape.sphere.center.z = 8.19152f;
	new_object->shape.sphere.center.x = 5.7357f;
	new_object->shape.sphere.radius = 4;
	new_object->color = GREEN;
	lst_add_back(&scene.objects, new_object);

	// Add second sphere
	new_object = hardcode_sphere();
	new_object->shape.sphere.center.z = 8.19152f;
	new_object->shape.sphere.center.x = -5.7357f;
	new_object->shape.sphere.radius = 4;
	new_object->color = RED;
	lst_add_back(&scene.objects, new_object);

	// Add third sphere
	new_object = hardcode_sphere();
	new_object->shape.sphere.center.z = 50;
	new_object->shape.sphere.radius = 3;
	new_object->color = BLUE;
	lst_add_back(&scene.objects, new_object);

	// add plane
	new_object = hardcode_plane();
	new_object->shape.plane.center.y = -50;
	new_object->shape.plane.normal.x = 0;
	new_object->shape.plane.normal.z = 0;
	new_object->shape.plane.normal.y = 1;
	new_object->color = BLUE;
	lst_add_back(&scene.objects, new_object);

	// add cylinder
	new_object = hardcode_cylinder();
	lst_add_back(&scene.objects, new_object);

	return (scene);
}
*/
