#include "common.h"

typedef struct S_818BDCE0_0_pre {
    u16 unk_00;
} S_818BDCE0_0_pre;   /* the 0x2 bytes before arg0 in func_818BDCE0, addressed as arg0[-1] */

typedef struct S_818BDCE0_0 {
    void * unk_00;
    u8 pad_04[0xC];
    union { u16 s; s16 u; } unk_10;   /* accessed as both */
    u8 pad_12[0x2];
    s16 unk_14;
} S_818BDCE0_0;   /* arg0 in func_818BDCE0 */

typedef struct S_818BDCE0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818BDCE0_1;   /* v1 in func_818BDCE0 */

typedef struct S_818BDCE0_2 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_818BDCE0_2;   /* arg2 in func_818BDCE0 */

typedef struct S_818BDCE0_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BDCE0_3;   /* arg1 in func_818BDCE0 */



extern s32 D_800814A0[];

void func_818BDCE0(void *arg0, S_818BDCE0_3 *arg1, S_818BDCE0_2 *arg2)
{
    S_818BDCE0_1 *v1;

    v1 = ((S_818BDCE0_0 *)arg0)->unk_00;
    v1->unk_14++;
    ((S_818BDCE0_0 *)arg0)->unk_10.s++;
    arg2->unk_1A += 0x300;

    arg1->unk_00 += arg1->unk_0C;
    arg1->unk_04 += arg1->unk_10;
    arg1->unk_08 += arg1->unk_14;

    if (((S_818BDCE0_0 *)arg0)->unk_10.u > ((S_818BDCE0_0 *)arg0)->unk_14) {
        ((S_818BDCE0_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
