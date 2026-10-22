#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800ABB20_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800ABB20_0;   /* arg1 in update_person_effect_fade */

typedef struct S_800ABB20_1 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
    s16 unk_06;
} S_800ABB20_1;   /* arg0 in update_person_effect_fade; pointer addresses record offset 0x2 */

extern void advance_sprite_animation_and_textures(void *primitive);

/* Update effect motion, fade its brightness, and mark it expired when its timer ends. */
void update_person_effect_fade(void *effect_record, S_800ABB20_0 *motion, SpriteFrameState *primitive) {
    u16 ticks_left;
    u8 brightness;

    motion->unk_14 = (s32) (motion->unk_14 + (((S_800ABB20_1 *)((u8 *)effect_record - 0x2))->unk_06 << 0xB));
    ((S_800ABB20_1 *)((u8 *)effect_record - 0x2))->unk_06 = (s16) ((u16) ((S_800ABB20_1 *)((u8 *)effect_record
        - 0x2))->unk_06 + 1);
    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C);
    motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10);
    motion->unk_08 = (s32) (motion->unk_08 + motion->unk_14);
    advance_sprite_animation_and_textures(primitive);
    brightness = primitive->color.c.r;
    if (brightness != 0) {
        brightness = brightness - 0x10;
        primitive->color.c.r = brightness;
        primitive->color.c.b = brightness;
        primitive->color.c.g = brightness;
    }
    ticks_left = ((S_800ABB20_1 *)((u8 *)effect_record - 0x2))->unk_04 - 1;
    ((S_800ABB20_1 *)((u8 *)effect_record - 0x2))->unk_04 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_800ABB20_1 *)((u8 *)effect_record - 0x2))->unk_00 = (u16) (((S_800ABB20_1 *)((u8 *)effect_record
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
