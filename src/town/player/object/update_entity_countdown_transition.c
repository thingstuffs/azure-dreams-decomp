#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_func_80090C68_arg0.h"
#include "town/player/object.h"
#include "town/player/state.h"
#include "shared/entity.h"




extern void dispatch_actor_interaction_actions(void *, EntityRec *, s32);
extern void initialize_shared_scene_data(void *record, void *context, s32 update_arg); /* Unprototyped: retail call passes more arguments than the callee reads */
extern void run_the_three_update_routines_context(void *context); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

/* Run follow-up updates if the record value is unchanged and flag 0x80 is set. */
void update_entity_countdown_transition(void *record_arg, void *context, s32 update_arg) {
    Rec_func_80090C68_arg0 *record = record_arg;
    s32 saved_value;
    GameWork *state_words;

    state_words = &g_game_work;
    saved_value = record->unk_00;
    dispatch_actor_interaction_actions(record, context, update_arg);
    if ((saved_value == record->unk_00) &&
        (state_words->buttons & 0x80)) {
        clear_entity_record_fields(context);
        run_the_three_update_routines_context(context);
        if (run_the_action_sequence_context_unless_flag_hex_a_5_set((u8 *)record - 0x20) != 0) {
            initialize_shared_scene_data(record, context, update_arg);
        }
    }
}
