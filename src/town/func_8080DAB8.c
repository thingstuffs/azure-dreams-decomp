/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8080DAB8_5 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_8080DAB8_5;   /* (u8 *)((u32)temp_a1 + (u32)*rootp) in func_8080DAB8 */


typedef struct S_8080DAB8_0 {
    u8 pad_00[0x8D0];
    s32 unk_8D0;
} S_8080DAB8_0;   /* *rootp in func_8080DAB8 */

typedef struct S_8080DAB8_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_8080DAB8_1;   /* temp_s0 in func_8080DAB8 */

typedef struct S_8080DAB8_2 {
    s32 unk_00;
    u8 pad_04[0x1C];
    s32 unk_20;
    s32 unk_24;
} S_8080DAB8_2;   /* var_s3 in func_8080DAB8; pointer addresses record offset 0x8 */

typedef struct S_8080DAB8_3 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_8080DAB8_3;   /* temp_a0_2 in func_8080DAB8 */

typedef struct S_8080DAB8_4 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_8080DAB8_4;   /* (u8 *)temp_a1 in func_8080DAB8 */


#define M2C_BREAK() ((void)0)

M2C_UNK func_8006BFA0();
s32 func_8006D9DC();
M2C_UNK func_8006DBBC();
M2C_UNK func_8006DD4C();
M2C_UNK func_8006F49C();
extern u8 *D_8012F130;

s32 func_8080DAB8(void *arg0) {
    register s32 temp_a0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    s32 temp_a1;
    s32 temp_s0;
    M2C_UNK *temp_s1;
    s32 var_v1;
    s32 var_v1_2;
    u16 temp_v0;
    u16 temp_v0_2;
    u32 temp_v1;
    u32 temp_v1_2;
    u32 coord0_shifted;
    u32 coord1_shifted;
    s32 coord0_signed;
    s32 coord1_signed;
    u32 temp_low;
    register S_8080DAB8_3 *temp_a0_2 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    void *temp_a1_2;
    void *var_s3;
    u8 **rootp;
    register u8 *scratch0;
    u8 *scratch1;
    u8 *scratch2;
    register u8 *bound_base0 ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *bound_base1 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    register u32 mask_low ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u32 mask_high;
    register u32 bound_const ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */

    var_s3 = arg0;
    rootp = &D_8012F130;
    scratch0 = (u8 *)0x1F800000;
    scratch1 = (u8 *)0x1F800100;
    scratch2 = (u8 *)0x1F800180;
    mask_low = 0x00FFFFFF;
    mask_high = 0xFF000000;
    do {
        func_8006BFA0(var_s3 + 8, scratch0, scratch1, scratch2, scratch2, 2);
        var_v1 = 0;
        ASM_KEEP_NV(var_v1);   /* MATCH pin: load-bearing for the whole function shape */
        temp_s0 = ((S_8080DAB8_0 *)(*rootp))->unk_8D0;
        if (temp_s0 != 0) {
            temp_v1 = temp_s0 + 0x14;
            bound_base0 = (u8 *)*rootp;
            ASM_KEEP_NV(bound_base0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            bound_const = 0x108D4;
            var_v1 = temp_v1 & (0 - ((u32)(bound_base0 + bound_const) >= temp_v1));
        }
        ((S_8080DAB8_0 *)(*rootp))->unk_8D0 = var_v1;
        var_v1_2 = 0;
        ASM_KEEP_NV(var_v1_2);   /* MATCH pin: load-bearing for the whole function shape */
        temp_s1 = ((S_8080DAB8_0 *)(*rootp))->unk_8D0;
        if (temp_s1 != 0) {
            temp_v1_2 = (u8 *)temp_s1 + 0xC;
            bound_base1 = (u8 *)*rootp;
            ASM_KEEP_NV(bound_base1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            bound_const = 0x108D4;
            var_v1_2 = temp_v1_2 & (0 - ((u32)(bound_base1 + bound_const) >= temp_v1_2));
        }
        ((S_8080DAB8_0 *)(*rootp))->unk_8D0 = var_v1_2;
        func_8006F49C((s32 *)temp_s1, 0, 0, func_8006D9DC(0, 0, 0, 0) & 0xFFFF, 0);
        ((S_8080DAB8_1 *)temp_s0)->unk_04 = (s32)((S_8080DAB8_2 *)((u8 *)var_s3 - 0x8))->unk_20;
        ((S_8080DAB8_1 *)temp_s0)->unk_0C = (s32)((S_8080DAB8_2 *)((u8 *)var_s3 - 0x8))->unk_24;
        func_8006DD4C((s32 *)temp_s0);
        func_8006DBBC((s32 *)temp_s0, 1);
        ((S_8080DAB8_1 *)temp_s0)->unk_08 = (s32)*(s32 *)scratch0;
        ((S_8080DAB8_1 *)temp_s0)->unk_10 = (s32)*(s32 *)(scratch0 + 4);
        temp_v0 = *(volatile u16 *)scratch1;
        coord0_shifted = temp_v0 << 0x10;
        temp_v0_2 = *((volatile u16 *)scratch1 + 1);
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        coord0_signed = (s32)coord0_shifted >> 0x10;
        coord1_shifted = temp_v0_2 << 0x10;
        coord1_signed = (s32)coord1_shifted >> 0x10;
        coord0_shifted = (u32)((s32)coord0_shifted >> 0x13);
        if (coord0_signed >= coord1_signed) {
            coord0_shifted = (u32)((s32)coord1_shifted >> 0x13);
        }
        temp_a1 = (s32)(coord0_shifted << 0x10) >> 0xE;
        ((S_8080DAB8_1 *)temp_s0)->unk_00 = (s32)((((S_8080DAB8_1 *)temp_s0)->unk_00 & mask_high) | (((S_8080DAB8_5 *)((u8 *)((u32)temp_a1 + (u32)*rootp)))->unk_B0 & mask_low));
        temp_a0_2 = (void *)((u32)temp_a1 + (u32)*rootp);
        temp_low = temp_s0 & mask_low;
        temp_a0_2->unk_B0 = (s32)((temp_a0_2->unk_B0 & mask_high) | temp_low);
        *temp_s1 = (s32)((*temp_s1 & mask_high) | (((S_8080DAB8_5 *)((u8 *)((u32)temp_a1 + (u32)*rootp)))->unk_B0 & mask_low));
        temp_a1 = temp_a1 + (u8 *)*rootp;
        temp_low = (u32)temp_s1 & mask_low;
        ((S_8080DAB8_4 *)((u8 *)temp_a1))->unk_B0 = (s32)((((S_8080DAB8_4 *)((u8 *)temp_a1))->unk_B0 & mask_high) | temp_low);
        temp_a0 = ((S_8080DAB8_2 *)((u8 *)var_s3 - 0x8))->unk_00;
        var_s3 = temp_a0 + 0x20;
    } while (temp_a0 != 0);
    ASM_KEEP_NV(temp_a0);   /* MATCH pin: retail register colouring depends on it */
    return 0;
}
