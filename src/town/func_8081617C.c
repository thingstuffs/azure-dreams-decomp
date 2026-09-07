#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002017C_0_pre {
    u16 unk_00;
} S_8002017C_0_pre;   /* the 0x2 bytes before arg0 in func_8002017C, addressed as arg0[-1] */

typedef struct S_8002017C_0 {
    union { s16 s; volatile u16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    void * unk_04;
    s32 unk_08;
    u8 pad_0C[0xA];
    u16 unk_16;
} S_8002017C_0;   /* arg0 in func_8002017C */

typedef struct S_8002017C_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8002017C_1;   /* sub in func_8002017C */


extern s32 D_800814A0;

void func_8002017C(void *arg0) {
    s16 temp_v1;
    s32 temp_v0_2;
    u16 temp_v0;
    void *sub;
    u16 state_u;
    s16 v1;
    u16 flags;

    sub = ((S_8002017C_0 *)arg0)->unk_04;
    temp_v1 = ((S_8002017C_0 *)arg0)->unk_00.s;
    state_u = ((S_8002017C_0 *)arg0)->unk_00.u;
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = ((S_8002017C_0 *)arg0)->unk_02 - 1;
        ((S_8002017C_0 *)arg0)->unk_02 = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            flags = ((S_8002017C_0 *)arg0)->unk_16;
            v1 = ((S_8002017C_0 *)arg0)->unk_00.s;
            flags &= 0xFFFD;
            v1 = (s16) (v1 + 1);
            ((S_8002017C_0 *)arg0)->unk_16 = flags;
            ((S_8002017C_0 *)arg0)->unk_00.s = v1;
            return;
        }
        return;
    case 1:
        if (((S_8002017C_1 *)sub)->unk_2A & 1) {
            do {
                ((S_8002017C_0 *)arg0)->unk_00.s = (s16) (state_u + 1);
            } while (0);
            return;
        }
        break;
    case 2:
        temp_v0_2 = ((S_8002017C_0 *)arg0)->unk_08 + 0xFFF7F7F8;
        ((S_8002017C_0 *)arg0)->unk_08 = temp_v0_2;
        if (temp_v0_2 <= 0x80808) {
            (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_8002017C_0_pre *)arg0)[-1].unk_00 | 0x8000);
            D_800814A0 |= 0x8000;
        }
        break;
    }
}
