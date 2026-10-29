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
    call_the_handler_selects_nonzero_entry((s32 *) D_800D01C0, (Rec_func_80094268_arg0 *) object, ptr2);
    object_index_slots[1].unk_00 = 0;
    object->unk4 = forward_value_context_data_mode;
    object_index_slots[1].unk_01 = 0;
    create_indexed_effect_object(object->unk36, object->unk38);
}
