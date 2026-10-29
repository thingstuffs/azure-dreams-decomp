#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene.h"



/* Checks whether the stored value is at least the callback result for query {5, 0x17}. */
s32 check_progress_against_callback(void) {
    s8 queryArgs[2];

    queryArgs[1] = 0x17;
    queryArgs[0] = 5;
    return (s32) ((u32)((TownProgressState *)town_scene_root->event_data)->unk_110)
    >= ((u32 (*) (s8 *))town_scene_root->services->callback_050)(queryArgs);
}
