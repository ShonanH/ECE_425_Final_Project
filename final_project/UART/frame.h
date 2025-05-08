
#include <stdint.h>

void sobel(uint8_t input[64][64], uint8_t output[64][64]);
void receive_image(uint8_t image[64][64]);
void send_image(uint8_t image[64][64]);