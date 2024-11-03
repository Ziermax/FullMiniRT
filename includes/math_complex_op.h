/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_complex_op.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 04:12:00 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/11/03 04:47:17 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_COMPLEX_OP_H
# define MATH_COMPLEX_OP_H

# include "structs.h"

t_vector	add_vec(t_vector vec1, t_vector vec2);
t_vector	sub_vec(t_vector vec1, t_vector vec2);
t_vector	scl_vec(t_vector vec, float scale);
float		dot_product(t_vector vec1, t_vector vec2);
float		distance_of_points(t_vector vec1, t_vector vec2);
float		angle_between_vectors(t_vector vec1, t_vector vec2);

#endif
