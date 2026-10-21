/* Object slot context (G00665). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D5AC8, PD:town/engine:800D5AD0, PD:town/engine:800D5AF8, PD:town/engine:800D5AFC. */
#include "town/person/object_slot_context_g00665.h"

void initialize_scene_slot_47_context(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 47, (s32)D_800D5AF8, (s32)D_800D5AFC, (s32)D_800D5AC8, (s32)D_800D5AD0);
}

void initialize_object_slot_0x17(void *context, s32 unused, u16 *stateWords) {
    initialize_object_and_register_slot(context, 0x17, (s32)D_800D5AF8, (s32)D_800D5AFC, (s32)D_800D5AC8,
                  (s32)D_800D5AD0);
    stateWords[9] = 0x280;
    stateWords[10] &= ~0x100;
}
