#include "common.h"

typedef long long s64;

typedef struct S_80BC1880_0 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_80BC1880_0;   /* arg2 in func_80BC1880 */

typedef struct S_80BC1880_1_pre {
    u16 unk_00;
} S_80BC1880_1_pre;   /* the 0x2 bytes before arg0 in func_80BC1880, addressed as arg0[-1] */

typedef struct S_80BC1880_1 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 pad_05[0x15];
    union { s16 s; u16 u; } unk_1A;   /* accessed as both */
    s16 unk_1C;
} S_80BC1880_1;   /* arg0 in func_80BC1880 */

typedef struct S_80BC1880_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80BC1880_2;   /* arg1 in func_80BC1880 */



extern s32 func_80065420(void *, void *, void *, void *);
extern s32 D_800814A0[3];

typedef struct StackWork {
    u16 xyz[3];
    u16 pad;
    s64 out18;
    s32 out20;
    s32 out24;
} StackWork;

void func_80BC1880(void *arg0, S_80BC1880_2 *arg1, S_80BC1880_0 *arg2)
{
    StackWork work;
    s16 count;

    arg2->unk_1C -= 500;
    arg2->unk_1E -= 500;
    arg2->unk_1A += 400;

    arg2->unk_0C =
        ((S_80BC1880_1 *)arg0)->unk_02 *
        (((S_80BC1880_1 *)arg0)->unk_1C - ((S_80BC1880_1 *)arg0)->unk_1A.s) /
        ((S_80BC1880_1 *)arg0)->unk_1C;
    arg2->unk_0D =
        ((S_80BC1880_1 *)arg0)->unk_03 *
        (((S_80BC1880_1 *)arg0)->unk_1C - ((S_80BC1880_1 *)arg0)->unk_1A.s) /
        ((S_80BC1880_1 *)arg0)->unk_1C;
    arg2->unk_0E =
        ((S_80BC1880_1 *)arg0)->unk_04 *
        (((S_80BC1880_1 *)arg0)->unk_1C - ((S_80BC1880_1 *)arg0)->unk_1A.s) /
        ((S_80BC1880_1 *)arg0)->unk_1C;

    work.xyz[0] = arg1->unk_02;
    work.xyz[1] = arg1->unk_06;
    work.xyz[2] = arg1->unk_0A;
    arg2->unk_06 =
        func_80065420(work.xyz, &work.out18, &work.out20, &work.out24) - 8;

    count = ((S_80BC1880_1 *)arg0)->unk_1A.u - 1;
    ((S_80BC1880_1 *)arg0)->unk_1A.u = count;
    if ((count << 16) <= 0) {
        ((S_80BC1880_1_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
