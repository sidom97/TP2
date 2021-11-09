/* DO NOT EDIT THIS FILE */

#ifndef INCLUDE_COLOR_H_
#define INCLUDE_COLOR_H_

#include "pixel.h"

unsigned int color_get_interval(float max);
float color_get_interval_inverse(float max);
void color_value(pixel_t* pixel, float value, int interval, float interval_inverse);

#endif /* INCLUDE_COLOR_H_ */
