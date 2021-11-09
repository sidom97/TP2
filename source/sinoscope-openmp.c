#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "log.h"
#include "sinoscope.h"

int sinoscope_image_openmp(sinoscope_t* sinoscope) {
       if (sinoscope == NULL) {
        LOG_ERROR_NULL_PTR();
        goto fail_exit;
    }
    unsigned int interval=sinoscope->interval;
    float phase1=sinoscope->phase1;
    float phase0=sinoscope->phase0;
    float time = sinoscope->time;
    float interval_inverse= sinoscope->interval_inverse;
    unsigned int width =sinoscope->width;
    unsigned int height =height=sinoscope->height;
    unsigned int taylor=sinoscope->taylor;
    float dx =sinoscope->dx;
    float dy=sinoscope->dy;
    float px=0.0;
    float py=0.0;
    float value=0.0;
    pixel_t pixel;
    int index=0;

   #pragma omp parallel for simd schedule(dynamic) firstprivate(sinoscope,index,pixel,px,py,value,taylor,width,interval_inverse,phase1,phase0,time,interval,height,dx,dy)
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
             px    = dx * j - 2 * M_PI;
             py    = dy * i - 2 * M_PI;
             value=0.0;
            for (int k = 1; k <= taylor; k += 2) {
                value += sin(px * k * phase1 + time) / k;
                value += cos(py * k * phase0) / k;
            }

            value = (atan(value) - atan(-value)) / M_PI;

            value = (value + 1) * 100;

            color_value(&pixel, value, interval, interval_inverse);
            index = (i * 3) + (j * 3) * width;
            
            sinoscope->buffer[index + 0] = pixel.bytes[0];
            sinoscope->buffer[index + 1] = pixel.bytes[1];
            sinoscope->buffer[index + 2] = pixel.bytes[2];
        }
    }
    return 0;

fail_exit:
    return -1;
}
