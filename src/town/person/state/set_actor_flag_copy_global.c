#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"
#include "town/person/state.h"


extern s32 loaded_town_resource_attributes[];
extern u8 D_800D61C4[];
extern u8 D_800D61CC[];
extern u8 D_800D61F4[];
extern u8 D_800D6200[];

/* Set the actor flag, copy the global value into its state, and configure mode 2 with its tables. */
void set_actor_flag_copy_global(void *actor, void *unused, struct SpriteFrameState *state) {
    *((s8 *)actor + 0x93) = 1;
    *(s32 *)((u8 *)state + 0x28) = loaded_town_resource_attributes[0];
    initialize_object_and_register_slot(actor, 2, D_800D61F4, D_800D6200, D_800D61C4,
                  D_800D61CC);
}
