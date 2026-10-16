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

extern void townInitializeItemMenuPanelRectangle(void *record);
extern void townSetItemMenuEntryCoordinates(void *object);
extern void townLayoutItemMenuUpperPairColumns(void *context);
extern void townLayoutItemMenuLowerItemColumns(void *context);
extern void townPositionItemMenuSideIndicators(void *record);
extern void townLayoutItemMenuLowerPairColumns(void *context);
extern void townProcessItemMenuSelectedEntry(void *record);

/* Initialize four object slots with shared or embedded data and paired offsets. */
void townInitializeItemMenuObjectSlots(Obj *object) {
    Obj *obj = object;
    s32 slot_index;

    for (slot_index = 0; slot_index < 2; slot_index++) {
        obj->unk0xA8[slot_index]->unk00 = D_80078CDC;
        obj->unk0xA8[slot_index]->unk04->unk08 = slot_index << 7;
    }

    townInitializeItemMenuPanelRectangle((u8 *)obj + 0x28);

    for (slot_index = 2; slot_index < 4; slot_index++) {
        obj->unk0xA8[slot_index]->unk00 = (u8 *)obj + 0x28;
        obj->unk0xA8[slot_index]->unk04->unk08 = (slot_index - 2) << 7;
    }

    townSetItemMenuEntryCoordinates(obj);
    townLayoutItemMenuUpperPairColumns(obj->unk0xA8);
    townLayoutItemMenuLowerItemColumns(obj->unk0xA8);
    townPositionItemMenuSideIndicators(obj->unk0xA8);
    townLayoutItemMenuLowerPairColumns(obj->unk0xA8);
    townProcessItemMenuSelectedEntry(obj);
}
