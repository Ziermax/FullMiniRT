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
