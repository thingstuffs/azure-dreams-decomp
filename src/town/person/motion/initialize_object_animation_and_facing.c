#include "common.h"
#include "shared/object_index_slots.h"

typedef struct {
    s8 val;
    u8 pad[7];
} Rec8;

#include "town/person/object/initialize_object_entries_api.h"

#include "town/person/object_setup.h"

/* Initialize the object's animation, clear its record flag, and update its facing. */
void initialize_object_animation_and_facing(void *object, void *position, void *animation_state) {
    initialize_object_entries(object, animation_state, *(void **)((u8 *)*(void **)((u8 *)object + 0x80) + 0x14));
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = (void *)apply_object_setup_update;
    *(s16 *)((u8 *)object + 0x72) = clamp_transform_coordinate_deltas(
        *(s16 *)((u8 *)object + 0x88),
        *(s16 *)((u8 *)object + 0x8A),
        position);
}
