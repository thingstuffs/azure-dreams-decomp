#include "common.h"

#include "common.h"

#define FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))

extern u8 D_80082040[0x10];
extern u8 D_80082538[0x10];

extern void func_800366F4(void);
extern void func_8003719C(s32, void *, s32 *, s16, s32, s32);

/* Copies the marker, applies the position offset, and installs the next callback. */
void func_8003666C(s32 *state) {
    s32 layout;
    s32 center_offset;
    u8 marker;
    s32 position;
    s16 doubled_position;

    layout = (s32) FIELD(state, void **, 0x74);
    marker = FIELD((void *) layout, u8 *, 0x27);
    position = FIELD((void *) layout, s16 *, 0x22);
    center_offset = FIELD((void *) layout, u8 *, 0x26);
    center_offset = ((center_offset + 1) >> 1) - 1;
    position -= center_offset;
    doubled_position = (s16) (position * 2);
    FIELD(state, u8 *, 0x4D) = marker;
    func_8003719C(
        (s32) D_80082538,
        D_80082040,
        state,
        1,
        doubled_position,
        FIELD(FIELD(state, void **, 0x74), s32 *, 0x80));
    FIELD(state, void (**)(void), 0x68) = func_800366F4;
}
