/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 21:51:10 by atudor            #+#    #+#             */
/*   Updated: 2024/12/07 21:51:47 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	clamp_rgba(int *red, int *green, int *blue, int *alpha)
{
	if (*red > 255)
		*red = 255;
	else if (*red < 0)
		*red = 0;
	if (*green > 255)
		*green = 255;
	else if (*green < 0)
		*green = 0;
	if (*blue > 255)
		*blue = 255;
	else if (*blue < 0)
		*blue = 0;
	if (alpha != NULL)
	{
		if (*alpha > 255)
			*alpha = 255;
		else if (*alpha < 0)
			*alpha = 0;
	}
}

int	sum_colors(int color1, int color2)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = ((color1 >> 24) & 0xFF) + ((color2 >> 24) & 0xFF);
	green = ((color1 >> 16) & 0xFF) + ((color2 >> 16) & 0xFF);
	blue = ((color1 >> 8) & 0xFF) + ((color2 >> 8) & 0xFF);
	if ((color1 & 0xFF) > (color2 & 0xFF))
		alpha = (color1 & 0xFF);
	else
		alpha = (color2 & 0xFF);
	clamp_rgba(&red, &green, &blue, &alpha);
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}

int	scale_color(int base_color, double brightness_factor)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = (base_color >> 24) & 0xFF;
	green = (base_color >> 16) & 0xFF;
	blue = (base_color >> 8) & 0xFF;
	alpha = base_color & 0xFF;
	red = (int)(red * brightness_factor);
	green = (int)(green * brightness_factor);
	blue = (int)(blue * brightness_factor);
	clamp_rgba(&red, &green, &blue, NULL);
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}

int	clamp_color(int color)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = (color >> 24) & 0xFF;
	green = (color >> 16) & 0xFF;
	blue = (color >> 8) & 0xFF;
	alpha = color & 0xFF;
	clamp_rgba(&red, &green, &blue, &alpha);
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}

int	multiply_colors_with_fallback(int color1, int color2, double fallback)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = ((color1 >> 24) & 0xFF) * ((color2 >> 24) & 0xFF) / 255;
	green = ((color1 >> 16) & 0xFF) * ((color2 >> 16) & 0xFF) / 255;
	blue = ((color1 >> 8) & 0xFF) * ((color2 >> 8) & 0xFF) / 255;
	if ((color1 & 0xFF) > (color2 & 0xFF))
		alpha = (color1 & 0xFF);
	else
		alpha = (color2 & 0xFF);
	red += ((color2 >> 24) & 0xFF) * fallback;
	green += ((color2 >> 16) & 0xFF) * fallback;
	blue += ((color2 >> 8) & 0xFF) * fallback;
	clamp_rgba(&red, &green, &blue, &alpha);
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}
