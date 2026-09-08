#include "common.h"

extern s16 D_80081468[3];
extern void func_800DBD5C(s16 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

// Handle changes to D_80081468[2] and update its cached value.
void func_800DBF94(s32 *cachedValue) {
    if (D_80081468[2] != *cachedValue) {
        func_800DBD5C(D_80081468[2], *cachedValue, 2, 0x18C, 0x1B8, 0);
        *cachedValue = D_80081468[2];
    }
}
