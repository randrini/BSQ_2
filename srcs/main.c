/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrini <randrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 15:37:16 by randrini          #+#    #+#             */
/*   Updated: 2016/02/11 13:22:27 by randrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int		ft_grid_empty(int fd)
{
	int	size;
	
   	size = lseek(fd, 0, SEEK_END);
	return(size);
}

int		ft_full_check(char *stream)
{
	if (ft_check_char(stream) != 1)
		return (0);
	if (ft_check_file(stream) != 1)
		return (0);
	if (ft_check_full_o(stream) != 1)
		return (0);
	if (ft_check_grid(stream) != 1)
		return (0);
	return (1);
}

int		ft_stdin(void)
{
	int		fd;
	char	*buf;
	int		ret;

	buf = (char*)malloc(sizeof(char) * 4096);
	if (buf == NULL)
		return (-1);
	fd = open("stdin_grid", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666);
	if (fd == -1)
		return (-1);
	while ((ret = read(0, buf, sizeof(buf) - 1)))
	{
		buf[ret] = '\0';
		write(fd, buf, ft_strlen(buf));
	}
	if (ft_grid_empty(fd) == 0)
		return (-1);
	if (close(fd) == -1 || buf == NULL)
		return (-1);
	free(buf);
	return (1);
}

int		main(int argc, char **argv)
{
	int		i;

	if (/*argc == 1 && */ft_stdin() == 1 && ft_full_check(parse_file("stdin_grid")) == 1)
		fill_grid(parse_file("stdin_grid"));
	else if (argc > 1)
	{
		i = 0;
		while (++i < argc)
		{
			if (open(argv[i], O_RDONLY) > -1 && ft_grid_empty
			(open(argv[i], O_RDONLY)) != 0 && ft_full_check(parse_file(argv[i])) == 1)
				fill_grid(parse_file(argv[i]));
			else
				ft_putstr("map error\n");
		}
	}
	else
		ft_putstr("map error\n");
	return (0);
}
