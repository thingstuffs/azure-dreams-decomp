#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "dungeon/effect/mesh.h"
#include "slus.h"
#include "shared/dungeon_effect_state.h"

/*
 * Increments the linked object's counter and advances sprite animation; flags removal when the
 * sprite reports 0x6000.
 */
void update_owner_linked_sprite_effect(OwnerLinkedSpriteEffectBody *object_slot, ObjectPosition *unused, SpriteFrameState *state) {
    B22_81893474_EffectState *object;

    object = object_slot->owner;
    object->z.u += 1;
    advance_sprite_animation_and_textures(state);
    if (state->flags & 0x6000) {
        *(u16 *)((u8 *)object_slot - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
