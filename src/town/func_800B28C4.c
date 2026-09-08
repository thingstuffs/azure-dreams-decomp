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

extern void func_800AFDD0(void *arg0);
extern void func_800AF36C(void *arg0);
extern void func_800AF4AC(void *arg0);
extern void func_800AF600(void *arg0);
extern void func_800AF734(void *arg0);
extern void func_800AF2F8(void *arg0);
extern void func_800AFFA8(void *arg0);

void func_800B0024(Obj *arg0) {
    Obj *this = arg0;
    register void *sp28 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 i;

    for (i = 0; i < 2; i++) {
        this->unk0xA8[i]->unk00 = D_80078CDC;
        this->unk0xA8[i]->unk04->unk08 = i << 7;
    }

    sp28 = (u8 *)this + 0x28;
    func_800AFDD0(sp28);

    for (i = 2; i < 4; i++) {
        this->unk0xA8[i]->unk00 = sp28;
        this->unk0xA8[i]->unk04->unk08 = (i - 2) << 7;
    }

    func_800AF36C(this);
    func_800AF4AC(this->unk0xA8);
    func_800AF600(this->unk0xA8);
    func_800AF734(this->unk0xA8);
    func_800AF2F8(this->unk0xA8);
    func_800AFFA8(this);
}
