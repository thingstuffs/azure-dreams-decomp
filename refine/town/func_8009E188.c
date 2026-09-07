#include "common.h"

extern s32 D_80083780[];

extern void func_8009539C(void *arg0);
extern void func_8008F294(void *arg0, void *arg1);
extern void func_8008F664(void *arg0, void *arg1);
extern void func_8009C1B4(void *arg0, s32 arg1, void *arg2, s32 arg3);

/* Update target-relative motion and advance when the countdown expires. */
void func_8009B8E8(void *state, s32 context, void *motion, s32 next_arg) {
    u16 ticks_left;

    *(s32 *)((u8 *)motion + 0xC) = (D_80083780[0] - *(s32 *)motion) / 2;
    *(s32 *)((u8 *)motion + 0x10) = (D_80083780[1] - *(s32 *)((u8 *)motion + 4)) / 2;
    func_8009539C(motion);
    func_8008F294(context, motion);
    func_8008F664(context, motion);
    ticks_left = *(u16 *)((u8 *)state + 0x6C) - 1;
    *(u16 *)((u8 *)state + 0x6C) = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        func_8009C1B4(state, context, motion, next_arg);
    }
}
