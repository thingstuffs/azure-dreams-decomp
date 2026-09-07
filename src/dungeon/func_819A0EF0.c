#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800814A0.h"

typedef struct S_800246F0_0_pre {
    u16 unk_00;
} S_800246F0_0_pre;   /* the 0x2 bytes before arg0 in func_800246F0, addressed as arg0[-1] */

typedef struct S_800246F0_0 {
    u8 pad_00[0x3A];
    union { u16 s; s16 u; } unk_3A;   /* accessed as both */
    s16 unk_3C;
} S_800246F0_0;   /* arg0 in func_800246F0 */


typedef struct S_800246F0_2 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_800246F0_2;   /* arg1 in func_800246F0 */



extern void func_800478B8(void *);
extern s16 D_800261B0[8];
extern u8 D_800814A0[];


void func_800246F0(void *arg0, S_800246F0_2 *arg1, Rec_D_80082E80 *arg2)
{
    s32 value;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s32 count;

    count = ((S_800246F0_0 *)arg0)->unk_3A.s;
    D_800261B0[0] = 1;
    ((S_800246F0_0 *)arg0)->unk_3A.s = count - 1;
    func_800478B8(arg2);
    value = ((s16)((S_800246F0_0 *)arg0)->unk_3A.s << 7) /
            ((S_800246F0_0 *)arg0)->unk_3C;
    arg2->unk_0C.at02_s8.v = value;
    arg2->unk_0C.at01_s8.v = value;
    arg2->unk_0C.at00_s8.v = value;
    x = arg1->unk_00;
    dx = arg1->unk_0C;
    y = arg1->unk_04;
    dy = arg1->unk_10;
    arg1->unk_00 = x + dx;
    arg1->unk_04 = y + dy;
    if (((S_800246F0_0 *)arg0)->unk_3A.u <= 0) {
        ((S_800246F0_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        ((Rec_D_800814A0 *)D_800814A0)->unk_00 |= 0x8000;
    }
}
