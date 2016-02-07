/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrini <randrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 15:37:00 by randrini          #+#    #+#             */
/*   Updated: 2016/02/06 19:10:31 by randrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*first_line(char *buf)
{
	char	*first_line;
	int		i;

	i = 0;
	if (buf[0] == '\0')
		ft_error();
	while (buf[i] != '\n')
		i++;
	first_line = (char*)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (buf[i] != '\n')
	{
		first_line[i] = buf[i];
		i++;
	}
	first_line[i] = '\0';
	return (first_line);
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_intlen(int n)
{
	int i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		++i;
	}
	return (i);
}

char	*parse_file(char *file)
{
	int			fd;
	int			ret;
	static char	buf[BUFFER_SIZE];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error();
	ret = read(fd, buf, BUFFER_SIZE);
	buf[ret] = '\0';
	close(fd);
	ft_check_file(buf);
	ft_check_char(buf);
	ft_check_full_o(buf);
	ft_check_grid(buf);
	return (buf);
}
