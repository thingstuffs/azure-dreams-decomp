#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/scene/list_setup.h"
#include "town/event/object_setup.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "shared/dungeon_effect_views.h"
#include "town/scene.h"
#include "town/event/state.h"

extern M2C_UNK D_800D0690;


   /* Select a state value and update the record according to its mode flag. */
void select_object_state_by_mode(Rec_D_800CFCB4 *record, void *context, SpriteFrameState *state, void *default_value,
    void *alternate_value, void *update_value) {
    if (record->unk_94 != 0) {
        state->source = alternate_value;
        configure_the_set_mode_n_3(record, context, update_value);
        initialize_optional_object_state(record, context, state, 0);
        return;
    }
    state->source = default_value;
    handle_insert_initialize_two_values_status_flags(record, context, update_value);
    {
        void *next_record;
        void *next_context;
        void *next_state;
        s32 *shared_data;

        next_record = record;
        next_context = context;
        next_state = state;
        shared_data = &D_800D0690;
        initialize_optional_object_state(next_record, next_context, next_state, shared_data);
    }
}
