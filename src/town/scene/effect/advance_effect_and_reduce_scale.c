#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "town/scene/effect.h"

   /* the 0x2 bytes before arg0 in advance_effect_and_reduce_scale, addressed as arg0[-1] */

typedef struct S_80814CC4_0 {
    void * unk_00;
    s32 unk_04;
} S_80814CC4_0;   /* arg0 in advance_effect_and_reduce_scale */


typedef struct S_80814CC4_2 {
    u8 pad_00[0x58];
    u16 unk_58;
} S_80814CC4_2;


extern s32 scene_object_flags;

/* Advance motion and reduce scale, marking the effect complete at the scale threshold. */
void advance_effect_and_reduce_scale(void *effect, ObjectPosition *motion, SpriteFrameState *scale) {
    ObjectStatusPrefix16 *effect_view = effect;
    u16 *flags;
    u16 next_scale;
    S_80814CC4_2 *object;

    object = ((S_80814CC4_0 *)effect)->unk_00;
    ((ObjectPosition *)motion)->x.v = (s32) (((ObjectPosition *)motion)->x.v + ((S_80814CC4_0 *)effect)->unk_04);
    ((ObjectPosition *)motion)->y.v = (s32) (((ObjectPosition *)motion)->y.v + ((ObjectPosition *)motion)->velocity_y);
    object->unk_58 = (u16) (object->unk_58 | 1);
    next_scale = ((SpriteFrameState *)scale)->scale_y - 0x100;
    ((SpriteFrameState *)scale)->scale_x = next_scale;
    ((SpriteFrameState *)scale)->scale_y = next_scale;
    if ((u16) ((SpriteFrameState *)scale)->scale_x < 0x201U) {
        object->unk_58 = (u16) (object->unk_58 & 0xFFFE);
        flags = &effect_view[-1].flags;
        *flags = (u16) (effect_view[-1].flags | 0x8000);
        scene_object_flags |= 0x8000;
    }
}
