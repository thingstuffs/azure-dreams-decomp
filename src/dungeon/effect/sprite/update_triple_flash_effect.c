#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_818BD0C0_0_pre {
    u16 unk_00;
} S_818BD0C0_0_pre;   /* the 0x2 bytes before arg0 in update_triple_flash_effect, addressed as arg0[-1] */

typedef struct S_818BD0C0_0 {
    void * unk_00;
    u16 unk_04;
    u16 unk_06;
} S_818BD0C0_0;   /* arg0 in update_triple_flash_effect */

typedef struct S_818BD0C0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818BD0C0_1;   /* p in update_triple_flash_effect */

extern void select_record_entry_and_value();
extern void advance_sprite_animation_and_textures();
extern u8 D_80025E04[];

/* Update state counters and cycle the primitive color for up to three flagged updates. */
void update_triple_flash_effect(void *state, s32 unused, SpriteFrameState *primitive)
{
    S_818BD0C0_1 *shared_state;
    u16 cycle_count;

    shared_state = ((S_818BD0C0_0 *)state)->unk_00;
    shared_state->unk_14++;
    ((S_818BD0C0_0 *)state)->unk_06++;
    advance_sprite_animation_and_textures(primitive);

    if (primitive->flags & 0x6000) {
        cycle_count = ((S_818BD0C0_0 *)state)->unk_04 + 1;
        ((S_818BD0C0_0 *)state)->unk_04 = cycle_count;
        if ((s16)cycle_count >= 3) {
            ((S_818BD0C0_0_pre *)state)[-1].unk_00 |= 0x8000;
            object_flag_block.flags = (u32)(object_flag_block.flags | 0x8000);
            return;
        }

        select_record_entry_and_value(primitive, D_80025E04, 0);
        if (primitive->color.c.r != 0) {
            primitive->color.c.r = 0;
            primitive->color.c.g = 0x80;
            return;
        }
        if (primitive->color.c.g != 0) {
            primitive->color.c.g = 0;
            primitive->color.c.b = 0x80;
            return;
        }
        primitive->color.c.b = 0;
        primitive->color.c.r = 0x80;
    }
}
