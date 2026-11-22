#include "common.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"
#include "shared/dungeon_delay_views.h"
#include "town/person/motion.h"
#include "town/menu/indexed_effect_vectors_g00583.h"

   /* arg1 in move_motion_value_halfway_toward */

/* Move the motion value halfway toward the target sum and switch callbacks when the countdown expires. */
void move_motion_value_halfway_toward(TownObjectRecord *actor, ObjectPosition *motion) {
    s32 current_value;
    u16 ticks_left;

    current_value = motion->z.v;
    motion->z.v = (s32) (current_value + ((s32) ((view_reference_entity.z.v + town_target_height_offset) - current_value) / 2));
    ticks_left = actor->timer - 1;
    actor->timer = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        actor->handler = &move_coordinates_halfway_toward_target;
    }
}
