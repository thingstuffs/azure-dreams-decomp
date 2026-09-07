#include "common.h"

/* Chains structs referenced by a byte-index array (a0[idx]) through their unkC field
 * until an index >= a2 (the terminator) is reached; returns the last-linked struct. */
typedef struct S_800491F4 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    struct S_800491F4 *unkC;
} S_800491F4;

S_800491F4 *func_800491F4(S_800491F4 **a0, volatile u8 *a1, s32 a2) {
    S_800491F4 *v1 = 0;

    while (*a1 < a2) {
        a0[*a1]->unkC = v1;
        v1 = a0[*a1];
        a1++;
    }

    return v1;
}
