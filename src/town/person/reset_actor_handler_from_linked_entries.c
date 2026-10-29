#include "common.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_80094268_arg0.h"

/* Pointer arguments follow the matched initialize_object_entries body. */
extern void initialize_object_entries(void *state, SpriteFrameState *output, s32 *entries);
#include "shared/object_index_slots.h"

extern u8 D_800C3C7C[];


/*
 * Initializes entries from linked data offset 0x18, clears the indexed object slot, and installs
 * D_800C3C7C with count 32.
 */
void reset_actor_handler_from_linked_entries(Rec_func_80094268_arg0 *actor, s32 unused, SpriteFrameState *output) {
    s32 *entries = *(s32 **)((u8 *)actor->unk_80 + 0x18);

    initialize_object_entries(actor, output, entries);
    object_index_slots[actor->unk_60].unk_00 = 0;
    actor->unk_54 = D_800C3C7C;
    actor->unk_6C.as_s16 = 32;
}
