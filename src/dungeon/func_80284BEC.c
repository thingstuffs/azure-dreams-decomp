#include "common.h"
#include "m2c_compat.h"

s32 func_80017CA4() __attribute__((noreturn));
s32 func_80017E88() __attribute__((noreturn));
s32 func_80017EBC();
s16 func_80017F88();
s16 func_8001816C();
s32 func_80018304();
M2C_UNK func_800BCB04();
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_8008333C;

typedef struct S_80017BEC_0 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_80017BEC_0;   /* temp_fp in func_80017BEC */

typedef struct S_80017BEC_1 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80017BEC_1;   /* temp_v0 in func_80017BEC */

typedef struct S_80017BEC_2 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80017BEC_2;   /* temp_a0 in func_80017BEC */

typedef struct S_80017BEC_3 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80017BEC_3;   /* temp_v0_3 in func_80017BEC */

typedef struct S_80017BEC_4 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80017BEC_4;   /* temp_v0_4 in func_80017BEC */

s32 func_80017BEC(s16 arg0) {
    struct {
        s16 sp10;
        s16 sp12;
        s32 pad;
        s16 sp18;
    } locals;
    s16 *var_s1;
    s16 *var_s2;
    register s16 temp_a1 ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
    register s16 temp_a2 ASM_REG("$6");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 var_s0;
    s16 var_s5;
    register s16 var_s4 ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    s32 *temp_fp;
    register s32 temp_a0_2 ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 temp_s7;
    register s32 temp_v0_2 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 var_s3;
    s32 var_s6;
    s32 var_v0;
    s32 bad_value;
    u16 temp_v1;
    s32 temp_v1_load;
    S_80017BEC_2 *temp_a0;
    S_80017BEC_1 *temp_v0;
    register S_80017BEC_3 *temp_v0_3 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    S_80017BEC_4 *temp_v0_4;
    register u8 *temp_t1 ASM_REG("$9");   /* MATCH pin: keeps a constant in a register as retail does */
    u16 *temp_v1_addr;

    temp_s7 = D_8008333C;
    temp_fp = &D_8008333C;
    locals.sp18 = arg0;
    var_s4 = func_80017F88(arg0, &locals.sp10, &locals.sp12, 0);
    if (var_s4 < 0x200) {
        goto valid;
    }
bad:
    bad_value = 0;
    ASM_TAILSLOT_PIN(bad_value);   /* MATCH pin: retail delay-slot contents depend on it */
    return func_80017E88();
valid:
    {
        s32 early_y;
        s32 early_shift;
        register s32 early_x ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */

        early_y = locals.sp12;
        early_shift = ((S_80017BEC_0 *)temp_fp)->unk_14;
        early_x = locals.sp10;
        temp_v0 = ((early_x + (early_y << early_shift)) * 6) + temp_s7;
    }
    temp_v0->unk_04 = (u16)(temp_v0->unk_04 | 0x100);
    var_s6 = func_80017EBC(arg0);
loop_4:
    var_s5 = -1;
    var_s3 = 0;
    var_s0 = 7;
    temp_t1 = (u8 *)&D_8006CCE8;
    var_s2 = (s16 *)(temp_t1 + 0xE);
    temp_t1 = (u8 *)&D_8006CCD8;
        var_s1 = (s16 *)(temp_t1 + 0xE);
    do {
        if ((func_80018304(locals.sp10, locals.sp12, var_s4, (s16)var_s0) << 0x10) != 0) {
            register s32 loop_x ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */

            loop_x = locals.sp10;
            temp_v0_2 = *var_s1;
            temp_v1_load = *var_s2;
            loop_x += temp_v0_2;
            temp_v0_2 = locals.sp12;
            temp_a0_2 = ((S_80017BEC_0 *)temp_fp)->unk_14;
            temp_v0_2 += temp_v1_load;
            temp_v0_2 <<= temp_a0_2;
            temp_a0_2 = loop_x + temp_v0_2;
            ASM_KEEP_NV(temp_a0_2);   /* MATCH pin: load-bearing for the whole function shape */
            temp_a0 = (void *)((temp_a0_2 * 6) + temp_s7);
            temp_v1 = temp_a0->unk_04;
            if (!(temp_v1 & 0x100)) {
                temp_a0->unk_04 = (u16)(temp_v1 | 0x200);
                var_s5 = var_s0;
            }
            var_s3 += 1;
        }
        var_s2 -= 1;
        var_s0 -= 1;
        var_s1 -= 1;
    } while (var_s0 >= 0);
    if (var_s3 != 0) {
        temp_v0_2 = (s16)var_s5;
        if (temp_v0_2 >= 0) {
            s32 tail_x;
            s32 tail_y;

            temp_v0_2 *= 2;
            temp_t1 = (u8 *)&D_8006CCD8;
            temp_v1_addr = (u16 *)(temp_t1 + temp_v0_2);
            temp_t1 = (u8 *)&D_8006CCE8;
            temp_v0_3 = temp_t1 + temp_v0_2;
            ASM_KEEP_NV(temp_v0_3);   /* MATCH pin: retail schedule: same instructions, different order without it */
            temp_a2 = (u16)locals.sp10;
               /* MATCH pin: retail schedule: same instructions, different order without it */
            temp_v1_load = *temp_v1_addr;
               /* MATCH pin: retail schedule: same instructions, different order without it */
            temp_a1 = (u16)locals.sp12;
            temp_v0_2 = *(u16 *)temp_v0_3;
            temp_a2 += temp_v1_load;
            temp_a1 += temp_v0_2;
            temp_v0_2 = (u32)(u16)temp_a2 << 16;
            {
                register s32 tail_sum ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */

                tail_x = temp_v0_2 >> 16;
                ASM_KEEP_NV(tail_x);   /* MATCH pin: retail schedule: same instructions, different order without it */
                temp_v1_load = (u32)(u16)temp_a1 << 16;
                temp_v0_2 = ((S_80017BEC_0 *)temp_fp)->unk_14;
                tail_y = temp_v1_load >> 16;
                tail_sum = tail_x + (tail_y << temp_v0_2);
                ASM_KEEP_NV(tail_sum);   /* MATCH pin: load-bearing for the whole function shape */
                temp_v0_3 = (tail_sum * 6) + temp_s7;
            }
            temp_a0_2 = var_s6 - 1;
            var_s6 = temp_a0_2;
            ASM_KEEP(var_s6);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            temp_v1_load = temp_v0_3->unk_04;
            locals.sp10 = temp_a2;
            locals.sp12 = temp_a1;
            temp_v0_3->unk_04 = (u16)(temp_v1_load | 0x100);
            if ((temp_a0_2 << 0x10) > 0) {
                var_s4 = func_800BCB04(((tail_x << 6) + 0x20) & 0xFFE0, ((tail_y << 6) + 0x20) & 0xFFE0, -0x400, tail_x);
                ASM_TAILSLOT_PIN(var_s4);   /* MATCH pin: retail delay-slot contents depend on it */
                return func_80017CA4();
            }
            goto block_17;
        }
        {
            register s16 *retry_a1 ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
            register s16 *retry_a2 ASM_REG("$6");   /* MATCH pin: keeps a constant in a register as retail does */
            register s32 retry_a3 ASM_REG("$7");   /* MATCH pin: keeps a statement from moving across a call/branch */
            s32 retry_a0;

            temp_t1 = (u8 *)(u32)(u16)locals.sp18;
            ASM_KEEP_NV(temp_t1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            retry_a1 = &locals.sp10;
            ASM_KEEP_NV(retry_a1);   /* MATCH pin: retail schedule: same instructions, different order without it */
            retry_a2 = &locals.sp12;
            ASM_KEEP_NV(retry_a2);   /* MATCH pin: retail schedule: same instructions, different order without it */
            retry_a3 = 1;
            ASM_KEEP_NV(retry_a3);   /* MATCH pin: retail schedule: same instructions, different order without it */
            retry_a0 = (s16)(u32)temp_t1;
            var_s4 = func_8001816C(retry_a0, retry_a1, retry_a2, retry_a3);
        }
        var_v0 = 0;
        if (var_s4 < 0x200) {
            s32 retry_y;
            s32 retry_shift;
            register s32 retry_x ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */

            retry_y = locals.sp12;
            retry_shift = ((S_80017BEC_0 *)temp_fp)->unk_14;
            retry_x = locals.sp10;
            temp_v0_4 = ((retry_x + (retry_y << retry_shift)) * 6) + temp_s7;
            ASM_KEEP(temp_v0_4);   /* MATCH pin: keeps a statement from moving across a call/branch */
            temp_a0_2 = var_s6 - 1;
            var_s6 = temp_a0_2;
            temp_v1_load = temp_v0_4->unk_04;
            temp_a0_2 <<= 0x10;
            temp_v0_4->unk_04 = (u16)(temp_v1_load | 0x100);
            if (temp_a0_2 <= 0) {
block_17:
                var_v0 = 1;
                return var_v0;
            }
            goto loop_4;
        }
        return var_v0;
    }
    goto bad;
}
