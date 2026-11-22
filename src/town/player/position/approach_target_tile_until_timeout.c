#include "common.h"
#include "town/player.h"
#include "town/player/action_initializers.h"
#include "town/player/position.h"

/* Move the fixed-point position halfway toward the target and advance when the countdown expires. */
void approach_target_tile_until_timeout(TownObjectRecord *target, ObjectPosition *position, struct SpriteFrameState *sprite) {
    s16 ticks_left;

    position->x.v = (((s16)target->unk_30 << 0x10) + position->x.v) / 2;
    position->y.v = (((s16)target->unk_32 << 0x10) + position->y.v) / 2;
    ticks_left = target->unk_0A - 1;
    target->unk_0A = ticks_left;
    if (ticks_left < 0) {
        initialize_scene_action_record(target, position, sprite);
    }
}
