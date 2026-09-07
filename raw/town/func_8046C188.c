#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8001D414();
extern s8 D_80016000[];
extern s8 D_8001902C[];

void func_8001D188(s32 arg0) {
    s32 temp_a3;
    s32 temp_s2;
    s32 temp_v0;
    s32 var_a0;
    u8 *temp_v0_2;
    u8 *temp_a1;
    s32 temp_v1;
    s32 var_s1;
    register void *temp_a2 ASM_REG("$6");
    s8 *temp_a0;
    u8 *page;
    void *cursor;
    s16 *entries;
    s32 next_count;
    register u8 count ASM_REG("$5");

    do { page = (u8 *)0x80010000; } while (0);
    temp_s2 = M2C_FIELD(M2C_FIELD(page, void **, 0x6000), s32 *, 0x38);
    var_s1 = arg0;
    temp_v0 = func_8001D414();
    cursor = M2C_FIELD(page, void **, 0x6000);
    ASM_KEEP_NV(cursor);
    ASM_SCHED_BARRIER();
    cursor = M2C_FIELD(cursor, void **, 0x24);
    ASM_KEEP_NV(cursor);
    ASM_SCHED_BARRIER();
    cursor = M2C_FIELD(cursor, void **, 0x6C);
    ASM_KEEP_NV(cursor);
    ASM_SCHED_BARRIER();
    entries = M2C_FIELD(cursor, s16 **, 0x1EC);
    ASM_KEEP_NV(entries);
    ASM_SCHED_BARRIER();
    temp_a3 = *(s16 *)((u8 *)entries + (var_s1 * 0x14));
    ASM_KEEP_NV(temp_a3);
    ASM_SCHED_BARRIER();
    temp_a2 = temp_s2 + temp_a3;
    ASM_KEEP_NV(temp_a2);
    next_count = M2C_FIELD(temp_a2, u8 *, 0x3700);
    ASM_KEEP_NV(next_count);
    ASM_SCHED_BARRIER();
    next_count += 1;
    M2C_FIELD(temp_a2, u8 *, 0x3700) = next_count;
    count = M2C_FIELD(temp_a2, volatile u8 *, 0x3700);
    ASM_USE(count);
    var_a0 = 0;
    temp_a0 = D_8001902C;
    if (count >= *(s16 *)((u8 *)temp_a0 + (((temp_a3 * 3) + temp_v0) * 8))) {
        M2C_FIELD(temp_a2, u8 *, 0x3700) = 0U;
    }
    ASM_KEEP_NV(temp_a3);
    temp_a1 = (u8 *)(temp_a3 * 0xC) + temp_s2 + 0x3640;
    do {
        temp_v0_2 = temp_a1 + var_a0;
        temp_v1 = *temp_v0_2;
        *temp_v0_2 = var_s1;
        ASM_SCHED_BARRIER();
        var_a0 += 1;
        var_s1 = temp_v1;
    } while (var_a0 < 0xC);
}
