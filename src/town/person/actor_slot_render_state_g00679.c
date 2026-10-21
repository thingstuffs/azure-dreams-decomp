/* G00679: actor slot render state. */
/* Original-file evidence (G00679): inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D6430, PD:town/engine:800D6438, PD:town/engine:800D6460, PD:town/engine:800D6464. */
#include "town/person/actor_slot_render_state_g00679.h"

void initialize_scene_slot_36(void *object, s32 unused, void *context)
{
    initialize_object_and_register_slot(object, 36, (s32)D_800D6460, (s32)D_800D6464, (s32)D_800D6430, (s32)D_800D6438);
}

void configure_actor_slot_26_and_render_state(void *context, s32 unused, u16 *stateWords) {
    func_800C3050(context, 0x1A, D_800D6460, D_800D6464, D_800D6430,
                  D_800D6438);
    stateWords[9] = 0x2C0;
    stateWords[10] &= ~0x100;
}
