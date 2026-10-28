#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"

extern u8 D_800D517C[];
extern u8 D_800D5184[];
extern u8 D_800D51AC[];
extern u8 D_800D51B0[];

/* Configure the actor with type 0x30 and its data tables. */
void init_actor_slot_30(void *actor, void *unused_position, struct SpriteFrameState *unused_sprite) {
    initialize_object_and_register_slot(actor, 0x30, D_800D51AC, D_800D51B0, D_800D517C, D_800D5184);
}
