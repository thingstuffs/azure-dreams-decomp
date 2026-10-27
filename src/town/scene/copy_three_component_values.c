#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/fixed_position.h"


/* Copy three signed 16-bit components into the current 32-bit component array. */
void copy_three_component_values(s16 *components) {
    {
        s32 *output_components = *(s32 **)((u8 *)*(s32 **)((u8 *)(&town_scene_root)) + 0x1C);
        output_components[0] = components[0];
    }
    {
        s32 *context = *(s32 **)((u8 *)(&town_scene_root));
        ((s32 *)*(s32 **)((u8 *)context + 0x1C))[1] = components[1];
        ((s32 *)*(s32 **)((u8 *)context + 0x1C))[2] = components[2];
    }
}
