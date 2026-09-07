#include "common.h"

extern u8 D_80083160_addr[] asm("D_80083160");
extern void func_80026A18(void) __attribute__((noreturn));
extern s32 func_800654B0();
extern s32 func_8006658C();
extern s32 func_800666F4();

s32 func_819611CC(void *arg0, s32 arg1, void *arg2)
{
    u8 *spad;
    u8 *global_base;
    u32 page_color;
    u8 *global_ptr;
    u8 *initial_ptr;
    u8 *var_s4;
    register u8 *temp_s0 ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u8 *temp_s1 ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v0_4;
    register u8 temp_v1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 temp_sum_rhs ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u16 copy_half;
    u16 last_half;
    u32 temp_v0;
    register u32 copy_word ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register void *temp_a0 ASM_REG("$4");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *call_a1 ASM_REG("$5");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *call_a3;
    u8 *stack_arg0;
    u8 *temp_a1;
    void *temp_a2;
    register void *arg0_reg ASM_REG("$19") = arg0;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *arg2_reg = arg2;
    register s32 ret ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 zero ASM_REG("$0");   /* MATCH pin: load-bearing for the whole function shape */

    initial_ptr = *((u8 **) D_80083160_addr);
    global_base = D_80083160_addr;
    var_s4 = *((u8 **) (initial_ptr + 0x8D0));
    spad = (volatile u8 *) 0x1F800000;
    *((u32 *) (spad + 0x20)) = (u32) (initial_ptr + 0xB0);
    ASM_KEEP_MEMDEP(spad, page_color, *((u8 **) D_80083160_addr));   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    temp_s0 = var_s4 + 7;
    ASM_KEEP(temp_s0);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    *((u32 *) (spad + 0x70)) = *((u32 *) (((u8 *) arg0_reg) + 0x10));
    *((u32 *) (spad + 0x78)) = *((u32 *) (((u8 *) arg0_reg) + 0x18));
    *((u32 *) (spad + 0x80)) = *((u32 *) (((u8 *) arg0_reg) + 0x20));
    temp_a0 = spad + 0x70;
    copy_half = *((u16 *) (((u8 *) arg0_reg) + 0x14));
    temp_s1 = *((u8 **) (((u8 *) arg2_reg) + 8));
    ASM_KEEP(temp_s1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    copy_word = *((u32 *) (((u8 *) arg0_reg) + 0x28));
    call_a1 = spad + 0x78;
    *((u16 *) (spad + 0x74)) = copy_half;
    copy_half = *((u16 *) (((u8 *) arg0_reg) + 0x1C));
    temp_a2 = spad + 0x80;
    *((u16 *) (spad + 0x7C)) = copy_half;
    copy_half = *((u16 *) (((u8 *) arg0_reg) + 0x24));
    ASM_SET(call_a3);   /* MATCH pin: retail schedule: same instructions, different order without it */
    call_a3 = spad + 0x88;
    *((u32 *) (spad + 0x88)) = copy_word;
    *((u16 *) (spad + 0x84)) = copy_half;
    last_half = *((u16 *) (((u8 *) arg0_reg) + 0x2C));
    stack_arg0 = var_s4 + 8;
    *((u16 *) (spad + 0x8C)) = last_half;
    ASM_KEEP_NV(global_base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_JALDELAY_PIN(last_half);   /* MATCH pin: load-bearing for the whole function shape */
    temp_v0 = func_800654B0(temp_a0, call_a1, temp_a2, call_a3, stack_arg0,
                            var_s4 + 0x10, var_s4 + 0x18, var_s4 + 0x20,
                            (void *) (spad + 0x90), (void *) (spad + 0x94)) - 8;
    *((u32 *) (spad + 0xC0)) = temp_v0;
    if (temp_v0 < 480) {
        temp_v0_2 = temp_s1[8];
        temp_s0[0x15] = temp_v0_2;
        temp_s0[5] = temp_v0_2;
        temp_v1 = temp_s1[8];
        temp_sum_rhs = temp_s1[0xA];
        temp_v1 = temp_v1 + temp_sum_rhs;
        temp_s0[0x1D] = temp_v1;
        temp_s0[0xD] = temp_v1;
        temp_v0_3 = temp_s1[9];
        temp_s0[0xE] = temp_v0_3;
        temp_s0[6] = temp_v0_3;
        temp_v1 = temp_s1[9];
        temp_sum_rhs = temp_s1[0xB];
        temp_v1 = temp_v1 + temp_sum_rhs;
        temp_s0[0x1E] = temp_v1;
        temp_s0[0x16] = temp_v1;
        *((u16 *) (temp_s0 + 0xF)) = *((u16 *) (temp_s1 + 4));
        *((s32 *) (temp_s0 - 3)) = *((s32 *) (((u8 *) arg2_reg) + 0xC));
        func_800666F4(var_s4);
        temp_a1 = var_s4;
        temp_v0_4 = temp_s0[0];
        var_s4 += 0x28;
        temp_s0[0] = temp_v0_4 | 2;
        temp_s0 += 0x28;
        ASM_KEEP(temp_s0);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        func_8006658C((*((u32 *) (spad + 0x20))) + ((*((u32 *) (spad + 0xC0))) << 2), temp_a1);
    }
    temp_a2 = ((void **) arg0_reg)[-2];
    if (temp_a2 != 0) {
        arg0_reg = ((u8 *) temp_a2) + 32;
        ASM_KEEP(arg0_reg);   /* MATCH pin: keeps a statement from moving across a call/branch */
        arg2_reg = *((void **) (((u8 *) temp_a2) + 12));
        ASM_KEEP(arg2_reg);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        func_80026A18();
    }
    global_ptr = *((u8 **) global_base);
    ASM_SET(zero);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ret = zero;
    ASM_KEEP(ret);   /* MATCH pin: retail schedule: same instructions, different order without it */
    *((u32 *) (global_ptr + 0x8D0)) = (u32) var_s4;
    return ret;
}
