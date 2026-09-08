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

/* Initialize slot data pointers and offsets, then set up the object. */
void func_800B3734(Obj *object) {
    Obj *obj = object;
    register void *slot_data ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 slot_index;

    for (slot_index = 0; slot_index < 2; slot_index++) {
        obj->unk0xA8[slot_index]->unk00 = D_80078CDC;
        obj->unk0xA8[slot_index]->unk04->unk08 = slot_index << 7;
    }

    slot_data = (u8 *)obj + 0x28;
    func_800B3558(slot_data);

    for (slot_index = 2; slot_index < 4; slot_index++) {
        obj->unk0xA8[slot_index]->unk00 = slot_data;
        obj->unk0xA8[slot_index]->unk04->unk08 = (slot_index - 2) << 7;
    }

    func_800B2E3C(obj);
    func_800B2F88((u8 *)obj->unk0xA8 + 0x18);
    func_800B3108((u8 *)obj->unk0xA8 + 0x40);
    func_800B331C(obj->unk0xA8);
    func_800B2DCC((u8 *)obj->unk0xA8 + 0x68);
    func_800B2F38(obj);
    func_800B3440(obj);
}
