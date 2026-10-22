#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
void advance_sprite_animation_and_textures(void *entity);                      /* extern */
typedef struct S_800CB374_0_pre {
    u16 unk_00;
} S_800CB374_0_pre;   /* the 0x2 bytes before arg0 in fade_effect_primitive, addressed as arg0[-1] */

typedef struct S_800CB374_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
    u8 pad_AC[0x8];
    s16 unk_B4;
} S_800CB374_0;   /* arg0 in fade_effect_primitive */

typedef struct S_800CB374_2 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_800CB374_2;

typedef struct S_800CB374_3 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
    u8 pad_20[0xAC];
    s32 unk_CC;
} S_800CB374_3;   /* ((S_800CB374_0 *)arg0)->unk_A8 in fade_effect_primitive */

/* Fades primitive colors or copies source attributes and propagates completion flags. */
void fade_effect_primitive(void *effect, void *unused, SpriteFrameState *primitive) {
    s16 fade_steps;
    u8 blue;
    S_800CB374_2 *source_primitive;

    advance_sprite_animation_and_textures(primitive);
    if (((S_800CB374_0 *)effect)->unk_B4 != 0) {
        primitive->color.c.r = (u8) (primitive->color.c.r
            - ((s32) primitive->color.c.r / (s16) ((S_800CB374_0 *)effect)->unk_96));
        primitive->color.c.g = (u8) (primitive->color.c.g
            - ((s32) primitive->color.c.g / (s16) ((S_800CB374_0 *)effect)->unk_96));
        blue = primitive->color.c.b - ((s32) primitive->color.c.b / (s16) ((S_800CB374_0 *)effect)->unk_96);
        primitive->color.c.b = blue;
        primitive->unk_06 = (u16) (*(u16 *)&primitive->unk_06 - 1);
        fade_steps = (u16) ((S_800CB374_0 *)effect)->unk_96 - 1;
        ((S_800CB374_0 *)effect)->unk_96 = fade_steps;
        if ((fade_steps << 0x10) > 0) {
            return;
        }
    } else {
        primitive->color.word = ((S_800CB374_3 *)(((S_800CB374_0 *)effect)->unk_A8))->unk_CC;
        source_primitive = ((S_800CB374_3 *)(((S_800CB374_0 *)effect)->unk_A8))->unk_0C;
        primitive->scale_x = (u16) source_primitive->unk_1C;
        primitive->scale_y = (u16) source_primitive->unk_1E;
        if (!(((S_800CB374_3 *)(((S_800CB374_0 *)effect)->unk_A8))->unk_1E & 0x8000)) {
            return;
        }
    }
    ((S_800CB374_0_pre *)effect)[-1].unk_00 = (u16) (((S_800CB374_0_pre *)effect)[-1].unk_00 | 0x8000);
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}
