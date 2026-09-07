#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 *D_80175D50[3];
extern u8 D_80083780[12];

s32 func_80170408(void) {
    s16 *node = *(s16 **)(D_80175D50[0] + 8);
    s16 *base = (s16 *)D_80083780;
    s16 base2 = base[1];
    s16 node2 = node[1];

    if (base2 < node2) {
        s16 base6 = base[3];
        s16 node6 = node[3];
        if (base6 < node6)
            return 1;
        if (node6 < base6)
            return 7;
        return 0;
    } else if (node2 < base2) {
        s16 base6 = base[3];
        s16 node6 = node[3];
        if (base6 < node6)
            return 3;
        if (node6 < base6)
            return 5;
        return 4;
    } else {
        s16 base6 = base[3];
        s16 node6 = node[3];
        s32 result = 6;
        if (base6 < node6)
            return 2;
        if (node6 < base6)
            return result;
        return 0;
    }
}
