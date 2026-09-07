#include "common.h"

typedef struct S_818BD0C0_0_pre {
    u16 unk_00;
} S_818BD0C0_0_pre;   /* the 0x2 bytes before arg0 in func_818BD0C0, addressed as arg0[-1] */

typedef struct S_818BD0C0_0 {
    void * unk_00;
    u16 unk_04;
    u16 unk_06;
} S_818BD0C0_0;   /* arg0 in func_818BD0C0 */

typedef struct S_818BD0C0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818BD0C0_1;   /* p in func_818BD0C0 */

typedef struct S_818BD0C0_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_818BD0C0_2;   /* arg2 in func_818BD0C0 */



extern void func_800249AC(void) __attribute__((noreturn));
extern void func_8003DB94();
extern void func_800478B8();
extern u8 D_80025E04[];
extern s32 D_800814A0[3];

void func_818BD0C0(void *arg0, s32 arg1, S_818BD0C0_2 *arg2)
{
    S_818BD0C0_1 *p;
    u16 n;

    p = ((S_818BD0C0_0 *)arg0)->unk_00;
    p->unk_14++;
    ((S_818BD0C0_0 *)arg0)->unk_06++;
    func_800478B8(arg2);

    if (arg2->unk_14 & 0x6000) {
        n = ((S_818BD0C0_0 *)arg0)->unk_04 + 1;
        ((S_818BD0C0_0 *)arg0)->unk_04 = n;
        if ((s16)n >= 3) {
            ((S_818BD0C0_0_pre *)arg0)[-1].unk_00 |= 0x8000;
            D_800814A0[0] = (u32)(D_800814A0[0] | 0x8000);
            func_800249AC();
        }

        func_8003DB94(arg2, D_80025E04, 0);
        if (arg2->unk_0C != 0) {
            arg2->unk_0C = 0;
            arg2->unk_0D = 0x80;
            func_800249AC();
        }
        if (arg2->unk_0D != 0) {
            arg2->unk_0D = 0;
            arg2->unk_0E = 0x80;
            func_800249AC();
        }
        arg2->unk_0E = 0;
        arg2->unk_0C = 0x80;
    }
}
