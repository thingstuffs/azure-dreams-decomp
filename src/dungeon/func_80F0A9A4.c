#include "common.h"

typedef struct S_801721A4_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_801721A4_0;   /* arg3 in func_801721A4 */

typedef struct S_801721A4_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
} S_801721A4_1;   /* arg0 in func_801721A4 */

typedef struct S_801721A4_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} S_801721A4_2;   /* arg2 in func_801721A4 */

typedef struct S_801721A4_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801721A4_3;   /* state in func_801721A4 */



extern void func_80047784(void *, s32, s32);
extern s32 func_800A2BDC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A6D30(void);

extern s16 D_80083228;
extern u8 D_80083460[12];
extern u16 D_80083462;
extern u8 D_80173D88[9];

void func_801721A4(S_801721A4_1 *arg0, void *arg1, S_801721A4_2 *arg2, S_801721A4_0 *arg3)
{
    u8 *state;

    arg3->unk_71 &= 0x7F;
    if (!(D_80083462 & 0x2000) &&
        ((func_800A2BDC(arg3) << 16) == 0)) {
        if (arg3->unk_1C & 0x400) {
            register s32 link ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            link = arg3->unk_14;
            if (link >= 0) {
                arg3->unk_14 = link | 0x80000000;
                arg3->unk_2A.s +=
                    (func_800A6D30() & 7) << 9;
            }
        }

        arg0->unk_9A = 0x17;
        arg0->unk_8C = 0;
        arg0->unk_9B = 0;
        arg0->unk_A6 = 1;
        arg0->unk_96 = 0;

        arg2->unk_14 |= 0xC;
        arg2->unk_12 -= 0x80;
        state = D_80083460;
        ((S_801721A4_3 *)state)->unk_0A++;
        arg3->unk_6D--;
        arg2->unk_2C = D_80173D88;
        arg2->unk_0C = 0xFFFFFF;
        arg2->unk_10 = 0x60;
        func_800A56E0(0x811);
        func_80047784(arg2,
            arg2->unk_2C[
                ((D_80083228 + arg3->unk_2A.u + 0x100) >> 9) & 7],
            0);
    }
}
