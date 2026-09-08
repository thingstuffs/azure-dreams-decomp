#include "common.h"

extern u16 D_80083462;

extern void func_80042B68(void *, s32);
extern s32 func_800A2B5C(void *);
extern s32 func_800A48F0(void *, s32, s32);
extern void func_800A4ACC(void *);

/* Reset action state and decrement the actor counter when the checks pass. */
void func_800D6068(void *action_state, void *unused_1, void *unused_2, void *actor) {
    *(u8 *) ((u8 *) actor + 0x71) &= 0x7F;
    if (!(D_80083462 & 0x2000) && (func_800A2B5C(actor) << 0x10) == 0 &&
        (func_800A2B5C(actor) << 0x10) == 0) {
        if ((func_800A48F0(actor, 0x1B, 0) << 0x10) < 0) {
            *(u16 *) ((u8 *) actor + 0x46) &= 0x7FFF;
            return;
        }
        *(s32 *) ((u8 *) action_state + 0x8C) = 0;
        *((u8 *) action_state + 0x9A) = 0x18;
        *((u8 *) action_state + 0x9B) = 0;
        *(s16 *) ((u8 *) action_state + 0x96) = 0;
        *((u8 *) action_state + 0xB3) = 0;
        *((u8 *) action_state + 0xB1) = 0;
        *((u8 *) action_state + 0xB2) = 0;
        *(s32 *) ((u8 *) actor + 0x1C) &= 0xFFFBFFFF;
        *(u16 *) ((u8 *) action_state + 0x98) |= 8;
        func_80042B68(actor, 5);
        func_800A4ACC(actor);
        *((u8 *) actor + 0x6D) -= 1;
    }
}
