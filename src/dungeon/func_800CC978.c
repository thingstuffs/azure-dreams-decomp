#include "common.h"

extern void func_800A9A0C(void *);
extern void func_800AAA54(s32, s32, s32, s32);
extern void func_800AA6B4(s32, s32, s32, s32);
extern void *D_80083470;

/* Processes active status, counts completed transitions, and dispatches follow-up work. */
void func_800D20D8(s32 dispatch_arg0, s32 dispatch_arg1, s32 dispatch_arg2, u8 *state) {
    void *update_state;
    s8 previous_status;
    s32 status_high;
    s32 status_scaled;

    if (*(s8 *)(state + 0x6D) > 0) {
        previous_status = *(volatile s8 *)(state + 0x6D);
        update_state = state;
        *(s32 *)(state + 0x60) = 0;
        ASM_KEEP(update_state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        status_high = (u8)previous_status << 0x18;
        ASM_KEEP(status_high);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800A9A0C(update_state);
        status_scaled = ((s32)status_high >> 0x18) << 0x10;
        if ((status_scaled != 0) && (*(s8 *)(state + 0x6D) == 0)) {
            *(u8 *)(state + 0x28) -= 1;
        }
        if (*(u8 *)(state + 0x28) == 0) {
            D_80083470 = state - 0x20;
            func_800AAA54(dispatch_arg0, dispatch_arg1, dispatch_arg2, 0);
            return;
        }
    }
    if (*(s16 *)(state + 0x64) != 0) {
        func_800AA6B4(dispatch_arg0, dispatch_arg1, dispatch_arg2, 0);
    }
}
