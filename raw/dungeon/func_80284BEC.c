#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

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

s32 func_80017BEC(s16 arg0) {
    struct {
        s16 sp10;
        s16 sp12;
        s32 pad;
        s16 sp18;
    } locals;
    s16 *var_s1;
    s16 *var_s2;
    register s16 temp_a1 ASM_REG("$5");
    register s16 temp_a2 ASM_REG("$6");
    s32 var_s0;
    register s16 var_s5 ASM_REG("$21");
    register s16 var_s4 ASM_REG("$20");
    s32 *temp_fp;
    register s32 temp_a0_2 ASM_REG("$4");
    register s32 temp_s7 ASM_REG("$23");
    register s32 temp_v0_2 ASM_REG("$2");
    s32 var_s3;
    s32 var_s6;
    s32 var_v0;
    register s32 bad_value ASM_REG("$2");
    u16 temp_v1;
    register s32 temp_v1_load ASM_REG("$3");
    void *temp_a0;
    void *temp_v0;
    register void *temp_v0_3 ASM_REG("$2");
    void *temp_v0_4;
    register u8 *temp_t1 ASM_REG("$9");
    register u16 *temp_v1_addr ASM_REG("$3");

    temp_s7 = D_8008333C;
    temp_fp = &D_8008333C;
    locals.sp18 = arg0;
    var_s4 = func_80017F88(arg0, &locals.sp10, &locals.sp12, 0);
    if (var_s4 < 0x200) {
        goto valid;
    }
bad:
    bad_value = 0;
    ASM_TAILSLOT_PIN(bad_value);
    return func_80017E88();
valid:
    {
        register s32 early_y ASM_REG("$2");
        register s32 early_shift ASM_REG("$3");
        register s32 early_x ASM_REG("$4");

        early_y = locals.sp12;
        early_shift = M2C_FIELD(temp_fp, s16 *, 0x14);
        early_x = locals.sp10;
        temp_v0 = ((early_x + (early_y << early_shift)) * 6) + temp_s7;
        ASM_KEEP_NV(early_y);
        ASM_KEEP_NV(early_shift);
        ASM_KEEP_NV(early_x);
    }
    M2C_FIELD(temp_v0, u16 *, 4) = (u16)(M2C_FIELD(temp_v0, u16 *, 4) | 0x100);
    var_s6 = func_80017EBC(arg0);
loop_4:
    var_s5 = -1;
    var_s3 = 0;
    var_s0 = 7;
    temp_t1 = (u8 *)&D_8006CCE8;
    ASM_KEEP_NV(temp_t1);
    var_s2 = (s16 *)(temp_t1 + 0xE);
    temp_t1 = (u8 *)&D_8006CCD8;
    ASM_KEEP_NV(temp_t1);
        var_s1 = (s16 *)(temp_t1 + 0xE);
    do {
        if ((func_80018304(locals.sp10, locals.sp12, var_s4, (s16)var_s0) << 0x10) != 0) {
            register s32 loop_x ASM_REG("$5");

            loop_x = locals.sp10;
            ASM_KEEP_NV(loop_x);
            temp_v0_2 = *var_s1;
            ASM_KEEP_NV(temp_v0_2);
            temp_v1_load = *var_s2;
            ASM_KEEP_NV(temp_v1_load);
            loop_x += temp_v0_2;
            ASM_KEEP_NV(loop_x);
            ASM_SET(temp_a0_2);
            temp_v0_2 = locals.sp12;
            ASM_KEEP_NV(temp_v0_2);
            temp_a0_2 = M2C_FIELD(temp_fp, s16 *, 0x14);
            ASM_KEEP_NV(temp_a0_2);
            temp_v0_2 += temp_v1_load;
            ASM_KEEP_NV(temp_v0_2);
            temp_v0_2 <<= temp_a0_2;
            ASM_KEEP_NV(temp_v0_2);
            temp_a0_2 = loop_x + temp_v0_2;
            ASM_KEEP_NV(temp_a0_2);
            temp_a0 = (void *)((temp_a0_2 * 6) + temp_s7);
            temp_v1 = M2C_FIELD(temp_a0, u16 *, 4);
            if (!(temp_v1 & 0x100)) {
                M2C_FIELD(temp_a0, u16 *, 4) = (u16)(temp_v1 | 0x200);
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
        ASM_KEEP_NV(temp_v0_2);
        if (temp_v0_2 >= 0) {
            register s32 tail_x ASM_REG("$7");
            register s32 tail_y ASM_REG("$8");

            temp_v0_2 *= 2;
            temp_t1 = (u8 *)&D_8006CCD8;
            temp_v1_addr = (u16 *)(temp_t1 + temp_v0_2);
            ASM_KEEP_NV(temp_v1_addr);
            temp_t1 = (u8 *)&D_8006CCE8;
            temp_v0_3 = temp_t1 + temp_v0_2;
            ASM_KEEP_NV(temp_v0_3);
            temp_a2 = (u16)locals.sp10;
            ASM_KEEP_NV(temp_a2);
            temp_v1_load = *temp_v1_addr;
            ASM_KEEP_NV(temp_v1_load);
            temp_a1 = (u16)locals.sp12;
            ASM_KEEP_NV(temp_a1);
            temp_v0_2 = *(u16 *)temp_v0_3;
            ASM_KEEP_NV(temp_v0_2);
            temp_a2 += temp_v1_load;
            temp_a1 += temp_v0_2;
            temp_v0_2 = (u32)(u16)temp_a2 << 16;
            ASM_KEEP_NV(temp_v0_2);
            {
                register s32 tail_sum ASM_REG("$4");

                tail_x = temp_v0_2 >> 16;
                ASM_KEEP_NV(tail_x);
                temp_v1_load = (u32)(u16)temp_a1 << 16;
                ASM_KEEP_NV(temp_v1_load);
                temp_v0_2 = M2C_FIELD(temp_fp, s16 *, 0x14);
                ASM_KEEP_NV(temp_v0_2);
                tail_y = temp_v1_load >> 16;
                ASM_KEEP_NV(tail_y);
                tail_sum = tail_x + (tail_y << temp_v0_2);
                ASM_KEEP_NV(tail_sum);
                temp_v0_3 = (tail_sum * 6) + temp_s7;
            }
            ASM_KEEP(temp_v0_3);
            temp_a0_2 = var_s6 - 1;
            var_s6 = temp_a0_2;
            ASM_KEEP(var_s6);
            temp_v1_load = M2C_FIELD(temp_v0_3, u16 *, 4);
            locals.sp10 = temp_a2;
            locals.sp12 = temp_a1;
            M2C_FIELD(temp_v0_3, u16 *, 4) = (u16)(temp_v1_load | 0x100);
            if ((temp_a0_2 << 0x10) > 0) {
                var_s4 = func_800BCB04(((tail_x << 6) + 0x20) & 0xFFE0, ((tail_y << 6) + 0x20) & 0xFFE0, -0x400, tail_x);
                ASM_TAILSLOT_PIN(var_s4);
                return func_80017CA4();
            }
            goto block_17;
        }
        {
            register s16 *retry_a1 ASM_REG("$5");
            register s16 *retry_a2 ASM_REG("$6");
            register s32 retry_a3 ASM_REG("$7");
            register s32 retry_a0 ASM_REG("$4");

            temp_t1 = (u8 *)(u32)(u16)locals.sp18;
            ASM_KEEP_NV(temp_t1);
            retry_a1 = &locals.sp10;
            ASM_KEEP_NV(retry_a1);
            retry_a2 = &locals.sp12;
            ASM_KEEP_NV(retry_a2);
            retry_a3 = 1;
            ASM_KEEP_NV(retry_a3);
            retry_a0 = (s16)(u32)temp_t1;
            var_s4 = func_8001816C(retry_a0, retry_a1, retry_a2, retry_a3);
        }
        var_v0 = 0;
        if (var_s4 < 0x200) {
            register s32 retry_y ASM_REG("$2");
            register s32 retry_shift ASM_REG("$3");
            register s32 retry_x ASM_REG("$4");

            retry_y = locals.sp12;
            retry_shift = M2C_FIELD(temp_fp, s16 *, 0x14);
            retry_x = locals.sp10;
            temp_v0_4 = ((retry_x + (retry_y << retry_shift)) * 6) + temp_s7;
            ASM_KEEP_NV(retry_y);
            ASM_KEEP_NV(retry_shift);
            ASM_KEEP_NV(retry_x);
            ASM_KEEP(temp_v0_4);
            temp_a0_2 = var_s6 - 1;
            var_s6 = temp_a0_2;
            ASM_KEEP(var_s6);
            ASM_KEEP_NV(temp_a0_2);
            temp_v1_load = M2C_FIELD(temp_v0_4, u16 *, 4);
            ASM_KEEP_NV(temp_v1_load);
            temp_a0_2 <<= 0x10;
            ASM_KEEP_NV(temp_a0_2);
            M2C_FIELD(temp_v0_4, u16 *, 4) = (u16)(temp_v1_load | 0x100);
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
