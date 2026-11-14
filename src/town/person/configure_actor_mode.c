#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "town/person.h"


extern M2C_UNK D_800D5624[];
extern M2C_UNK D_800D562C[];
extern M2C_UNK D_800D5654[];
extern M2C_UNK D_800D5658[];

/* Configure the actor with mode 13 and its associated tables, then set its state flag. */
void configure_actor_mode_13(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite) {
    register_object_slot_with_tables(actor, 0xD, D_800D5654, D_800D5658, D_800D5624, D_800D562C);
    actor->unk_70 = 1;
}
