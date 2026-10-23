#include "common.h"
#include "shared/object_index_slots.h"

typedef struct {
    s8 active;
    u8 pad1[3];
    void *object;
} ObjectSlot;

extern void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);

/* Store the object in its slot, mark the slot inactive, and call the next handler. */
void store_object_slot_and_dispatch(void *object, s32 update_context, s32 setup_context) {
    s32 slot_index;

    slot_index = *(s32 *)((u8 *)object + 0x60);
    object_index_slots[slot_index].object = (u8 *)object - 0x20;
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    apply_object_setup_and_update(object, update_context, setup_context);
}
