/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:00:16 by Kekuhne           #+#    #+#             */
/*   Updated: 2024/01/12 17:13:53 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_intersect *ray_intersect_plane(t_xyz *viewpoint, t_xyz ray, t_plane *plane);

t_intersect *ray_intersect_plane(t_xyz *viewpoint, t_xyz ray, t_plane *plane)
{
	t_intersect *intersection;
	float dot_product;
	float t;

	intersection = new_intersect();
	dot_product = v_dot(*plane->norm, ray);
	if (dot_product == 0)
		return (NULL);
	t = ((plane->point->x - viewpoint->x) * plane->norm->x + (plane->point->y - viewpoint->y) * plane->norm->y + (plane->point->z - viewpoint->z) * plane->norm->z) / dot_product;
	if (t < 0.0f)
		return (NULL);
	intersection->distance = t;
	intersection->point.x = viewpoint->x + t * ray.x;
	intersection->point.y = viewpoint->y + t * ray.y;
	intersection->point.z = viewpoint->z + t * ray.z;
	intersection->shape = plane;
	intersection->type = PLANE;
	return (intersection);
}

/* #include <stdlib.h>

t_intersect *ray_intersect_plane(t_xyz *viewpoint, t_xyz ray, t_plane *plane);

// Function to calculate the intersection point between a ray and a plane
t_intersect *calculate_intersection_point(t_xyz *viewpoint, t_xyz ray, t_plane *plane)
{
    float dotProduct = (plane->norm->x * ray.x) + (plane->norm->y * ray.y) + (plane->norm->z * ray.z);

    // Check if the ray is parallel to the plane
    if (dotProduct == 0) {
        // The ray is parallel to the plane, no intersection
        free(intersection);
        return NULL;
    }

    // Calculate the distance from the viewpoint to the intersection point
    float t = ((plane->point->x - viewpoint->x) * plane->norm->x +
               (plane->point->y - viewpoint->y) * plane->norm->y +
               (plane->point->z - viewpoint->z) * plane->norm->z) /
              dotProduct;

    // Calculate the intersection point
    intersection->point = (t_xyz *)malloc(sizeof(t_xyz));
    intersection->point->x = viewpoint->x + t * ray.x;
    intersection->point->y = viewpoint->y + t * ray.y;
    intersection->point->z = viewpoint->z + t * ray.z;

    // Copy the plane's normal and color to the intersection struct
    intersection->normal = plane->norm;
    intersection->color = plane->color;

    return intersection;
}

// Example usage in ray_intersect_plane function
t_intersect *ray_intersect_plane(t_xyz *viewpoint, t_xyz ray, t_plane *plane) {
    return calculate_intersection_point(viewpoint, ray, plane);
}
 */