#include "common.h"
#include "town/minigame/gym.h"
#include "shared/town_handler_entries.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "town/person/position.h"
#include "town/minigame.h"
#include "town/player.h"

extern u8 D_800D00C0[];


/* Updates the three-choice selection and the object's vertical motion. */
void update_gym_lane_selection(void *unused, EntityRec *object)
{
    GameWork *button_base;
    s32 height_limit;

    button_base = &g_game_work;
    height_limit = (s16)query_lowered_transform_position(object);
    if (gym_lane_delay > 0) {
        gym_lane_delay--;
        view_reference_entity.velocity_x -= view_reference_entity.velocity_x >> 1;
    } else {
        s16 choice_index;
        u16 choice_id;
        s32 buttons;
        ObjectPosition *record_base;

        record_base = &view_reference_entity;
        choice_index = gym_lane;
        choice_id = gym_lane_positions[choice_index];
        buttons = (button_base->pressed_buttons);

        record_base->velocity_x = 0;
        record_base->x.w.i = choice_id;
        if ((buttons & 0x8000) && choice_index != 0) {
            gym_lane--;
            record_base->velocity_x = (s32)0xFFD00000;
            gym_lane_delay = 3;
            apply_global_scene_value(D_800D00C0);
        } else if (((button_base->pressed_buttons) & 0x2000) && gym_lane < 2) {
            gym_lane++;
            view_reference_entity.velocity_x = 0x300000;
            gym_lane_delay = 3;
            apply_global_scene_value(D_800D00C0);
        } else if (reference_tile_object.sprite_flags & 0x6000) {
            apply_global_scene_value(movement_action_handler_table);
        }
    }

    object->flags14 += 0x1D000;
    if (height_limit < object->z.w.i) {
        object->z.w.i = height_limit;
        object->flags14 = 0;
    }
}
