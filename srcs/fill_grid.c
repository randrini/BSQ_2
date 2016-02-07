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

void	convert_grid(char **grid, int max_row, int max_col, t_param *params)
{
	int i;
	int j;

	i = 0;
	while (i < max_row)
	{
		j = 0;
		while (j < max_col)
		{
			if (grid[i][j] == params->empty)
				grid[i][j] = 1;
			if (grid[i][j] == params->obst)
				grid[i][j] = 0;
			j++;
		}
		i++;
	}
	solve_grid(grid, max_row, max_col, params);
}

void	solve_grid(char **grid, int max_row, int max_col, t_param *params)
{
	int		i;
	int		j;
	int		max_of_s;
	int		max_i;
	int		max_j;
	char	sub[max_row][max_col];

	i = 0;
	while (i < max_row)
	{
		sub[i][0] = grid[i][0];
		i++;
	}
	j = 0;
	while (j < max_col)
	{
		sub[0][j] = grid[0][j];
		j++;
	}
	max_of_s = sub[0][0];
	max_i = 0;
	max_j = 0;
	i = 1;
	while (i < max_row)
	{
		j = 1;
		while (j < max_col)
		{
			if (grid[i][j] == 1)
				sub[i][j] = ft_min(sub[i][j - 1], sub[i - 1][j],
						sub[i - 1][j - 1]) + 1;
			else
				sub[i][j] = 0;
			if (sub[i][j] > max_of_s)
			{
				max_of_s = sub[i][j];
				max_i = i;
				max_j = j;
			}
			j++;
		}
		i++;
	}
	print_solved_grid(grid, max_row, max_col, max_i, max_j, max_of_s, params);
}

void	print_solved_grid(char **grid, int max_row, int max_col,
		int max_i, int max_j, int max_of_s, t_param *params)
{
	int	i;
	int	j;

	i = 0;
	while (i < max_row)
	{
		j = 0;
		while (j < max_col)
		{
			if (grid[i][j] == 1)
			{
				grid[i][j] = params->empty;
			}
			if (grid[i][j] == 0)
				grid[i][j] = params->obst;
			if ((i < max_i + 1 && i > max_i - max_of_s) && (j <= max_j &&
						j > max_j - max_of_s))
				grid[i][j] = params->full;
			ft_putchar(grid[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

void	fill_grid(char *str)
{
	char	**grid;
	int		max_row;
	int		max_col;
	int		row;
	int		col;
	int		i;
	t_param	*params;

	max_row = size_row(str);
	max_col = size_col(str);
	row = 0;
	params = ft_get_parameters(str);
	i = skip_first_line(str);
	grid = malloc(sizeof(char *) * max_row);
	while (row < max_row)
	{
		grid[row] = malloc(sizeof(char) * max_col);
		row++;
	}
	row = 0;
	while (row < max_row)
	{
		col = 0;
		while (col < max_col)
		{
			grid[row][col] = str[i];
			col++;
			i++;
		}
		i += 1;
		row++;
	}
	convert_grid(grid, max_row, max_col, params);
}
