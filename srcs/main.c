/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrini <randrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 15:37:16 by randrini          #+#    #+#             */
/*   Updated: 2016/02/15 15:25:22 by randrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_strcat_mod(char *dest, char c)
{
	int 	i;
	char	*ret;

	i = 0;
	ret = malloc(ft_strlen(dest) + 2);
	while(dest[i])
	{
		ret[i] = dest[i];
		i++;
	}
	ret[i++] = c;
	ret[i] = '\0';
	return (ret);
}

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
