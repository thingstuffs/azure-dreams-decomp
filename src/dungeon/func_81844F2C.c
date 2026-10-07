#include "common.h"

typedef struct S_81844F2C_0_pre {
    u16 unk_00;
} S_81844F2C_0_pre;   /* the 0x2 bytes before base in func_8002472C, addressed as base[-1] */

typedef struct S_81844F2C_0 {
    void * unk_00;
    u16 unk_04;
    union { u16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x4];
    u16 unk_0C;
    u16 unk_0E;
    u8 pad_10[0x1A];
    union { u16 s; u16 u; s16 p; } unk_2A;   /* accessed as both */
    union { u16 s; s16 u; u16 p; } unk_2C;   /* accessed as both */
} S_81844F2C_0;   /* base in func_8002472C */

typedef struct S_81844F2C_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_81844F2C_1;   /* entity in func_8002472C */

typedef struct S_81844F2C_4 {
    u8 pad_00[0x14A0];
    u32 unk_14A0;
} S_81844F2C_4;   /* page in func_8002472C */



/* Updates an effect_base's position, colors, countdown, and completion flags. */
void func_8002472C(s32 effect_or_count) {
    S_81844F2C_0 *effect;
    u32 *cursor;
    s32 i;
    u16 saved;
    u32 position;
    u32 step;
    s32 state;
    u8 *page;

    ASM_KEEP(effect_or_count);
    effect = (S_81844F2C_0 *)effect_or_count;
    page = effect->unk_00;
    ((S_81844F2C_1 *)page)->unk_52 |= 0x8000;
    position = effect->unk_04;
    step = effect->unk_0C;
    effect_or_count = effect->unk_2A.s;
    position += step;
    effect->unk_04 = position;
    position = effect->unk_06.s;
    step = effect->unk_0E;
    saved = effect->unk_2C.s;
    position += step;
    state = effect->unk_2C.u;
    effect_or_count -= 1;
    effect->unk_2A.u = effect_or_count;
    effect->unk_06.u = position;
    switch (state) {
    case 0:
        effect_or_count = 7 - (s16)effect_or_count;
        if (effect_or_count < 5) {
            ((u32 *)((u8 *)effect + 0x14))[effect_or_count] = 0x00808080;
        } else {
            for (i = 4; i >= 0; i--) {
                ((u32 *)((u8 *)effect + 0x14))[i] += 0xFFDFDFE0;
            }
        }
        if (effect->unk_2A.p > 0) {
            return;
        }
        effect->unk_2A.s = 3;
        effect->unk_2C.p += 1;
        return;
    case 1:
        if ((effect_or_count << 16) > 0) {
            return;
        }
        effect->unk_2C.p = saved + 1;
        return;
    case 2:
        ((S_81844F2C_0_pre *)effect)[-1].unk_00 |= 0x8000;
        page = (u8 *)0x80080000;
        ((S_81844F2C_4 *)page)->unk_14A0 |= 0x8000;
    }
}
