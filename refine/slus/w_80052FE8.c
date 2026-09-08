#include "common.h"

typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
    u16 f4;
    u16 f6;
    u8 f8;
    u8 f9;
    u8 f10;
    u8 f11;
} S_80084478;

extern S_80084478 D_80084478[16];
extern void func_80052CE0(void);
extern void func_80044BB0(void);
extern void func_8004491C(void *a0, void *a1);

typedef struct {
    u8 pad0[8];
    S_80084478 *unk8;
    u32 unkC;
    u8 pad10[4];
    u16 unk14;
    u8 pad16[6];
    u16 unk1C;
    u16 unk1E;
} S_80052FE8_C;

typedef struct {
    u32 unk0;
    u32 unk4;
    u32 unk8;
} S_80052FE8_B;

typedef struct {
    u8 pad0[8];
    S_80052FE8_B *unk8;
    S_80052FE8_C *unkC;
    void (*unk10)(void);
    u8 pad14[0xC];
    u16 unk20;
    u16 unk22;
    u16 unk24;
    u8 pad26[2];
    s16 unk28;
    u8 pad2A[2];
    u16 unk2C;
    u16 unk2E;
} S_80052FE8;

/* Initialize the object callbacks, display entry, rendering defaults, and position. */
void func_80052FE8(S_80052FE8 *object, s16 entry_index) {
    S_80052FE8_C *render_state;
    S_80052FE8_B *position;
    u16 *state_fields;

    object->unk10 = func_80052CE0;
    state_fields = &object->unk20;
    state_fields[0] = 0;
    state_fields[1] = 0;
    state_fields[2] = 0;
    state_fields[6] = 0;
    state_fields[7] = 0;
    state_fields[4] = entry_index;
    render_state = object->unkC;
    render_state->unkC = 0x808080;
    render_state->unk1E = 0x1000;
    render_state->unk1C = 0x1000;
    render_state->unk8 = D_80084478 + entry_index;
    render_state->unk14 |= 0x80;
    func_8004491C(object, func_80044BB0);
    position = object->unk8;
    position->unk0 = 0;
    position->unk4 = 0;
    position->unk8 = 0x600000;
}
