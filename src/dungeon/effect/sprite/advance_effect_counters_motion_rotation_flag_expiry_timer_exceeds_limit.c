#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/effect/sprite.h"

typedef struct S_818BDCE0_0_pre {
    u16 unk_00;
} S_818BDCE0_0_pre;   /* the 0x2 bytes before arg0 in advance_effect_counters_motion_rotation_flag_expiry_timer_exceeds_limit, addressed as arg0[-1] */


typedef struct S_818BDCE0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818BDCE0_1;   /* v1 in advance_effect_counters_motion_rotation_flag_expiry_timer_exceeds_limit */

typedef struct S_818BDCE0_2 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_818BDCE0_2;   /* arg2 in advance_effect_counters_motion_rotation_flag_expiry_timer_exceeds_limit */

typedef struct S_818BDCE0_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BDCE0_3;   /* arg1 in advance_effect_counters_motion_rotation_flag_expiry_timer_exceeds_limit */




/* Advance effect counters, motion, and rotation, and flag expiry when its timer exceeds the limit. */
void advance_effect_counters_motion_rotation_flag_expiry_timer_exceeds_limit(OwnerTintedEffectBody *effect, S_818BDCE0_3 *motion, S_818BDCE0_2 *rotation)
{
    S_818BDCE0_1 *counter_state;

    counter_state = effect->unk_00;
    counter_state->unk_14++;
    effect->unk_10.s++;
    rotation->unk_1A += 0x300;

    motion->unk_00 += motion->unk_0C;
    motion->unk_04 += motion->unk_10;
    motion->unk_08 += motion->unk_14;

    if (effect->unk_10.u > effect->unk_14) {
        ((S_818BDCE0_0_pre *)effect)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
