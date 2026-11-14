/* actor slot render state. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D6430, PD:town/engine:800D6438, PD:town/engine:800D6460, PD:town/engine:800D6464. */
#include "town/person/actor_slot_render_state_g00679.h"
#include "shared/sprite_frame_state.h"

/* Registers the object in scene slot 36 using the four local setup tables. */
void initialize_scene_slot_36(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context)
{
    register_object_slot_with_tables(object, 36, D_800D6460, D_800D6464, D_800D6430, D_800D6438);
}

/*
 * Configures scene slot 26 with the four local tables, stores 0x2C0 in render halfword 9, and
 * clears flag 0x100 in halfword 10.
 */
void configure_actor_slot_26_and_render_state(TownObjectRecord *context, ObjectPosition *unused, struct SpriteFrameState *stateWords) {
    register_object_slot_with_tables(context, 0x1A, D_800D6460, D_800D6464, D_800D6430,
                  D_800D6438);
    stateWords->clut = 0x2C0;
    stateWords->flags &= ~0x100;
}
