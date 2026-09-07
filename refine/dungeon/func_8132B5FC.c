#include "common.h"

typedef struct S_80172DFC_0_pre {
    u16 unk_00;
} S_80172DFC_0_pre;   /* the 0x2 bytes before arg0 in func_80172DFC, addressed as arg0[-1] */

typedef struct S_80172DFC_0 {
    u8 pad_00[0x16];
    u16 unk_16;
    u16 unk_18;
    u8 pad_1A[0x3E];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    s32 unk_6C;
} S_80172DFC_0;   /* arg0 in func_80172DFC */

typedef struct S_80172DFC_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80172DFC_1;   /* arg1 in func_80172DFC */

typedef struct S_80172DFC_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80172DFC_2;   /* arg2 in func_80172DFC */



extern void func_800478B8(void *);
extern s32 D_800814A0[3];

/* Advance effect motion and animation, and flag completion when its lifetime ends. */
void func_80172DFC(void *effect, S_80172DFC_1 *position, S_80172DFC_2 *animation) {
    u16 frame_count;
    u16 remaining_ticks;

    ((S_80172DFC_0 *)effect)->unk_58 = ((S_80172DFC_0 *)effect)->unk_58 + ((S_80172DFC_0 *)effect)->unk_64;
    ((S_80172DFC_0 *)effect)->unk_5C = ((S_80172DFC_0 *)effect)->unk_5C + ((S_80172DFC_0 *)effect)->unk_68;
    ((S_80172DFC_0 *)effect)->unk_60 = ((S_80172DFC_0 *)effect)->unk_60 + ((S_80172DFC_0 *)effect)->unk_6C;
    position->unk_00 = position->unk_00 + ((S_80172DFC_0 *)effect)->unk_58;
    position->unk_04 = position->unk_04 + ((S_80172DFC_0 *)effect)->unk_5C;
    position->unk_08 = position->unk_08 + ((S_80172DFC_0 *)effect)->unk_60;
    frame_count = ((S_80172DFC_0 *)effect)->unk_18 + 1;
    ((S_80172DFC_0 *)effect)->unk_18 = frame_count;
    if (!(frame_count & 1)) {
        func_800478B8(animation);
    }
    animation->unk_1C = animation->unk_1C + 0x28;
    animation->unk_1E = animation->unk_1E + 0x28;
    remaining_ticks = ((S_80172DFC_0 *)effect)->unk_16 - 1;
    ((S_80172DFC_0 *)effect)->unk_16 = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        ((S_80172DFC_0_pre *)effect)[-1].unk_00 = ((S_80172DFC_0_pre *)effect)[-1].unk_00 | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
    if (animation->unk_14 & 0x8000) {
        ((S_80172DFC_0_pre *)effect)[-1].unk_00 = ((S_80172DFC_0_pre *)effect)[-1].unk_00 | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
