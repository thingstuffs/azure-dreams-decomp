#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

s32 lookup_item_category_mapped_value();                /* extern */
void configure_the_set_mode_n_3();     /* extern */
void initialize_optional_object_state(); /* extern */
extern s32 D_800D0678[];


/* Initializes the state value and sets up the context using D_800D0678. */
void initialize_reaction_context(s32 contextId, s32 contextData, Rec_D_80082E80 *state) {
    state->unk_08 = lookup_item_category_mapped_value(4, 1);
    configure_the_set_mode_n_3(contextId, contextData, &D_800D0678);
    initialize_optional_object_state(contextId, contextData, state, 0);
}
