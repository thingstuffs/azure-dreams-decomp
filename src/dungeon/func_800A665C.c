#include "common.h"

typedef struct {
    u8 pad0[0x92];
    s16 field92;
    u8 pad94[2];
    s16 field96;
    u8 pad98[3];
    u8 field9B;
} State;

typedef struct {
    u8 pad0[2];
    s16 field2;
    u8 pad4[2];
    s16 field6;
    u8 pad8[4];
    s32 fieldC;
    s32 field10;
    s32 field14;
} Motion;

typedef struct {
    u8 pad0[0x1C];
    u16 field1C;
    u16 field1E;
    u8 pad20[4];
    u8 field24;
    u8 field25;
} Params;

typedef struct {
    u8 pad0[0x1C];
    s32 field1C;
    u8 pad20[0x6A];
    u16 field8A;
} Extra;

extern volatile s16 D_80013714[8];
extern void func_800A2B04(Motion *, u8, u8);
extern s32 func_800644B8(s32);

/* Advance movement to the target tile, updating height and scale until complete. */
s32 func_800ABDBC(State *state, Motion *motion, Params *params, Extra *extra) {
    s32 phase;
    s32 current_y;
    s32 height_offset;
    s32 current_x;
    s32 move_frames;
    u16 scale;
    s16 frames_left;

    phase = state->field9B;
    switch (phase) {
    case 0:
        state->field96 = 0x10;
        extra->field1C &= 0xFFFBFFFF;
        if ((*D_80013714 & 2) != 0) {
            func_800A2B04(motion, params->field24, params->field25);
            params->field1C = 0x1000;
            params->field1E = 0x1000;
            state->field9B = 2;
        } else {
            state->field9B = (u8) (state->field9B + 1);
            extra->field8A = 0x800 / state->field96;
        }
        return 0;

    case 1:
        if ((state->field96 + 2) >= 0x10) {
            motion->field10 = 0;
            motion->fieldC = 0;
        } else {
            move_frames = state->field96 - 2;
            if (move_frames > 0) {
                current_y = motion->field6;
                current_y -= 0x20;
                motion->fieldC = (((params->field24 << 6) - (current_x = motion->field2 - 0x20)) << 16) / move_frames;
                motion->field10 = (((params->field25 << 6) - current_y) << 16) / (state->field96 - 2);
            } else {
                motion->field10 = 0;
                motion->fieldC = 0;
                func_800A2B04(motion, params->field24, params->field25);
            }
        }
        if (state->field96 != 0) {
            motion->field14 = ((-(func_800644B8(state->field96 << 6) >> 4) - (height_offset = state->field92 + 0x20)) << 16) / state->field96;
        }
        scale = params->field1C + extra->field8A;
        params->field1C = scale;
        params->field1E = scale;
        frames_left = (u16) state->field96 - 1;
        state->field96 = frames_left;
        if ((s16) frames_left < 0) {
            motion->field14 = 0;
            motion->field10 = 0;
            motion->fieldC = 0;
            func_800A2B04(motion, params->field24, params->field25);
            state->field92 = -0x20;
            state->field9B = (u8) (state->field9B + 1);
        }
        return 0;

    case 2:
        return 1;

    default:
        return 0;
    }
}
