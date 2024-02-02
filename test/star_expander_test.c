/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_expander_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:13:03 by lporoshi          #+#    #+#             */
/*   Updated: 2024/02/02 19:19:28 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansions.h"

int	main(void)
{
	char	**tmp;
	char	**result_of_star_expansions;
	char	*line;

	line = ft_strdup("*e*");
	result_of_star_expansions = expand_stars_string(line);
	tmp = result_of_star_expansions;
	while (*result_of_star_expansions != NULL)
	{
		ft_printf("%s\n", *result_of_star_expansions);
		result_of_star_expansions++;
	}
	free_str_arr(&tmp);
	free(line);
	ft_printf("===========================");
	return (0);
}
