#include "common.h"

extern void func_800A9A0C(void *);
extern void func_800AA258(void);
extern void func_800AA6B4(s32, s32, s32, s32);
extern void func_800AAA54(s32, s32, s32, s32);
extern u16 D_80083462;
extern void *D_80083470;

/* Updates the actor state, consumes completed counts, and dispatches its action. */
void func_800D4494(s32 actor, s32 action_arg, s32 action_data, u8 *state) {
    void *update_state;
    s8 old_count;
    s32 count_bits;
    s32 scaled_count;

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
        update_state = state;
        ASM_KEEP(update_state);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        old_count = *(volatile s8 *)(state + 0x6D);
        *(s32 *)(state + 0x60) = 0;
        count_bits = (u8)old_count << 0x18;
        ASM_KEEP(count_bits);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800A9A0C(update_state);
        scaled_count = ((s32)count_bits >> 0x18) << 0x10;
        if ((scaled_count != 0) && (*(s8 *)(state + 0x6D) == 0)) {
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
