#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"
#include "town/person/state.h"

extern u8 D_800D6AE4[];
extern u8 D_800D6AEC[];
extern u8 D_800D6B14[];
extern u8 D_800D6B18[];

// Configure the context for ID 0x27, then clear state word 9 and flag 0x100.
void reset_object_substate_and_flag(void *context, void *unused, struct SpriteFrameState *stateWords) {
    initialize_object_and_register_slot(context, 0x27, D_800D6B14, D_800D6B18, D_800D6AE4,
                  D_800D6AEC);
    stateWords->clut = 0;
    stateWords->flags &= ~0x100;
}
