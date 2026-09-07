#include "common.h"
#include "m2c_compat.h"

typedef struct S_80093E74_7 {
    u8 pad_00[0xD0];
    union { void * s; s32 u; } unk_D0;   /* accessed as both */
} S_80093E74_7;   /* ((arg3->unk_8A * 4) + arg0) in func_80093E74 */


typedef struct S_80093E74_0 {
    u8 pad_00[0x60];
    void * unk_60;
    u8 pad_64[0x26];
    s16 unk_8A;
} S_80093E74_0;   /* arg3 in func_80093E74 */

typedef struct S_80093E74_1 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_80093E74_1;   /* temp_a0 in func_80093E74 */

typedef struct S_80093E74_2 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x94];
    u8 unk_A8;
} S_80093E74_2;   /* temp_s1 in func_80093E74 */

typedef struct S_80093E74_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80093E74_3;   /* temp_a0_2 in func_80093E74 */

typedef struct S_80093E74_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80093E74_4;   /* temp_a0_3 in func_80093E74 */

typedef struct S_80093E74_5 {
    void * unk_00;
    u8 pad_04[0x2C];
    s32 unk_30;
} S_80093E74_5;   /* temp_v1 in func_80093E74; pointer addresses record offset 0x14 */

typedef struct S_80093E74_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80093E74_6;   /* temp_v1_2 in func_80093E74 */


#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

typedef struct {
    s32 words[4];
} Copy16;

typedef struct {
    s32 words[3];
} Copy12;

typedef struct {
    s32 words[35];
} Copy140;

s32 func_80042900();                 /* extern */
void func_8009A3D0(u8, u8, s32);     /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern void *D_800E3DF0[];
extern u8 D_800E3E48[];

void func_80093E74(s32 arg0, void *arg1, void *arg2, S_80093E74_0 *arg3) {
    M2C_UNK var_a2_2;
    u8 var_a0_4;
    u8 var_a1_4;
    s32 temp_s0;
    register s32 temp_v0_3 ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 temp_s3 ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void **temp_base2;
    void **temp_s2;
    S_80093E74_3 *temp_a0_2;
    S_80093E74_4 *temp_a0_3;
    S_80093E74_2 *temp_s1;
    void *temp_t0;
    void *temp_v0_2;
    void *temp_v1;
    S_80093E74_6 *temp_v1_2;
    void *var_a2;
    void *var_a3;

    {
        s32 temp_v1_byte;
        register s32 temp_v0 ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
        register S_80093E74_1 *temp_a0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
        void **temp_base;
        u8 temp_s3_byte;

        temp_a0 = ((S_80093E74_7 *)(((arg3->unk_8A * 4) + arg0)))->unk_D0.s;
        temp_v0 = temp_a0->unk_03;
        temp_v1_byte = temp_v0 & 0xDF;
        temp_v0 &= 0x1F;
        ASM_KEEP(temp_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        temp_s3_byte = (u8)temp_v0;
        temp_s3 = temp_s3_byte;
        temp_s0 = temp_s3;
        ASM_KEEP(temp_s0);   /* MATCH pin: retail delay-slot fill depends on it */
        temp_base = D_800E3DF0;
        temp_a0->unk_03 = (u8) temp_v1_byte;
        temp_s2 = temp_base + temp_s0;
        temp_s1 = *temp_s2;
    }
    if ((func_80042900(temp_s1, 0xA) << 0x10) != 0) {
        temp_s1->unk_13 = (u8) temp_s1->unk_A8;
    }
    temp_v0_2 = &D_800E3E48[((((temp_s0 * 8) + temp_s0) * 4) - temp_s0) * 4];
    *temp_s2 = temp_v0_2;
    *(Copy140 *) temp_v0_2 = *(Copy140 *) temp_s1;
    temp_base2 = D_800E3DF0;
    ASM_KEEP(temp_base2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_v0_3 = temp_s3 << 2;
    temp_v0_3 += (s32)temp_base2;
    temp_a0_2 = *(void **)temp_v0_3;
    temp_a0_2->unk_14 = (s32) (temp_a0_2->unk_14 & ~0x4000);
    ((S_80093E74_7 *)(((arg3->unk_8A * 4) + arg0)))->unk_D0.u = 0;
    temp_a0_3 = arg3->unk_60;
    temp_a0_3->unk_1C = (s32) (temp_a0_3->unk_1C | 0x400000);
    temp_v1 = arg3->unk_60;
    temp_v1_2 = ((S_80093E74_5 *)((u8 *)temp_v1 - 0x14))->unk_00;
    var_a0_4 = temp_v1_2->unk_24;
    var_a1_4 = temp_v1_2->unk_25;
    var_a2_2 = 0x3000;
    if (((S_80093E74_5 *)((u8 *)temp_v1 - 0x14))->unk_30 & 0x2000) {
        var_a2_2 = 0x300;
    }
    func_8009A3D0(var_a0_4, var_a1_4, var_a2_2);
    func_800A56E0(0x704);
}
