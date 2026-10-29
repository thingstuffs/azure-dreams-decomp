/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person/object.h"

extern u8 D_800D6C4C[];
extern u8 D_800D6C54[];
extern u8 D_800D6C7C[];
extern u8 D_800D6C80[];


/*
 * Configures scene slot 0x15 using the four local setup tables, writes render word 9 to 0x240, and
 * clears bit 0x100 in render word 10.
 */
void configure_actor_slot_21_and_render_state(void *context, void *unused, struct SpriteFrameState *stateWords) {
    func_800C3050(context, 0x15, D_800D6C7C, D_800D6C80, D_800D6C4C,
                  D_800D6C54);
    stateWords->clut = 0x240;
    stateWords->flags &= ~0x100;
}
