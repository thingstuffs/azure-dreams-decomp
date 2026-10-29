/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"
#include "town/person/object.h"

extern u8 D_800D5328[];
extern u8 D_800D5330[];
extern u8 D_800D5358[];
extern u8 D_800D535C[];


/* Calls func_800C3050 with actor, 0x10, D_800D5358, D_800D535C, D_800D5328, D_800D5330. */
void configure_actor_slot_16(void *actor, void *unused_position, struct SpriteFrameState *unused_sprite) {
    func_800C3050(actor, 0x10, D_800D5358, D_800D535C, D_800D5328, D_800D5330);
}
