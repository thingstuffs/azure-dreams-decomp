#include "common.h"

#define F(e, t, o) (*(t *)((s8 *)(e) + (o)))

extern void func_800AE734(void *);

/* Animate the cursor position, row offsets, and colors during a row transition. */
void func_800AE854(void *state) {
    s32 start_row;
    s32 start_r_duration;
    s32 start_g_duration;
    s32 end_r_duration;
    s32 end_g_duration;
    s32 slide_offset;
    s32 cursor_offset;
    s32 start_b_duration;
    s32 row_delta;
    s32 scaled_progress;
    s32 end_b_duration;
    void *cursor_prim;

    func_800AE734(state);
    start_row = F(state, s32, 0x20);
    row_delta = F(state, s32, 0x1C) - start_row;
    scaled_progress = F(state, s32, 8) * 0x10;
    cursor_offset = row_delta * scaled_progress / F(state, s32, 4) + 0xA;
    cursor_prim = F(F(F(state, void *, 0xD8), void *, 4), void *, 4);
    F(cursor_prim, s16, 0xA) = (s16)(start_row * 0x10 + cursor_offset);
    slide_offset = (F(state, s32, 8) * 8) / F(state, s32, 4);
    F(F(F(F(state, s32, 0x20) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s16, 8) = (s16)(0x28 - slide_offset);
    F(F(F(F(state, s32, 0x1C) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s16, 8) = (s16)(slide_offset + 0x20);
    F(F(F(F(state, s32, 0x20) * 4 + F(state, void *, 0xD8), void *, 0x50), void *, 4), s16, 8) = (s16)(0x97 - slide_offset);
    F(F(F(F(state, s32, 0x1C) * 4 + F(state, void *, 0xD8), void *, 0x50), void *, 4), s16, 8) = (s16)(slide_offset + 0x8F);
    F(F(F(F(state, s32, 0x20) * 4 + F(state, void *, 0xD8), void *, 8), void *, 4), s16, 8) = (s16)(0x11 - slide_offset);
    F(F(F(F(state, s32, 0x1C) * 4 + F(state, void *, 0xD8), void *, 8), void *, 4), s16, 8) = (s16)(slide_offset + 9);
    F(F(F(F(state, s32, 0x20) * 4 + F(state, void *, 0xD8), void *, 0x20), void *, 4), s16, 8) = (s16)(0x41 - slide_offset);
    F(F(F(F(state, s32, 0x1C) * 4 + F(state, void *, 0xD8), void *, 0x20), void *, 4), s16, 8) = (s16)(slide_offset + 0x39);
    start_r_duration = F(state, s32, 4);
    F(F(F(F(state, s32, 0x20) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s8, 0) = (s8)(((start_r_duration - F(state, s32, 8)) * 0x18) / start_r_duration + 0x68);
    start_g_duration = F(state, s32, 4);
    F(F(F(F(state, s32, 0x20) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s8, 1) = (s8)(((start_g_duration - F(state, s32, 8)) * 0x18) / start_g_duration + 0x68);
    start_b_duration = F(state, s32, 4);
    F(F(F(F(state, s32, 0x20) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s8, 2) = (s8)(((start_b_duration - F(state, s32, 8)) << 5) / start_b_duration + 0x60);
    end_r_duration = F(state, s32, 4);
    F(F(F(F(state, s32, 0x1C) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s8, 0) = (s8)(-0x80 - ((end_r_duration - F(state, s32, 8)) * 0x18) / end_r_duration);
    end_g_duration = F(state, s32, 4);
    F(F(F(F(state, s32, 0x1C) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s8, 1) = (s8)(-0x80 - ((end_g_duration - F(state, s32, 8)) * 0x18) / end_g_duration);
    end_b_duration = F(state, s32, 4);
    F(F(F(F(state, s32, 0x1C) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s8, 2) = (s8)(-0x80 - ((end_b_duration - F(state, s32, 8)) << 5) / end_b_duration);
}
