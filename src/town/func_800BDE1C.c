#include "common.h"

typedef struct {
    s32 unk0;
    s8 unk4;
    s8 unk5;
    u8 pad6[6];
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

extern void func_8004491C(s32, void *);
extern void func_8008F104(s32, void *, void *);
extern u8 D_80046398[];
extern u8 D_80083160[];
extern u8 D_800D1BDC[];

/* Initialize object state, scale, and color, then offset and configure the object. */
void func_800BB57C(s32 object_id, void *object, FuncData *state) {
    func_8004491C(object_id - 0x20, D_80046398);

    state->unk12 = 0;
    state->unk14 = 0;
    state->unk10 = 0;
    state->unk16 = 0;
    state->unk18 = 0;
    state->unk1A = 0;
    state->unk0 = 0;
    state->unk4 = 0;
    state->unk5 = 0;
    state->unk1C = 0x1000;
    state->unk1E = 0x1000;
    state->unk20 = 0x1000;
    state->unkC = D_80083160[0xA8];
    state->unkD = D_80083160[0xA9];
    state->unkE = D_80083160[0xAA];
    *(s32 *)((u8 *)object + 8) += 0x200000;

    func_8008F104(object_id, object, D_800D1BDC);
}
