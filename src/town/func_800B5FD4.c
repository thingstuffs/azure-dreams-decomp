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

extern void func_800B3558(void *ptr);
extern void func_800B2E3C(void *ptr);
extern void func_800B2F88(void *ptr);
extern void func_800B3108(void *ptr);
extern void func_800B331C(void *ptr);
extern void townArrangeTenObjectsInColumns(void *objects);
extern void townApplyLinkedRecordDefaults(void *record);
extern void townUpdateAndFinalizeRecord(void *record);

/* Initialize slot data pointers and offsets, then set up the object. */
void townInitializeFourSlotObjectVariant(Obj *object) {
    Obj *obj = object;
    s32 slot_index;

    for (slot_index = 0; slot_index < 2; slot_index++) {
        obj->unk0xA8[slot_index]->unk00 = D_80078CDC;
        obj->unk0xA8[slot_index]->unk04->unk08 = slot_index << 7;
    }

    func_800B3558((u8 *)obj + 0x28);

    for (slot_index = 2; slot_index < 4; slot_index++) {
        obj->unk0xA8[slot_index]->unk00 = (u8 *)obj + 0x28;
        obj->unk0xA8[slot_index]->unk04->unk08 = (slot_index - 2) << 7;
    }

    func_800B2E3C(obj);
    func_800B2F88((u8 *)obj->unk0xA8 + 0x18);
    func_800B3108((u8 *)obj->unk0xA8 + 0x40);
    func_800B331C(obj->unk0xA8);
    townArrangeTenObjectsInColumns((u8 *)obj->unk0xA8 + 0x68);
    townApplyLinkedRecordDefaults(obj);
    townUpdateAndFinalizeRecord(obj);
}
