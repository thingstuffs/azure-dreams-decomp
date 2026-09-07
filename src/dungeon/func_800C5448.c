#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CABA8_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x8];
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_AC;   /* overlapping accesses */
    u16 unk_B0;
    u8 pad_B2[0x4];
    u16 unk_B6;
    s16 unk_B8;
} S_800CABA8_0;   /* arg0 in func_800CABA8 */

typedef struct S_800CABA8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CABA8_1;   /* arg2 in func_800CABA8 */

typedef struct S_800CABA8_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_800CABA8_2;   /* temp_s2 in func_800CABA8 */


extern void *D_80089440[];
M2C_UNK func_8009C12C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
extern void func_800CAA94(void *, M2C_UNK, void *);
M2C_UNK func_800CAFDC();
M2C_UNK func_800CB4C0();
extern u16 D_80013714;
extern s32 D_8008346C;
extern u8 D_800C9F34;

void func_800CABA8(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    s16 temp_v1_2;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s16 var_v1;
    register s32 temp_a0 ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 temp_a2;
    s32 temp_divisor;
    s32 temp_v0_2;
    register s32 temp_v0_3 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    s32 var_t1;
    u16 temp_v0;
    u16 temp_v0_4;
    u16 temp_flags;
    u8 temp_a1;
    s32 temp_a1_2;
    s32 temp_a3;
    s32 temp_a3_2;
    register u8 temp_t0 ASM_REG("$8");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 temp_v1;
    void *temp_s0;
    void *temp_s2;
    void *var_a3;

    var_a3 = arg3;
    temp_v1 = ((S_800CABA8_0 *)arg0)->unk_9B;
    temp_s2 = var_a3;
    if (temp_v1 >= 5U) {
        goto block_23;
    }
    (void)jt_keep; goto *D_80089440[(u32)(temp_v1)];
jt_c0:
    ((S_800CABA8_0 *)arg0)->unk_B8 = 1;
    if (!(((S_800CABA8_1 *)arg2)->unk_14 & 0x8000)) {
        goto block_4;
    }
    func_8009C12C(temp_s2, arg2, ((S_800CABA8_2 *)temp_s2)->unk_2A, 0);
    ((S_800CABA8_0 *)arg0)->unk_9B = 4U;
    return;
block_4:
    ((S_800CABA8_0 *)arg0)->unk_B0 = (u16) ((S_800CABA8_2 *)temp_s2)->unk_2A;
    ((S_800CABA8_0 *)arg0)->unk_9B = (u8) (((S_800CABA8_0 *)arg0)->unk_9B + 1);
jt_c1:
    ((S_800CABA8_0 *)arg0)->unk_98 |= 8;
    temp_v0 = ((S_800CABA8_0 *)arg0)->unk_A0.at02.v + 0x10;
    ((S_800CABA8_0 *)arg0)->unk_A0.at02.v = temp_v0;
    if ((s16) temp_v0 < 0x81) {
        goto block_23;
    }
    ((S_800CABA8_0 *)arg0)->unk_A0.at02.v = 0x80U;
    ASM_MEM_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    temp_v0_2 = ((S_800CABA8_0 *)arg0)->unk_9B;
    var_v1 = 8;
    goto block_9;
jt_c2:
    temp_s0 = arg0 - 0x20;
    ((S_800CABA8_0 *)arg0)->unk_A0.at00.v = (s32) (((S_800CABA8_0 *)arg0)->unk_A0.at00.v - (((S_800CABA8_0 *)arg0)->unk_A0.at00.v / (s16) ((S_800CABA8_0 *)arg0)->unk_96));
    func_800CAFDC(temp_s0, ((S_800CABA8_2 *)temp_s2)->unk_2A, ((S_800CABA8_0 *)arg0)->unk_AC.at00.v);
    func_800CB4C0(temp_s0, 1);
    temp_t0 = (u8) ((S_800CABA8_0 *)arg0)->unk_AC.at00.v;
    temp_a2 = (s32) (0xE0 - temp_t0) / (s16) ((S_800CABA8_0 *)arg0)->unk_96;
    temp_a3 = ((S_800CABA8_0 *)arg0)->unk_AC.at01.v;
    ASM_MEM_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    temp_divisor = ((S_800CABA8_0 *)arg0)->unk_96;
    ASM_KEEP(temp_divisor);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_a0 = (s32) (8 - temp_a3) / temp_divisor;
    ASM_MEM_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    temp_a1 = ((S_800CABA8_0 *)arg0)->unk_AC.at02.v;
    temp_v0_3 = (s32) (8 - temp_a1) / (s16) ((S_800CABA8_0 *)arg0)->unk_96;
    temp_v1_2 = (u16) ((S_800CABA8_0 *)arg0)->unk_96 - 1;
    ((S_800CABA8_0 *)arg0)->unk_96 = temp_v1_2;
    temp_t0 = (u8) (temp_t0 + temp_a2);
    temp_a3 += temp_a0;
    ((S_800CABA8_0 *)arg0)->unk_AC.at00u.v = temp_t0;
    ((S_800CABA8_0 *)arg0)->unk_AC.at01.v = (u8) temp_a3;
    ((S_800CABA8_0 *)arg0)->unk_AC.at02.v = (u8) (temp_a1 + temp_v0_3);
    if ((temp_v1_2 << 0x10) > 0) {
        goto block_23;
    }
    func_8009C12C(temp_s2, arg2, ((S_800CABA8_2 *)temp_s2)->unk_2A, 0);
    temp_v0_2 = ((S_800CABA8_0 *)arg0)->unk_9B;
    ASM_KEEP(temp_v0_2);   /* MATCH pin: retail basic-block layout depends on it */
    var_v1 = 4;
block_9:
    ((S_800CABA8_0 *)arg0)->unk_96 = var_v1;
    ASM_MEM_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    ((S_800CABA8_0 *)arg0)->unk_9B = (u8) (temp_v0_2 + 1);
    return;
jt_c3:
    if ((s16) ((S_800CABA8_0 *)arg0)->unk_B0 == ((S_800CABA8_2 *)temp_s2)->unk_2A) {
        goto block_12;
    }
    ((S_800CABA8_2 *)temp_s2)->unk_2A = (s16) ((u16) ((S_800CABA8_2 *)temp_s2)->unk_2A + 0x200);
    var_t1 = 0;
    goto block_13;
block_12:
    var_t1 = 1;
block_13:
    temp_v1_3 = ((S_800CABA8_0 *)arg0)->unk_96;
    if (temp_v1_3 <= 0) {
        goto block_15;
    }
    temp_t0 = (u8) ((S_800CABA8_0 *)arg0)->unk_AC.at00.v;
    temp_a3_2 = ((S_800CABA8_0 *)arg0)->unk_AC.at01.v;
    temp_a1_2 = ((S_800CABA8_0 *)arg0)->unk_AC.at02.v;
    ((S_800CABA8_0 *)arg0)->unk_AC.at00u.v = (u8) (temp_t0 + ((s32) (0x40 - temp_t0) / temp_v1_3));
    var_a3 = temp_a3_2 + ((s32) (0x40 - temp_a3_2) / (s16) ((S_800CABA8_0 *)arg0)->unk_96);
    ((S_800CABA8_0 *)arg0)->unk_AC.at01.v = (u8) var_a3;
    ((S_800CABA8_0 *)arg0)->unk_AC.at02.v = (u8) (temp_a1_2 + ((s32) (0x40 - temp_a1_2) / (s16) ((S_800CABA8_0 *)arg0)->unk_96));
    goto block_16;
block_15:
    ((S_800CABA8_0 *)arg0)->unk_96 = 0;
block_16:
    temp_v0_2 = (u16) ((S_800CABA8_0 *)arg0)->unk_96;
    temp_v1_4 = temp_v0_2 - 1;
    temp_v0_2 = var_t1;
    ((S_800CABA8_0 *)arg0)->unk_96 = temp_v1_4;
    if (temp_v0_2 == 0) {
        goto block_23;
    }
    temp_v0_2 = temp_v1_4 << 0x10;
    if (temp_v0_2 > 0) {
        goto block_23;
    }
    ((S_800CABA8_0 *)arg0)->unk_98 = (u16) (((S_800CABA8_0 *)arg0)->unk_98 & 0xFFF7);
    ((S_800CABA8_0 *)arg0)->unk_9B = (u8) (((S_800CABA8_0 *)arg0)->unk_9B + 1);
jt_c4:
    ((S_800CABA8_0 *)arg0)->unk_A0.at02.v = 0U;
    func_800A2B04(arg1, ((S_800CABA8_1 *)arg2)->unk_24, ((S_800CABA8_1 *)arg2)->unk_25);
    D_8008346C = 0;
    ((S_800CABA8_2 *)temp_s2)->unk_46 = (u16) ((*(u16 *)((u8 *)temp_s2 + 0x46)) & 0x7FFF);
    func_800A4ACC(temp_s2);
    temp_v0_4 = ((S_800CABA8_0 *)arg0)->unk_B6 - 1;
    ((S_800CABA8_0 *)arg0)->unk_B6 = temp_v0_4;
    temp_a0 = (s32) arg0;
    if ((temp_v0_4 << 0x10) <= 0) {
        goto block_21;
    }
    if (!(D_80013714 & 8)) {
        goto block_22;
    }
block_21:
    func_800CAA94((void *) temp_a0, arg1, arg2);
    return;
block_22:
    ((S_800CABA8_0 *)arg0)->unk_8C = &D_800C9F34;
block_23:
    return;
}
