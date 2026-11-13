#include "town/player/position_handlers.h"
#include "common.h"
#include "shared/game_work.h"
#include "town.h"
#include "town/player.h"
#include "town/player/position.h"
#include "town/player/input.h"

typedef struct {
    u8 pad0[0x14];
    s32 field14;
} TownObject;

extern u8 town_blocked_directions[];

extern void initialize_threshold_interaction_object(void *, TownObject *, void *);

/* Updates the town object and dispatches its action based on input and state. */
void update_town_object_from_input(void *context, ObjectPosition *object, void *action_data)
{
    GameWork *input = &g_game_work;

    resolve_collision_axis_order(object);
    store_input_angle(context);
    accelerate_toward_input_keep_speed(object);

    if (town_blocked_directions[0] != 0) {
        object->velocity_z = 0;
        copy_z_to_collision_motion(object);
    } else {
        add_vertical_gravity(object);
    }

    if (((u32)input->pressed_buttons) & 0x40) {
        init_sound_threshold_action(context, object, action_data);
        return;
    }

    if (object->velocity_z >= 0) {
        initialize_threshold_interaction_object(context, object, action_data);
    }
}
