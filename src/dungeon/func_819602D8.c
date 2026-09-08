#include "common.h"
#include "m2c_compat.h"

extern u16 D_800273CC[8];
extern u8 D_8002744C[9];
extern u8 D_8002744D[9];
extern u8 *D_800E3D7C[];
extern u8 D_8008333C[32];
extern s16 D_8008333C_second[16] __asm__("D_8008333C");
extern s32 D_800274DC[7][8];
void func_80025C14(void) __attribute__((noreturn));
s32 func_80025D30(s32, s32, s32);
void *func_8009B4B0(void *, u16, u16);
s32 func_800BCA68(s32, u16);
extern s32 D_8002732C;

typedef struct S_819602D8_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_819602D8_0;   /* temp_v0 in func_819602D8 */

void func_819602D8(s16 arg0, s32 arg1) {
    volatile union {
        u16 h;
        u8 b;
    } subroutine_arg4;
    register s32 var_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 var_s3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 var_s5;
    u8 *var_s7;
    s32 temp_s6;
    s32 temp_s8;
    register u16 *var_s2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u32 var_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u32 var_s4;
    u8 *store_page;
    s32 var_a0;
    s32 first_result;
    void *lookup_arg;
    S_819602D8_0 *temp_v0;

    var_s5 = arg1 - 3;
    var_s4 = 0;
    var_s7 = D_800273CC;
    store_page = (u8 *)0x80020000;
    subroutine_arg4.h = arg0;
    {
        register u32 store_byte ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        store_byte = subroutine_arg4.b;
        ASM_KEEP4_NV(store_page, var_s4, var_s5, var_s7);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        store_page[0x744C] = store_byte;
    }
    do { *D_8002744D = arg1; } while (0);
loop_1:
    {
        register u32 loop_arg ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 sign_temp ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        loop_arg = subroutine_arg4.h;
        ASM_KEEP_NV(loop_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        var_s1 = 0;
        sign_temp = var_s5 << 16;
        var_s3 = sign_temp >> 16;
        temp_s6 = var_s3 << 6;
        ASM_KEEP_NV(temp_s6);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        temp_s8 = temp_s6 + 0x20;
        ASM_KEEP_NV(temp_s6);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        var_s2 = (u16 *)var_s7;
        var_s0 = loop_arg - 3;
    }
    ASM_USE2_NV(temp_s6, var_s5);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_USE_NV(var_s4);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
loop_2:
    first_result = func_800BCA68((var_s0 << 6) & 0xFFC0, temp_s6);
    lookup_arg = *D_800E3D7C;
    *var_s2 = 0 - first_result;
    temp_v0 = func_8009B4B0(lookup_arg, var_s0, var_s5);
    if ((temp_v0 != NULL) && (temp_v0 != D_8002732C)) {
        temp_v0->unk_14 = (s32)(temp_v0->unk_14 | 0x100000);
    }
    var_a0 = (s16)var_s0;
    if (var_a0 < 0) {
        goto bounds_fail;
    }
    {
        s32 shift0;
        {
            register s16 *bounds0 ASM_REG("$7") = (s16 *)D_8008333C;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            shift0 = bounds0[10];
            ASM_USE_NV(bounds0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        }
        {
            register s32 one0 ASM_REG("$7") = 1;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            shift0 = one0 << shift0;
        }
        shift0 = var_a0 < shift0;
        if (!shift0) {
            goto bounds_fail;
        }
    }
    if (var_s3 < 0) {
        goto bounds_fail;
    }
    {
        s32 shift1;
        {
            register s16 *bounds1 ASM_REG("$7") = D_8008333C_second;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            shift1 = bounds1[11];
            ASM_USE_NV(bounds1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        }
        {
            register s32 one1 ASM_REG("$7") = 1;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            shift1 = one1 << shift1;
        }
        shift1 = var_s3 < shift1;
        if (shift1) {
            goto bounds_ok;
        }
    }
bounds_fail:
    {
        register s32 zero_arg ASM_REG("$4") = 0;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_TAILSLOT_PIN(zero_arg);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80025C14();
    }
bounds_ok:
    {
        s32 *output_base;
        register u32 output_row ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        s32 output_value;
        var_a0 <<= 6;
        var_a0 += 0x20;
        var_a0 &= 0xFFE0;
        output_value = func_80025D30(var_a0, temp_s8 & 0xFFFF, -0x400);
        ASM_KEEP_NV(output_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        output_base = &D_800274DC[0][0];
        ASM_KEEP_NV(output_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        output_row = var_s4 << 5;
        output_row += (u32)output_base;
        ((s32 *)output_row)[var_s1] = output_value;
    }
    var_s2 += 1;
    var_s1 += 1;
    var_s0 += 1;
    if (var_s1 >= 7U) {
        var_s7 += 16;
        var_s4 += 1;
        var_s5 += 1;
        if (var_s4 >= 7U) {
            return;
        }
        goto loop_1;
    }
    goto loop_2;
}
