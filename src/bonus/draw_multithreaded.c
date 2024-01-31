/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:21:56 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/30 18:36:42 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS

# include "bonus.h"
# include "xyz.h"
# include "draw.h"
# include "msaa.h"

static t_xyz	get_ray(t_vars *data, t_camera *camera, int x, int y);
static void		*draw_closest_shape(void *void_data);
static void		*draw_closest_shape_msaa(void *void_data);

int	draw_scene(t_rt *rt)
{
	int				i;
	pthread_t		thread[THREADS];
	t_thread_info	*data[THREADS];
	int				id[THREADS];

	calculate_camera_right_up(rt->scene->camera);
	i = 0;
	pthread_mutex_init(&rt->print_lock, NULL);
	while (i < THREADS)
	{
		id[i] = i;
		data[i] = create_threaddata(rt, start(i, rt), end(i, rt));
		if (!rt->msaa)
			pthread_create(&thread[i], NULL, draw_closest_shape, data[i]);
		else
			pthread_create(&thread[i], NULL, draw_closest_shape_msaa, data[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(thread[i], NULL);
		free(data[i++]);
	}
	return (0);
}

static void	*draw_closest_shape(void *void_data)
{
	int					x;
	int					y;
	t_xyz				ray;
	t_intersect			intersect;
	t_thread_info		*data;

	data = (t_thread_info *)void_data;
	y = data->start_y;
	while (y < data->end_y)
	{
		x = 0;
		while (x < data->mlx->win_x)
		{
			ray = get_ray(data->mlx, data->camera, x, y);
			intersect = get_closest_shape(*data->camera->position, ray,
					data->rt->scene);
			if (intersect.valid)
				draw_pixel(data->rt, (t_xyz){x, y, 0}, intersect, ray);
			x++;
		}
		y++;
	}
	return (NULL);
}

static void	*draw_closest_shape_msaa(void *void_data)
{
	int					x;
	int					y;
	t_msaa				ray_info;
	t_thread_info		*data;

	data = (t_thread_info *)void_data;
	y = data->start_y;
	while (y < data->end_y)
	{
		x = 0;
		while (x < data->mlx->win_x)
		{
			ray_info = get_ray_info(data->rt, data->camera, x, y);
			ray_info = process_shadows(data->rt->scene, ray_info);
			print_pixel_msaa(data->rt, x, y, ray_info);
			x++;
		}
		y++;
	}
	return (NULL);
}

static t_xyz	get_ray(t_vars *data, t_camera *camera, int x, int y)
{
	double	dx;
	double	dy;
	double	scale;
	t_xyz	result;

	scale = tanf(0.5 * (float)camera->fov * (M_PI / 180.0));
	dx = scale * data->aspect_ratio * (((x + 0.5) / data->win_x) * 2.0 - 1.0);
	dy = scale * (1.0 - ((y + 0.5) / data->win_y) * 2.0);
	result = v_add(v_add(v_scale(camera->right, dx),
				v_scale(camera->up, dy)), *camera->forward);
	result = v_normalize(result);
	return (result);
}

#endif
