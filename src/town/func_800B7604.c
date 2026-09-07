#include "common.h"

typedef struct SlotB {
    s8 pad[8];
    s16 unk08;
} SlotB;

typedef struct SlotA {
    void *unk00;
    SlotB *unk04;
} SlotA;

typedef struct Obj {
    u8 pad20[0x20];
    void *unk20;
    u8 pad5c[0x38];
    SlotA **unk5c;
} Obj;

extern u8 D_80078CDC[];

extern void func_800B3558(void *arg0);
extern void func_800B474C(void *arg0);
extern void func_800B47BC(void *arg0);
extern void func_800B48B8(void *arg0);
extern void func_800B4908(void *arg0);
extern void func_800B49A8(void *arg0);
extern void func_800B4A60(void *arg0);
extern void func_800B4B7C(void *arg0);

void func_800B4D64(Obj *arg0) {
    s32 i;

    for (i = 0; i < 2; i++) {
        arg0->unk5c[i]->unk00 = D_80078CDC;
        arg0->unk5c[i]->unk04->unk08 = i << 7;
    }

    func_800B3558(arg0->unk20);

    for (i = 2; i < 4; i++) {
        arg0->unk5c[i]->unk00 = arg0->unk20;
        arg0->unk5c[i]->unk04->unk08 = (i - 2) << 7;
    }

    func_800B47BC(arg0);
    func_800B4908((u8 *)arg0->unk5c + 0x18);
    func_800B49A8((u8 *)arg0->unk5c + 0x40);
    func_800B4A60(arg0->unk5c);
    func_800B474C((u8 *)arg0->unk5c + 0x68);
    func_800B48B8(arg0);
    func_800B4B7C(arg0);
}
