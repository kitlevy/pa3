#ifdef DOUBLE
#define FP_TYPE double
#define UNSIGN_TYPE unsigned long
#define TYPE_BITS 64
#define EXP_BITS 11
#define MANT_BITS 52
#else
#define FP_TYPE float
#define UNSIGN_TYPE unsigned int
#define TYPE_BITS 32
#define EXP_BITS 8
#define MANT_BITS 23
#endif

typedef struct {
    unsigned int mantissa : MANT_BITS;
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
FP_TYPE power_of_2(int exponent);
