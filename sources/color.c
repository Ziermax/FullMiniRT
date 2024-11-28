/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 04:28:03 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/11/03 04:28:49 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	proportional_trgb(float percentage, int color, int max_color)
{
	int	diff;

	diff = max_color - color;
	color = color + diff * percentage;
	return (color);
}

int	proportional_color(float percentage, int min_color, int max_color)
{
    int	new_t;
    int	new_r;
    int	new_g;
    int	new_b;
    int	color;

    if (min_color == max_color)
        return (min_color);
    new_t = proportional_trgb(percentage,
            min_color >> 24 & 255, max_color >> 24 & 255);
    new_r = proportional_trgb(percentage,
            min_color >> 16 & 255, max_color >> 16 & 255);
    new_g = proportional_trgb(percentage,
            min_color >> 8 & 255, max_color >> 8 & 255);
    new_b = proportional_trgb(percentage,
            min_color & 255, max_color & 255);
    color = new_t << 24 | new_r << 16 | new_g << 8 | new_b;
    return (color);
}

t_vector	surface_normal(t_object *object, t_vector intersection)
{
	t_vector normal;

	normal = (t_vector){0, 0, 0};
	if (object->type == SPHERE)
	{
		normal = vector_subtract(intersection, object->shape.sphere.center);
		normal = normalize_vector(normal.x, normal.y, normal.z);
	}
	// else if (object->type == PLANE)
	// {
	// 	normal = object->shape.plane.normal;
	// }
	// else if (object->type == CYLINDER)
	// {
	// 	normal = vector_subtract(intersection, object->shape.cylinder.center);
	// 	normal = normalize_vector(normal.x, normal.y, normal.z);
	// }
	// else if (object->type == PARABOLOID)
	// {
	// 	normal = vector_subtract(intersection, object->shape.paraboloid.center);
	// 	normal = normalize_vector(normal.x, normal.y, normal.z);
	// }
	return (normal);
}

int clamp_color(int color) {
    int alpha = (color >> 24) & 0xFF;
    int red = (color >> 16) & 0xFF;
    int green = (color >> 8) & 0xFF;
    int blue = color & 0xFF;

    red = red > 255 ? 255 : (red < 0 ? 0 : red);
    green = green > 255 ? 255 : (green < 0 ? 0 : green);
    blue = blue > 255 ? 255 : (blue < 0 ? 0 : blue);
    alpha = alpha > 255 ? 255 : (alpha < 0 ? 0 : alpha);

    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

int scale_color(int base_color, double scale_factor) {
    int alpha = (base_color >> 24) & 0xFF;
    int red = (base_color >> 16) & 0xFF;
    int green = (base_color >> 8) & 0xFF;
    int blue = base_color & 0xFF;

    red = (int)(red * scale_factor);
    green = (int)(green * scale_factor);
    blue = (int)(blue * scale_factor);

    red = red > 255 ? 255 : red;
    green = green > 255 ? 255 : green;
    blue = blue > 255 ? 255 : blue;
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

int apply_diffuse_lighting(int object_color, t_vector normal, t_light *light, t_vector intersection) {
    t_vector light_dir = vector_subtract(light->origin, intersection);
    light_dir = normalize_vector(light_dir.x, light_dir.y, light_dir.z);

    double brightness = dot_product(normal, light_dir);
    brightness = brightness > 1.0 ? 1.0 : (brightness < 0.0 ? 0.0 : brightness);

    return scale_color(object_color, brightness * light->brightness);
}

int get_color(t_data *data, t_vector intersection, t_object *object) {
    t_vector normal = surface_normal(object, intersection);
    t_light *light = data->scene.lights;

    double ambient_intensity = data->scene.amb_light.brightness;
	int non_direct_light_color = proportional_color(0.99, object->color, BLACK);
    int final_color = proportional_color(ambient_intensity, object->color, non_direct_light_color);

    while (light) {
        t_vector light_dir = vector_subtract(light->origin, intersection);
        light_dir = normalize_vector(light_dir.x, light_dir.y, light_dir.z);

        double brightness = dot_product(normal, light_dir);
        if (brightness > 0) {
            int diffuse_color = apply_diffuse_lighting(object->color, normal, light, intersection);
            final_color = proportional_color(brightness, final_color, diffuse_color);
        }
        light = light->next;
    }
    return clamp_color(final_color);
}

// to do:
// normalize light brightness, it looks weird when brightness is 0.3 or lower. also at 3 it should be the brightest possible, its weird af
// add specular lighting
// add shadows
// add plane and cylinder



// int get_color(t_data *data, t_vector intersection, t_object *object) {
//     t_vector normal = surface_normal(object, intersection);
//     t_light *light = data->scene.lights;

//     int color =0;

//     while (light)
// 	{
//             int diffuse_color = apply_diffuse_lighting(object->color, normal, light, intersection);
//             color = proportional_color(1.0, color, diffuse_color);
//         light = light->next;
//     }

//     return clamp_color(color);  // Clamp color to valid range (0–255 per channel)
// }


// int get_color(t_data *data, t_vector intersection, t_object *object) {
//     t_vector normal = surface_normal(object, intersection);
//     t_light *light = data->scene.lights;
//     int color = object->color; // Start with the object's base color
//     int diffuse_color;
//     double brightness;

//     // Iterate over all lights
//     while (light)
// 	{
//         t_vector light_dir = vector_subtract(light->origin, intersection);
//         light_dir = normalize_vector(light_dir.x, light_dir.y, light_dir.z);

//         brightness = dot_product(normal, light_dir);
//         if (brightness > 0) {
//             diffuse_color = blend_lighting(color, light->color, brightness);
//             color = proportional_color(brightness, color, diffuse_color);
//         }
//         light = light->next;
//     }

//     // Clamp the final color to prevent overflow
//     return clamp_color(color);
// }

// int get_color(t_data *data, t_vector intersection, t_object *object)
// {
//     t_vector	normal;
//     t_light		*light;
//     t_vector	light_dir;
//     float		brightness;
//     int			color = 0;
//     int			ambient_color;
//     double		ambient_intensity;

//     light = data->scene.lights;
//     ambient_intensity = data->scene.amb_light.brightness;
//     normal = surface_normal(object, intersection);

//     // Step 1: Ambient lighting
//     ambient_color = proportional_color(ambient_intensity, object->color, data->scene.amb_light.color);
//     color = proportional_color(50, color, ambient_color);

//     // Step 2: Diffuse lighting
//     while (light)
//     {
//         light_dir = vector_subtract(light->origin, intersection);
//         light_dir = normalize_vector(light_dir.x, light_dir.y, light_dir.z);
//         brightness = dot_product(normal, light_dir);
//         if (brightness > 0)
//         {
//             int diffuse_color = proportional_color(brightness, 0, light->color);
//             color = proportional_color(50, color, diffuse_color);
//         }
//         light = light->next;
//     }

//     // Step 3: Specular lighting (not implemented)

//     return color;
// }

