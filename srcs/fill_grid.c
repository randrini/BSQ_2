/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrini <randrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 16:19:48 by randrini          #+#    #+#             */
/*   Updated: 2016/02/06 17:12:42 by randrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_param		*ft_get_parameters(char *buf)
{
	int		i;
	char	*str;
	t_param	*params;

	str = first_line(buf);
	str[ft_strlen_mod(buf) - 3] = '\0';
	i = ft_intlen(ft_atoi(str));
	str = first_line(buf);
	params = malloc(sizeof(params));
	params->empty = str[i];
	params->obst = str[i + 1];
	params->full = str[i + 2];
	return (params);
}

void	convert_grid(char **grid, t_coord  coordi, t_param *params)
{
	int i;
	int j;

	i = 0;
	while (i < coordi.max_row)
	{
		j = 0;
		while (j < coordi.max_col)
		{
			if (grid[i][j] == params->empty)
				grid[i][j] = 1;
			if (grid[i][j] == params->obst)
				grid[i][j] = 0;
			j++;
		}
		i++;
	}
	solve_grid(grid, coordi, params);
}

void	solve_grid(char **grid, t_coord coordi, t_param *params)
{
	t_submat	sub_m;
	char	sub[coordi.max_row][coordi.max_col];

	coordi.row = 0;
	while (coordi.row < coordi.max_row)
	{
		sub[coordi.row][0] = grid[coordi.row][0];
		coordi.row++;
	}
	coordi.col = 0;
	while (coordi.col < coordi.max_col)
	{
		sub[0][coordi.col] = grid[0][coordi.col];
		coordi.col++;
	}
	sub_m.max_of_s = sub[0][0];
	sub_m.max_i = 0;
	sub_m.max_j = 0;
	coordi.row = 1;
	while (coordi.row < coordi.max_row)
	{
		coordi.col = 1;
		while (coordi.col < coordi.max_col)
		{
			if (grid[coordi.row][coordi.col] == 1)
				sub[coordi.row][coordi.col] = ft_min(sub[coordi.row][coordi.col - 1], sub[coordi.row - 1][coordi.col],
						sub[coordi.row - 1][coordi.col - 1]) + 1;
			else
				sub[coordi.row][coordi.col] = 0;
			if (sub[coordi.row][coordi.col] > sub_m.max_of_s)
			{
				sub_m.max_of_s = sub[coordi.row][coordi.col];
				sub_m.max_i = coordi.row;
				sub_m.max_j = coordi.col;
			}
			coordi.col++;
		}
		coordi.row++;
	}
	print_solved_grid(grid, coordi, sub_m, params);
}

void	print_solved_grid(char **grid, t_coord coordi,
		t_submat sub_m, t_param *params)
{
	coordi.row = 0;
	while (coordi.row < coordi.max_row)
	{
		coordi.col = 0;
		while (coordi.col < coordi.max_col)
		{
			if (grid[coordi.row][coordi.col] == 1)
			{
				grid[coordi.row][coordi.col] = params->empty;
			}
			if (grid[coordi.row][coordi.col] == 0)
				grid[coordi.row][coordi.col] = params->obst;
			if ((coordi.row < sub_m.max_i + 1 && coordi.row > sub_m.max_i - sub_m.max_of_s) && (coordi.col <= sub_m.max_j &&
						coordi.col > sub_m.max_j - sub_m.max_of_s))
				grid[coordi.row][coordi.col] = params->full;
			ft_putchar(grid[coordi.row][coordi.col]);
			coordi.col++;
		}
		ft_putchar('\n');
		coordi.row++;
	}
}

void	fill_grid(char *str)
{
	char	**grid;
	t_coord	coordi;
	int		i;
	t_param	*params;

	coordi.max_row = size_row(str);
	coordi.max_col = size_col(str);
	coordi.row = 0;
	params = ft_get_parameters(str);
	i = skip_first_line(str);
	grid = malloc(sizeof(char *) * coordi.max_row);
	while (coordi.row < coordi.max_row)
	{
		grid[coordi.row] = malloc(sizeof(char) * coordi.max_col);
		coordi.row++;
	}
	coordi.row = 0;
	while (coordi.row < coordi.max_row)
	{
		coordi.col = 0;
		while (coordi.col < coordi.max_col)
		{
			grid[coordi.row][coordi.col] = str[i];
			coordi.col++;
			i++;
		}
		i += 1;
		coordi.row++;
	}
	convert_grid(grid, coordi, params);
}
