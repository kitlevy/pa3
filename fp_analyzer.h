#define FLOAT_BITS 32
#define EXP_BITS 8
#define MANT_BITS 23
#ifdef DOUBLE
#define FP_TYPE double
#else
#define FP_TYPE float
#endif
#define UNSIGN_TYPE unsigned FP_TYPE

typedef union {
    float f;
    unsigned int u;
} Converter;

typedef struct {
    unsigned int mantissa : MANT_BITS;
    unsigned int exponent : EXP_BITS;
    unsigned int sign : 1;
} Components;

void print_bits(UNSIGN_TYPE value, int length);
void print_components(UNSIGN_TYPE value, FP_TYPE original);
void print_normalized(UNSIGN_TYPE value);

