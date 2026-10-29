#include "common.h"
#include "shared/game_work.h"
#include "town.h"
#include "town/player.h"
#include "town/player/position.h"

typedef struct {
    u8 pad0[0x14];
    s32 field14;
} TownObject;

extern u8 town_blocked_directions[];

extern void handle_adjust_vector_toward_selected_angle_limit_magnitude(TownObject *);
extern void initialize_threshold_interaction_object(void *, TownObject *, void *);

/* Updates the town object and dispatches its action based on input and state. */
void update_town_object_from_input(void *context, TownObject *object, void *action_data)
{
    GameWork *input = &g_game_work;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(object);
    store_the_valid_shared_angle_in_offset_hex_10(context);
    handle_adjust_vector_toward_selected_angle_limit_magnitude(object);

    if (town_blocked_directions[0] != 0) {
        object->field14 = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(object);
    } else {
        add_hex_20000_s_signed_offset_hex_14(object);
    }

    if (((u32)input->pressed_buttons) & 0x40) {
        init_sound_threshold_action(context, object, action_data);
        return;
    }

    if (object->field14 >= 0) {
        initialize_threshold_interaction_object(context, object, action_data);
    }
}
