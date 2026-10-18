#include "common.h"
#include "m2c_compat.h"

void initialize_object_entries();          /* extern */
void clear_record_indexed_flag();       /* extern */
extern M2C_UNK D_800D5540;

/* Initialize the actor with the state table and run its follow-up handler. */
void initialize_actor_state_table(s32 actor, s32 context, s32 state_context) {
    initialize_object_entries(actor, state_context, &D_800D5540);
    clear_record_indexed_flag(actor, context, state_context);
}
