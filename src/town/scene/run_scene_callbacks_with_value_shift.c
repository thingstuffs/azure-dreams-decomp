#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene.h"

typedef void (*Callback)(s32);


/* Invoke both town callbacks and subtract 0x30 from the entry value in state 3. */
s32 run_scene_callbacks_with_value_shift(void)
{
    town_scene_root->services->callback_248(1);
    town_scene_root->services->callback_244(1);
    if (town_scene_root->position->unk_00 == 3) {
        town_scene_root->position->x -= 0x30;
        return 1;
    }
    return 0;
}
