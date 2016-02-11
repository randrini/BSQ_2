/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrini <randrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 15:37:16 by randrini          #+#    #+#             */
/*   Updated: 2016/02/08 22:04:53 by randrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int		ft_stdin(void)
{
	int		fd;
	char	*buf;
	int		ret;
	
	buf = (char*)malloc(sizeof(char) * 4096);
	if (buf == NULL)
		return (0);
	fd = open("stdin_grid", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666);
	if (fd == -1)
		return (0);
	while ((ret = read(0, buf, sizeof(buf) -1)))
	{
		buf[ret] = '\0';
		write(fd, buf, ft_strlen(buf));
	}
	if (close(fd) == -1 || buf == NULL)
		return (0);
	free(buf);
	return (1);
}

int	main(int argc, char **argv)
{
	int		i;
	char	*buf;

	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			buf = parse_file(argv[i]);
			if (ft_check_char(buf) == 1 && ft_check_file(buf) == 1 &&
			ft_check_full_o(buf) == 1 && ft_check_grid(buf) == 1)
				fill_grid(parse_file(argv[i]));
			i++;
		}
	}
	else if (ft_stdin() == 1)
	{
		buf = parse_file("stdin_grid");
		if (ft_check_char(buf) == 1 && ft_check_file(buf) == 1 &&
		ft_check_full_o(buf) == 1 && ft_check_grid(buf) == 1)
			fill_grid(parse_file("stdin_grid"));
	}
	else
		ft_putstr("map error\n");
	return (0);
}
