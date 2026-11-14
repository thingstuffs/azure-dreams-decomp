#include "town/player.h"
#include "common.h"
#include "town/player/initialize_shared_scene_data.h"
#include "shared/game_work.h"
#include "records/Rec_func_80090C68_arg0.h"
#include "town/player/object.h"
#include "town/player/state.h"
#include "shared/entity.h"



extern s32 init_button_transition_action();
/* Updates the record, then handles a flagged action or countdown if its state is unchanged. */
void update_entity_and_handle_flagged_action(void *record_arg, void *context, SpriteFrameState *sprite) {
    Rec_func_80090C68_arg0 *record = record_arg;
    s32 previous_state;
    GameWork *global_state;
    u16 ticks_left;

    global_state = &g_game_work;
    previous_state = record->unk_00;
    dispatch_actor_interaction_actions(record_arg, context, sprite);
    if (previous_state == record->unk_00) {
        if (global_state->buttons & 0x80) {
            clear_object_velocity(context);
            sync_collision_motion_xyz(context);
            if (create_item_menu_unless_minigame(record_arg - 0x20) != 0) {
                initialize_shared_scene_data(record_arg, context, sprite);
                return;
            }
        } else {
            ticks_left = record->unk_0A - 1;
            record->unk_0A = ticks_left;
            if ((ticks_left << 0x10) <= 0) {
                init_button_transition_action(record, context, sprite);
            }
        }
    }
}

