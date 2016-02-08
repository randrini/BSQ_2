/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrini <randrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 15:37:16 by randrini          #+#    #+#             */
/*   Updated: 2016/02/06 19:12:17 by randrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	main(int argc, char **argv)
{
	int		i;
	char	*buf;

	i = 1;
	if (argc == 1)
		ft_putstr("map error\n");

	while (i < argc)
	{
		buf = parse_file(argv[i]);
		if (ft_check_char(buf) == 1 && ft_check_file(buf) == 1 &&
		ft_check_full_o(buf) == 1 && ft_check_grid(buf) == 1)
			fill_grid(parse_file(argv[i]));
		i++;
	}
	return (0);
}
