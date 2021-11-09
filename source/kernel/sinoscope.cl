#include "helpers.cl"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338328
#endif
/*
 * TODO
 *
 * Déclarez les structures partagées avec l'autre code si nécessaire selon votre énoncé.
 * Utilisez l'attribut `__attribute__((packed))` à vos déclarations.
 */

/*
 * TODO
 *
 * Modifiez les paramètres du noyau avec ceux demandés par votre énoncé.
 */

__kernel void sinoscope_kernel(__global unsigned char* buffer,  const int width, const int height, const int taylor, const int interval, const float interval_inverse, const float time, const float max, const float phase0, const float phase1, const float dx, const float dy) {
    /*
     * TODO
     *
     * En vous basant sur l'implémentation dans `sinoscope-serial.c`, effectuez le même calcul. Ce
     * noyau est appelé pour chaque coordonnée, alors vous ne devez pas spécifiez les boucles
     * extérieures.
     */

    int i = get_global_id(0);
	// int j = get_global_id(1);
    for (int j = 0; j < height; j++) {

        float px = dx * j - 2 * M_PI;
        float py = dy * i - 2 * M_PI;
        float value = 0;

        for (int k = 1; k <= taylor; k += 2) {
            value += sin(px * k * phase1 + time) / k;
            value += cos(py * k * phase0) / k;
        }

            value = (atan(value) - atan(-value)) / M_PI;
            value = (value + 1) * 100;

            pixel_t pixel;
            color_value(&pixel, value, interval, interval_inverse);

            int index = (i * 3) + (j * 3) * width;

            buffer[index + 0] = pixel.bytes[0];
            buffer[index + 1] = pixel.bytes[1];
            buffer[index + 2] = pixel.bytes[2];
    }
	
}
