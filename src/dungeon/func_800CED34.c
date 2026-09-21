#include "common.h"

extern void func_800A9A0C(void *);
extern void func_800AA258(void);
extern void func_800AA6B4(s32, s32, s32, s32);
extern void func_800AAA54(s32, s32, s32, s32);
extern u16 D_80083462;
extern void *D_80083470;

/* Updates the actor state, consumes completed counts, and dispatches its action. */
void func_800D4494(s32 actor, s32 action_arg, s32 action_data, u8 *state) {
    s16 old_count;

    if (!(D_80083462 & 0x2000)) {
        if (*(s32 *)(state + 0x1C) & 0x100) {
            func_800AA258();
            return;
        }
        if (*(u8 *)(actor + 0x9A) != 0xE) {
            *(u8 *)(actor + 0x9A) = 0xE;
        }
    }
    if (*(s8 *)(state + 0x6D) > 0) {
        old_count = (s8)(state[0x6D] + 0);
        *(s32 *)(state + 0x60) = 0;
        func_800A9A0C(state);
        if ((old_count != 0) && (*(s8 *)(state + 0x6D) == 0)) {
            *(u8 *)(state + 0x28) -= 1;
        }
        if (*(u8 *)(state + 0x28) == 0) {
            D_80083470 = state - 0x20;
            func_800AAA54(actor, action_arg, action_data, 0);
            return;
        }
    }
    if (*(s16 *)(state + 0x64) != 0) {
        func_800AA6B4(actor, action_arg, action_data, 0);
    }
}
