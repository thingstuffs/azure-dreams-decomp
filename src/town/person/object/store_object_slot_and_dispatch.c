#include "common.h"
#include "shared/object_index_slots.h"

typedef struct {
    s8 active;
    u8 pad1[3];
    void *object;
} ObjectSlot;

#include "town/person/object_setup.h"
#include "town/person/object.h"

/* Store the object in its slot, mark the slot inactive, and call the next handler. */
void store_object_slot_and_dispatch(void *object, void *update_context, void *setup_context) {
    s32 slot_index;

    slot_index = *(s32 *)((u8 *)object + 0x60);
    object_index_slots[slot_index].object = (u8 *)object - 0x20;
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    apply_object_setup_and_update(object, update_context, setup_context);
}
