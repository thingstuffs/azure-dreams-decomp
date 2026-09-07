#include "common.h"

typedef struct Entry {
    s32 a;
    s32 b;
} Entry;

extern Entry D_800CF720[];

s32 func_8008ACE8(s32 arg0) {
    s32 sum;
    s32 i;

    sum = 0;
    for (i = 0; i < arg0; i++) {
        sum += D_800CF720[i].b;
    }
    return sum;
}
