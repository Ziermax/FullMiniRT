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

int get_alpha(int color) {
    return (color >> 24) & 0xFF;
}

int get_red(int color) {
    return (color >> 16) & 0xFF;
}

int get_green(int color) {
    return (color >> 8) & 0xFF;
}

int get_blue(int color) {
    return color & 0xFF;
}

int create_color(int alpha, int red, int green, int blue) {
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

int blend_colors(int color1, int color2) {
    int alpha1 = get_alpha(color1);
    int red1 = get_red(color1);
    int green1 = get_green(color1);
    int blue1 = get_blue(color1);

    int alpha2 = get_alpha(color2);
    int red2 = get_red(color2);
    int green2 = get_green(color2);
    int blue2 = get_blue(color2);

    // Blend using alpha
    float alpha1_frac = alpha1 / 255.0;
    float alpha2_frac = alpha2 / 255.0;
    float out_alpha = alpha1_frac + alpha2_frac * (1 - alpha1_frac);

    // Blend colors using the formula: result = c1 * alpha1 + c2 * alpha2 * (1 - alpha1)
    int out_red = (int)((red1 * alpha1_frac + red2 * alpha2_frac * (1 - alpha1_frac)) / out_alpha);
    int out_green = (int)((green1 * alpha1_frac + green2 * alpha2_frac * (1 - alpha1_frac)) / out_alpha);
    int out_blue = (int)((blue1 * alpha1_frac + blue2 * alpha2_frac * (1 - alpha1_frac)) / out_alpha);
    int out_alpha_int = (int)(out_alpha * 255);

    return create_color(out_alpha_int, out_red, out_green, out_blue);
}


int	compute_diffuse_intensity(t_vector normal, t_vector light_dir)
{
	double	dot;

	dot = dot_product(normal, light_dir);
	if (dot < 0)
		dot = 0;
	return (dot);
}

int apply_diffuse_lighting(int color, double intensity, int light_color) {
    int alpha = get_alpha(color);  // Preserve the original alpha channel
    int red = (int)(((color >> 16 & 255) * intensity * (light_color >> 16 & 255)) / 255);
    int green = (int)(((color >> 8 & 255) * intensity * (light_color >> 8 & 255)) / 255);
    int blue = (int)(((color & 255) * intensity * (light_color & 255)) / 255);

    // Ensure values are within 0-255 range
    red = red > 255 ? 255 : red;
    green = green > 255 ? 255 : green;
    blue = blue > 255 ? 255 : blue;

    return create_color(alpha, red, green, blue);
}


int clamp_color(int color) {
    int alpha = get_alpha(color);
    int red = get_red(color);
    int green = get_green(color);
    int blue = get_blue(color);

    // Clamp each channel to the range 0-255
    red = red > 255 ? 255 : (red < 0 ? 0 : red);
    green = green > 255 ? 255 : (green < 0 ? 0 : green);
    blue = blue > 255 ? 255 : (blue < 0 ? 0 : blue);
    alpha = alpha > 255 ? 255 : (alpha < 0 ? 0 : alpha);

    return create_color(alpha, red, green, blue);
}

int get_final_color(int final_color, t_light *light, t_vector normal, t_vector intersection, t_object *object)
{
	t_vector light_dir;
	// double light_intensity;
	double diffuse_intensity;
	int diffuse_color;

	light_dir = vector_subtract(light->origin, intersection);

	//get angle between light and object

	//light_dir = normalize_vector(light_dir.x, light_dir.y, light_dir.z);
	// light_intensity = light->brightness;
	//diffuse_intensity = compute_diffuse_intensity(normal, light_dir);
	//diffuse_color = apply_diffuse_lighting(object->color, diffuse_intensity, light->color);
	// // Optionally, calculate specular lighting (Phong reflection model)
	// double specular_intensity = compute_specular_intensity(ray, normal, light_dir);
	// int specular_color = apply_specular_lighting(light->color, specular_intensity);

	// Blend the diffuse and specular components with the final color
			
	// final_color = blend_colors(final_color, specular_color);
	printf("Color after blending w diffuse: %x\n", proportional_color(0.5, final_color, diffuse_color));
	return (proportional_color(0.5, final_color, diffuse_color));
}

int get_color(t_data *data, t_vector intersection, t_object *object)
{
    t_vector	normal;
    t_light		*light;
	float		brightness;
    int			color = 0;
//	int			ambient_color;
    double		ambient_intensity;

	light = data->scene.lights;
	ambient_intensity = data->scene.amb_light.brightness;
	normal = surface_normal(object, intersection);

    // Step 1: Calculate ambient color
	//ambient_color = proportional_color(object->color, ambient_intensity, data->scene.amb_light.color);
	//printf("initial given object color: %x\n", object->color);
    // Step 2: Initialize the final color with ambient contribution
   //color = proportional_color(0.5,color, ambient_color);
   printf("Color after blending w ambient: %x\n", color);

    // Step 3: Iterate over all lights to calculate diffuse and specular contributions
    while (light)
	{
		//color = get_finaldclor(color, light, normal, intersection, object);
		brightness += get_brightness_intesity(light, intersection);
        light = light->next;
    }
	if (brightness > 1)
		brightness = 1;
	color = proportional_color(brightness, ambient_intensity, color);

    // Step 4: Clamp the final color values to ensure they are within valid ranges
	printf("Final color before returning: %x\n", color);
    return (color);
}

