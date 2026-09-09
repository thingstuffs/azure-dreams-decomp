#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B6B10_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B6B10_2;   /* temp_a0 in func_800B6B10 */

typedef struct S_800B6B10_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B6B10_3;   /* *var_s0 in func_800B6B10 */

typedef struct S_800B6B10_4 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_800B6B10_4;   /* ((S_800B6B10_2 *)temp_a0)->unk_04 in func_800B6B10 */

typedef struct S_800B6B10_5 {
    u8 pad_00[0xE];
    s8 unk_0E;
} S_800B6B10_5;   /* ((S_800B6B10_3 *)(*var_s0))->unk_04 in func_800B6B10 */

M2C_UNK func_8004B1A4();
M2C_UNK func_8004E99C();

typedef struct S_800B6B10_0 {
    s32 unk_00;
} S_800B6B10_0;   /* temp_a0 in func_800B6B10 */

typedef struct S_800B6B10_1 {
    s32 unk_00;
} S_800B6B10_1;   /* *var_s0 in func_800B6B10 */

void func_800B6B10(void **arg0) {
    s32 var_s1;
    s32 var_s2;
    u8 temp_v1;
    void **var_s0;
    S_800B6B10_0 *temp_a0;

    var_s1 = 0;
    var_s2 = 2;
    var_s0 = arg0;
loop_1:
    temp_a0 = *var_s0;
    temp_v1 = ((S_800B6B10_4 *)(((S_800B6B10_2 *)temp_a0)->unk_04))->unk_0E;
    if (temp_v1 == var_s2) {
        func_8004E99C(temp_a0->unk_00);
    } else if (temp_v1 == 1) {
        func_8004B1A4(temp_a0->unk_00);
    } else {
        goto next;
    }
    ((S_800B6B10_1 *)(*var_s0))->unk_00 = 0;
    ((S_800B6B10_5 *)(((S_800B6B10_3 *)(*var_s0))->unk_04))->unk_0E = 0;
next:
    var_s1 += 1;
    var_s0 = (void **)((s8 *)((void **)((s8 *)var_s0 + 4)));
    if (var_s1 >= 0x18) {
        return;
    }
    goto loop_1;
}
