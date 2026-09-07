#include "common.h"

/* If a1 is non-null: a0->f8 += a1->f0; a0->f9 += a1->f1; a0->fA = a1->f2; a0->fB = a1->f3; (bytes at a0 offsets 8..0xB) */
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

void func_8004DA24(S_8004DA24_dst *a0, S_8004DA24_src *a1) {
    if (a1 != 0) {
        a0->f8 += a1->f0;
        a0->f9 += a1->f1;
        a0->fA = a1->f2;
        a0->fB = a1->f3;
    }
}
