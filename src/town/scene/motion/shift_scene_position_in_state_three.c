#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene/motion.h"

/* Invoke town services 0x248 and 0x244 with 1; when the position state is 3, advance X by 0x30 and report it. */
s32 shift_scene_position_in_state_three(void) {
    TownPositionState *position;

    town_scene_root->services->callback_248(1);
    town_scene_root->services->callback_244(1);
    position = town_scene_root->position;
    if (position->unk_00 == 3) {
        position->x += 0x30;
        return 1;
    }
    return 0;
}
