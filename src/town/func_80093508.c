#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_func_80090C68_arg0.h"



extern void dispatch_actor_interaction_actions(void *, s32, s32);
extern void initialize_shared_scene_data();
extern s32 func_80093DD8();
extern s32 run_the_action_sequence_context_unless_flag_hex_a_5_set();
extern void run_the_three_update_routines_context();
extern void clear_entity_record_fields();
/* Updates the record, then handles a flagged action or countdown if its state is unchanged. */
void update_entity_and_handle_flagged_action(void *record, s32 context, s32 update_arg) {
    s32 previous_state;
    GameWork *global_state;
    u16 ticks_left;

    global_state = &g_game_work;
    previous_state = ((Rec_func_80090C68_arg0 *)record)->unk_00;
    dispatch_actor_interaction_actions(record, context, update_arg);
    if (previous_state == ((Rec_func_80090C68_arg0 *)record)->unk_00) {
        if (global_state->buttons & 0x80) {
            clear_entity_record_fields(context);
            run_the_three_update_routines_context(context);
            if (run_the_action_sequence_context_unless_flag_hex_a_5_set(record - 0x20) != 0) {
                initialize_shared_scene_data(record, context, update_arg);
                return;
            }
        } else {
            ticks_left = ((Rec_func_80090C68_arg0 *)record)->unk_0A - 1;
            ((Rec_func_80090C68_arg0 *)record)->unk_0A = ticks_left;
            if ((ticks_left << 0x10) <= 0) {
                func_80093DD8(record, context, update_arg);
            }
        }
    }
}

