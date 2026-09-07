#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80024064_0_pre {
    u16 unk_00;
} S_80024064_0_pre;   /* the 0x2 bytes before arg0 in func_80024064, addressed as arg0[-1] */

typedef struct S_80024064_0 {
    void * unk_00;
    u16 * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; volatile u16 u; u16 p; } unk_0A;   /* accessed as both */
    s32 unk_0C;
    u8 pad_10[0xA];
    s16 unk_1A;
    u8 pad_1C[0x4];
    s16 unk_20;
    s16 unk_22;
} S_80024064_0;   /* arg0 in func_80024064 */


typedef struct S_80024064_2 {
    u8 pad_00[0xA8];
    u8 unk_A8;
    u8 pad_A9[0x4B];
    s32 unk_F4;
} S_80024064_2;   /* state_base in func_80024064 */

typedef struct S_80024064_3_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_80024064_3_pre;   /* the 0x18 bytes before temp_a1 in func_80024064, addressed as temp_a1[-1] */

typedef struct S_80024064_4 {
    u8 pad_00[0xA8];
    u8 unk_A8;
    u8 unk_A9;
} S_80024064_4;   /* global_base in func_80024064 */

typedef struct S_80024064_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80024064_5;   /* base_83460 in func_80024064 */

typedef struct S_80024064_6 {
    u8 pad_00[0x96];
    s16 unk_96;
} S_80024064_6;   /* (*(void **)((u8 *)D_800814A8 + 0)) in func_80024064 */

typedef struct S_80024064_7 {
    u8 pad_00[0x102];
    s8 unk_102;
} S_80024064_7;   /* ((Rec_D_800814A8 *)D_800814A8)->unk_00.as_pv in func_80024064 */


typedef struct StackPair {
    s32 first;
    s32 second;
} StackPair;

/* cfail-repair: tf7-phase1-cache-v3 */
extern int D_800814A8[4];
struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern s16 D_800269F8[5];
extern s32 D_80083460[3];
extern s32 D_800814A0[3];
extern void *D_80024008[];
void func_80024238(void) __attribute__((noreturn)); /* extern */
void func_8002423C(void) __attribute__((noreturn)); /* extern */
void func_80024294(void) __attribute__((noreturn)); /* extern */
s32 func_800244EC();                     /* extern */
M2C_UNK func_800263F0();                         /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern s32 D_800269D0;
extern M2C_UNK D_80027750;
extern M2C_UNK D_80027C74;
extern s16 D_80027C94;
extern u8 D_80027C96;
extern void *D_80027C98;

void func_80024064(void *arg0) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    StackPair stack_args;
    s16 temp_a0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 temp_v1;
    s32 temp_v0;
    u8 temp_u8;
    void *temp_a1;
    S_8003E2D8 *global_base;
    void *state_base;
    void *arg_value;
    s32 *base_83460;

    global_base = &D_80083160;
    temp_v1 = ((S_80024064_0 *)arg0)->unk_0A.s;
    if ((u32) temp_v1 >= 5U) {
        goto block_15;
    }
    (void)jt_keep; goto *D_80024008[(u32)(temp_v1)];
jt_c0:
    stack_args.first = 0x010003A0;
    stack_args.second = 0x400020;
    func_80040490(&D_80027750, &stack_args);
    func_8003F80C(&D_80027C74, 0x7AC0, 1, 2);
    D_80027C94 = 1;
    temp_u8 = ((S_80024064_0 *)arg0)->unk_09;
    state_base = ((Rec_D_800814A8 *)D_800814A8)->unk_00.as_pv;
    D_800269D0 = 0;
    D_80027C96 = temp_u8;
    arg_value = (*(void **)((u8 *)arg0 + 0));
    ((S_80024064_2 *)state_base)->unk_F4 = 0;
    D_80027C98 = arg_value;
    ((S_80024064_2 *)state_base)->unk_A8 = (u8) ((S_80024064_0 *)arg0)->unk_08;
    func_800263F0(state_base);
    ((S_80024064_6 *)((*(void **)((u8 *)D_800814A8 + 0))))->unk_96 = 0x14;
    ((S_80024064_7 *)(((Rec_D_800814A8 *)D_800814A8)->unk_00.as_pv))->unk_102 = 1;
    ((S_80024064_0 *)arg0)->unk_0A.s = (s16) ((u16) ((S_80024064_0 *)arg0)->unk_0A.s + 1);
jt_c1:
    if (!(*((S_80024064_0 *)arg0)->unk_04 & 0x80)) {
        goto block_15;
    }
    temp_a1 = ((S_80024064_0 *)arg0)->unk_00;
    temp_v0 = func_800244EC(((S_80024064_3_pre *)temp_a1)[-1].unk_00, temp_a1);
    ((S_80024064_0 *)arg0)->unk_0C = temp_v0;
    if (temp_v0 == 0) {
        goto block_15;
    }
    ((S_80024064_0 *)arg0)->unk_20 = -1;
    ((S_80024064_0 *)arg0)->unk_22 = 0x20;
    func_800A56E0(0x300);
    func_80024238();
    return;
jt_c2:
    temp_v1 = 0x10;
    if (D_80027C94 != 0) {
        goto block_15;
    }
    ((S_80024064_0 *)arg0)->unk_1A = (s16) temp_v1;
    (void) ((S_80024064_0 *)arg0)->unk_0A.u;
    func_8002423C();
    return;
jt_c3:
    ((S_80024064_4 *)global_base)->unk_A9 = (u8) (((S_80024064_4 *)global_base)->unk_A9 + ((s32) (0x80 - ((S_80024064_4 *)global_base)->unk_A9) / (s16) ((S_80024064_0 *)arg0)->unk_1A));
    temp_a0 = ((S_80024064_0 *)arg0)->unk_1A;
    ((S_80024064_4 *)global_base)->unk_A8 = (u8) (((S_80024064_4 *)global_base)->unk_A8 + ((s32) (0x80 - ((S_80024064_4 *)global_base)->unk_A8) / temp_a0));
    temp_v0_2 = (u16) ((S_80024064_0 *)arg0)->unk_1A - 1;
    ((S_80024064_0 *)arg0)->unk_1A = temp_v0_2;
    if ((temp_v0_2 << 0x10) > 0) {
        goto block_15;
    }
    ((S_80024064_4 *)global_base)->unk_A9 = 0x80U;
    ((S_80024064_4 *)global_base)->unk_A8 = 0x80U;
    ((S_80024064_0 *)arg0)->unk_0A.p = (u16) ((S_80024064_0 *)arg0)->unk_0A.p + 1;
    func_80024294();
    return;
jt_c4:
    if ((s16) *D_800269F8 != 0) {
        goto block_15;
    }
    base_83460 = D_80083460;
    ((S_80024064_5 *)base_83460)->unk_0C = 0;
    ((S_80024064_5 *)base_83460)->unk_0A = (u16) (((S_80024064_5 *)base_83460)->unk_0A - 1);
    ((S_80024064_0_pre *)arg0)[-1].unk_00 = (u16) (((S_80024064_0_pre *)arg0)[-1].unk_00 | 0x8000);
    D_800814A0[0] = D_800814A0[0] | 0x8000;
block_15:
    if (((S_80024064_0 *)arg0)->unk_20 >= 0) {
        goto block_18;
    }
    ((S_80024064_4 *)global_base)->unk_A9 = (u8) (((S_80024064_4 *)global_base)->unk_A9 + ((s32) (0x20 - ((S_80024064_4 *)global_base)->unk_A9) / (s16) ((S_80024064_0 *)arg0)->unk_22));
    ((S_80024064_4 *)global_base)->unk_A8 = (u8) (((S_80024064_4 *)global_base)->unk_A8 + ((s32) (0x20 - ((S_80024064_4 *)global_base)->unk_A8) / (s16) ((S_80024064_0 *)arg0)->unk_22));
    temp_v0_3 = (u16) ((S_80024064_0 *)arg0)->unk_22 - 1;
    ((S_80024064_0 *)arg0)->unk_22 = temp_v0_3;
    if ((temp_v0_3 << 0x10) > 0) {
        goto block_18;
    }
    ((S_80024064_0 *)arg0)->unk_20 = 0;
block_18:
    *D_800269F8 = 0;
    return;
}
/* Warning: struct S_8003E2D8 is not defined (only forward-declared) */
