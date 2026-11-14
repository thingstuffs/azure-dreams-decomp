#include "common.h"
#include "town/player.h"
#include "shared/object_index_slots.h"
#include "shared/town_handler.h"
#include "town/menu.h"

extern u8 D_800D01C0[];

typedef struct {
    u8 unk0[4];
    void *unk4;
    u8 unk8[0x2E];
    s16 unk36;
    s16 unk38;
} TownObject;

/* Initialize the town object, clear its slot flags, and apply its coordinates. */
void initialize_object_slot_and_position(TownObject *object, void *ptr, void *ptr2) {
    dispatch_selected_entry_if_nonzero((s32 *) D_800D01C0, (TownObjectRecord *) object, ptr2);
    object_index_slots[1].unk_00 = 0;
    object->unk4 = forward_state_callback_dispatch;
    object_index_slots[1].unk_01 = 0;
    create_item_category_effect(object->unk36, object->unk38);
}
