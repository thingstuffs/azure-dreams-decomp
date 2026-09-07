/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AF520_3 {
    void * unk_00;
} S_800AF520_3;   /* ctx in func_800AF520 */

typedef struct S_800AF520_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800AF520_4;   /* ((S_800AF520_3 *)ctx)->unk_00 in func_800AF520 */






extern s32 func_8004A658();
extern M2C_UNK func_800AF554();

typedef struct S_800AF520_0 {
    void * unk_00;
    u8 pad_04[0xA4];
    s32 unk_A8;
} S_800AF520_0;   /* ctx in func_800AF520 */

typedef struct S_800AF520_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
} S_800AF520_1;   /* temp_struct in func_800AF520 */

typedef struct S_800AF520_2 {
    u8 unk_00;
    u8 unk_01;
} S_800AF520_2;   /* temp_v0 in func_800AF520 */

void func_800AF520(void *arg0) {
    s32 *temp_v0_2;
    void *temp_a0;
    register s32 temp_s1;
    s32 temp_index;
    register s32 temp_product ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 temp_result;
    register s32 temp_cond ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 var_s0;
    s32 cleanup_offset;
    s32 var_v0;
    S_800AF520_2 *temp_v0;
    s32 *temp_v1;
    register void *temp_addr ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    S_800AF520_1 *temp_struct;
    S_800AF520_0 *ctx = arg0;

    temp_index = ((S_800AF520_4 *)(((S_800AF520_3 *)ctx)->unk_00))->unk_10;
    ASM_MEM_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    var_s0 = 6;
    ASM_KEEP(var_s0);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    temp_product = temp_index << 2;
    temp_product += temp_index;
    temp_s1 = temp_product << 1;
    ASM_MEM_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_struct = ctx->unk_00;
    temp_cond = temp_s1 < temp_struct->unk_1C;
    if (temp_cond == 0) {
        goto block_5;
    }
    temp_product = temp_s1 << 2;
    temp_addr = (void *)(temp_product + temp_struct->unk_20);
    temp_v0 = *(void **)temp_addr;
    temp_result = func_8004A658(temp_v0->unk_01, temp_v0->unk_00);
    temp_s1 += 1;
    ASM_USE(temp_s1);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    temp_a0 = (void *)ctx->unk_A8;
    temp_v1 = *((s32 **)((var_s0 * 4) + (u8 *)temp_a0));
    var_s0 += 1;
    *temp_v1 = temp_result;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    var_v0 = var_s0 < 0x10;
    if (var_v0 == 0) {
        goto block_5;
    }
    func_800AF554(temp_a0);
    return;
block_4:
    cleanup_offset = var_s0 << 2;
    temp_addr = (void *)(cleanup_offset + ctx->unk_A8);
    ASM_KEEP(temp_addr);   /* MATCH pin: load-bearing for the whole function shape */
    temp_v0_2 = *(s32 **)temp_addr;
    var_s0 += 1;
    *temp_v0_2 = 0;
block_5:
    var_v0 = var_s0 < 0x10;
block_6:
    if (var_v0 != 0) {
        goto block_4;
    }
    return;
}
