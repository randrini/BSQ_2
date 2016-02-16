/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrini <randrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 16:51:02 by randrini          #+#    #+#             */
/*   Updated: 2016/02/15 15:21:01 by randrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int		ft_error(void)
{
	return (0);
}

int		ft_check_file(char *buf)
{
	int		i;
	char	*str;
	t_param	*tmp_param;

	i = 0;
	str = first_line(buf);
	tmp_param = ft_get_parameters(buf);
	if (str[0] >= 48 && str[0] <= 57)
	{
		str[ft_strlen_mod(buf) - 3] = '\0';
		if (ft_atoi(str) != size_row(buf))
			return (ft_error());
		i = ft_intlen(ft_atoi(str));
		str = first_line(buf);
		if (str[i] == tmp_param->empty)
			i++;
		if (str[i] == tmp_param->obst)
			i++;
		if (str[i] == tmp_param->full)
			return (1);
	}
	return (ft_error());
}

int		ft_check_char(char *buf)
{
	int		i;
	t_param	*tmp_param;

	i = skip_first_line(buf);
	tmp_param = ft_get_parameters(buf);
	while (buf[i] != '\0')
	{
		if (buf[i] == tmp_param->empty ||
				buf[i] == tmp_param->obst || buf[i] == '\n')
				i++;
		else
			return (0);
	}
	return (1);
}

int		ft_check_full_o(char *str)
{
	int		i;
	t_param	*tmp_param;

	i = 0;
	tmp_param = ft_get_parameters(str);
	while (str[i] != '\n')
		i++;
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == tmp_param->obst || str[i] == '\n')
			i++;
		else
			return (1);
	}
	return (ft_error());
}

int		ft_check_grid(char *str)
{
	int i;
	int	j;
	int k;

	j = 0;
	i = skip_first_line(str);
	while (str[++i] != '\n' && str[i] != '\0')
		j++;
	i += 1;
	k = i;
	while (str[i] != '\0')
	{
		while (str[i] != '\n' && str[i] != '\0')
			++i;
		if ((i - 1 - k) != j)
			return (ft_error());
		else
		{
			i++;
			k = i;
		}
	}
	return (1);
}
