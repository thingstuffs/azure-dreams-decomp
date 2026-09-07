#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B6094_4 {
    u8 pad_00[0x38];
    void * unk_38;
} S_800B6094_4;   /* temp_v1 in func_800B6094 */

typedef struct S_800B6094_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B6094_5;   /* ((S_800B6094_4 *)temp_v1)->unk_38 in func_800B6094 */

typedef struct S_800B6094_6 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800B6094_6;   /* ((S_800B6094_5 *)(((S_800B6094_4 *)temp_v1)->unk_38))->unk_04 in func_800B6094 */




s32 func_800439BC();
M2C_UNK func_800498EC();
s32 func_80049918();
s32 func_80049944();
M2C_UNK func_800B5264();
M2C_UNK func_800B53BC();
s32 func_800B6030();
extern u8 D_8006DE24[];

typedef struct S_800B6094_0 {
    u8 unk_00;
    u8 unk_01;
} S_800B6094_0;   /* held_arg0 in func_800B6094 */

typedef struct S_800B6094_1 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x8];
    s32 unk_2C;
    u8 pad_30[0x8];
    s32 * unk_38;
} S_800B6094_1;   /* temp_s1 in func_800B6094 */

typedef struct S_800B6094_2 {
    s32 unk_00;
    u8 pad_04[0xC];
    u8 unk_10;
} S_800B6094_2;   /* temp_s0 in func_800B6094 */

typedef struct S_800B6094_3 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2C];
    void * unk_38;
} S_800B6094_3;   /* temp_v1 in func_800B6094 */

void func_800B6094(void *arg0, s32 arg1, s32 arg2) {
    register S_800B6094_0 *held_arg0 ASM_REG("$19") = arg0;   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 held_arg1 = arg1;
    s32 held_arg2 = arg2;
    register s32 first_zero ASM_REG("$6") = 0;   /* MATCH pin: retail schedule: same instructions, different order without it */
    M2C_UNK sp18[3];
    s32 *temp_s1_2;
    s32 temp_s0_2;
    s32 temp_s2;
    s32 branch_result;
    S_800B6094_2 *temp_s0;
    register void *temp_s1 ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
    S_800B6094_3 *temp_v1;

    temp_s2 = (held_arg2 * 0x10) + 0xD8;
    temp_s1 = (void *) (held_arg2 * 4);
    ASM_KEEP(held_arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_s0 = (held_arg0->unk_00 * 0x14) + D_8006DE24;
    temp_s1 = (void *) ((s8 *)temp_s1 + (s32)held_arg1);
    func_800B5264(((S_800B6094_1 *)temp_s1)->unk_20, temp_s0->unk_00, first_zero, 0x58, temp_s2);
    func_800B53BC(((S_800B6094_1 *)temp_s1)->unk_2C, func_800B6030(held_arg0->unk_01, sp18), 0, 0xA0, temp_s2);
    ASM_KEEP(held_arg0);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    temp_s0_2 = func_80049944(temp_s0->unk_10);
    temp_s1_2 = ((S_800B6094_1 *)temp_s1)->unk_38;
    if (func_800439BC(held_arg0->unk_00) != 0) {
        branch_result = func_800498EC(temp_s0_2);
    } else {
        branch_result = func_80049918(temp_s0_2);
    }
    temp_v1 = (held_arg2 * 4) + held_arg1;
    ASM_KEEP(branch_result);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(held_arg1);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(held_arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    *temp_s1_2 = branch_result;
    ((S_800B6094_6 *)(((S_800B6094_5 *)(((S_800B6094_4 *)temp_v1)->unk_38))->unk_04))->unk_08 = -0x30;
    temp_v1 = temp_v1->unk_38;
    branch_result = (held_arg2 * 0x10) + 0x67;
    temp_v1 = temp_v1->unk_04;
    temp_v1->unk_0A = (s16) branch_result;
}
