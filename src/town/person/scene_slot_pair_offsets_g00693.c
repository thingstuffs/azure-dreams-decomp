/* G00693: scene slot pair offsets. */
/* Original-file evidence (G00693): inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D75E0, PD:town/engine:800D75E8, PD:town/engine:800D7610, PD:town/engine:800D7614. */
#include "town/person/scene_slot_pair_offsets_g00693.h"

void initialize_scene_slot_62(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 62, (s32)D_800D7610, (s32)D_800D7614, (s32)D_800D75E0, (s32)D_800D75E8);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}

void initialize_scene_slot_57(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 57, (s32)D_800D7610, (s32)D_800D7614, (s32)D_800D75E0, (s32)D_800D75E8);
    *(s16 *)((u8 *)context + 0x12) = 0x40;
}
