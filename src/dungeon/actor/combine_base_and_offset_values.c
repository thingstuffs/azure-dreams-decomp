#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "m2c_compat.h"
#include "dungeon/actor.h"

typedef struct S_800B06C0_0 {
    u8 pad_00[0xB8];
    u16 unk_B8;
    u16 unk_BA;
    u8 pad_BC[0x4];
    s32 unk_C0;
} S_800B06C0_0;   /* arg2 in combine_base_and_offset_values */



/* Copy two base values and combine the base and offset into the output. */
void combine_base_and_offset_values(ObjectPosition *base_values, SpriteFrameState *offset_values, S_800B06C0_0 *output) {
    output->unk_B8 = (u16) base_values->x.unsigned_parts.integer;
    output->unk_BA = (u16) base_values->y.unsigned_parts.integer;
    output->unk_C0 = (s32) (base_values->z.w.i + offset_values->unk_04);
}
