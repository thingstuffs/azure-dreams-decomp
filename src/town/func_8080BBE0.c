#include "common.h"
#include "m2c_compat.h"

typedef struct S_805267E0_0_pre {
    u16 unk_00;
} S_805267E0_0_pre;   /* the 0x2 bytes before arg0 in func_805267E0, addressed as arg0[-1] */

typedef struct S_805267E0_0 {
    s16 unk_00;
    u16 unk_02;
    void * unk_04;
    s32 unk_08;
    u8 pad_0C[0xA];
    u16 unk_16;
} S_805267E0_0;   /* arg0 in func_805267E0 */

typedef struct S_805267E0_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_805267E0_1;   /* sub in func_805267E0 */


extern s32 D_80084D5C;

void func_805267E0(void *arg0) {
    s16 temp_v1;
    s32 temp_v0_2;
    u16 temp_v0;
    void *sub;
    s16 v1;
    u16 flags;

    temp_v1 = ((S_805267E0_0 *)arg0)->unk_00;
    sub = ((S_805267E0_0 *)arg0)->unk_04;
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = ((S_805267E0_0 *)arg0)->unk_02 - 1;
        ((S_805267E0_0 *)arg0)->unk_02 = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            v1 = ((S_805267E0_0 *)arg0)->unk_00;
            flags = ((S_805267E0_0 *)arg0)->unk_16;
            v1 = (s16) (v1 + 1);
            flags &= 0xFFFD;
            ((S_805267E0_0 *)arg0)->unk_16 = flags;
            ((S_805267E0_0 *)arg0)->unk_00 = v1;
            return;
        }
        return;
    case 1:
        if (((S_805267E0_1 *)sub)->unk_2A & 1) {
            ((S_805267E0_0 *)arg0)->unk_00 = (s16) (temp_v1 + 1);
            return;
        }
        break;
    case 2:
        temp_v0_2 = ((S_805267E0_0 *)arg0)->unk_08 + 0xFFF7F7F8;
        ((S_805267E0_0 *)arg0)->unk_08 = temp_v0_2;
        if (temp_v0_2 <= 0x80808) {
            (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_805267E0_0_pre *)arg0)[-1].unk_00 | 0x8000);
            D_80084D5C |= 0x8000;
        }
        break;
    }
}
