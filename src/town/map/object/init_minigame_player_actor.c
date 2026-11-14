#include "common.h"
#include "shared/object_node.h"
#include "town/player.h"
#include "town/map/course.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"
#include "engine/node.h"
#include "town/map/object.h"


extern M2C_UNK D_800D0C58;

/* Initializes object and rendering data and registers its resources. */
void init_minigame_player_actor(TownCourseActor *object_data, void *unused, SpriteFrameState *render_data) {
    NODE_HEADER(object_data)->update_callback = &update_player_minigame_motion;
    object_data->sprite_direction = -1;
    object_data->facing.s = 0xC00;
    object_data->unk_18 = 0xC00;
    render_data->scale_y = 0x1000;
    render_data->scale_x = 0x1000;
    render_data->color.word = 0x808080;
    render_data->frameTable = &D_800D0C58;
    store_entry_and_set_frame((s32) &D_800D0C58, object_data, render_data);
    unlink_node_if_registered(object_data);
    apply_pending_table_entry(0x24, store_pending_value_and_get_source);
    apply_pending_indexed_value(0xE4, read_and_clear_stored_value);
}
