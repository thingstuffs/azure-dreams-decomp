#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/fixed_position.h"
#include "town/scene.h"
#include "shared/town_root.h"


/* Copy three signed 16-bit components into the current 32-bit component array. */
void set_scene_position_triple(s16 *components) {
    {
        s32 *output_components = ((s32 *)(town_scene_root->position));
        output_components[0] = components[0];
    }
    {
        s32 *context = (s32 *)town_scene_root;
        (*(s32 **)((u8 *)context + 0x1C))[1] = components[1];
        (*(s32 **)((u8 *)context + 0x1C))[2] = components[2];
    }
}
