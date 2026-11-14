/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"
#include "town/person/object.h"

extern u8 D_800D57E8[];
extern u8 D_800D57F0[];
extern u8 D_800D5818[];
extern u8 D_800D581C[];


/* Calls func_800C3050 with actor, 0x20, D_800D5818, D_800D581C, D_800D57E8, D_800D57F0. */
void configure_actor_slot_32(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite) {
    register_object_slot_with_tables(actor, 0x20, D_800D5818, D_800D581C, D_800D57E8, D_800D57F0);
}
