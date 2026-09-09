#include "common.h"

#include "common.h"

#define FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))

typedef struct S_func_8003666C_0 {
    u8 pad_00[0x4D];
    u8 unk_4D;
    u8 pad_4E[0x1A];
    void (*unk_68)(void);
    u8 pad_6C[0x8];
    void *unk_74;
} S_func_8003666C_0;

typedef struct S_func_8003666C_1 {
    u8 pad_00[0x22];
    s16 unk_22;
    u8 pad_24[0x2];
    u8 unk_26;
    u8 unk_27;
    u8 pad_28[0x58];
    s32 unk_80;
} S_func_8003666C_1;

extern u8 D_80082040[0x10];
extern u8 D_80082538[0x10];

extern void func_800366F4(void);
extern void func_8003719C(s32, void *, s32 *, s16, s32, s32);

/* Copies the marker, applies the position offset, and installs the next callback. */
void func_8003666C(S_func_8003666C_0 *state) {
    S_func_8003666C_1 *layout;
    s32 center_offset;
    u8 marker;
    s32 position;
    s16 doubled_position;

    layout = (S_func_8003666C_1 *) state->unk_74;
    marker = layout->unk_27;
    position = layout->unk_22;
    center_offset = layout->unk_26;
    center_offset = ((center_offset + 1) >> 1) - 1;
    position -= center_offset;
    doubled_position = (s16) (position * 2);
    state->unk_4D = marker;
    func_8003719C(
        (s32) D_80082538,
        D_80082040,
        (s32 *) state,
        1,
        doubled_position,
        ((S_func_8003666C_1 *) state->unk_74)->unk_80);
    state->unk_68 = func_800366F4;
}
