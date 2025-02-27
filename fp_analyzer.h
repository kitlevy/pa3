#ifdef DOUBLE
#define FP_TYPE double
#define UNSIGN_TYPE unsigned long
#define TYPE_BITS 64
#define EXP_BITS 11
#define MANT_BITS 52
#define BIAS 1023
#else
#define FP_TYPE float
#define UNSIGN_TYPE unsigned int
#define TYPE_BITS 32
#define EXP_BITS 8
#define MANT_BITS 23
#define BIAS 127
#endif

typedef struct {
    UNSIGN_TYPE mantissa : MANT_BITS;
    unsigned int exponent : EXP_BITS;
    unsigned int sign : 1;
} Components;

typedef union {
    float f;
    unsigned int u;
    Components c;
} Converter;

void print_bits(UNSIGN_TYPE value, int length);
void print_components(UNSIGN_TYPE value, FP_TYPE original);
void print_normalized(UNSIGN_TYPE value);
void print_denormalized(UNSIGN_TYPE value);
void print_reconstitution(UNSIGN_TYPE value);
FP_TYPE power_of_2(int exponent);
