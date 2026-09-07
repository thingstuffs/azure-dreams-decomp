#include "common.h"

typedef struct S_8197D3B8_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8197D3B8_0;   /* arg1 in func_8197D3B8 */

typedef struct S_8197D3B8_1_pre {
    u16 unk_00;
} S_8197D3B8_1_pre;   /* the 0x2 bytes before arg0 in func_8197D3B8, addressed as arg0[-1] */

typedef struct S_8197D3B8_1 {
    void * unk_00;
} S_8197D3B8_1;   /* arg0 in func_8197D3B8 */

typedef struct S_8197D3B8_2 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_8197D3B8_2;   /* primitive in func_8197D3B8 */

typedef struct S_8197D3B8_3 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8197D3B8_3;   /* arg2 in func_8197D3B8 */



extern void func_800478B8(void *);
extern s32 D_800814A0[3];

void func_8197D3B8(void *arg0, S_8197D3B8_0 *arg1, S_8197D3B8_3 *arg2)
{
    s32 delta_y;
    s32 delta_z;
    S_8197D3B8_2 *primitive;

    delta_y = arg1->unk_10;
    delta_z = arg1->unk_14;
    arg1->unk_00 += arg1->unk_0C;
    arg1->unk_04 += delta_y;
    arg1->unk_08 += delta_z;

    primitive = ((S_8197D3B8_1 *)arg0)->unk_00;
    primitive->unk_52 |= 0x8000;

    func_800478B8(arg2);
    if (arg2->unk_14 & 0x6000) {
        ((S_8197D3B8_1_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
