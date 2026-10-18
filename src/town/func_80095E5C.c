#include "common.h"

typedef struct S_800935BC_0 {
    s32 unk_00;
    s32 unk_04;
} S_800935BC_0;   /* arg1 in approach_target_tile_until_timeout */

typedef struct S_800935BC_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0x24];
    s16 unk_30;
    s16 unk_32;
} S_800935BC_1;   /* arg0 in approach_target_tile_until_timeout */


extern void initialize_scene_action_record(S_800935BC_1 *);

/* Move the fixed-point position halfway toward the target and advance when the countdown expires. */
void approach_target_tile_until_timeout(S_800935BC_1 *target, S_800935BC_0 *position, s32 transition_arg) {
    s16 ticks_left;

    position->unk_00 = (s32) (((s32) (target->unk_30 << 0x10) + position->unk_00) / 2);
    position->unk_04 = (s32) (((s32) (target->unk_32 << 0x10) + position->unk_04) / 2);
    ticks_left = target->unk_0A - 1;
    target->unk_0A = ticks_left;
    if (ticks_left < 0) {
        initialize_scene_action_record(target);
    }
}
