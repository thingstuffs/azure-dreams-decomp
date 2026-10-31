#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "slus.h"
#include "dungeon/effect/sprite.h"

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





/* Copy stored values, run the update, and flag completion when the count reaches zero. */
void update_effect_countdown(void *object_arg, MovingPosition *output, void *update_arg) {
    S_800D6FEC_0 *object = object_arg;
    u16 remaining;
    MovingPosition *source;

    source = object->unk_B0;
    output->x = (u16) source->x;
    output->y = (u16) source->y;
    output->z = (u16) source->z;
    advance_sprite_animation_and_textures(update_arg);
    remaining = object->unk_96 - 1;
    object->unk_96 = remaining;
    if ((remaining << 0x10) <= 0) {
        ((S_800D6FEC_0_pre *)object)[-1].unk_00 = (u16) (((S_800D6FEC_0_pre *)object)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
