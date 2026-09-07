#include "common.h"

typedef struct S_80173C40_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80173C40_0;   /* state in func_80173C40 */

typedef struct S_80173C40_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
} S_80173C40_1;   /* arg3 in func_80173C40 */

typedef struct S_80173C40_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_80173C40_2;   /* arg0 in func_80173C40 */



extern void func_80047784();
extern s32 func_800A2BDC();

extern s16 D_80083228;
extern u8 D_80083460[12];
extern u8 D_80176670[16];

void func_80173C40(void *arg0, void *arg1, void *arg2, void *arg3) {
    u8 *state = D_80083460;

    if (((S_80173C40_0 *)state)->unk_02 & 0x2000) {
        ((S_80173C40_1 *)arg3)->unk_71 &= 0x7F;
        return;
    }

    if ((func_800A2BDC(arg3) << 16) == 0) {
        s32 index;

        ((S_80173C40_2 *)arg0)->unk_9A = 0x17;
        ((S_80173C40_2 *)arg0)->unk_9B = 0;
        ((S_80173C40_2 *)arg0)->unk_8C = 0;
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80176670;

        index = ((D_80083228 + ((S_80173C40_1 *)arg3)->unk_2A + 0x100) >> 9) & 7;
        func_80047784(arg2, D_80176670[index], 0);

        ((S_80173C40_2 *)arg0)->unk_96 = 0;
        ((S_80173C40_1 *)arg3)->unk_1C |= 0x10000000;
        ((S_80173C40_0 *)state)->unk_0A++;
        ((S_80173C40_1 *)arg3)->unk_46 &= 0x7FFF;
    }
}
