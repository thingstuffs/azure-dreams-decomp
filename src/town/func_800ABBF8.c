#include "common.h"

extern void func_800A8CA8(void *, s32, s32, s32);
extern void func_800A8EE8(void *);
extern s32 func_800B28A0(void);
extern s32 D_80083160;
extern s32 D_800D0E48[];
extern s32 D_80100E30;

void func_800A9358(s32 arg0, s32 arg1)
{
    u32 *scratch;
    register volatile s32 i ASM_REG("$17");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 *count_base;
    s32 accum;
    s32 saved_arg1;
    s32 saved_arg0;
    u32 *call_scratch;
    register s32 scale ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 call_arg2 ASM_REG("$6");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 call_arg3 ASM_REG("$7");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 *table;
    register u32 temp_114 ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u32 temp_e8 ASM_REG("$3");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u32 temp_ec ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register u32 temp_124 ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
    register u32 loop_114 ASM_REG("$3");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u32 loop_e8 ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register u32 loop_ec ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
    u32 loop_124;
    s32 keep_loop;
    u32 final_c4;
    register u32 restore_114 ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    s32 table_index;
    s32 table_value;
    u32 initial_24;
    volatile u32 save_114[1];
    u32 save_e8;
    u32 save_ec;
    register u32 save_124 ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */

    saved_arg0 = arg0;
    ASM_KEEP_NV(saved_arg0);   /* MATCH pin: keeps a statement from moving across a call/branch */
    saved_arg1 = arg1;
    ASM_KEEP_NV(saved_arg1);   /* MATCH pin: load-bearing for the whole function shape */
    accum = 0;
    ASM_KEEP_NV(accum);   /* MATCH pin: load-bearing for the whole function shape */
    table_index = func_800B28A0();
    call_scratch = (u32 *)0x1F800000;
    ASM_KEEP_NV(call_scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */
    scale = 0;
    ASM_KEEP_NV(scale);   /* MATCH pin: retail schedule: same instructions, different order without it */
    call_arg2 = saved_arg1;
    call_arg3 = saved_arg0;
    table = D_800D0E48;
    ASM_KEEP_NV(table);   /* MATCH pin: retail immediate-load split depends on it */
    table_value = table[table_index];
    ASM_KEEP_NV(table_value);   /* MATCH pin: retail immediate-load split depends on it */
    count_base = (u8 *)0x80100000;
    ASM_KEEP_NV(count_base);   /* MATCH pin: keeps a constant in a register as retail does */
    *(s32 *)(count_base + 0xE30) = table_value;
    initial_24 = D_80083160;
    ASM_KEEP_NV(initial_24);   /* MATCH pin: retail schedule: same instructions, different order without it */
    scratch = call_scratch;
    ASM_KEEP_NV(scratch);   /* MATCH pin: retail schedule: same instructions, different order without it */
    initial_24 += 0xB0;
    scratch[0x24 / 4] = initial_24;
    func_800A8CA8((void *)call_scratch, scale, call_arg2, call_arg3);
    i = 0;
    temp_114 = scratch[0x114 / 4];
    temp_e8 = scratch[0xE8 / 4];
    temp_ec = scratch[0xEC / 4];
    temp_124 = scratch[0x124 / 4];
    save_e8 = temp_e8;
    save_ec = temp_ec;
    scratch[0x118 / 4] = temp_114;
    scratch[0xF0 / 4] = temp_e8;
    scratch[0xF4 / 4] = temp_ec;
    scratch[0x128 / 4] = temp_124;
    save_114[-1] = temp_114;
    save_124 = temp_124;

    if ((*(s32 *)(count_base + 0xE30) - 1) > 0) {
        do {
            scale = 0x1000;
            scale = scale / *(s32 *)(count_base + 0xE30);
            scale = accum + scale;
            accum = scale;
            ASM_KEEP_NV(scale);   /* MATCH pin: retail schedule: same instructions, different order without it */
            func_800A8CA8((void *)scratch, (s16)scale,
                          saved_arg1, saved_arg0);
            if (scratch[0xC4 / 4] < 0x1E0U) {
                func_800A8EE8((void *)scratch);
            }
            i++;
            loop_114 = scratch[0x114 / 4];
            loop_e8 = scratch[0xE8 / 4];
            loop_ec = scratch[0xEC / 4];
            keep_loop = *(s32 *)(count_base + 0xE30);
            loop_124 = scratch[0x124 / 4];
            keep_loop -= 1;
            keep_loop = i < keep_loop;
            scratch[0x118 / 4] = loop_114;
            scratch[0xF0 / 4] = loop_e8;
            scratch[0xF4 / 4] = loop_ec;
            scratch[0x128 / 4] = loop_124;
        } while (keep_loop);
    }

    scale = 0x1000;
    func_800A8CA8((void *)scratch,
                  (s16)(accum + (scale / D_80100E30)),
                  saved_arg1, saved_arg0);
    final_c4 = scratch[0xC4 / 4];
    ASM_KEEP_NV(final_c4);   /* MATCH pin: retail schedule: same instructions, different order without it */
    restore_114 = save_114[-1];
    ASM_KEEP_NV(restore_114);   /* MATCH pin: retail schedule: same instructions, different order without it */
    final_c4 = final_c4 < 0x1E0U;
    scratch[0x114 / 4] = restore_114;
    scratch[0xE8 / 4] = save_e8;
    scratch[0xEC / 4] = save_ec;
    scratch[0x124 / 4] = save_124;
    if (final_c4) {
        func_800A8EE8((void *)scratch);
    }
}
