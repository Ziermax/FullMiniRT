/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:28:04 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/12/12 16:34:07 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "structs.h"

t_vector     normalize_vector(double x, double y, double z);

enum e_type
{
	NO_TYPE,
	AMB,
	CAM,
	LIGHT,
	SP,
	PL,
	CY
};

typedef struct s_anal_data
{
	char		light;
	char		object;
	char		camera;
	char		ambient;
	int			type;
}	t_anal_data;

#endif
