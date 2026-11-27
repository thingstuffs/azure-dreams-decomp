#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene/motion.h"

/* Run town services 0x258 (with 10), 0x248 and 0x244 (with 1) - script services 150, 146 and 145
 * (anyone_now_pos_get, player_now_pos_get, player_now_ang_get) - keeping the Y that the first call
 * left in the scene position; when the state word is then 2, set Y to that saved Y plus 0x30 if the
 * new Y is greater, else minus 0x30, and return 1. */
s32 nudge_scene_y_in_state_two(void) {
    TownPositionState *position;
    s32 saved_y;

    town_scene_root->services->callback_258(10);
    saved_y = town_scene_root->position->y;
    town_scene_root->services->callback_248(1);
    town_scene_root->services->callback_244(1);

    position = town_scene_root->position;
    if (position->script_var_0 == 2) {
        if (position->y > saved_y) {
            position->y = saved_y + 0x30;
        } else {
            position->y = saved_y - 0x30;
        }
        return 1;
    }
    return 0;
}
