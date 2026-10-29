/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"
#include "town/person/object.h"

extern u8 D_800D53C4[];
extern u8 D_800D53CC[];
extern u8 D_800D53F4[];
extern u8 D_800D53F8[];


/* Calls func_800C3050 with actor, 0x16, D_800D53F4, D_800D53F8, D_800D53C4, D_800D53CC. */
void configure_actor_slot_22(void *actor, void *unused_position, struct SpriteFrameState *unused_sprite) {
    func_800C3050(actor, 0x16, D_800D53F4, D_800D53F8, D_800D53C4, D_800D53CC);
}
