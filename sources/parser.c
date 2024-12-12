/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 16:49:01 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/12/12 12:42:50 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/structs.h"
#include "../includes/parser.h"
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

char	*get_type(int type)
{
	if (type == SPHERE)
		return ("Sphere");
	if (type == PLANE)
		return ("Plane");
	if (type == CYLINDER)
		return ("Cylinder");
	return ("NO_TYPE");
}

void	print_vector(t_vector vec)
{
	printf("(%.2f, %.2f, %.2f)", vec.x, vec.y, vec.z);
}

void	print_sph(t_sphere sph)
{
	printf(" | Center: ");
	print_vector(sph.center);
	printf("\n | Radius: %f\n", sph.radius);
}

void	print_pln(t_plane pln)
{
	printf(" | Center: ");
	print_vector(pln.center);
	printf("\n | Normal: ");
	print_vector(pln.normal);
	printf("\n");
}

void	print_cyl(t_cylinder cyl)
{
	printf(" | Center: ");
	print_vector(cyl.center);
	printf("\n | Axis: ");
	print_vector(cyl.axis);
	printf("\n | Radius: %f\n | Height: %f\n", cyl.radius, cyl.height);
}

void	print_shape(t_shape shape, int type)
{
	if (type == SPHERE)
		print_sph(shape.sphere);
	else if (type == PLANE)
		print_pln(shape.plane);
	else if (type == CYLINDER)
		print_cyl(shape.cylinder);
}

void	print_obj(void *aux)
{
	t_object *obj;

	obj = aux;
	printf("Type: %s\n", get_type(obj->type));
	print_shape(obj->shape, obj->type);
	printf(" | Color: %#x\n", obj->color);
}

void	print_light(void *aux)
{
	t_light *light;

	light = aux;
	printf("Light:\n | Origin: ");
	print_vector(light->origin);
	printf("\n | Brightness: %f\n | Color: %#x\n",
		light->brightness, light->color);
}

void	print_camera(void *aux)
{
	t_camera *camera;

	camera = aux;
	printf("Camera:\n | Origin: ");
	print_vector(camera->origin);
	printf("\n | Orientation: ");
	print_vector(camera->orientation);
	printf("\n | Fov: %f\n", camera->fov);
}

void	print_scene(t_scene scene)
{
	lst_for_each(scene.objects, print_obj);
	lst_for_each(scene.lights, print_light);
	printf("Ambient ");
	print_light(&scene.amb_light);
	print_camera(&scene.camera);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	lst_clear(&scene->objects, free);
	lst_clear(&scene->lights, free);
}

static int	select_data_type(char *data)
{
	if (!data || !*data)
		return (NO_TYPE);
	if (!ft_strncmp(data, "A", 2))
		return (AMB);
	if (!ft_strncmp(data, "C", 2))
		return (CAM);
	if (!ft_strncmp(data, "L", 2))
		return (LIGHT);
	if (!ft_strncmp(data, "sp", 3))
		return (SP);
	if (!ft_strncmp(data, "pl", 3))
		return (PL);
	if (!ft_strncmp(data, "cy", 3))
		return (CY);
	return (NO_TYPE);
}

static long	ft_atol(char *str)
{
	int		sign;
	long	num;

	sign = 1;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	num = 0;
	while (ft_isdigit(*str))
	{
		num = num * 10 + *str - '0';
		++str;
	}
	return (num * sign);
}

static int	length_long(long nbr)
{
	int	length;

	length = 0;
	while (nbr)
	{
		length++;
		nbr = nbr / 10;
	}
	return (length);
}

static int	error_atod(char *str, double *store)
{
	long	whole;
	long	fract;
	int		sign;

	whole = ft_atol(str);
	sign = 1;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	while (ft_isdigit(*str))
		++str;
	if (!*str)
		return (*store = whole, 0);
	if (*(str++) != '.')
		return (1);
	fract = ft_atol(str);
	while (ft_isdigit(*str))
		++str;
	if (*str)
		return (1);
	*store = (double)(sign * whole)
		+ (double)fract / (int)pow(10, length_long(fract));
	return (0);
}

static int	error_atocomponent(char *str, int *store)
{
	*store = 0;
	if (*str == '0' && str[1])
		return (1);
	while (ft_isdigit(*str))
	{
		*store = *store * 10 + *str - '0';
		if (*store > 255)
			return (1);
		++str;
	}
	if (*str)
		return (1);
	return (0);
}

char	*next_component(char *str)
{
	while (*str && *str != ',')
		++str;
	return (str);
}

char	*skip_comma(char *str)
{
	if (*str == ',')
		return (str + 1);
	return (str);
}

static int	error_atorgb(char *str, int *store)
{
	char	**split_rgb;
	int		component;

	if (*str == ',' || str[ft_strlen(str) - 1] == ',')
		return (1);
	split_rgb = ultra_split(str, skip_comma, next_component);
	if (!split_rgb)
		return (1);
	if (ft_arraylen(split_rgb) != 3)
		return (free_split(split_rgb), 1);
	*store = 0;
	if (error_atocomponent(split_rgb[0], &component))
		return (free_split(split_rgb), 1);
	*store = component;
	if (error_atocomponent(split_rgb[1], &component))
		return (free_split(split_rgb), 1);
	*store = (*store << 8) | component;
	if (error_atocomponent(split_rgb[2], &component))
		return (free_split(split_rgb), 1);
	*store = (*store << 8) | component;
	free_split(split_rgb);
	*store = (*store << 8) | 0xff;
	return (0);
}

static int	error_atovec(char *str, t_vector *store)
{
	char	**split_vec;

	if (*str == ',' || str[ft_strlen(str) - 1] == ',')
		return (1);
	split_vec = ultra_split(str, skip_comma, next_component);
	if (!split_vec)
		return (1);
	if (ft_arraylen(split_vec) != 3)
		return (free_split(split_vec), 1);
	if (error_atod(split_vec[0], &store->x))
		return (free_split(split_vec), 1);
	if (error_atod(split_vec[1], &store->y))
		return (free_split(split_vec), 1);
	if (error_atod(split_vec[2], &store->z))
		return (free_split(split_vec), 1);
	free_split(split_vec);
	return (0);
}

static int	fill_amb(char **input, t_scene *scene, t_anal_data *data)
{
	double	intensity;
	int		color;

	if (data->ambient)
		return (2);
	if (ft_arraylen(input) != 3)
		return (2);
	if (error_atod(input[1], &intensity))
		return (2);
	if (error_atorgb(input[2], &color))
		return (2);
	data->ambient = 1;
	scene->amb_light.brightness = intensity;
	scene->amb_light.color = color;
	return (0);
}

static int	fill_cam(char **input, t_scene *scene, t_anal_data *data)
{
	t_vector	origin;
	t_vector	orientation;
	double		fov;

	if (data->camera)
		return (3);
	if (ft_arraylen(input) != 4)
		return (3);
	if (ft_strchr(input[3], '.'))
		return (3);
	if (error_atovec(input[1], &origin))
		return (3);
	if (error_atovec(input[2], &orientation))
		return (3);
	if (error_atod(input[3], &fov))
		return (3);
	data->camera = 1;
	scene->camera.origin = origin;
	scene->camera.orientation = orientation;
	scene->camera.fov = fov;
	return (0);
}

static int	fill_light(char **input, t_scene *scene, t_anal_data *data)
{
	t_light		*light;
	t_vector	origin;
	double		brightness;
	int			color;

	if (data->light)
		return (4);
	if (ft_arraylen(input) != 4)
		return (4);
	if (error_atovec(input[1], &origin))
		return (4);
	if (error_atod(input[2], &brightness))
		return (4);
	if (error_atorgb(input[3], &color))
		return (4);
	data->light = 1;
	light = malloc(sizeof(t_light));
	if (!light)
		return (1);
	light->next = NULL;
	light->origin = origin;
	light->brightness = brightness;
	light->color = color;
	lst_add_back(&scene->lights, light);
	return (0);
}

static int	fill_sphere(char **input, t_object *object)
{
	t_vector	center;
	double		radius;
	int			color;

	if (ft_arraylen(input) != 4)
		return (6);
	if (error_atovec(input[1], &center))
		return (6);
	if (error_atod(input[2], &radius))
		return (6);
	if (error_atorgb(input[3], &color))
		return (6);
	object->type = SPHERE;
	object->shape.sphere.center = center;
	object->shape.sphere.radius = radius;
	object->color = color;
	return (0);
}

static int	fill_plane(char **input, t_object *object)
{
	t_vector	center;
	t_vector	normal;
	int			color;

	if (ft_arraylen(input) != 4)
		return (7);
	if (error_atovec(input[1], &center))
		return (7);
	if (error_atovec(input[2], &normal))
		return (7);
	if (error_atorgb(input[3], &color))
		return (7);
	object->type = PLANE;
	object->shape.plane.center = center;
	object->shape.plane.normal = normal;
	object->color = color;
	return (0);
}

static int	fill_cylinder(char **input, t_object *object)
{
	t_vector	center;
	t_vector	axis;
	double		radius;
	double		height;
	int			color;

	if (ft_arraylen(input) != 6)
		return (8);
	if (error_atovec(input[1], &center))
		return (8);
	if (error_atovec(input[2], &axis))
		return (8);
	if (error_atod(input[3], &radius))
		return (8);
	if (error_atod(input[4], &height))
		return (8);
	if (error_atorgb(input[5], &color))
		return (8);
	object->type = CYLINDER;
	object->shape.cylinder.center = center;
	object->shape.cylinder.axis = axis;
	object->shape.cylinder.radius = radius;
	object->shape.cylinder.height = height;
	object->color = color;
	return (0);
}

static int	fill_object(char **input, t_scene *scene, t_anal_data *data)
{
	t_object	*object;
	t_object	aux;
	int			error;

	if (data->type == SP)
		error = fill_sphere(input, &aux);
	else if (data->type == PL)
		error = fill_plane(input, &aux);
	else if (data->type == CY)
		error = fill_cylinder(input, &aux);
	else
		error = 5;
	if (error)
		return (error);
	object = malloc(sizeof(t_object));
	if (!object)
		return (1);
	data->object = 1;
	lst_add_back(&scene->objects, object);
	*object = aux;
	object->next = NULL;
	return (0);
}

static int	fill_type(char **input, t_scene *scene, t_anal_data *data)
{
	if (data->type == AMB)
		return (fill_amb(input, scene, data));
	if (data->type == CAM)
		return (fill_cam(input, scene, data));
	if (data->type == LIGHT)
		return (fill_light(input, scene, data));
	else
		return (fill_object(input, scene, data));
}

static int	get_data(char *line, t_scene *scene, t_anal_data *data)
{
	char	**split_line;
	int		error;

	if (*line == '#' || *skip_spaces(line) == '\0')
		return (0);
	split_line = ultra_split(line, skip_spaces, next_simple_word);
	if (!split_line)
		return (1);
	data->type = select_data_type(split_line[0]);
	if (!data->type)
		return (free_split(split_line), 5);
	error = fill_type(split_line, scene, data);
	return (free_split(split_line), error);
}

void	print_error(int error, t_anal_data data)
{
	if (error)
	{
		if (error == 1)
			fd_printf(2, "Mallocking error\n");
		else if (error == 2)
			fd_printf(2, "Ambient Error\n");
		else if (error == 3)
			fd_printf(2, "Camera Error\n");
		else if (error == 4)
			fd_printf(2, "Light Error\n");
		else if (error == 5)
			fd_printf(2, "No type specified\n");
		else if (error == 6)
			fd_printf(2, "Sphere Error\n");
		else if (error == 7)
			fd_printf(2, "Plane Error\n");
		else if (error == 8)
			fd_printf(2, "Cylinder Error\n");
		return ;
	}
	else if (!data.object)
		fd_printf(2, "No Object Specified\n");
}

t_scene	get_scene(char *file)
{
	t_scene		scene;
	char		*line;
	t_anal_data	data;
	int			error;
	int			fd;

	ft_bzero(&scene, sizeof(t_scene));
	ft_bzero(&data, sizeof(t_anal_data));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (scene);
	error = 0;
	while (!error)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		error = get_data(line, &scene, &data);
		free(line);
	}
	close(fd);
	if (error || !data.object || !data.camera || !data.ambient)
		free_scene(&scene);
	print_error(error, data);
	return (scene);
}
