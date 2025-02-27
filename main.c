#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fp_analyzer.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "special") == 0) {
        FP_TYPE special_values[] = {1.0 / 0.0, -1.0 / 0.0, NAN, -NAN};
        for (int i = 0; i < 4; i++) {
            Converter conv;
            conv.f = special_values[i];
            print_components(conv.u, conv.f);
            printf("\n");
        }
        return EXIT_SUCCESS;
    }
    Converter conv;
    printf("Please enter a floating point number or q to quit: \n");
    printf("> ");
    while (scanf("%f", &conv.f) == 1) {
        print_components(conv.u, conv.f);
        print_reconstitution(conv.f);
        printf("> ");
    }
    return EXIT_SUCCESS;
}

