/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trusanov <trusanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:17:16 by trusanov          #+#    #+#             */
/*   Updated: 2024/02/06 21:19:40 by trusanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global_code.h"

static int	*get_return_code_ptr(void)
{
	static int	ptr[1];

	return (ptr);
}

int		get_return_code(void)
{
	return (*get_return_code_ptr());
}

void	set_return_code(int c)
{
	*get_return_code_ptr() = c;
}
