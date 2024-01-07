#include "colour.h"

int	rgb_to_hex(t_rgb *colour)
{
	return ((colour->r << 16) | (colour->g << 8) | colour->b);
}
