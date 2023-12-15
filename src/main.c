/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/12 18:01:52 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/miniRT.h"

int	main(int argc, char **argv)
{
	t_vars	*mlx_data;

	if (argc != 2)
		return (ft_putstr_fd("usage: ./miniRT <path/map.rt>\n", 2), 1);
	(void)argv;
	if (parse(argv[1]) == FAIL)
		return (1);
	mlx_data = ft_calloc(sizeof(t_vars), 1);
	initialise(mlx_data);
	raytrace(mlx_data);
	return (0);
}
