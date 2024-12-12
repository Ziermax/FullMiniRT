/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:28:04 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/12/10 12:17:26 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "structs.h"

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
