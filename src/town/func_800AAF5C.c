#include "common.h"

typedef struct S_800A86BC_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A86BC_0;   /* arg1 in func_800A86BC */

typedef struct S_800A86BC_1_pre {
    u16 unk_00;
} S_800A86BC_1_pre;   /* the 0x2 bytes before arg0 in func_800A86BC, addressed as arg0[-1] */

typedef struct S_800A86BC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    s32 unk_04;
} S_800A86BC_1;   /* arg0 in func_800A86BC */

typedef struct S_800A86BC_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800A86BC_2;   /* arg2 in func_800A86BC */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800478B8();
extern s32 D_800814A0[];

void func_800A86BC(void *arg0, S_800A86BC_0 *arg1, S_800A86BC_2 *arg2) {
    u8 temp;
    u16 count;

    arg1->unk_14 = arg1->unk_14 + ((S_800A86BC_1 *)arg0)->unk_04;
    arg1->unk_00 = arg1->unk_00 + arg1->unk_0C;
    arg1->unk_04 = arg1->unk_04 + arg1->unk_10;
    arg1->unk_08 = arg1->unk_08 + arg1->unk_14;
    func_800478B8(arg2);
    temp = arg2->unk_0C;
    if (temp != 0) {
        temp -= 0x10;
        arg2->unk_0C = temp;
        arg2->unk_0E = temp;
        arg2->unk_0D = temp;
    }
    count = ((S_800A86BC_1 *)arg0)->unk_02 - 1;
    ((S_800A86BC_1 *)arg0)->unk_02 = count;
    if ((count << 0x10) <= 0) {
        ((S_800A86BC_1_pre *)arg0)[-1].unk_00 = ((S_800A86BC_1_pre *)arg0)[-1].unk_00 | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
