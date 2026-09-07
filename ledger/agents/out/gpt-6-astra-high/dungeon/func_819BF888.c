#include "common.h"

extern void func_800478B8(void *arg0);
extern s16 D_8002992E[5];
extern s32 D_800814A0[3];

/* Updates motion and rotation and marks the object finished when flagged or expired. */
void func_80025088(void *state, void *position, void *render_state) {
    s32 x_step;
    s32 y_step;
    s32 z_step;
    u16 end_flag;
    u16 ticks_left;
    u16 frame_count;

    frame_count = *(u16 *)((u8 *)state + 0x2A);
    D_8002992E[0] = 1;
    frame_count = frame_count + 1;
    *(u16 *)((u8 *)state + 0x2A) = frame_count;
    if (!(frame_count & 1)) {
        func_800478B8(render_state);
    }
    if (*(s16 *)((u8 *)state + 0x2C) == 0) {
        *(u16 *)((u8 *)render_state + 0x16) = *(u16 *)((u8 *)render_state + 0x16) + 0x190;
    }
    if (*(s16 *)((u8 *)state + 0x2C) == 1) {
        *(u16 *)((u8 *)render_state + 0x1A) = *(u16 *)((u8 *)render_state + 0x1A) + 0x190;
    }
    x_step = *(s32 *)((u8 *)state + 0x7C);
    *(s32 *)((u8 *)state + 0x84) += *(s32 *)((u8 *)state + 0x90);
    if (x_step < 0) {
        x_step += 0xFFFF;
    }
    *(u16 *)((u8 *)position + 2) += x_step >> 16;
    y_step = *(s32 *)((u8 *)state + 0x80);
    if (y_step < 0) {
        y_step += 0xFFFF;
    }
    *(u16 *)((u8 *)position + 6) += y_step >> 16;
    z_step = *(s32 *)((u8 *)state + 0x84);
    if (z_step < 0) {
        z_step += 0xFFFF;
    }
    *(u16 *)((u8 *)position + 0xA) += z_step >> 16;
    end_flag = *(u16 *)((u8 *)render_state + 0x14) & 0x8000;
    *(u16 *)((u8 *)render_state + 0x14) = end_flag;
    if ((end_flag != 0) || (ticks_left = *(u16 *)((u8 *)state + 0x28) - 1,
                            *(u16 *)((u8 *)state + 0x28) = ticks_left,
                            ((ticks_left << 16) <= 0))) {
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
