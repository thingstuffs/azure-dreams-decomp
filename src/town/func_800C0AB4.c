#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800BE214_3 {
    M2C_UNK * unk_00;
} S_800BE214_3;   /* (s8 *)sp10 + (arg0->unk_68 * 4) in func_800BE214 */

typedef struct S_800BE214_4 {
    M2C_UNK * unk_00;
} S_800BE214_4;   /* (s8 *)sp10 + (arg0->unk_A4 * 4) in func_800BE214 */


typedef union {
    s16 state;
    u16 raw;
} StateWord;

struct Dst;
struct Elem;

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} Copy16;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800352FC();
extern void func_8003DB94(struct Dst *, struct Elem *, s16);
extern M2C_UNK func_800478B8();
extern s32 func_80064584();
extern s32 rand();
extern s32 func_800C2AB4();

extern M2C_UNK D_80089684[9];
extern void *D_800896A8[];
extern M2C_UNK D_800F9D80[3];

typedef struct S_800BE214_0 {
    u8 pad_00[0x68];
    s16 unk_68;
    u8 pad_6A[0x2];
    s16 unk_6C;
    u8 pad_6E[0x32];
    u16 unk_A0;
    u8 pad_A2[0x2];
    s32 unk_A4;
} S_800BE214_0;   /* arg0 in func_800BE214 */

typedef struct S_800BE214_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800BE214_1;   /* arg2 in func_800BE214 */

typedef struct S_800BE214_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800BE214_2;   /* arg1 in func_800BE214 */

void func_800BE214(S_800BE214_0 *arg0, S_800BE214_2 *arg1, S_800BE214_1 *arg2) {
    void *sp10[9];
    Copy16 *var_a2;
    Copy16 *var_a3;
    Copy16 *end;
    s16 temp_v0;
    s32 temp_v1;
    u16 temp_v0_2;

    var_a3 = (Copy16 *)sp10;
    var_a2 = (Copy16 *)&D_80089684;
    end = var_a2 + 2;
    do {
        *var_a3 = *var_a2;
        var_a2++;
        var_a3++;
    } while (var_a2 != end);
    var_a3->w0 = var_a2->w0;
    do { } while (0);
    func_800478B8(arg2);
    temp_v1 = arg0->unk_68;
    if ((u32)temp_v1 >= 0x61) {
        goto L_default;
    }
    switch (temp_v1) {
    case 0: goto L_case_0;
    case 0x20: goto L_case_20;
    case 0x23: goto L_case_23;
    case 0x24: goto L_case_24;
    case 0x25: goto L_case_25;
    case 0x21:
    case 0x22:
    case 0x26:
    case 0x27: goto L_case_212227;
    case 0x40: goto L_case_40;
    case 0x60: goto L_case_60;
    default: goto L_default;
    }

L_case_0:
    if ((func_800352FC() != 0) && (func_800C2AB4(arg0) != 0)) {
        temp_v0 = rand() & 7;
        arg0->unk_68 = temp_v0;
        arg0->unk_A4 = (u32)temp_v0;
        func_8003DB94((struct Dst *)arg2, (struct Elem *)((S_800BE214_3 *)((s8 *)sp10 + (arg0->unk_68 * 4)))->unk_00, 0);
        arg0->unk_68 = (s16)((u16)arg0->unk_68 + 0x20);
    }
    goto L_default;

L_case_20:
    if (!(arg2->unk_14 & 0x6000)) goto L_return;
    func_8003DB94((struct Dst *)arg2, (struct Elem *)sp10[0], 0);
    arg0->unk_6C = 0;
    arg0->unk_A4 = 0;
    arg1->unk_0A = (u16)arg0->unk_A0;
    goto L_block_16;

L_case_23:
    if (!(arg2->unk_14 & 0x6000)) goto L_return;
    arg0->unk_6C = 6;
    arg0->unk_A4 = 8;
    func_8003DB94((struct Dst *)arg2, (struct Elem *)sp10[8], 0);
    arg0->unk_68 = 0x40;
    goto L_default;

L_case_24:
    if (!(arg2->unk_14 & 0x6000)) goto L_return;
    func_8003DB94((struct Dst *)arg2, (struct Elem *)&D_800F9D80, 0);
    {
        StateWord next = { 0x20 };
        arg0->unk_68 = next.state;
    }
    goto L_default;

L_case_25:
    if (!(arg2->unk_14 & 0x6000)) goto L_return;
    func_8003DB94((struct Dst *)arg2, (struct Elem *)D_800F9D80, 0);
    goto L_block_19;

L_case_212227:
    if (!(arg2->unk_14 & 0x6000)) goto L_return;
    goto L_block_16;

L_block_16:
    arg0->unk_68 = 0x60;
    goto L_default;

L_case_40:
    arg1->unk_0A = (u16)(arg0->unk_A0 + (func_80064584((arg0->unk_6C << 0xC) / 22) >> 8));
    temp_v0_2 = (u16)arg0->unk_6C;
    arg0->unk_6C = (s16)(temp_v0_2 + 1);
    if ((s16)temp_v0_2 >= 0xDC) goto L_block_19;
    goto L_default;

L_block_19:
    arg0->unk_68 = 0x20;
    goto L_default;

L_case_60:
    if ((func_800352FC() == 0) || (func_800C2AB4(arg0) == 0)) {
        arg0->unk_68 = 0;
    }
    goto L_default;

L_default:
    if (arg2->unk_14 & 0x6000) {
        func_8003DB94((struct Dst *)arg2, (struct Elem *)((S_800BE214_4 *)((s8 *)sp10 + (arg0->unk_A4 * 4)))->unk_00, 0);
    }

L_return:
    return;
}
