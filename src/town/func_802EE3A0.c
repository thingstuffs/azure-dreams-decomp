#include "common.h"

typedef struct S_802EE3A0_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_802EE3A0_2;   /* temp_v1 in func_802EE3A0 */

typedef struct S_802EE3A0_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_802EE3A0_3;   /* ((S_802EE3A0_2 *)temp_v1)->unk_04 in func_802EE3A0 */




typedef struct Local64 { s32 word; s8 byte; u8 pad[59]; } Local64;
typedef struct Local16 { u8 data[16]; } Local16;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_8003830C();
s32 func_80051B50();
s32 func_8007BF50();
s32 func_80402268();
void func_80405454();
void *memcpy(void *dst, const void *src, u32 n);
extern u8 D_804006C4[];
extern u8 D_804006EC[];
extern s32 D_80400714;
extern u8 D_8040071C[];

typedef struct S_802EE3A0_0 {
    u8 pad_00[0xB18];
    void * unk_B18;
} S_802EE3A0_0;   /* (base + var_v1) in func_802EE3A0 */

typedef struct S_802EE3A0_1 {
    s32 unk_00;
} S_802EE3A0_1;   /* temp_v1 in func_802EE3A0 */

void func_802EE3A0(s32 arg0) {
    s32 base;
    s32 temp_ret;
    Local64 sp10;
    Local16 sp50;
    Local64 *sp10p;
    Local16 *sp50p;
    s32 var_a2;
    s32 var_v1;
    s32 data_offset;
    S_802EE3A0_1 *temp_v1;
    s32 edge;
    s32 gate;

    base = arg0;
    temp_ret = func_80402268();
    if (temp_ret >= 3) goto block_3;
    func_80051B50(base + 0x80, D_804006C4, 1);
    func_80405454(base + 0x188, D_804006EC);
    goto fake_tail;
block_3:
    memcpy(&sp10, &D_80400714, 5);
    sp50p = &sp50;
    func_8003830C(temp_ret / 3, sp50p);
    sp10p = &sp10;
    func_8007BF50(sp10p, sp50p);
    func_8007BF50(sp10p, D_8040071C);
    func_80051B50(base + 0x80, sp10p, 1);
block_common:
    var_a2 = 0;
    while (temp_ret < 3 ? var_a2 < 2 : var_a2 < 1) {
        var_v1 = var_a2 * 4;
        temp_v1 = ((S_802EE3A0_0 *)((base + var_v1)))->unk_B18;
        data_offset = (var_a2 * 0x108) + 0x80;
        temp_v1->unk_00 = (s32) (base + data_offset);
        ((S_802EE3A0_3 *)(((S_802EE3A0_2 *)temp_v1)->unk_04))->unk_08 = 0xA9;
        ((S_802EE3A0_3 *)(((S_802EE3A0_2 *)temp_v1)->unk_04))->unk_0A = (s16) ((var_a2 * 0x10) + 0x110);
        var_a2 += 1;
    }
    return;
fake_tail:
    edge = D_80400714;
    if (edge != 0) gate = 0;
    else if (edge < 0) gate = 0;
    else gate = 0;
    if (gate != 0) goto block_common;
    return;
}
