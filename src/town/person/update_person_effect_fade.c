#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "slus.h"
#include "town/person.h"


typedef struct S_800ABB20_1 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
    s16 unk_06;
} S_800ABB20_1;   /* arg0 in update_person_effect_fade; pointer addresses record offset 0x2 */

/* Update effect motion, fade its brightness, and mark it expired when its timer ends. */
void update_person_effect_fade(void *effect_record, ObjectPosition *motion, SpriteFrameState *primitive) {
    u16 ticks_left;
    u8 brightness;

    motion->velocity_z = (s32) (motion->velocity_z + (((S_800ABB20_1 *)((u8 *)effect_record - 0x2))->unk_06 << 0xB));
    ((S_800ABB20_1 *)((u8 *)effect_record - 0x2))->unk_06 = (s16) ((u16) ((S_800ABB20_1 *)((u8 *)effect_record
        - 0x2))->unk_06 + 1);
    motion->x.v = (s32) (motion->x.v + motion->velocity_x);
    motion->y.v = (s32) (motion->y.v + motion->velocity_y);
    motion->z.v = (s32) (motion->z.v + motion->velocity_z);
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
