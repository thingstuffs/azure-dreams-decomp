#include "common.h"
#include "shared/object_index_slots.h"

typedef struct {
    u8 active;
    u8 unk1;
    u8 variant;
    u8 unk3[5];
} TownSlot;

extern u16 D_800D5070[];
extern void func_800C41D4(void *, void *, void *, void *);

/* Deactivate the town slot, apply its variant to the object and child, and update the object. */
void func_800C4A88(void *town_object, void *passthru_1, void *passthru_2, void *child)
{
    u32 slot;
    u8 raw_variant;
    ObjectIndexSlot *slot_table;

    slot_table = D_80082660;
    slot = (u32)(&slot_table[*(s32 *)((u8 *)town_object + 0x60)]);
    raw_variant = ((TownSlot *)slot)->variant;
    ((TownSlot *)slot)->active = 0;
    child = *(void **)((u8 *)town_object + 0x98);
    slot = raw_variant & 3;
    if (child != 0) {
        *(u8 *)((u8 *)child + 4) = slot;
    }
    *(u16 *)((u8 *)town_object + 0x6E) = D_800D5070[slot];
    func_800C41D4(town_object, passthru_1, passthru_2, child);
}
