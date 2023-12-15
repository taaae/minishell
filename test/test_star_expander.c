/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_star_expander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lporoshi <lporoshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:55:33 by lporoshi          #+#    #+#             */
/*   Updated: 2023/12/15 13:56:02 by lporoshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char **argv)
{
	char	**res;

	printf("[%s]\n", compose_expansion_str(argv[1], argv + 2));
	return (0);
}
