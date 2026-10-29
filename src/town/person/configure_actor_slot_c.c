/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person/object.h"

extern u8 D_800D5774[];
extern u8 D_800D577C[];
extern u8 D_800D57A4[];
extern u8 D_800D57A8[];


/* Calls func_800C3050 with actor, 0x3F, D_800D57A4, D_800D57A8, D_800D5774, D_800D577C. */
void configure_actor_slot_63(void *actor, void *unused_position, struct SpriteFrameState *unused_sprite) {
    func_800C3050(actor, 0x3F, D_800D57A4, D_800D57A8, D_800D5774, D_800D577C);
}
