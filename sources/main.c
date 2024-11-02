/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:41:02 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/11/02 23:52:31 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structs.h" 

void	key_events(void *param)
{
	mlx_image_t	*image;
	mlx_t		*mlx;

	mlx = ((t_data *)param)->mlx;
	image = ((t_data *)param)->img;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)data;
	data.mlx = mlx_init(W_WIDTH, W_HEIGHT, "miniRT", false);
	data.img = mlx_new_image(data.mlx, W_WIDTH, W_HEIGHT);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_loop_hook(data.mlx, key_events, &data.mlx);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
