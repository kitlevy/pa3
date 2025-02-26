#include <stdio.h>

#define FLOAT_BITS 32
#define EXP_BITS 8
#define MANT_BITS 23

typedef union {
    float f;
    unsigned int u;
} Converter;

typedef struct {
    unsigned int mantissa : MANT_BITS;
    unsigned int exponent : EXP_BITS;
    unsigned int sign : 1;
} Components;

void print_bits(unsigned int value, int length) {
    for (int i = length - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

void print_components(unsigned int value) {
    Components *comp = (Components *)&value;
    printf("Sign: "); print_bits(comp->sign, 1);
    printf("Exponent: "); print_bits(comp->exponent, EXP_BITS);
    printf("Mantissa: "); print_bits(comp->mantissa, MANT_BITS);
}

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

