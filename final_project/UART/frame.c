#include <stdint.h>
#include "frame.h"
#include "UART0.h"

#define IMG_SIZE 64

static const int8_t Gx[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};
static const int8_t Gy[3][3] = {
    {-1, -2, -1},
    { 0,  0,  0},
    { 1,  2,  1}
};

void sobel(uint8_t input[IMG_SIZE][IMG_SIZE], uint8_t output[IMG_SIZE][IMG_SIZE]) {
    for (int y = 1; y < IMG_SIZE - 1; y++) {
        for (int x = 1; x < IMG_SIZE - 1; x++) {
            int gx = 0, gy = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    gx += Gx[i+1][j+1] * input[y+i][x+j];
                    gy += Gy[i+1][j+1] * input[y+i][x+j];
                }
            }
            int mag = (gx > 0 ? gx : -gx) + (gy > 0 ? gy : -gy); // approx sqrt
            output[y][x] = (mag > 255) ? 255 : mag;
        }
    }
}

void receive_image(uint8_t image[IMG_SIZE][IMG_SIZE]) {
    for (int y = 0; y < IMG_SIZE; y++) {
        for (int x = 0; x < IMG_SIZE; x++) {
            image[y][x] = UART0_InChar();
        }
    }
}

void send_image(uint8_t image[IMG_SIZE][IMG_SIZE]) {
    for (int y = 0; y < IMG_SIZE; y++) {
        for (int x = 0; x < IMG_SIZE; x++) {
            UART0_OutChar(image[y][x]);
        }
    }
}