#include "common.h"

typedef struct {
    u32 unk0;
    s8 unk4;
    s8 unk5;
    u8 pad6[2];
    s32 unk8;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 padF;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
} FuncData;

extern void func_8004491C(void *, void *);
extern u8 D_80046398[];
extern u8 D_80083160[];
extern u8 D_800B9998[];

/* Initializes object data, transform, color, and rendering defaults. */
void func_800B9B28(u8 *object, u8 *render_data, FuncData *state) {
    u8 *colors;
    u8 blue;

    *(void **)(object - 0x10) = D_800B9998;
    func_8004491C(object - 0x20, D_80046398);

    *(s16 *)(object + 0x66) = 0;
    state->unk1C = 0x1000;
    state->unk1E = 0x1000;
    state->unk20 = 0x1000;
    colors = D_80083160;
    state->unk12 = 0;
    state->unk14 = 0;
    state->unk10 = 0;
    state->unk16 = 0;
    state->unk18 = 0;
    state->unk1A = 0;
    state->unk0 = 0;
    state->unk4 = 0;
    state->unk5 = 0;
    state->unkC = colors[0xA8];
    state->unkD = colors[0xA9];
    blue = colors[0xAA];
    state->unk8 = 0x1F;
    state->unkE = blue;
    *(s32 *)(render_data + 8) = 0xFF600000;
}
