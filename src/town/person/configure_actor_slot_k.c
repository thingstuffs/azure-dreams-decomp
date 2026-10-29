/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"
#include "town/person/object.h"

extern u8 D_800D72FC[];
extern u8 D_800D7304[];
extern u8 D_800D732C[];
extern u8 D_800D7338[];


/* Calls func_800C3050 with actor, 0x5, D_800D732C, D_800D7338, D_800D72FC, D_800D7304. */
void configure_actor_slot_5(void *actor, void *unused_position, struct SpriteFrameState *unused_sprite) {
    func_800C3050(actor, 0x5, D_800D732C, D_800D7338, D_800D72FC, D_800D7304);
}
