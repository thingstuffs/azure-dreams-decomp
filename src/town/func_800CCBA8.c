#include "common.h"


extern void func_800C4174(void *arg0, void *arg1, s32 arg2);
extern void func_800CA3D4(void);


typedef struct S_800CA308_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u8 pad_6E[0x16];
    u16 unk_84;
    u16 unk_86;
} S_800CA308_0;   /* arg0 in func_800CA308 */

typedef struct S_800CA308_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CA308_1;   /* arg1 in func_800CA308 */

void func_800CA308(S_800CA308_0 *arg0, S_800CA308_1 *arg1, s32 arg2) {
    s32 delta;
    s32 delta2;
    s32 delta3;
    u16 timer;

    timer = arg0->unk_6C - 1;
    arg0->unk_6C = timer;
    if ((timer << 16) <= 0) {
        func_800C4174(arg0, arg1, arg2);
        arg1->unk_02 = arg0->unk_84;
        arg1->unk_06 = arg0->unk_86;
        arg1->unk_0A = 0;
        func_800CA3D4();
        return;
    }

    delta = (s16)arg0->unk_84 -
            (s16)arg1->unk_02;
    if (delta < 0) {
        delta += 7;
    }
    arg1->unk_02 =
        (u16)(arg1->unk_02 + (delta >> 3));

    delta2 = (s16)arg0->unk_86 - arg1->unk_06;
    if (delta2 < 0) {
        delta2 += 7;
    }
    arg1->unk_06 =
        (s16)((u16)arg1->unk_06 + (delta2 >> 3));

    delta3 = -arg1->unk_0A;
    if (delta3 < 0) {
        delta3 += 7;
    }
    arg1->unk_0A =
        (s16)((u16)arg1->unk_0A + (delta3 >> 3));
}
