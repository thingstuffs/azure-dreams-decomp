#include "dungeon/effect/particle/advance_object_spawning_displays_high.h"
#include "shared/object_flags.h"






// Decrease position and timer, setting entity and global flags when the timer expires.
void func_80024734(Entity *entity, State *state)
{
    s16 remainingTimer;

    state->position -= 0x18000;
    D_8002571C = 1;
    remainingTimer = entity->timer - 8;
    entity->timer = remainingTimer;
    if (remainingTimer <= 0) {
        ((u16 *)entity)[-1] |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
