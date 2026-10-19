#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "shared/dungeon_effect_views.h"

void handle_insert_initialize_two_values_status_flags();        /* extern */
void configure_the_set_mode_n_3();                         /* extern */
void initialize_optional_object_state(); /* extern */
extern M2C_UNK D_800D0690;


   /* arg2 in select_object_state_by_mode */

/* Select a state value and update the record according to its mode flag. */
void select_object_state_by_mode(Rec_D_800CFCB4 *record, s32 context, EffectStateWordView *state, s32 default_value,
    s32 alternate_value, s32 update_value) {
    if (record->unk_94 != 0) {
        state->unk_08 = alternate_value;
        configure_the_set_mode_n_3(record, context, update_value);
        initialize_optional_object_state(record, context, state, 0);
        return;
    }
    state->unk_08 = default_value;
    handle_insert_initialize_two_values_status_flags(record, context, update_value);
    {
        void *next_record;
        s32 next_context;
        void *next_state;
        s32 *shared_data;

        next_record = record;
        next_context = context;
        next_state = state;
        shared_data = &D_800D0690;
        initialize_optional_object_state(next_record, next_context, next_state, shared_data);
    }
}
