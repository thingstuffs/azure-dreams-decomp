#include "common.h"

extern s32 func_800C30E0(void *arg0, void *arg1, s32 arg2);
extern s32 func_800644B8(s32 angle);
extern s32 func_80064584(s32 angle);
extern s32 *func_8008FAC0(void *arg0, void *arg1);
extern void func_800CDD98(void *arg0, void *arg1, s32 arg2);

extern u8 D_800CFCB4[];

#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define S32_AT(p, off) (*(s32 *)((u8 *)(p) + (off)))

/* Updates turning motion, applies a position adjustment, and checks the timer. */
void func_800CD87C(void *actor, void *position, s32 update_param) {
    s32 *adjustment;
    s32 axis;
    u16 angle;
    u16 timer;

    if (func_800C30E0(actor, position, update_param) != 0) {
        return;
    }

    angle = U16_AT(actor, 0x86);
    U16_AT(actor, 0x86) = angle - 0x40;
    S16_AT(actor, 0x72) = angle - 0x440;

    U16_AT(position, 2) = U16_AT(actor, 0x84) +
        func_800644B8(S16_AT(actor, 0x86)) / (0x1000 / S16_AT(actor, 0x84));
    U16_AT(position, 6) = U16_AT(actor, 0x86) +
        func_80064584(S16_AT(actor, 0x86)) / (0x1000 / S16_AT(actor, 0x84)) -
        U16_AT(actor, 0x84);

    adjustment = func_8008FAC0(actor, D_800CFCB4);
    if (adjustment != 0) {
        axis = adjustment[0];
        if (axis != 2) {
            if (axis == 0) {
                S32_AT(position, 0) -= adjustment[1];
            } else if (axis == 1) {
                S32_AT(position, 4) -= adjustment[1];
            }
            func_800CDD98(actor, position, update_param);
            return;
        }
    }

    timer = U16_AT(actor, 0x6C) - 1;
    U16_AT(actor, 0x6C) = timer;
    if ((s32)(timer << 16) <= 0) {
        func_800CDD98(actor, position, update_param);
    }
}
