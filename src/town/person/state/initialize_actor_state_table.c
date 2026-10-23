#include "common.h"
#include "m2c_compat.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
void clear_record_indexed_flag();       /* extern */
extern s32 D_800D5540[];

/* Initialize the actor with the state table and run its follow-up handler. */
void initialize_actor_state_table(s32 actor, s32 context, s32 state_context) {
    initialize_object_entries((Struct800C5724 *)(actor), (s8 *)(state_context), &D_800D5540);
    clear_record_indexed_flag(actor, context, state_context);
}
