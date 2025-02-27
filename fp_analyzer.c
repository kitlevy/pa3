#include <math.h>
#include <stdio.h>

#include "fp_analyzer.h"

void print_bits(UNSIGN_TYPE value, int length) {
    for (int i = length - 1; i >= 0; i--) {
        printf("%lu", (long)((value >> i) & 1));
    }
}

void print_components(UNSIGN_TYPE value, FP_TYPE original) {
    if (isnan(original)) {
        if (signbit(original)) {
            printf("-nan\n");
        } else {
            printf("nan\n");
        }
    } else {
        printf("%f\n", original);
    }

    Converter conv;
    conv.u = value; 

    printf("Bits: ");
    print_bits(conv.c.sign, 1);
    printf("|");
    print_bits(conv.c.exponent, EXP_BITS);
    printf("|");
    print_bits(conv.c.mantissa, MANT_BITS);
    printf("\n");    
}

void print_normalized(UNSIGN_TYPE value) {
    Converter conv;
    conv.u = value;
    int og_exponent = conv.c.exponent;
    FP_TYPE og_mantissa = (FP_TYPE)conv.c.mantissa / (1ULL << MANT_BITS);
    int sign;
    if (conv.c.sign) {
        sign = -1;
    } else {
        sign = 1;
    }   
    int true_exponent = og_exponent - BIAS;
    FP_TYPE mantissa_value = 1 + og_mantissa;
    FP_TYPE reconstructed = sign * mantissa_value * power_of_2(true_exponent);
        
    printf("Original value:\n");
    printf("(-1)^{%d} x (1 + %g) x 2^{%d - %d}\n", conv.c.sign, og_mantissa, og_exponent, BIAS);
    printf(" = {%d} x %g x 2^{%d}\n", sign, mantissa_value, true_exponent);
    printf(" = %g x %g\n", sign * mantissa_value, power_of_2(true_exponent));
    printf(" = %g\n", reconstructed);

}

void print_denormalized(UNSIGN_TYPE value) {
    Converter conv;
    conv.u = value;
    int og_exponent = conv.c.exponent;
    FP_TYPE og_mantissa = (FP_TYPE)conv.c.mantissa / (1ULL << MANT_BITS);
    int sign;
    if (conv.c.sign) {
        sign = -1;
    } else {
        sign = 1;
    }
    int true_exponent = og_exponent - BIAS;
    FP_TYPE mantissa_value = og_mantissa;
    FP_TYPE reconstructed = sign * mantissa_value * power_of_2(true_exponent);
    
    printf("Original value:\n");
    printf("(-1)^{%d} x (1 + %g) x 2^{%d - %d}\n", conv.c.sign, og_mantissa, og_exponent, BIAS);
    printf(" = {%d} x %g x 2^{%d}\n", sign, mantissa_value, true_exponent);
    printf(" = %g x %g\n", sign * mantissa_value, power_of_2(true_exponent));
    printf(" = %g\n", reconstructed);
}

void print_reconstitution(UNSIGN_TYPE value) {
    Converter conv;
    conv.u = value;
    if (conv.c.exponent == 0) {
        print_denormalized(value);
    } else {
        print_normalized(value);
    }
}

FP_TYPE power_of_2(int exponent) {
    FP_TYPE result = 1.0;
    if (exponent >= 0) {
        for (int i = 0; i < exponent; ++i) {
            result *= 2.0;
        }
    } else {
        for (int i = exponent; i < 0; ++i) {
            result /= 2.0;
        }
    }
    return result;
}

