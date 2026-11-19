#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "town/event/object.h"
#include "town/menu/indexed_effect_vectors_g00583.h"
#include "town/player/position.h"
#include "town/shop.h"
#include "town/shop/item_lookup.h"

/*
 * Moves halfway toward view_reference_entity with a Z offset of 0x200000 each update. After
 * countdown expiry, when item processing fails, restores the target height and selects the next
 * height-band state.
 */
void move_toward_view_reference(TownObjectRecord *actor, void *context,
                   ObjectPosition *motion, SpriteFrameState *extra)
{
    s32 work[5];
    u32 shifted_z;
    u32 delta_y;
    u16 countdown;

    motion->velocity_x = (s32)((u32)view_reference_entity.x.v - (u32)motion->x.v) / 2;
    delta_y = (u32)view_reference_entity.y.v - (u32)motion->y.v;
    motion->velocity_y = (s32)delta_y / 2;
    shifted_z = (u32)motion->z.v + 0x200000U;
    motion->velocity_z = (s32)((u32)view_reference_entity.z.v - shifted_z) / 2;
    add_motion_deltas_to_position(motion);

    countdown = actor->timer - 1;
    actor->timer = countdown;
    if (((s32)((u32)countdown << 16) <= 0) &&
        (remove_object_if_item_found(actor, context, motion, extra, work) == 0)) {
        motion->z.v = (s32)((u32)view_reference_entity.z.v + (u32)town_target_height_offset);
        select_object_value_by_height_band(actor, context, motion, extra);
    }
}
