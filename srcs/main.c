/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrini <randrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 15:37:16 by randrini          #+#    #+#             */
/*   Updated: 2016/02/16 18:54:45 by randrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int		ft_grid_empty(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\0')
		i++;
	return (i);
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
	if (ft_grid_empty(buf) == 0)
		return (-1);
	if (close(fd) == -1 || buf == NULL)
		return (-1);
	free(buf);
	return (1);
}

void		fill_grid(char *str)
{
	int		i;
	char	**grid;
	t_coord	coordi;
	t_param	*params;

	coordi.max_row = size_row(str);
	coordi.max_col = size_col(str);
	coordi.row = -1;
	params = ft_get_parameters(str);
	i = skip_first_line(str) - 1;
	grid = malloc(sizeof(char *) * coordi.max_row);
	while (++coordi.row < coordi.max_row)
		grid[coordi.row] = malloc(sizeof(char) * coordi.max_col);
	coordi.row = -1;
	while (++coordi.row < coordi.max_row)
	{
		coordi.col = -1;
		while (++coordi.col < coordi.max_col)
			grid[coordi.row][coordi.col] = str[++i];
		i += 1;
	}
	free(str);
	convert_grid(grid, coordi, params);
}

int		main(int argc, char **argv)
{
	int		i;

	if (argc > 1)
	{
		i = 0;
		while (++i < argc)
		{
			if (open(argv[i], O_RDONLY) > -1 &&
					ft_grid_empty(parse_file(argv[i])) > 0 &&
					ft_full_check(parse_file(argv[i])) == 1)
				fill_grid(parse_file(argv[i]));
			else
				ft_putstr("map error\n");
		}
	}
	if (argc == 1)
	{
		if (ft_stdin() == 1 && ft_full_check(parse_file("stdin_grid")) == 1)
			fill_grid(parse_file("stdin_grid"));
		else
			ft_putstr("map error\n");
	}
	return (0);
}
