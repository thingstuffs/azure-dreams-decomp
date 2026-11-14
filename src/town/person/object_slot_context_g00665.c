/* Object slot context. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D5AC8, PD:town/engine:800D5AD0, PD:town/engine:800D5AF8, PD:town/engine:800D5AFC. */
#include "town/person/object_slot_context_g00665.h"
#include "shared/sprite_frame_state.h"

/* Registers the object in scene slot 47 using the four local setup tables. */
void initialize_scene_slot_47_context(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context)
{
    register_object_slot_with_tables(object, 47, D_800D5AF8, D_800D5AFC, D_800D5AC8, D_800D5AD0);
}

/*
 * Registers scene slot 0x17 using the four local tables, sets render halfword 9 to 0x280, and
 * clears flag 0x100 in halfword 10.
 */
void initialize_scene_slot_23(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords) {
    register_object_slot_with_tables(context, 0x17, D_800D5AF8, D_800D5AFC, D_800D5AC8,
                  D_800D5AD0);
    stateWords->clut = 0x280;
    stateWords->flags &= ~0x100;
}
