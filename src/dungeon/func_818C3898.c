#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_818C3898_0_pre {
    u16 unk_00;
} S_818C3898_0_pre;   /* the 0x2 bytes before arg0 in func_818C3898, addressed as arg0[-1] */

typedef struct S_818C3898_0 {
    void * unk_00;
    u8 pad_04[0xC];
    u16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
} S_818C3898_0;   /* arg0 in func_818C3898 */

typedef struct S_818C3898_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_818C3898_1;   /* temp_v1 in func_818C3898 */


typedef struct S_818C3898_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818C3898_3;   /* temp_arg1 in func_818C3898 */

typedef struct S_818C3898_4 {
    s32 unk_00;
} S_818C3898_4;   /* temp_d in func_818C3898 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800814A0[3];
extern void func_800478B8(void *arg0);
/* Advance effect motion, color, rotation, and size, and flag lifetime expiration. */
void func_818C3898(void *effect, void *motion_data, Rec_D_80082E80 *sprite) {
    s16 size;
    s32 color_step;
    s32 color_index;
    s32 quarter_bias;
    s32 half_color;
    u16 frame;
    S_818C3898_1 *owner;
    S_818C3898_3 *motion;
    s32 *global_flags;

    owner = ((S_818C3898_0 *)effect)->unk_00;
    motion = motion_data;
    owner->unk_0C = (u16) (owner->unk_0C + 1);
    frame = ((S_818C3898_0 *)effect)->unk_10;
    frame = (u16) (frame + 1);
    color_step = (s16) frame;
    ((S_818C3898_0 *)effect)->unk_10 = frame;
    color_step = color_step % 7;
    color_step += 1;
    func_800478B8(sprite);
    color_index = (s16) color_step;
    sprite->unk_1A.as_u16 = (u16) (sprite->unk_1A.as_u16 + 0x300);
    quarter_bias = color_index;
    if (color_index < 0) {
        quarter_bias = color_index + 3;
    }
    half_color = (s32) (color_index + ((u32) (color_step << 0x10) >> 0x1F)) >> 1;
    sprite->unk_0C.at00_s8.v = (s8) ((quarter_bias >> 2) << 7);
    sprite->unk_0C.at01_s8.v = (s8) ((s32) (((s16) half_color - (((s32) ((s16) half_color + ((u32) (half_color << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9);
    sprite->unk_0C.at02_s8.v = (s8) ((s32) ((color_index - (half_color * 2)) << 0x10) >> 9);
    size = (0x1400 / (s16) ((S_818C3898_0 *)effect)->unk_14) * (s16) ((S_818C3898_0 *)effect)->unk_10;
    sprite->unk_1C.at02_s16.v = size;
    sprite->unk_1C.at00_s16.v = size;
    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C);
    motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10);
    motion->unk_08 = (s32) (motion->unk_08 + motion->unk_14);
    if ((s16) ((S_818C3898_0 *)effect)->unk_10 > ((S_818C3898_0 *)effect)->unk_14) {
        ((S_818C3898_0_pre *)effect)[-1].unk_00 = (u16) (((S_818C3898_0_pre *)effect)[-1].unk_00 | 0x8000);
        global_flags = D_800814A0;
        ((S_818C3898_4 *)global_flags)->unk_00 = (s32) (((S_818C3898_4 *)global_flags)->unk_00 | 0x8000);
    }
}
