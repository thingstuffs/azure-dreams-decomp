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

/* Initialize four object slots with shared or embedded data and paired offsets. */
void func_800B0024(Obj *object) {
    Obj *obj = object;
    register void *slot_data ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 slot_index;

    for (slot_index = 0; slot_index < 2; slot_index++) {
        obj->unk0xA8[slot_index]->unk00 = D_80078CDC;
        obj->unk0xA8[slot_index]->unk04->unk08 = slot_index << 7;
    }

    slot_data = (u8 *)obj + 0x28;
    func_800AFDD0(slot_data);

    for (slot_index = 2; slot_index < 4; slot_index++) {
        obj->unk0xA8[slot_index]->unk00 = slot_data;
        obj->unk0xA8[slot_index]->unk04->unk08 = (slot_index - 2) << 7;
    }

    func_800AF36C(obj);
    func_800AF4AC(obj->unk0xA8);
    func_800AF600(obj->unk0xA8);
    func_800AF734(obj->unk0xA8);
    func_800AF2F8(obj->unk0xA8);
    func_800AFFA8(obj);
}
