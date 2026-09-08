#include "common.h"

typedef struct S_8004DA24_dst {
    u8 pad[8];
    u8 f8;
    u8 f9;
    u8 fA;
    u8 fB;
} S_8004DA24_dst;

typedef struct S_8004DA24_src {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
} S_8004DA24_src;

/* Adds the first two source bytes and copies the next two into the destination when the source exists. */
void func_8004DA24(S_8004DA24_dst *destination, S_8004DA24_src *source) {
    if (source != 0) {
        destination->f8 += source->f0;
        destination->f9 += source->f1;
        destination->fA = source->f2;
        destination->fB = source->f3;
    }
}
