#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

extern void *D_80016000;
extern void func_8001ACA0();
extern void func_8001AC6C();

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

void func_80018094(s32 arg0, s32 arg1)
{
    Rect rect0;
    Rect rect1;
    s32 offset;

    func_8001ACA0(&rect0);
    arg0 <<= 6;
    arg1 <<= 6;
    rect0.w = 0;
    offset = FIELD(
        (FIELD(D_80016000, s32, 8) << 5) +
            *FIELD(D_80016000, s32 *, 0x30),
        u16, 0xC) + 0x20;
    arg0 += offset;
    rect1.x = arg0;
    offset = FIELD(
        (FIELD(D_80016000, s32, 8) << 5) +
            *FIELD(D_80016000, s32 *, 0x30),
        u16, 0xE) + 0x20;
    rect1.w = 0;
    arg1 += offset;
    rect1.y = arg1;
    func_8001AC6C(&rect0, &rect1, 0x20);
}

/* MECHANISM: Separate Rect locals produce the retail 0x30 frame and sibling slots.
   Natural arg liveness selects s0/s1; removing the output pin and ASM_USE barriers
   lets 2.7.2-cdk-G0 stage both shifts and the three callee arguments exactly. */
