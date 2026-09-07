#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009CE1C_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8009CE1C_3_pre;   /* the 0x14 bytes before arg0 in func_8009CE1C, addressed as arg0[-1] */

typedef struct S_8009CE1C_4 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8009CE1C_4;   /* ((S_8009CE1C_3_pre *)arg0)[-1].unk_00 in func_8009CE1C */


typedef struct S_8009CE1C_0 {
    u8 pad_00[0x11];
    u8 unk_11;
} S_8009CE1C_0;   /* *D_800E3D7C in func_8009CE1C */

typedef struct S_8009CE1C_1 {
    void * unk_00;
    u8 pad_04[0x23];
    u8 unk_27;
    u8 pad_28[0x8];
    s32 unk_30;
    u8 pad_34[0x2];
    union { u16 s; s16 u; } unk_36;   /* accessed as both */
    u8 pad_38[0x3];
    u8 unk_3B;
    u8 pad_3C[0x2];
    u16 unk_3E;
    u8 pad_40[0x1A];
    u16 unk_5A;
    u8 pad_5C[0x18];
    s32 unk_74;
    union { u16 s; s16 u; } unk_78;   /* accessed as both */
    u8 pad_7A[0x4];
    u16 unk_7E;
    u8 pad_80[0x1C];
    u16 unk_9C;
} S_8009CE1C_1;   /* arg0 in func_8009CE1C; pointer addresses record offset 0x14 */

typedef struct S_8009CE1C_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8009CE1C_2;   /* temp_t1 in func_8009CE1C */


extern u8 *D_800E3D7C[];
extern u8 D_800E3E41;
extern void *D_80083470[3];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
M2C_UNK func_80094E34();
s32 func_80098250();
M2C_UNK func_8009CFB4();
M2C_UNK func_8009CFF4();
M2C_UNK func_8009D034();
s32 func_8009D218(void *, s32, s32);
M2C_UNK func_800A56E0();
M2C_UNK func_800B4C7C();
extern void func_80099C58(s16, s16, s16, s16, s32);

void func_8009CE1C(void *arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4, s32 arg5, u16 arg6) {
    M2C_UNK var_a0;
    s16 temp_lo;
    s32 var_a2;
    s16 var_s2;
    s16 var_v1;
    s32 temp_s2;
    register s32 temp_s3 ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    s32 temp_v1;
    M2C_UNK temp_v1_2;
    s32 var_s1;
    register s16 var_s3 ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    s32 var_v0_2;
    s32 var_v0_3;
    M2C_UNK var_v0_4;
    register s32 var_v0_5 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    S_8009CE1C_2 *temp_t1;
    register u16 var_s4 = arg1;
    register s16 var_s5 ASM_REG("$21") = arg3;   /* MATCH pin: load-bearing for the whole function shape */
    s32 var_v0;

    var_s3 = arg2;
    var_s2 = var_s3;
    var_s1 = 0;
    if ((arg0 != NULL) && (func_8009D218(arg0, var_s5 & 0xFFFF, arg5) == 0)) {
        if (var_s3 == 0xFF) {
            var_s2 = ((S_8009CE1C_0 *)(*D_800E3D7C))->unk_11 * 4;
            if (var_s2 >= 0x64) {
                var_s2 = 0x63;
            }
            {
                s32 inner_shift;
                inner_shift = var_s4 << 0x10;
                var_v0 = inner_shift;
            }
        } else {
            s32 default_shift;
            default_shift = var_s4 << 0x10;
            var_v0 = default_shift;
        }
        ASM_USE_NV(var_s3);   /* MATCH pin: load-bearing for the whole function shape */
        temp_s2 = ((var_v0 >> 0x10) + var_s2) * 2;
        ((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_7E = arg4;
        if ((((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_27 != 0) && !(((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_30 & 0x238) && !(((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_5A & 0x8000)) {
            ((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_3E = (u16) (arg4 + 0x800);
        }
        ((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_36.s = (u16) (((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_3B + func_80098250(arg0));
        if ((func_80042900(arg0, 0xA) << 0x10) != 0) {
            ((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_36.s = (u16) ((s32) (((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_36.s << 0x10) >> 0x11);
        }
        if (((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_36.u == 0) {
            ((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_36.s = (u16) (((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_36.s + 1);
        }
        temp_s3 = func_8009CD58(arg0, 7, 0);
        if (var_s5 & 1) {
            if ((func_80042900(arg0, 0x13) << 0x10) != 0) {
                temp_s2 >>= 2;
                goto block_21;
            }
            if (temp_s3 & 4) {
                var_s1 += 1;
            }
            if (temp_s3 & 2) {
                var_s1 -= 1;
                goto block_21;
            }
            var_v0_2 = var_s5 & 2;
            goto block_22;
        }
block_21:
        var_v0_2 = var_s5 & 2;
block_22:
        if (var_v0_2 != 0) {
            if ((func_80042900(arg0, 0x14) << 0x10) != 0) {
                temp_s2 >>= 2;
                goto block_30;
            }
            if (temp_s3 & 1) {
                var_s1 += 1;
            }
            if (temp_s3 & 4) {
                var_s1 -= 1;
                goto block_30;
            }
            var_v0_3 = var_s5 & 4;
            goto block_31;
        }
block_30:
        var_v0_3 = var_s5 & 4;
block_31:
        if (var_v0_3 != 0) {
            if ((func_80042900(arg0, 0x12) << 0x10) != 0) {
                temp_s2 >>= 2;
                goto block_39;
            }
            if (temp_s3 & 2) {
                var_s1 += 1;
            }
            var_v0_5 = temp_s3 & 1;
            if (var_v0_5) {
                var_s1 -= 1;
                goto block_39;
            }
            var_v0_4 = var_s1 << 0x10;
            goto block_40;
        }
block_39:
        var_v0_4 = var_s1 << 0x10;
block_40:
        temp_lo = temp_s2 * (var_v0_4 >> 0x10);
        var_v1 = temp_lo;
        if (temp_lo < 0) {
            var_v1 = (s16) ((u32) (temp_lo + 3) >> 2);
        }
        temp_s2 += var_v1;
        temp_v1 = (s32) ((s16) ((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_36.s - temp_s2) / 2;
        ((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_78.s = (u16) temp_v1;
        if ((s16) temp_v1 >= 0) {
            ((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_78.u = -1;
        }
        ((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_30 = (s32) (((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_30 | 0x20000000);
        if ((func_80042900(arg0, 0x1D) << 0x10) == 0) {
            var_a2 = (s16) (0 - ((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_78.s);
        } else {
            var_a2 = 0;
        }
        func_800B4C7C(3, arg0, var_a2, 0);
        if (arg0 == *D_800E3D7C) {
            D_800E3E41 = (u8) arg6;
            func_80094E34();
        }
        ((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_74 = arg5;
        D_80083470[0] = arg0 - 0x20;
        if (!(((S_8009CE1C_4 *)(((S_8009CE1C_3_pre *)arg0)[-1].unk_00))->unk_14 & 0x8000)) {
            func_800419EC(8, 0x10);
        }
        var_a0 = 0x601;
        if ((arg5 != 0) && !(arg5 & 0x20000000)) {
            var_a0 = 0x602;
        }
        func_800A56E0(var_a0);
        temp_t1 = ((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_00;
        temp_v1_2 = ((u16) ((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_3E >> 8) & 0xE;
        func_80099C58((u16) ((temp_t1->unk_24 << 6) + ((D_8006CCD8[(u32) temp_v1_2 >> 1] * 0x20) + 0x20)), (u16) ((temp_t1->unk_25 << 6) + ((D_8006CCE8[(u32) temp_v1_2 >> 1] * 0x20) + 0x20)), (s16) (((S_8009CE1C_1 *)((u8 *)arg0 - 0x14))->unk_9C - 0x30), var_s5, (s32) (s16) arg4);
    }
}
