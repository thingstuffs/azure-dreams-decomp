#include "common.h"
#include "shared/object_flags.h"


typedef struct S_80026E3C_0_pre {
    u16 unk_00;
} S_80026E3C_0_pre;   /* the 0x2 bytes before arg0 in alternate_effect_shade_and_decay, addressed as arg0[-1] */

typedef struct S_80026E3C_0 {
    u8 pad_00[0x66];
    u16 unk_66;
    u16 unk_68;
    union { u8 u8; u16 u16; } unk_6A;   /* accessed as both */
} S_80026E3C_0;   /* arg0 in alternate_effect_shade_and_decay */

typedef struct S_80026E3C_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_80026E3C_1;   /* arg2 in alternate_effect_shade_and_decay */



/* Alternate the effect shade, decay its intensity, and flag expiration. */
void alternate_effect_shade_and_decay(void *effect, s32 ticks_left, S_80026E3C_1 *color)
{
    u16 frame;
    u16 intensity;
    u32 shade;
    s32 decay;

    frame = ((S_80026E3C_0 *)effect)->unk_68 + 1;
    ((S_80026E3C_0 *)effect)->unk_68 = frame;
    if (frame & 1) {
        shade = ((S_80026E3C_0 *)effect)->unk_6A.u8;
    } else {
        shade = ((S_80026E3C_0 *)effect)->unk_6A.u16 >> 3;
    }
    color->unk_0E = (s8) shade;
    color->unk_0D = (s8) shade;
    color->unk_0C = (s8) shade;
    intensity = ((S_80026E3C_0 *)effect)->unk_6A.u16;
    decay = (s16)intensity >> 4;
    ((S_80026E3C_0 *)effect)->unk_6A.u16 = intensity - decay;
    ticks_left = ((S_80026E3C_0 *)effect)->unk_66 - 1;
    ((S_80026E3C_0 *)effect)->unk_66 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_80026E3C_0_pre *)effect)[-1].unk_00 =
            (u16)(((S_80026E3C_0_pre *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32)(object_flag_block.flags | 0x8000);
    }
}
