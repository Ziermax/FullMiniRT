/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:21:10 by atudor            #+#    #+#             */
/*   Updated: 2024/10/20 17:21:12 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/structs.h"

t_vector	calculate_direction(t_vector camera_dir, double ndc_x, double ndc_y)
{
    t_vector direction;
    t_vector right;
    t_vector up;

    // Calculate the right vector using a fixed up vector (assumes camera_dir is normalized)
    right = vector_cross_product(camera_dir, (t_vector){0, 1, 0});
    right = normalize_vector(right.x, right.y, right.z);

    // Calculate the up vector as orthogonal to the camera direction and right vector
    up = vector_cross_product(right, camera_dir);
    up = normalize_vector(up.x, up.y, up.z);

    // Scale the right and up vectors by ndc_x and ndc_y
    right = vector_scalar(right, ndc_x);
    up = vector_scalar(up, ndc_y);

    // Combine the camera direction with the scaled right and up vectors
    direction = vector_add(camera_dir, right);
    direction = vector_add(direction, up);

    // Normalize the resulting direction vector
    direction = normalize_vector(direction.x, direction.y, direction.z);
    return direction;
}


t_ray create_ray(t_data *data, int x, int y) {
    double ndc_x;
    double ndc_y;
    t_vector camera_dir;
    t_ray ray;

    // Calculate aspect ratio as a double (not integer division)
    double aspect_ratio = (double)data->w_width / (double)data->w_height;

    // Get the camera orientation (assumes it's normalized)
    camera_dir = data->scene.camera.orientation;

    // Calculate NDC coordinates
    ndc_x = normal_dev_coordinates(x, data, 0) * aspect_ratio * tan(data->scene.camera.fov * 0.5 * M_PI / 180);
    ndc_y = normal_dev_coordinates(y, data, 1) * tan(data->scene.camera.fov * 0.5 * M_PI / 180);

    // Calculate the ray direction
    ray.origin = data->scene.camera.origin; // Assuming you have a camera position
    ray.direction = calculate_direction(camera_dir, ndc_x, ndc_y);

    // Normalize the ray direction
    ray.direction = normalize_vector(ray.direction.x, ray.direction.y, ray.direction.z);

    // Debugging output
    printf("Ray origin: (%f, %f, %f)\n", ray.origin.x, ray.origin.y, ray.origin.z);
    printf("Ray direction: (%f, %f, %f)\n", ray.direction.x, ray.direction.y, ray.direction.z);
    printf("ndc_x: %f, ndc_y: %f\n", ndc_x, ndc_y);

    return ray;
}