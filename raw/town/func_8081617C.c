#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 D_800814A0;

void func_8002017C(void *arg0) {
    s16 temp_v1;
    s32 temp_v0_2;
    u16 temp_v0;
    void *sub;
    u16 state_u;
    s16 v1;
    u16 flags;

    sub = M2C_FIELD(arg0, void **, 4);
    temp_v1 = M2C_FIELD(arg0, s16 *, 0);
    state_u = M2C_FIELD(arg0, volatile u16 *, 0);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = M2C_FIELD(arg0, u16 *, 2) - 1;
        M2C_FIELD(arg0, u16 *, 2) = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            flags = M2C_FIELD(arg0, u16 *, 0x16);
            v1 = M2C_FIELD(arg0, s16 *, 0);
            flags &= 0xFFFD;
            v1 = (s16) (v1 + 1);
            M2C_FIELD(arg0, u16 *, 0x16) = flags;
            M2C_FIELD(arg0, s16 *, 0) = v1;
            return;
        }
        return;
    case 1:
        if (M2C_FIELD(sub, u16 *, 0x2A) & 1) {
            do {
                M2C_FIELD(arg0, s16 *, 0) = (s16) (state_u + 1);
            } while (0);
            return;
        }
        break;
    case 2:
        temp_v0_2 = M2C_FIELD(arg0, s32 *, 8) + 0xFFF7F7F8;
        M2C_FIELD(arg0, s32 *, 8) = temp_v0_2;
        if (temp_v0_2 <= 0x80808) {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            D_800814A0 |= 0x8000;
        }
        break;
    }
}
