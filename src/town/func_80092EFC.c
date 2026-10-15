#include "modules/town_player_init.h"

void func_8009065C(void *context, void *input, void *record) {
    GameWork *work = &gameWork;
    void *callback;
    s32 initial_flags;
    s32 flags;
    s32 movement;
    s32 index;

    func_80095544(input);

    if (D_80100DB0[0] == 0) {
        if (((u16)work->view.viewAngle) >= 0x800) {
            work->view.viewAngle |= 0xF000;
        }

        callback = *(void **)context;
                /* garbage-passthru: a1/a2/a3 are caller-saved residue after func_80095544. */
        if (callback == (void *)D_80097D2C || callback == (void *)&func_80090A64 ||
            func_800352FC() != 0) {
            if (D_8006ADD4[0] == 12) {
                func_800909A0();
            } else if (*(s16 *)((u8 *)input + 6) < 0x400) {
                func_80090A04(input);
            }
        } else if (D_8006ADD4[0] == 12) {
            initial_flags = work->buttons;
            if (initial_flags & 8) {
                work->view.viewAngle -= 0x20;
                if (work->view.viewAngle < -0x1E0) {
                    work->view.viewAngle = -0x1E0;
                }
            } else if (initial_flags & 4) {
                work->view.viewAngle += 0x20;
                if (work->view.viewAngle > 0x1E0) {
                    work->view.viewAngle = 0x1E0;
                }
            } else {
                func_800909A0();
            }
        } else if (*(s16 *)((u8 *)input + 6) < 0x400) {
            func_80090A04(input);
        } else {
            movement = func_8003BD84(*(s32 *)((u8 *)input + 0xC),
                                     *(s32 *)((u8 *)input + 0x10));
            if (movement == 0) {
                work->view.viewAngle =
                    (((u16)work->view.viewAngle) + 8) & 0xFFF0;
            }
            movement /= 0x10000;
            flags = work->buttons;
            if (flags & 8) {
                work->view.viewAngle -= 0x10 + movement;
            }
            if (flags & 4) {
                work->view.viewAngle += 0x10 + movement;
            }
        }
    }

    callback = *(void **)context;
    if ((callback == (void *)&D_80091260) ||
        (callback == (void *)&D_80091528)) {
        *(s16 *)((u8 *)context + 0x18) =
            func_80094AA0(*(s16 *)((u8 *)context + 0x18),
                          *(s16 *)((u8 *)context + 0x10), 0x200);
    } else {
        *(s16 *)((u8 *)context + 0x18) = *(u16 *)((u8 *)context + 0x10);
    }
    index = func_80095360(*(s16 *)((u8 *)context + 0x18));
    if (*(s16 *)((u8 *)context + 0x12) != index) {
        func_800489F4(record,
                      *(u8 *)(*(u8 **)((u8 *)context + 0x1C) + index),
                      *(s8 *)((u8 *)record + 4), 0);
        *(s16 *)((u8 *)context + 0x12) = index;
    }

    {

        if (D_800D01F8[index] != 0) {
            *(u16 *)((u8 *)record + 0x14) |= 1;
        } else {
            *(u16 *)((u8 *)record + 0x14) &= 0xFFFE;
        }
    }
    func_80096868(context, input, record);
    func_80048AC8(record, 0);

    {
        u8 *state = D_80100D98;

        func_800A48B0(state, input);
        if (D_80100E18[0] == 0) {
            *(s32 *)(state + 8) = 0;
            return;
        }
        if (D_80100E18[0] == 2) {
            *(s32 *)(state + 8) /= 2;
        }
    }
}

/* MECHANISM: The three arguments stay in s1/s2/s3 and D_80083160 in s0, yielding the retail 0x28 frame.
   A one-sided schedule barrier preserves both clamp tails; ASM_TAILSLOT_PIN sinks the dead OR into its j slot.
   Memory fences retain the clear/store call sequence and force the post-store signed-halfword reload. */
