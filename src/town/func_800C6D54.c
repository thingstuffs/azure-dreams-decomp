#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* Pointer arguments follow the matched townInitializeObjectEntries body. */
extern void townInitializeObjectEntries(void *state, s8 *output, s32 *entries);
#include "shared/object_index_slots.h"

extern u8 D_800C3C7C[];


void reset_actor_handler_from_linked_entries(Rec_func_80094268_arg0 *actor, s32 unused, s8 *output) {
    s32 *entries = *(s32 **)((u8 *)actor->unk_80 + 0x18);

    townInitializeObjectEntries(actor, output, entries);
    D_80082660[actor->unk_60].unk_00 = 0;
    actor->unk_54 = D_800C3C7C;
    actor->unk_6C.as_s16 = 32;
}
