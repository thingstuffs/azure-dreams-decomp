#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene/event.h"


typedef s32 (*Callback)(s32);



/* Runs the context callback and checks whether the state code is in 0x3DC through 0x3E4. */
s32 check_event_state_range(void) {
    s32 stateCode;

    ((Callback)town_scene_root->services->callback_248)(0);
    stateCode =
        town_scene_root->position->x;
    return stateCode >= 0x3E0 ? stateCode < 0x3E5 : stateCode >= 0x3DC;
}
