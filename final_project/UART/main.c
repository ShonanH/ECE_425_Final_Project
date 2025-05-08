#include <stdint.h>
#include "UART0.h"
#include "frame.h"

#define IMG_SIZE 64

uint8_t image[IMG_SIZE][IMG_SIZE];
uint8_t edge[IMG_SIZE][IMG_SIZE];

int main(void) {
    UART0_Init();

    receive_image(image);
    sobel(image, edge);
    send_image(edge);

    while (1); // Halt
}


//int main(void) {
//    UART0_Init();

//    for (int i = 0; i < 4096; i++) {
//        UART0_OutChar(i % 256);  // Send test pattern
//    }

//    while (1);
//}