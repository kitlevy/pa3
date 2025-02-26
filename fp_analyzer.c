#include <stdio.h>

#include "fp_analyzer.h"

void print_bits(UNSIGN_TYPE value, int length) {
    for (int i = length - 1; i >= 0; i--) {
        printf("%d", ((value >> i) & 1));
    }
    printf("\n");
}

void print_components(UNSIGN_TYPE value, FP_TYPE original) {
    Components * comp = (Components *)&value;
    printf("Original Value: %g\n", original);
    print_bits(comp->sign, 1);
    printf("|");
    print_bits(comp->exponent, EXP_BITS);
    printf("|");
    print_bits(comp->mantissa, MANT_BITS);
    printf("\n");    
}

void print_normalized(UNSIGN_TYPE value) {
    Components * comp = (Components *)&value;
    int og_exponent = (int)comp->exponent
    int og_mantissa = ((FP_TYPE)comp->mantissa / (1 << MANT_BITS))
    int sign = 0;
    if (comp->sign) {
        sign = -1;
    } else {
        sign = 1;
    }
    
    //need to consider special values?
    
    int true_exponent = og_exponent - BIAS;
    FP_TYPE mantissa_value = 1 + og_mantissa;
    FP_TYPE reconstructed = sign * mantissa_value * power_of_2(true_exponent);
        
    printf("Original value:\n");

    printf("(-1)^{%d} x (1 + %f) x 2^{%d - %d}\n", (int)comp->sign, og_mantissa, og_exponent, BIAS);
    printf(" = {%d} x %f x 2^{%d}\n", sign, mantissa_value, true_exponent);
    printf(" = %f x %d\n", sign * mantissa_value, power_of_2(true_exponent));
    printf(" = %f", reconstructed);

}

void print_denormalized(UNSIGN_TYPE value) {
    Components * comp = (Components *)&value;
    FP_TYPE og_mantissa = ((FP_TYPE)comp->mantissa / (1 << MANT_BITS))
    int sign = 0;
    if (comp->sign) {
        sign = -1;
    } else {
        sign = 1;
    }
    
    //need to consider special values?
    
    FP_TYPE mantissa_value = 1 + og_mantissa;
    FP_TYPE reconstructed = sign * mantissa_value * power_of_2(1 - BIAS);
        
    printf("Original value:\n");
    printf("(-1)^{%d} x (1 + %.45f) x 2^{%d - %d}\n", (int)comp->sign, og_mantissa, og_exponent, BIAS);
    printf(" = {%d} x %.45f x 2^{%d}\n", sign, mantissa_value, true_exponent);
    printf(" = %.45f x %d\n", sign * mantissa_value, power_of_2(true_exponent));
    printf(" = %.45f", reconstructed);

}

void print_reconstitution(UNSIGN_TYPE value) {
    Components * comp = (Components *)&value;
    if (comp->exponent == 0) {
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

