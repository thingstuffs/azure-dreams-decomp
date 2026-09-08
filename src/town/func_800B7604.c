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

/* Initialize slot data and offsets, then configure the object. */
void func_800B4D64(Obj *obj) {
    s32 slot_index;

    for (slot_index = 0; slot_index < 2; slot_index++) {
        obj->unk5c[slot_index]->unk00 = D_80078CDC;
        obj->unk5c[slot_index]->unk04->unk08 = slot_index << 7;
    }

    func_800B3558(obj->unk20);

    for (slot_index = 2; slot_index < 4; slot_index++) {
        obj->unk5c[slot_index]->unk00 = obj->unk20;
        obj->unk5c[slot_index]->unk04->unk08 = (slot_index - 2) << 7;
    }

    func_800B47BC(obj);
    func_800B4908((u8 *)obj->unk5c + 0x18);
    func_800B49A8((u8 *)obj->unk5c + 0x40);
    func_800B4A60(obj->unk5c);
    func_800B474C((u8 *)obj->unk5c + 0x68);
    func_800B48B8(obj);
    func_800B4B7C(obj);
}
