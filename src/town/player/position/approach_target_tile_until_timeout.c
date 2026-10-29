#include "common.h"
#include "town/player.h"
#include "town/player/action_initializers.h"
#include "town/player/position.h"

typedef struct S_800935BC_0 {
    s32 unk_00;
    s32 unk_04;
} S_800935BC_0;   /* arg1 in approach_target_tile_until_timeout */


/* Move the fixed-point position halfway toward the target and advance when the countdown expires. */
void approach_target_tile_until_timeout(Rec_func_80094268_arg0 *target, S_800935BC_0 *position, void *transition_arg) {
    s16 ticks_left;

    position->unk_00 = ((s32) ((s16)target->unk_30 << 0x10) + position->unk_00) / 2;
    position->unk_04 = ((s32) ((s16)target->unk_32 << 0x10) + position->unk_04) / 2;
    ticks_left = target->unk_0A.as_u16 - 1;
    target->unk_0A.as_u16 = ticks_left;
    if (ticks_left < 0) {
        initialize_scene_action_record(target, position, transition_arg);
    }
}
