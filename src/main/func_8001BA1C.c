#include "common.h"
#include "m2c_compat.h"

extern u8 D_80410000[];
extern u8 D_80400000[];
extern u8 D_80408ADC[];

typedef struct S_80402A1C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0xC];
    u32 unk_18;
    u32 unk_1C;
} S_80402A1C_0;   /* arg1 in func_80402A1C */

void *func_80402A1C(void *arg0, S_80402A1C_0 *arg1) {
    M2C_UNK sp0;
    M2C_UNK sp4;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 second_p10;
    u32 temp_a0;
    u32 temp_a2;
    u32 temp_t3;
    u32 temp_t4;
    s32 first_shifted;
    u32 constant48;
    u32 constant101010;
    u8 *var_t1;
    u8 temp_v0_2;
    u8 *var_a3;
    u8 *var_t0;
    u8 *stack_end;

    var_t0 = (u8 *)arg0;
    memcpy(&sp0, D_80400000 + 0x544, 4);
    do {
        constant48 = 0x48;
    } while (0);
    constant101010 = 0x101010;
    var_t1 = (u8 *)&sp0;
    stack_end = (u8 *)&sp4;
    temp_v1 = arg1->unk_08 * 4;
    var_a3 = var_t0 + 0xB;
    temp_v0 = D_80408ADC[temp_v1] * 0xC;
    temp_a2 = temp_v0 + 8;
    temp_v1_2 = D_80408ADC[temp_v1 + 1] * 0x11;
    temp_t4 = temp_a2 >> 1;
    arg1->unk_18 = temp_a2;
    temp_a0 = temp_v1_2 + 8;
    temp_t3 = temp_a0 >> 1;
    temp_v0 += 0xA;
    first_shifted = (s32)temp_v0 >> 1;
    do {
        do {
            second_p10 = temp_v1_2 + 0xA;
        } while (0);
    } while (0);
    arg1->unk_1C = temp_a0;
loop:
        do {
            var_a3[-1] = (u8)temp_t4;
            var_a3[0] = (u8)temp_t3;
            var_a3[-0xA] = (u8)constant48;
            *(u32 *)(var_a3 - 7) = constant101010;
            var_a3 += 0xC;
            var_t0[0] = *var_t1;
            var_t0 += 0xC;
            var_a3[-1] = (u8)first_shifted;
            var_a3[0] = (u8)((u32)second_p10 >> 1);
            var_a3[-0xA] = (u8)constant48;
            *(u32 *)(var_a3 - 7) = constant101010;
            temp_v0_2 = *var_t1;
            var_a3 += 0xC;
            var_t0[0] = temp_v0_2;
            var_t0 += 0xC;
            memcpy(var_t0, D_80410000 - 0x7394, 0x18);
            *(u32 *)(var_a3 - 7) = 0x30BFC0;
            *(u32 *)(var_a3 + 1) = 0x30BFC0;
            *(u32 *)(var_a3 + 5) = 0x30BFC0;
            *(u32 *)(var_a3 + 9) = 0x30BFC0;
            var_a3[-1] = (u8)temp_t4;
            var_a3[0] = (u8)temp_t3;
            var_a3 += 0x18;
            temp_v0_2 = *var_t1;
            var_t1 += 1;
            var_t0[0] = temp_v0_2;
            var_t0 += 0x18;
        } while (0);
    if ((s32)var_t1 < (s32)stack_end)
        goto loop;
    ASM_SET(stack_end);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_t0[-0x18] |= 0x80;
    return var_t0;
}
