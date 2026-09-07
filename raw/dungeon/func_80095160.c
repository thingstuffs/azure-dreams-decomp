#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u8 pad24[0x24];
    u8 x;
    u8 y;
    s8 flag;
} FuncArg1;

typedef struct {
    u8 pad1c[0x1c];
    u32 flags;
    u8 pad20[0x68];
    u16 height;
} FuncArg2;

typedef struct {
    u8 pad0c[0x0c];
    u16 flags;
    u8 tail[6];
} FuncMonster;

typedef struct {
    u16 value;
    u8 pad02[6];
} StackU16;

extern s16 D_8006CCD8[];
extern s16 D_8008333C[];
extern s16 D_8006CCE8[];
extern s16 D_800DCEAC[];
extern s16 D_800DCEBC[];
extern FuncMonster D_800E2970[];
extern s32 func_8009A350(s32, s32, s32, u16 *);
extern s32 func_8009A540(s32, s32, s32, s16);
void func_8009AB6C(void);
s32 func_8009B25C(FuncArg2 *, s32, s32, s32);
s16 func_8009FB34(u16, u16);
s32 func_800BCB04(s32, s32, s16);

s32 func_8009A8C0(u32 arg0, FuncArg1 *arg1, FuncArg2 * volatile arg2, u16 arg3) {
    StackU16 sp10;
    u16 sp18;
    s16 temp_v0_2;
    register s32 temp_v0_3 ASM_REG("$18");
    s32 var_a3;
    register u32 temp_idx ASM_REG("$4");
    register u8 *base_6ccd8 ASM_REG("$2");
    register s32 temp_a0 ASM_REG("$21");
    register s32 temp_s0 ASM_REG("$16");
    register s32 temp_s1 ASM_REG("$17");
    register s32 temp_s3 ASM_REG("$19");
    register s32 temp_v0_load ASM_REG("$2");
    s32 var_v0;
    register s32 var_v1 ASM_REG("$3");
    s32 first_mask;
    s16 *limits;
    u16 *temp_fp;
    register u16 *temp_s7 ASM_REG("$23");
    register u16 temp_s6 ASM_REG("$22");
    u32 temp_s0_2;
    u32 temp_s1_2;
    register u32 temp_s4 ASM_REG("$20");
    register s32 call_a0 ASM_REG("$4");
    register s32 call_a1 ASM_REG("$5");
    register s32 call_a2 ASM_REG("$6");
    register u32 call_a3 ASM_REG("$7");
    register u16 saved_arg3 ASM_REG("$7");
    u32 temp_t0;

    saved_arg3 = arg3;
    ASM_KEEP_NV(saved_arg3);
    temp_idx = (arg0 >> 9) & 7;
    ASM_KEEP_NV(temp_idx);
    temp_a0 = temp_idx;
    ASM_KEEP_NV(temp_a0);
    base_6ccd8 = (u8 *)D_8006CCD8;
    ASM_KEEP_NV(base_6ccd8);
    temp_s3 = temp_a0 * 2;
    temp_fp = (u16 *)((s32)temp_s3 + (s32)base_6ccd8);
    var_v1 = arg1->x;
    ASM_KEEP(var_v1);
    temp_v0_load = *temp_fp;
    ASM_KEEP_NV(temp_v0_load);
    call_a0 = temp_a0;
    ASM_KEEP_NV(call_a0);
    sp18 = saved_arg3;
    ASM_MEM_BARRIER();
    temp_s1 = var_v1 + temp_v0_load;
    limits = D_8008333C;
    first_mask = temp_s1 & 0xFFFF;
    if (first_mask != 0) {
        if (((1 << limits[10]) - 1) >= first_mask) {
            ASM_USE_NV(temp_s1);
            temp_s7 = (u16 *)((u8 *)D_8006CCE8 + temp_s3);
            var_v1 = arg1->y;
            ASM_KEEP(var_v1);
            temp_v0_load = *temp_s7;
            ASM_KEEP_NV(temp_v0_load);
            temp_s0 = var_v1 + temp_v0_load;
            var_v1 = temp_s0 & 0xFFFF;
            if (var_v1 != 0) {
                if (((1 << limits[11]) - 1) >= var_v1) {
                    var_v1 = *(volatile u8 *)&arg1->x;
                    ASM_KEEP_NV(var_v1);
                    temp_v0_load = *(volatile u8 *)&arg1->y;
                    ASM_KEEP_NV(temp_v0_load);
                    temp_t0 = (u32)arg2;
                    ASM_KEEP_NV(temp_t0);
                    temp_s6 = ((FuncArg2 *)temp_t0)->height;
                    var_v1 <<= 6;
                    ASM_KEEP_NV(var_v1);
                    call_a1 = (u32)var_v1 >> 6;
                    ASM_KEEP_NV(call_a1);
                    temp_v0_load <<= 6;
                    ASM_KEEP_NV(temp_v0_load);
                    call_a2 = (u32)temp_v0_load >> 6;
                    ASM_KEEP_NV(call_a2);
                    temp_s0 = var_v1 + 0x20;
                    temp_s4 = temp_v0_load + 0x20;
                    var_v0 = func_8009A540(call_a0, call_a1, call_a2, (s16) (temp_s6 - saved_arg3)) << 0x10;
                    if (var_v0 != 0) {
                        call_a2 = temp_a0;
                        ASM_KEEP_NV(call_a2);
                        ASM_SET(call_a3);
                        call_a3 = (u32)&sp10.value;
                        ASM_KEEP_NV(call_a3);
                        ASM_SET(var_v1);
                        ASM_SET(temp_v0_load);
                        var_v1 = (s32)((u8 *)D_800DCEAC + temp_s3);
                        ASM_KEEP_NV(var_v1);
                        temp_v0_load = (s32)((u8 *)D_800DCEBC + temp_s3);
                        ASM_KEEP_NV(temp_v0_load);
                        call_a0 = arg1->x;
                        ASM_KEEP_NV(call_a0);
                        call_a1 = arg1->y;
                        ASM_KEEP_NV(call_a1);
                        var_v1 = *(u16 *)var_v1;
                        ASM_KEEP_NV(var_v1);
                        temp_v0_load = *(u16 *)temp_v0_load;
                        ASM_KEEP_NV(temp_v0_load);
                        temp_s1 = var_v1 + temp_s0;
                        temp_s0 = temp_v0_load + temp_s4;
                        func_8009A350(call_a0, call_a1, call_a2, (u16 *)call_a3);
                        if ((sp10.value & 0x8002) == 0) {
                            goto collision_clear;
                        }
                    }
                    var_v0 = 0;
                    func_8009AB6C();
                    return 0;
collision_clear:
                    ASM_KEEP(temp_s3);
                    if ((arg1->flag >= 0) || (temp_v0_2 = func_8009FB34((arg1->x + *temp_fp) & 0xFFFF, (arg1->y + *temp_s7) & 0xFFFF), (temp_v0_2 < 0)) || !(D_800E2970[temp_v0_2].flags & 2) || (var_v0 = 0, ((temp_t0 = (u32)arg2, ((FuncArg2 *)temp_t0)->flags & 0x2000) != 0))) {
                        if (sp10.value & 0x3300) {
                            temp_s1_2 = temp_s1 & 0xFFFF;
                            if (sp10.value & 0x40) {
                                {
                                    register s32 late_a0 ASM_REG("$4");
                                    register u32 late_t0 ASM_REG("$8");
                                    late_a0 = temp_s1_2;
                                    ASM_KEEP_NV(late_a0);
                                    temp_s0_2 = temp_s0 & 0xFFFF;
                                    ASM_USE(temp_s0_2);
                                    late_t0 = sp18;
                                    temp_v0_3 = func_800BCB04(late_a0, temp_s0_2, (s16) (temp_s6 - late_t0));
                                }
                                call_a1 = temp_s1_2 >> 6;
                                call_a2 = temp_s0_2 >> 6;
                                var_a3 = (s16)temp_v0_3;
                                if (var_a3 >= 0x201) {
                                    temp_t0 = (u32)arg2;
                                    var_a3 = (s16)((FuncArg2 *)temp_t0)->height;
                                }
                                ASM_KEEP_NV(temp_v0_3);
                                var_v0 = func_8009B25C(arg2, call_a1, call_a2, var_a3);
                                if (var_v0 == 0) {
                                    var_v1 = temp_v0_3 << 0x10;
                                    goto block_20;
                                }
                            }
tail_minus1:
                            var_v0 = -1;
                            func_8009AB6C();
                            return -1;
                        }
                        {
                            register u32 late_t0 ASM_REG("$8");
                            late_t0 = sp18;
                            temp_v0_3 = func_800BCB04(temp_s1 & 0xFFFF, temp_s0 & 0xFFFF, (s16) (temp_s6 - late_t0));
                        }
                        ASM_KEEP_NV(temp_v0_3);
                        var_v1 = temp_v0_3 << 0x10;
block_20:
                        var_v0 = -1;
                        if ((var_v1 >> 0x10) < 0x201) {
                            var_v0 = 1;
                        }
                        return var_v0;
                    }
                    return var_v0;
                }
            }
        }
        return -1;
    }
    goto tail_minus1;
}
