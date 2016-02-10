/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrini <randrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 15:37:41 by randrini          #+#    #+#             */
/*   Updated: 2016/02/08 22:18:16 by randrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

# define BUFFER_SIZE 40960000

char			*parse_file(char *file);
void			fill_grid(char *str);
void			ft_putchar(char c);
void			ft_putstr(char *str);
int				size_row(char *str);
int				size_col(char *str);
int				ft_min(int a, int b, int c);

int				ft_atoi(char *str);
int				skip_first_line(char *str);
char			*first_line(char *str);
int				ft_strlen(char *str);
void			ft_check_parameters(char *str);
int				ft_intlen(int n);
int				ft_error(void);
int				ft_check_file(char *buf);
int				ft_check_full_o(char *buf);
int				ft_check_char(char *buf);
int				ft_check_grid(char *buf);

typedef struct	s_param
{
	char	empty;
	char	obst;
	char	full;
}				t_param;

typedef struct	s_coord
{
	int		row;
	int		col;
	int		max_col;
	int		max_row;
}				t_coord;

typedef struct	s_submat
{
	int		max_i;
	int		max_j;
	int		max_of_s;
}				t_submat;

void			print_solved_grid(char **grid, t_coord coordi,
		t_submat sub_m, t_param *params);
void			solve_grid(char **grid, t_coord coordi, t_param *params);
t_param			*ft_get_parameters(char *buf);
int				ft_strlen_mod(char *str);

#endif
