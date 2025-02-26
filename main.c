#include <stdio.h>

#include "fp_analyzer.h"


int main() {
    Converter conv;
    printf("Enter a floating-point number: \n");
    while (scanf("%f", &conv.f) == 1) {
        printf("Bit representation: ");
        print_bits(conv.u, FLOAT_BITS);
        print_components(conv.u);
        printf("\nEnter another number (or non-number to exit): \n");
    }
    return 0;
}

