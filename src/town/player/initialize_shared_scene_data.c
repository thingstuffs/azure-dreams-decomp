#include "common.h"
#include "town/player/initialize_shared_scene_data.h"
#include "town/player.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"
extern s32 *town_player_action_callback;

/* Initializes the output pointer and the shared data pointer. */
void initialize_shared_scene_data(s32 **out_ptr, void *unused_position, struct SpriteFrameState *unused_sprite) {
    *out_ptr = &noop_player_scene_action;
    town_player_action_callback = &initialize_scene_action_record;
}
