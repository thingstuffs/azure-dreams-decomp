#include "common.h"
#include "m2c_compat.h"
#include "shared/object_links.h"

   /* the 0x2 bytes before arg0 in advance_effect_and_reduce_scale, addressed as arg0[-1] */

typedef struct S_80814CC4_0 {
    void * unk_00;
    s32 unk_04;
} S_80814CC4_0;   /* arg0 in advance_effect_and_reduce_scale */

typedef struct S_80814CC4_1 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_80814CC4_1;   /* arg1 in advance_effect_and_reduce_scale */

typedef struct S_80814CC4_2 {
    u8 pad_00[0x58];
    u16 unk_58;
} S_80814CC4_2;

typedef struct S_80814CC4_3 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80814CC4_3;   /* arg2 in advance_effect_and_reduce_scale */


extern s32 scene_object_flags;

/* Advance motion and reduce scale, marking the effect complete at the scale threshold. */
void advance_effect_and_reduce_scale(void *effect, void *motion, void *scale) {
    ObjectStatusPrefix16 *effect_view = effect;
    u16 *flags;
    u16 next_scale;
    void *object;

    object = ((S_80814CC4_0 *)effect)->unk_00;
    ((S_80814CC4_1 *)motion)->unk_00 = (s32) (((S_80814CC4_1 *)motion)->unk_00 + ((S_80814CC4_0 *)effect)->unk_04);
    ((S_80814CC4_1 *)motion)->unk_04 = (s32) (((S_80814CC4_1 *)motion)->unk_04 + ((S_80814CC4_1 *)motion)->unk_10);
    ((S_80814CC4_2 *)object)->unk_58 = (u16) (((S_80814CC4_2 *)object)->unk_58 | 1);
    next_scale = ((S_80814CC4_3 *)scale)->unk_1E - 0x100;
    ((S_80814CC4_3 *)scale)->unk_1C = next_scale;
    ((S_80814CC4_3 *)scale)->unk_1E = next_scale;
    if ((u16) ((S_80814CC4_3 *)scale)->unk_1C < 0x201U) {
        ((S_80814CC4_2 *)object)->unk_58 = (u16) (((S_80814CC4_2 *)object)->unk_58 & 0xFFFE);
        flags = &effect_view[-1].unk_00;
        *flags = (u16) (effect_view[-1].unk_00 | 0x8000);
        scene_object_flags |= 0x8000;
    }
}
