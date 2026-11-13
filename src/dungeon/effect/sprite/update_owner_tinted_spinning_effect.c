#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/effect/sprite.h"



typedef struct S_818BDCE0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818BDCE0_1;   /* v1 in update_owner_tinted_spinning_effect */

typedef struct S_818BDCE0_2 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_818BDCE0_2;   /* arg2 in update_owner_tinted_spinning_effect */

typedef struct S_818BDCE0_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BDCE0_3;   /* arg1 in update_owner_tinted_spinning_effect */




/* Advance effect counters, motion, and rotation, and flag expiry when its timer exceeds the limit. */
void update_owner_tinted_spinning_effect(OwnerTintedEffectBody *effect, S_818BDCE0_3 *motion, S_818BDCE0_2 *rotation)
{
    S_818BDCE0_1 *counter_state;

    counter_state = effect->unk_00;
    counter_state->unk_14++;
    effect->elapsed_ticks = (s16)((u16)effect->elapsed_ticks + 1);
    rotation->unk_1A += 0x300;

    motion->unk_00 += motion->unk_0C;
    motion->unk_04 += motion->unk_10;
    motion->unk_08 += motion->unk_14;

    if (effect->elapsed_ticks > effect->unk_14) {
        NODE_HEADER(effect)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
