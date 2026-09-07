#include "common.h"

typedef struct S_8196BE48_0_pre {
    u16 unk_00;
} S_8196BE48_0_pre;   /* the 0x2 bytes before obj in func_8196BE48, addressed as obj[-1] */

typedef struct S_8196BE48_0 {
    u8 pad_00[0x2C];
    u16 unk_2C;
    u8 pad_2E[0x6];
    u16 unk_34;
    u8 pad_36[0xA];
    u8 unk_40;
    u8 unk_41;
    u8 pad_42[0xE];
    u16 unk_50;
} S_8196BE48_0;   /* obj in func_8196BE48 */

typedef struct S_8196BE48_1 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_8196BE48_1;   /* arg2 in func_8196BE48 */



extern s16 D_800269B4;
extern s32 D_800814A0;

/* Advance the effect animation, offset its sprite, and mark it expired when its lifetime ends. */
void func_8196BE48(void *effect_data, s32 unused, void *sprite) {
    u8 *effect = effect_data;
    u8 *global_page = (u8 *)&D_800269B4 - 0x69B4;
    u16 frame_ticks;
    u16 frame_index;
    u8 texture_u;

    ((S_8196BE48_0 *)effect)->unk_2C = (u16)(((S_8196BE48_0 *)effect)->unk_2C - 1);
    ((S_8196BE48_1 *)sprite)->unk_1C = (u16)(((S_8196BE48_1 *)sprite)->unk_1C + 0x7C);
    ((S_8196BE48_1 *)sprite)->unk_1E = (u16)(((S_8196BE48_1 *)sprite)->unk_1E + 0x54);
    frame_ticks = ((S_8196BE48_0 *)effect)->unk_34 + 1;
    *(s16 *)(global_page + 0x69B4) = 1;
    ((S_8196BE48_0 *)effect)->unk_34 = frame_ticks;
    if ((s16)frame_ticks == 3) {
        frame_index = ((S_8196BE48_0 *)effect)->unk_50 + 1;
        ((S_8196BE48_0 *)effect)->unk_50 = frame_index;
        if ((s16)frame_index < 7) {
            ((S_8196BE48_0 *)effect)->unk_34 = 0;
            texture_u = ((S_8196BE48_0 *)effect)->unk_40 + 0x18;
            ((S_8196BE48_0 *)effect)->unk_40 = texture_u;
            if ((texture_u & 0xFF) == 0x60) {
                ((S_8196BE48_0 *)effect)->unk_40 = 0;
                ((S_8196BE48_0 *)effect)->unk_41 = (u8)(((S_8196BE48_0 *)effect)->unk_41 + 0x20);
            }
        }
    }
    if ((s16)((S_8196BE48_0 *)effect)->unk_2C <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16)(((S_8196BE48_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
