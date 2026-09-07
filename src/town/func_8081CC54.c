#include "common.h"

typedef struct S_80026C54_0_pre {
    u16 unk_00;
} S_80026C54_0_pre;   /* the 0x2 bytes before arg0 in func_80026C54, addressed as arg0[-1] */

typedef struct S_80026C54_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u8 pad_02[0x2];
    void * unk_04;
    s32 unk_08;
} S_80026C54_0;   /* arg0 in func_80026C54 */

typedef struct S_80026C54_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_80026C54_1;   /* temp_v0 in func_80026C54 */



extern s32 D_800814A0[3];

void func_80026C54(void *arg0) {
    S_80026C54_1 *temp_v0;
    s16 temp_v1;
    u16 temp_a0;
    s32 value;

    temp_v0 = ((S_80026C54_0 *)arg0)->unk_04;
    temp_v1 = ((S_80026C54_0 *)arg0)->unk_00.s;
    temp_a0 = *(volatile u16 *)arg0;

    switch (temp_v1) {
    case 0:
        if (temp_v0->unk_1A & 8) {
            ((S_80026C54_0 *)arg0)->unk_00.u = temp_a0 + 1;
        }
        break;

    case 1:
        value = ((S_80026C54_0 *)arg0)->unk_08 + 0xFFF7F7F8U;
        ((S_80026C54_0 *)arg0)->unk_08 = value;
        if (value <= 0x80808) {
            ((S_80026C54_0_pre *)arg0)[-1].unk_00 |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
        break;
    }

}
