#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_800D6FEC_0_pre {
    u16 unk_00;
} S_800D6FEC_0_pre;   /* the 0x2 bytes before arg0 in update_effect_countdown, addressed as arg0[-1] */

typedef struct S_800D6FEC_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x18];
    void * unk_B0;
} S_800D6FEC_0;   /* arg0 in update_effect_countdown */

   /* arg1 in update_effect_countdown */




void advance_sprite_animation_and_textures();                     /* extern */

/* Copy stored values, run the update, and flag completion when the count reaches zero. */
void update_effect_countdown(void *object, MovingPosition *output, M2C_UNK update_arg) {
    u16 remaining;
    MovingPosition *source;

    source = ((S_800D6FEC_0 *)object)->unk_B0;
    output->unk_02 = (u16) source->unk_02;
    output->unk_06 = (u16) source->unk_06;
    output->unk_0A = (u16) source->unk_0A;
    advance_sprite_animation_and_textures(update_arg);
    remaining = ((S_800D6FEC_0 *)object)->unk_96 - 1;
    ((S_800D6FEC_0 *)object)->unk_96 = remaining;
    if ((remaining << 0x10) <= 0) {
        ((S_800D6FEC_0_pre *)object)[-1].unk_00 = (u16) (((S_800D6FEC_0_pre *)object)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
