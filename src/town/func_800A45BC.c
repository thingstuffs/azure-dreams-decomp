#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800649A0();                            /* extern */
M2C_UNK func_80064A40();                            /* extern */
M2C_UNK func_80064CF0();                      /* extern */
M2C_UNK func_80064D80();                      /* extern */
M2C_UNK func_80065320();     /* extern */
M2C_UNK func_800A1DD4();                            /* extern */
M2C_UNK func_800A1E14();                            /* extern */
M2C_UNK func_800A1E54();                            /* extern */
extern s32 D_800814A0;


typedef struct S_800A1D1C_0_pre {
    u16 unk_00;
} S_800A1D1C_0_pre;   /* the 0x2 bytes before arg0 in func_800A1D1C, addressed as arg0[-1] */

typedef struct S_800A1D1C_0 {
    M2C_UNK (*unk_00)(void *, void *, void *);
    u8 pad_04[0xC];
    void * unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
    u16 unk_24;
    u8 pad_26[0x2];
    u16 unk_28;
    u8 pad_2A[0x2];
    u16 unk_2C;
    u8 pad_2E[0xE];
    u8 unk_3C;
    u8 unk_3D;
    u8 unk_3E;
} S_800A1D1C_0;   /* arg0 in func_800A1D1C */

typedef struct S_800A1D1C_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x4];
    union { u8 u8; s16 s16; } unk_10;   /* accessed as both */
} S_800A1D1C_1;   /* temp_s1 in func_800A1D1C */

typedef struct S_800A1D1C_2 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800A1D1C_2;   /* global_page in func_800A1D1C */

typedef struct S_800A1D1C_3 {
    u8 pad_00[0xC];
    union { u8 u; s8 s; } unk_0C;   /* accessed as both */
    union { u8 u; s8 s; } unk_0D;   /* accessed as both */
    union { u8 u; s8 s; } unk_0E;   /* accessed as both */
} S_800A1D1C_3;   /* arg2_local in func_800A1D1C */

typedef struct S_800A1D1C_4 {
    u8 pad_00[0x2C];
    u16 unk_2C;
    u16 unk_2E;
    u16 unk_30;
} S_800A1D1C_4;   /* scratch in func_800A1D1C */

typedef struct S_800A1D1C_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A1D1C_5;   /* arg1 in func_800A1D1C */

void func_800A1D1C(void *arg0, S_800A1D1C_5 *arg1, void *arg2) {
    s32 temp_s0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    u8 *global_page;
    register void *arg2_local ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
    register u8 *scratch ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    void *temp_a0;
    void *temp_s0_2;
    void *temp_s1;

    temp_s1 = ((S_800A1D1C_0 *)arg0)->unk_10;
    arg2_local = arg2;
    scratch = (u8 *)0x1F800000;
    if (((S_800A1D1C_1 *)temp_s1)->unk_0A != 0) {
        ((S_800A1D1C_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800A1D1C_0_pre *)arg0)[-1].unk_00 | 0x8000);
        global_page = (u8 *)0x80080000;
        ASM_KEEP(global_page);   /* MATCH pin: retail immediate-load split depends on it */
        ((S_800A1D1C_2 *)global_page)->unk_14A0 |= 0x8000;
        return;
    }
    ASM_KEEP(arg2_local);   /* MATCH pin: retail keeps a computation the compiler would drop */
    ASM_KEEP(scratch);   /* MATCH pin: retail immediate-load split depends on it */
    ((S_800A1D1C_0 *)arg0)->unk_00(arg0, arg1, arg2_local);
    if (((S_800A1D1C_0 *)arg0)->unk_3C != 0) {
        ((S_800A1D1C_3 *)arg2_local)->unk_0C.u = ((S_800A1D1C_1 *)temp_s1)->unk_10.u8;
        func_800A1DD4();
        return;
    }
    var_v0 = ((S_800A1D1C_1 *)temp_s1)->unk_10.s16 * 3;
    if (var_v0 < 0) {
        var_v0 += 3;
    }
    ((S_800A1D1C_3 *)arg2_local)->unk_0C.s = (s8) (var_v0 >> 2);
    if (((S_800A1D1C_0 *)arg0)->unk_3D != 0) {
        ((S_800A1D1C_3 *)arg2_local)->unk_0D.u = ((S_800A1D1C_1 *)temp_s1)->unk_10.u8;
        func_800A1E14();
        return;
    }
    var_v0_2 = ((S_800A1D1C_1 *)temp_s1)->unk_10.s16 * 3;
    if (var_v0_2 < 0) {
        var_v0_2 += 3;
    }
    ((S_800A1D1C_3 *)arg2_local)->unk_0D.s = (s8) (var_v0_2 >> 2);
    if (((S_800A1D1C_0 *)arg0)->unk_3E != 0) {
        ((S_800A1D1C_3 *)arg2_local)->unk_0E.u = ((S_800A1D1C_1 *)temp_s1)->unk_10.u8;
        func_800A1E54();
        return;
    }
    var_v0_3 = ((S_800A1D1C_1 *)temp_s1)->unk_10.s16 * 3;
    if (var_v0_3 < 0) {
        var_v0_3 += 3;
    }
    ((S_800A1D1C_3 *)arg2_local)->unk_0E.s = (s8) (var_v0_3 >> 2);
    ((S_800A1D1C_4 *)scratch)->unk_2C = ((S_800A1D1C_0 *)arg0)->unk_24;
    ((S_800A1D1C_4 *)scratch)->unk_2E = ((S_800A1D1C_0 *)arg0)->unk_28;
    ((S_800A1D1C_4 *)scratch)->unk_30 = ((S_800A1D1C_0 *)arg0)->unk_2C;
    temp_s0 = ((S_800A1D1C_0 *)arg0)->unk_22 != 0;
    func_800649A0();
    temp_s0_2 = temp_s1 + ((temp_s0 << 5) + 0x14);
    func_80064CF0(temp_s0_2);
    func_80064D80(temp_s0_2);
    temp_a0 = scratch + 0x2C;
    func_80065320(temp_a0, temp_a0, (void *)((u32)scratch | 0x98));
    func_80064A40();
    arg1->unk_02 = ((S_800A1D1C_4 *)scratch)->unk_2C;
    arg1->unk_06 = ((S_800A1D1C_4 *)scratch)->unk_2E;
    arg1->unk_0A = ((S_800A1D1C_4 *)scratch)->unk_30;
}
/* MECHANISM: Pinned s3 scratch and s2 arg2 holds produce the five-register 0x28 frame.
   A held 0x80080000 page base recovers the v1 RMW; signed halfword loads and tail-arm byte copies recover the body.
   Assigning scratch before the branch but fencing both holds at fallthrough fills retail's load and branch delay slots. */
