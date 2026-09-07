#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_818BD3B0_0_pre {
    u16 unk_00;
} S_818BD3B0_0_pre;   /* the 0x2 bytes before arg0 in func_818BD3B0, addressed as arg0[-1] */

typedef struct S_818BD3B0_0 {
    void * unk_00;
    u16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    u16 unk_0C;
} S_818BD3B0_0;   /* arg0 in func_818BD3B0 */

typedef struct S_818BD3B0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818BD3B0_1;   /* temp_v1 in func_818BD3B0 */

typedef struct S_818BD3B0_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BD3B0_2;   /* arg1 in func_818BD3B0 */



extern void func_80024D10(void) __attribute__((noreturn));
s32 func_8003DB94();
s32 func_800478B8();
s32 func_800644B8();
s32 func_80064584();
extern s32 D_800814A0[3];
extern M2C_UNK D_800DEC70[3];

void func_818BD3B0(void *arg0, S_818BD3B0_2 *arg1, Rec_D_80082E80 *arg2) {
    s16 temp_v0_2;
    s32 temp_lo;
    s32 temp_v1_2;
    u16 temp_v0;
    S_818BD3B0_1 *temp_v1;

    temp_v1 = ((S_818BD3B0_0 *)arg0)->unk_00;
    temp_v1->unk_14 = (u16) (temp_v1->unk_14 + 1);
    temp_v0 = ((S_818BD3B0_0 *)arg0)->unk_04 + 1;
    ((S_818BD3B0_0 *)arg0)->unk_04 = temp_v0;
    if (((S_818BD3B0_0 *)arg0)->unk_06 < (s16) temp_v0) {
        ((S_818BD3B0_0_pre *)arg0)[-1].unk_00 = (u16) (((S_818BD3B0_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        func_80024D10();
        return;
    }
    temp_v1_2 = (s32) ((func_80064584((s16) temp_v0 << 7) >> 4) * ((S_818BD3B0_0 *)arg0)->unk_0A) >> 8;
    ((S_818BD3B0_0 *)arg0)->unk_08 = (s16) temp_v1_2;
    arg1->unk_08 = (s32) (arg1->unk_14 - (temp_v1_2 << 0x10));
    temp_lo = (func_800644B8((s16) ((S_818BD3B0_0 *)arg0)->unk_04 << 7) >> 4) * ((S_818BD3B0_0 *)arg0)->unk_0A;
    temp_v0_2 = ((S_818BD3B0_0 *)arg0)->unk_0C + 0x80;
    ((S_818BD3B0_0 *)arg0)->unk_0C = (u16) temp_v0_2;
    ((S_818BD3B0_0 *)arg0)->unk_08 = (s16) (temp_lo >> 8);
    arg1->unk_00 = (s32) (arg1->unk_0C + (((func_80064584(temp_v0_2) >> 4) * ((S_818BD3B0_0 *)arg0)->unk_08) << 8));
    arg1->unk_04 = (s32) (arg1->unk_10 + (((func_800644B8((s16) ((S_818BD3B0_0 *)arg0)->unk_0C) >> 4) * ((S_818BD3B0_0 *)arg0)->unk_08) << 8));
    func_800478B8(arg2);
    if (arg2->unk_14.at00_u16.v & 0x6000) {
        func_8003DB94(arg2, &D_800DEC70, 0);
    }
}

/* MECHANISM: Preserve the seed's exact 0x20 frame and s0/s2/s1 lifetime shape.
   The zero-argument func_80024D10 edge is noreturn, enabling LEAD 18 to replace
   jal-plus-epilogue with retail's tail j while retaining the global store slot. */
