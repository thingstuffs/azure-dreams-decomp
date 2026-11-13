#include "town/player.h"
#include "common.h"
#include "town/player/initialize_shared_scene_data.h"
#include "shared/game_work.h"
#include "records/Rec_func_80090C68_arg0.h"
#include "town/player/object.h"
#include "town/player/state.h"
#include "shared/entity.h"





/* Run follow-up updates if the record value is unchanged and flag 0x80 is set. */
void update_entity_countdown_transition(void *record_arg, void *context, SpriteFrameState *sprite) {
    Rec_func_80090C68_arg0 *record = record_arg;
    s32 saved_value;
    GameWork *state_words;

    state_words = &g_game_work;
    saved_value = record->unk_00;
    dispatch_actor_interaction_actions(record_arg, context, sprite);
    if ((saved_value == record->unk_00) &&
        (state_words->buttons & 0x80)) {
        clear_entity_record_fields(context);
        sync_collision_motion_xyz(context);
        if (create_item_menu_unless_minigame((u8 *)record - 0x20) != 0) {
            initialize_shared_scene_data(record_arg, context, sprite);
        }
    }
}
