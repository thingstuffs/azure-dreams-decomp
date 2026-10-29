/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person/object.h"

extern u8 D_800D6C4C[];
extern u8 D_800D6C54[];
extern u8 D_800D6C7C[];
extern u8 D_800D6C80[];


/*
 * Configures scene slot 44 with the four local tables, stores 0x2C0 in render halfword 9, and
 * clears flag 0x100 in halfword 10.
 */
void configure_actor_slot_44_and_render_state(void *context, void *unused, struct SpriteFrameState *stateWords) {
    func_800C3050(context, 0x2C, D_800D6C7C, D_800D6C80, D_800D6C4C,
                  D_800D6C54);
    stateWords->clut = 0x2C0;
    stateWords->flags &= ~0x100;
}
