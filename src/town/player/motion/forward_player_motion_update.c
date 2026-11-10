#include "town/player/initialize_record_with_handler_table_api.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player/motion.h"
#include "shared/sprite_frame_state.h"


/* Forward the object and values to initialize_record_with_handler_table. */
void forward_player_motion_update(void *object, ObjectPosition *position, SpriteFrameState *sprite) {
    initialize_record_with_handler_table(object, position, sprite);
}
