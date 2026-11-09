#include "town/player/initialize_record_with_handler_table_api.h"
#include "common.h"
#include "town/player/scene_action_setup.h"
#include "m2c_compat.h"
#include "town/player/motion.h"
#include "shared/sprite_frame_state.h"
#include "town/player/state.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Forward the state, value, and mode to initialize_record_with_handler_table. */
void forward_player_motion_state(void *state, ObjectPosition *position, SpriteFrameState *sprite) {
    initialize_record_with_handler_table(state, position, sprite);
}
