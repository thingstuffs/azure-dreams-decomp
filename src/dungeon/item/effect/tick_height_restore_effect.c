#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "dungeon/item/effect.h"


/* Decrements an entity's countdown and finalizes it when the countdown expires. */
void tick_height_restore_effect(u16 *entity) {
    s16 remainingTicks;
    u16 *destination;

    remainingTicks = entity[1] - 1;
    entity[1] = remainingTicks;
    if (remainingTicks <= 0) {
        destination = *(u16 **)((u8 *)entity + 0xC);
        destination[0x88 / 2] = entity[4];
        entity[-1] |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        g_dungeon_status.activity_counts.parts.pending_action_count--;
    }
}
