#include "common.h"
#include "town/person/actor_slot_global_state_g00680.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"
#include "town/person/state.h"


extern u8 D_800D61C4[];
extern u8 D_800D61CC[];
extern u8 D_800D61F4[];
extern u8 D_800D6200[];

/* Set the actor flag, copy the global value into its state, and configure mode 2 with its tables. */
void set_actor_flag_copy_global(TownObjectRecord *actor, ObjectPosition *unused, struct SpriteFrameState *state) {
    actor->unk_93 = 1;
    state->animation_resource = loaded_town_resource_attributes[0];
    register_object_slot_with_tables(actor, 2, D_800D61F4, D_800D6200, D_800D61C4,
                  D_800D61CC);
}
