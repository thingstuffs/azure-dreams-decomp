#include "common.h"
#include "m2c_compat.h"
#include "shared/object_index_slots.h"
#include "records/Rec_func_80094268_arg0.h"


extern void initialize_object_entries(void *state, s32 output, void *entries);
extern void person_countdown_update_address();
extern s32 D_800D5670[];


/* Initialize the actor state, clear its entry flag, and set a callback with a 32-tick countdown. */
void initialize_actor_with_32_tick_callback(void *actor, s32 unused, s32 state_context) {
    initialize_object_entries(actor, state_context, &D_800D5670);
    object_index_slots[((Rec_func_80094268_arg0 *)actor)->unk_60].unk_00 = 0;
    ((Rec_func_80094268_arg0 *)actor)->unk_54 = &person_countdown_update_address;
    ((Rec_func_80094268_arg0 *)actor)->unk_6C.as_s16 = 0x20;
}
