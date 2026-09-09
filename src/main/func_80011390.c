#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_80024390_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80024390_5;   /* temp_s3 in func_80024390 */

typedef struct S_80024390_6 {
    u8 pad_00[0x8];
    s16 unk_08;
    u8 pad_0A[0x1A];
    s32 unk_24;
    s32 unk_28;
    u32 unk_2C;
    u8 pad_30[0x4];
    s32 unk_34;
} S_80024390_6;   /* ((((S_80024390_0 *)arg0)->unk_7C << 7) + temp_fp) in func_80024390 */

typedef struct S_80024390_7 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80024390_7;   /* ((S_80024390_5 *)temp_s3)->unk_04 in func_80024390 */


typedef struct S_80024390_0 {
    u8 pad_00[0x7C];
    s32 unk_7C;
    u8 pad_80[0xACC];
    void * unk_B4C;
    void * unk_B50;
    void * unk_B54;
    void * unk_B58;
    void * unk_B5C;
    void * unk_B60;
    void * unk_B64;
} S_80024390_0;   /* arg0 in func_80024390 */

typedef struct S_80024390_1 {
    union { void * s; s32 u; } unk_00;   /* accessed as both */
} S_80024390_1;   /* temp_s3 in func_80024390 */

typedef struct S_80024390_2 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    M2C_UNK * unk_0C;
} S_80024390_2;   /* table_base in func_80024390 */

typedef struct S_80024390_3 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x10];
    s32 unk_30;
} S_80024390_3;   /* temp_v0 in func_80024390 */

typedef struct S_80024390_4 {
    u8 pad_00[0xB68];
    void * unk_B68;
} S_80024390_4;   /* var_a1 in func_80024390 */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8003AD08();
M2C_UNK func_8004DA74();
M2C_UNK func_8004E298();
M2C_UNK func_8004E5A0();
M2C_UNK func_8004E5E8();
M2C_UNK func_8004E69C();
M2C_UNK func_80069E38();
M2C_UNK func_80069E78();
extern u8 D_800200A4[0x100];
extern s32 D_80027FD4[0x40];
extern u8 D_800282D8[0x100];
extern u8 D_800282E8[0x100];
extern u8 D_800283A8[0x100];
extern u8 D_80083EA4[0x4000];

void func_80024390(void *arg0) {
    u8 sp10[256];
    u8 sp110[16];
    s32 var_a3;
    register s32 *var_a2 ASM_REG("$6"); /* MATCH: Keep the table cursor in retail's a2 after removing the label call. */
    s32 temp_s0_5;
    s32 temp_s4;
    s32 temp_s5;
    s32 var_a0;
    s32 var_a0_3;
    u32 temp_v1;
    u32 var_a0_2;
    u32 one;
    s32 width;
    s32 temp_hi;
    void *temp_fp;
    void *temp_base;
    void *loop_base;
    void *asset0;
    void *asset1;
    void *asset2;
    void *asset3;
    void *asset4;
    void *asset5;
    void *asset6;
    S_80024390_2 *table_base;
    S_80024390_1 *temp_s3;
    void *temp_v0;
    register void *var_a1 ASM_REG("$5"); /* MATCH: Keep the object cursor in retail's a1 so the loop count uses a0. */
    s32 *global_table;

    temp_s3 = ((S_80024390_0 *)arg0)->unk_B4C;
    func_8003AD08(((S_80024390_0 *)arg0)->unk_7C + 1, &sp10);
    func_80069E38(&sp10, D_800282D8);
    temp_base = D_80083EA4;
    func_80069E38(&sp10, (((S_80024390_0 *)arg0)->unk_7C << 7) + temp_base);
    asset0 = arg0 + 0x84;
    func_8004DA74(asset0, &sp10, 1);
    temp_s3->unk_00.s = asset0;
    ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_08 = 0xA8;
    ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_0A = 0x110;
    temp_s3 = ((S_80024390_0 *)arg0)->unk_B50;
    func_80069E78(&sp10, D_800282E8);
    asset1 = arg0 + 0x204;
    func_8004DA74(asset1, &sp10, 1);
    temp_s3->unk_00.s = asset1;
    ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_08 = 0xA0;
    ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_0A = 0x110;
    temp_fp = temp_base - 0xC;
    if (((S_80024390_6 *)(((((S_80024390_0 *)arg0)->unk_7C << 7) + temp_fp)))->unk_08 != 0) {
        table_base = D_800283A8;
        temp_s3 = ((S_80024390_0 *)arg0)->unk_B54;
        func_80069E78(&sp10, table_base->unk_08);
        func_8003AD08(((S_80024390_6 *)(((((S_80024390_0 *)arg0)->unk_7C << 7) + temp_fp)))->unk_34, &sp110);
        func_80069E38(&sp10, &sp110);
        func_80069E38(&sp10, table_base->unk_0C);
        asset2 = arg0 + 0x384;
        func_8004DA74(asset2, &sp10, 1);
        temp_s3->unk_00.s = asset2;
        ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_08 = 0xB8;
        ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_0A = 0x140;
    }
    temp_s3 = ((S_80024390_0 *)arg0)->unk_B58;
    func_8004E5A0(((S_80024390_6 *)(((((S_80024390_0 *)arg0)->unk_7C << 7) + temp_fp)))->unk_24, 0xA, &sp10);
    func_8004E69C(&sp10);
    asset3 = arg0 + 0x504;
    func_8004E298(asset3, &sp10, 1);
    temp_s3->unk_00.s = asset3;
    ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_08 = 0x148;
    ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_0A = 0x110;
    temp_v0 = (((S_80024390_0 *)arg0)->unk_7C << 7) + temp_fp;
    temp_hi = ((S_80024390_3 *)temp_v0)->unk_1C / 60;
    temp_s5 = temp_hi;
    temp_s3 = ((S_80024390_0 *)arg0)->unk_B5C;
    temp_s4 = temp_s5 / 3600;
    var_a0 = 0x3E7;
    if (temp_s4 < 0x3E8) {
        var_a0 = temp_s4;
    }
    func_8004E5A0(var_a0, 3, &sp10);
    func_80069E38(&sp10, D_800200A4);
    temp_s0_5 = temp_s5 / 60;
    func_8004E5E8(temp_s0_5 - (temp_s4 * 0x3C), 2, &sp110);
    func_80069E38(&sp10, &sp110);
    func_80069E38(&sp10, D_800200A4);
    func_8004E5E8(temp_s5 - (temp_s0_5 * 0x3C), 2, &sp110);
    func_80069E38(&sp10, &sp110);
    func_8004E69C(&sp10);
    asset4 = arg0 + 0x684;
    func_8004E298(asset4, &sp10, 1);
    temp_s3->unk_00.s = asset4;
    ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_08 = 0x150;
    ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_0A = 0x120;
    temp_v1 = ((S_80024390_6 *)(((((S_80024390_0 *)arg0)->unk_7C << 7) + temp_fp)))->unk_2C;
    temp_s3 = ((S_80024390_0 *)arg0)->unk_B60;
    var_a0_2 = 0x3E7;
    if (temp_v1 < 0x3E8U) {
        var_a0_2 = temp_v1;
    }
    func_8004E5A0((s32) var_a0_2, 3, &sp10);
    func_8004E69C(&sp10);
    asset5 = arg0 + 0x804;
    func_8004E298(asset5, &sp10, 1);
    temp_s3->unk_00.s = asset5;
    ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_08 = 0x100;
    ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_0A = 0x120;
    temp_s3 = ((S_80024390_0 *)arg0)->unk_B64;
    func_8004E5A0(((S_80024390_6 *)(((((S_80024390_0 *)arg0)->unk_7C << 7) + temp_fp)))->unk_28, 2, &sp10);
    func_8004E69C(&sp10);
    asset6 = arg0 + 0x984;
    func_8004E298(asset6, &sp10, 1);
    var_a0_3 = 0;
    loop_base = temp_fp;
    global_table = D_80027FD4;
    one = 1;
    width = 0xB0;
    var_a3 = 0x34;
    var_a2 = global_table;
    var_a1 = arg0;
    temp_s3->unk_00.s = asset6;
    ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_08 = 0x188;
    ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_0A = 0x130;
loop_7:
    temp_s3 = ((S_80024390_4 *)var_a1)->unk_B68;
    temp_v0 = (void *)(((S_80024390_0 *)arg0)->unk_7C << 7);
    temp_v0 = (void *)((u32)temp_v0 + (u32)loop_base);
    if (((S_80024390_3 *)temp_v0)->unk_30 & (one << var_a0_3)) {
        temp_v1 = *(volatile s32 *)var_a2;
        var_a2 += 1;
    } else {
        temp_v1 = global_table[8];
        var_a2 += 1;
    }
    var_a1 += 4;
    var_a0_3 += 1;
    temp_s3->unk_00.u = (s32) temp_v1;
    ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_08 = var_a3;
    ((S_80024390_7 *)(((S_80024390_5 *)temp_s3)->unk_04))->unk_0A = width;
    var_a3 += 0x10;
    if (var_a0_3 >= 8) {
        return;
    }
    goto loop_7;
}
