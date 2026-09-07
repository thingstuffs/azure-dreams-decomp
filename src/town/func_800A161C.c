#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009ED7C_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8009ED7C_0;   /* arg2 in func_8009ED7C */

typedef struct S_8009ED7C_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8009ED7C_1;   /* temp_a0 in func_8009ED7C */

typedef struct S_8009ED7C_2_pre {
    u16 unk_00;
} S_8009ED7C_2_pre;   /* the 0x2 bytes before arg0 in func_8009ED7C, addressed as arg0[-1] */

typedef struct S_8009ED7C_2 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_8009ED7C_2;   /* arg0 in func_8009ED7C */


M2C_UNK func_80033D08();                      /* extern */
M2C_UNK func_8008F134();                      /* extern */
M2C_UNK func_8008F294();             /* extern */
M2C_UNK func_8008F664();             /* extern */
M2C_UNK func_8009539C();                      /* extern */
M2C_UNK func_800A0150(); /* extern */
M2C_UNK func_800C0C88();                            /* extern */
extern s32 D_800814A0[];
typedef struct {
    s32 words[0x15];
} Record84;
extern Record84 D_80100AF8;
extern s32 D_80100B50[];
extern s32 D_80100B68[];

void func_8009ED7C(void *arg0, M2C_UNK arg1, void *arg2) {
    s32 *temp_a0;
    s32 *temp_v1;
    u16 temp_v0;

    temp_a0 = D_80100B50;
    ((S_8009ED7C_0 *)arg2)->unk_0C = (s32) ((s32) (((S_8009ED7C_1 *)temp_a0)->unk_00 - ((S_8009ED7C_0 *)arg2)->unk_00) / 2);
    ((S_8009ED7C_0 *)arg2)->unk_10 = (s32) ((s32) (((S_8009ED7C_1 *)temp_a0)->unk_04 - ((S_8009ED7C_0 *)arg2)->unk_04) / 2);
    ((S_8009ED7C_0 *)arg2)->unk_14 = (s32) ((s32) (((S_8009ED7C_1 *)temp_a0)->unk_08 - ((S_8009ED7C_0 *)arg2)->unk_08) / 2);
    func_8009539C(arg2);
    func_8008F294(arg1, arg2);
    func_8008F664(arg1, arg2);
    temp_v0 = ((S_8009ED7C_2 *)arg0)->unk_6C - 1;
    ((S_8009ED7C_2 *)arg0)->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800A0150(D_80100B68[0], arg0 + 0x4C, &D_80100AF8, 0);
        func_8008F134(arg0);
        func_80033D08(arg0);
        temp_v0 = ((S_8009ED7C_2_pre *)arg0)[-1].unk_00;
        temp_v1 = D_800814A0;
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (temp_v0 | 0x8000);
        *temp_v1 = *temp_v1 | 0x8000;
        func_800C0C88();
    }
}

/* MECHANISM: A named D_80100B50 base carries the three source words in one page register.
   The three arguments remain live in s2/s1/s0 across calls; exact-width halfword updates
   preserve the countdown CFG, while a shared D_800814A0 pointer expresses the tail RMW. */
