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

void func_80052FE8(S_80052FE8 *a0, s16 a1) {
    S_80052FE8_C *a2;
    S_80052FE8_B *b;
    u16 *v0;

    a0->unk10 = func_80052CE0;
    v0 = &a0->unk20;
    v0[0] = 0;
    v0[1] = 0;
    v0[2] = 0;
    v0[6] = 0;
    v0[7] = 0;
    v0[4] = a1;
    a2 = a0->unkC;
    a2->unkC = 0x808080;
    a2->unk1E = 0x1000;
    a2->unk1C = 0x1000;
    a2->unk8 = D_80084478 + a1;
    a2->unk14 |= 0x80;
    func_8004491C(a0, func_80044BB0);
    b = a0->unk8;
    b->unk0 = 0;
    b->unk4 = 0;
    b->unk8 = 0x600000;
}
