#include "common.h"

extern u8 D_800170C8[];
extern u8 D_8001BAB6[];

/* Returns the byte array selected by the variant. */
void *func_800177B0(s32 unused_0, s32 unused_1, s32 variant) {
    if (variant != 1) {
        return D_8001BAB6;
    }
    return D_800170C8;
}
