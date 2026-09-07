#include "common.h"

typedef struct S_819711E0_0_pre {
    u16 unk_00;
} S_819711E0_0_pre;   /* the 0x2 bytes before arg0 in func_819711E0, addressed as arg0[-1] */

typedef struct S_819711E0_0 {
    u8 pad_00[0x38];
    union { u16 s; s16 u; } unk_38;   /* accessed as both */
    s16 unk_3A;
    u8 pad_3C[0x4];
    void * unk_40;
    u16 unk_44;
    u16 unk_46;
    u16 unk_48;
} S_819711E0_0;   /* arg0 in func_819711E0 */

typedef struct S_819711E0_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_819711E0_1;   /* arg2 in func_819711E0 */

typedef struct S_819711E0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_819711E0_2;   /* arg1 in func_819711E0 */

typedef struct S_819711E0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_819711E0_3;   /* src in func_819711E0 */


extern s16 D_80025FF4;
extern s32 D_800814A0[3];


void func_819711E0(void *arg0, S_819711E0_2 *arg1, S_819711E0_1 *arg2) {
    s32 value;
    u16 count;
    S_819711E0_3 *src;

    count = ((S_819711E0_0 *)arg0)->unk_38.s - 1;
    value = (s32) ((s32) (count << 16) >> 9) / (s16) ((S_819711E0_0 *)arg0)->unk_3A;
    D_80025FF4 = 1;
    ((S_819711E0_0 *)arg0)->unk_38.s = count;
    arg2->unk_0E = (s8) value;
    arg2->unk_0D = (s8) value;
    arg2->unk_0C = (s8) value;

    src = ((S_819711E0_0 *)arg0)->unk_40;
    arg1->unk_02 = ((S_819711E0_0 *)arg0)->unk_44;
    arg1->unk_06 = ((S_819711E0_0 *)arg0)->unk_46;
    arg1->unk_0A = ((S_819711E0_0 *)arg0)->unk_48;
    arg1->unk_02 = (u16) (arg1->unk_02 + src->unk_02);
    arg1->unk_06 = (u16) (arg1->unk_06 + src->unk_06);
    arg1->unk_0A = (u16) (arg1->unk_0A + src->unk_0A);

    if (((S_819711E0_0 *)arg0)->unk_38.u <= 0) {
        ((S_819711E0_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
