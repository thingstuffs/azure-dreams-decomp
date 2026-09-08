#include "common.h"

/* D_80083160: shared state table (own view here); this function only touches
 * a u32 field at offset 8 and a s16 field at offset 0xC8 (declared >8 bytes
 * to force %hi/%lo addressing). */
struct S_800978DC_D80083160 {
    char pad0[8];
    s32 field_8;
    char pad_C[0xC8 - 0xC];
    s16 field_C8;
};

extern struct S_800978DC_D80083160 D_80083160;

extern s32 func_80094BC8(s32 arg0, s16 arg1);
extern void func_80094F58(s16 arg0, s32 arg1, s32 arg2);

/* Passes the valid shared angle, fixed value 0x120000, and context to func_80094F58. */
void func_8009503C(s32 context)
{
    s16 angle = func_80094BC8(D_80083160.field_8, D_80083160.field_C8);

    if (angle != -1) {
        func_80094F58(angle, 0x120000, context);
    }
}
