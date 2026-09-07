#include "common.h"

typedef struct SlotB {
    u8 pad[8];
    s16 unk08;
} SlotB;

typedef struct SlotA {
    void *unk00;
    SlotB *unk04;
} SlotA;

typedef struct Obj {
    u8 pad[0xA8];
    SlotA **unk0xA8;
} Obj;

extern u8 D_80078CDC[];

extern void func_800B3558(void *arg0);
extern void func_800B2E3C(void *arg0);
extern void func_800B2F88(void *arg0);
extern void func_800B3108(void *arg0);
extern void func_800B331C(void *arg0);
extern void func_800B2DCC(void *arg0);
extern void func_800B2F38(void *arg0);
extern void func_800B3440(void *arg0);

void func_800B3734(Obj *arg0) {
    register Obj *this ASM_REG("$17") = arg0;
    register void *sp28 ASM_REG("$16");
    s32 i;

    for (i = 0; i < 2; i++) {
        this->unk0xA8[i]->unk00 = D_80078CDC;
        this->unk0xA8[i]->unk04->unk08 = i << 7;
    }

    sp28 = (u8 *)this + 0x28;
    func_800B3558(sp28);

    for (i = 2; i < 4; i++) {
        this->unk0xA8[i]->unk00 = sp28;
        this->unk0xA8[i]->unk04->unk08 = (i - 2) << 7;
    }

    func_800B2E3C(this);
    func_800B2F88((u8 *)this->unk0xA8 + 0x18);
    func_800B3108((u8 *)this->unk0xA8 + 0x40);
    func_800B331C(this->unk0xA8);
    func_800B2DCC((u8 *)this->unk0xA8 + 0x68);
    func_800B2F38(this);
    func_800B3440(this);
}
