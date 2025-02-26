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
    Components *comp = (Components *)&value;
    
    //need to consider special values?
    
    int true_exponent = (int)comp->exponent - BIAS;
    FP_TYPE mantissa_value = 1 + ((FP_TYPE)comp->mantissa / (1 << MANT_BITS));
    FP_TYPE reconstructed = mantissa_value * power_of_2(true_exponent);
    
    if (comp->sign)
        reconstructed_value = -reconstructed_value;
    
   //print
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

