#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800AD058_arg0.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s16 D_8008346A[];
extern u8 D_80083780[12];
extern s32 D_80083460[3];
extern s32 D_800814A0[3];
s32 func_800644B8(s32);
s32 func_80064584(s32);
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A2FE0();
M2C_UNK func_800A32A4();
M2C_UNK func_800A56E0();
M2C_UNK func_800ACF88();
s32 func_80042900();
M2C_UNK func_800B8228();



typedef struct S_800AD058_1 {
    u8 pad_00[0xC];
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x1];
    u8 unk_27;
} S_800AD058_1;   /* arg2 in func_800AD058 */

typedef struct S_800AD058_2_pre {
    u16 unk_00;
} S_800AD058_2_pre;   /* the 0x2 bytes before arg3_local in func_800AD058, addressed as arg3_local[-1] */

typedef struct S_800AD058_2 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x29];
    u8 unk_49;
    u8 pad_4A[0x1];
    u8 unk_4B;
    u8 pad_4C[0x3C];
    s16 unk_88;
} S_800AD058_2;   /* arg3_local in func_800AD058 */

typedef struct S_800AD058_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
} S_800AD058_3;   /* arg1 in func_800AD058 */


typedef struct S_800AD058_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AD058_5;   /* base in func_800AD058 */

s32 func_800AD058(u8 *arg0, s32 *arg1, u8 *arg2, u8 *arg3) {
    M2C_UNK var_a0;
    M2C_UNK var_a1;
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    s16 temp_v0;
    s16 temp_v0_3;
    s32 temp_flags;
    s32 temp_v1_8;
    s32 temp_value;
    s32 var_v0;
    s32 dispatch_zero;
    u16 temp_a0;
    u16 temp_v1_4;
    u8 temp_v0_2;
    s32 temp_v1;
    u8 temp_v1_5;
    u8 temp_v1_6;
    u8 temp_v1_7;
    void *arg3_local = arg3;

    temp_v1 = ((Rec_func_800AD058_arg0 *)arg0)->unk_9B;
    if (temp_v1 == 1) {
        goto block_11;
    }
    if ((s32) temp_v1 < 2) {
        dispatch_zero = 0;
        if (temp_v1 == 0) {
            goto phase_0;
        }
        return dispatch_zero;
    }
    if (temp_v1 == 2) {
        goto block_15;
    }
    dispatch_zero = 3;
    if (temp_v1 == 3) {
        dispatch_zero = 0;
        goto phase_3;
    }
    ASM_SCHED_BARRIER(); /* MATCH: keep the phase-3 branch followed by the default epilogue jump. */
    return 0;

phase_0:
    ASM_KEEP(dispatch_zero);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    if (*D_8008346A != 0) {
        return 0;
    }
    ((Rec_func_800AD058_arg0 *)arg0)->unk_9B = 1U;
block_11:
    ((S_800AD058_1 *)arg2)->unk_10 = 0x20;
    ((S_800AD058_1 *)arg2)->unk_12 = (u16) (((S_800AD058_1 *)arg2)->unk_12 - 0x80);
    ((S_800AD058_1 *)arg2)->unk_14 = (u16) (((S_800AD058_1 *)arg2)->unk_14 | 0xC);
    ((S_800AD058_2 *)arg3_local)->unk_1C = (s32) (((S_800AD058_2 *)arg3_local)->unk_1C | 0x10000000);
    temp_v1_5 = ((S_800AD058_2 *)arg3_local)->unk_13;
    if ((temp_v1_5 == 5) || (var_a0 = 0x805, (temp_v1_5 == 0x1E))) {
        var_a0 = 0x806;
    }
    func_800A56E0(var_a0);
    ((S_800AD058_1 *)arg2)->unk_0C.at00.v = 0x808080;
    ((Rec_func_800AD058_arg0 *)arg0)->unk_96 = 0x10;
    ((Rec_func_800AD058_arg0 *)arg0)->unk_9B = (u8) (((Rec_func_800AD058_arg0 *)arg0)->unk_9B + 1);
block_15:
    temp_v1_6 = (u8) ((S_800AD058_1 *)arg2)->unk_0C.at00.v;
    ((S_800AD058_1 *)arg2)->unk_0C.at00u.v = (s8) (temp_v1_6 + ((s32) (0x20 - temp_v1_6) / (s16) ((Rec_func_800AD058_arg0 *)arg0)->unk_96));
    temp_v1_7 = ((S_800AD058_1 *)arg2)->unk_0C.at01.v;
    temp_v0_2 = ((S_800AD058_1 *)arg2)->unk_0C.at02.v;
    ((S_800AD058_1 *)arg2)->unk_0C.at01.v = (u8) (temp_v1_7 + ((s32) (0x20 - temp_v1_7) / (s16) ((Rec_func_800AD058_arg0 *)arg0)->unk_96));
    ((S_800AD058_1 *)arg2)->unk_0C.at02.v = (u8) (temp_v0_2 + ((s32) (0x20 - temp_v0_2) / (s16) ((Rec_func_800AD058_arg0 *)arg0)->unk_96));
    temp_v0_3 = (u16) ((Rec_func_800AD058_arg0 *)arg0)->unk_96 - 1;
    ((Rec_func_800AD058_arg0 *)arg0)->unk_96 = temp_v0_3;
    if (((temp_v0_3 << 0x10) <= 0) || (var_v0 = 0, ((((S_800AD058_1 *)arg2)->unk_14 & 0x8000) != 0))) {
        if (!(((S_800AD058_2 *)arg3_local)->unk_14 & 0x20000000)) {
            s32 *base = D_80083460;
            if (base[4] == (s32) (arg3_local - 0x20)) {
                base[4] = (s32) (base[4] & 0x7FFFFFFF);
            }
        }
        temp_v1_8 = ((S_800AD058_2 *)arg3_local)->unk_14;
        if (!(temp_v1_8 & 0x4000)) {
            func_800A2FE0(arg3_local);
            func_800A32A4(arg3_local);
            if (((S_800AD058_2 *)arg3_local)->unk_49 == 0) {
                goto block_35;
            }
            {
                register void *cleanup_arg ASM_REG("$4") = arg3_local;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                if (((S_800AD058_2 *)arg3_local)->unk_4B & 0x20) {
                    goto block_35;
                }
                func_800B8228(((S_800AD058_3 *)arg1)->unk_00.at02.v, ((S_800AD058_3 *)arg1)->unk_04.at02.v, ((S_800AD058_2 *)arg3_local)->unk_88, arg3_local + 0x48);
                goto block_35;
            }
        }
        if (!(temp_v1_8 & 0x20000000)) {
            func_800ACF88(arg3_local);
        }
        func_800A2FE0(arg3_local);
        func_800A32A4(arg3_local);
        if ((func_80042900(arg3_local, 0x1B) << 0x10) == 0) {
            temp_flags = ((S_800AD058_2 *)arg3_local)->unk_1C;
            var_a0 = ((S_800AD058_1 *)arg2)->unk_24;
            var_a1 = ((S_800AD058_1 *)arg2)->unk_25;
            var_a2_2 = 0x3000;
            if (temp_flags & 0x2000) {
                var_a2_2 = 0x300;
            }
            func_8009A3D0(var_a0, var_a1, var_a2_2);
        }
        func_8009A028(arg3_local);
        ((S_800AD058_2_pre *)arg3_local)[-1].unk_00 = (u16) (((S_800AD058_2_pre *)arg3_local)[-1].unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
        func_800A56E0(0x609);
        return 1;
    }
    return var_v0;

phase_3:
    ASM_KEEP(dispatch_zero);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    temp_value = (((Rec_func_800AD058_arg0 *)arg0)->unk_96 * func_80064584(((S_800AD058_1 *)arg2)->unk_27 << 7)) << 5;
    ((S_800AD058_3 *)arg1)->unk_00.at00.v += (s32) ((((Rec_D_800E3D7C *)D_80083780)->unk_00.at00_s32.v + temp_value - ((S_800AD058_3 *)arg1)->unk_00.at00.v) >> 2);
    temp_value = (((Rec_func_800AD058_arg0 *)arg0)->unk_96 * func_800644B8(((S_800AD058_1 *)arg2)->unk_27 << 7)) << 5;
    ((S_800AD058_3 *)arg1)->unk_04.at00.v += (s32) ((((Rec_D_800E3D7C *)D_80083780)->unk_04.at00_s32.v + temp_value - ((S_800AD058_3 *)arg1)->unk_04.at00.v) >> 2);
    {
        s32 vertical_step;

        vertical_step = func_800644B8(((Rec_func_800AD058_arg0 *)arg0)->unk_96 * 8) >> 6;
        ((S_800AD058_2 *)arg3_local)->unk_88 = (s16) ((u16) ((S_800AD058_2 *)arg3_local)->unk_88 +
            ((((Rec_D_800E3D7C *)D_80083780)->unk_08.at02_s16.v - vertical_step - ((S_800AD058_2 *)arg3_local)->unk_88) >> 4));
    }
    temp_v1_4 = ((S_800AD058_1 *)arg2)->unk_1C;
    temp_a0 = ((S_800AD058_1 *)arg2)->unk_1E;
    ((S_800AD058_1 *)arg2)->unk_1C = (u16) (temp_v1_4 - ((s32) temp_v1_4 / (s16) ((Rec_func_800AD058_arg0 *)arg0)->unk_96));
    ((S_800AD058_1 *)arg2)->unk_1E = (u16) (temp_a0 - ((s32) temp_a0 / (s16) ((Rec_func_800AD058_arg0 *)arg0)->unk_96));
    ((S_800AD058_1 *)arg2)->unk_27 = (u8) (((S_800AD058_1 *)arg2)->unk_27 + 1);
    temp_v0 = (u16) ((Rec_func_800AD058_arg0 *)arg0)->unk_96 - 1;
    ((Rec_func_800AD058_arg0 *)arg0)->unk_96 = temp_v0;
    var_v0 = 0;
    if ((temp_v0 << 0x10) <= 0) {
        register s32 *base ASM_REG("$2") = D_80083460;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        ((S_800AD058_5 *)base)->unk_0A = (u16) (((S_800AD058_5 *)base)->unk_0A - 1);
        func_800A2FE0(arg3_local);
        func_800A32A4(arg3_local);
        goto block_35;
    }
    return var_v0;

block_35:
    if ((func_80042900(arg3_local, 0x1B) << 0x10) == 0) {
        temp_flags = ((S_800AD058_2 *)arg3_local)->unk_1C;
        var_a0 = ((S_800AD058_1 *)arg2)->unk_24;
        var_a1 = ((S_800AD058_1 *)arg2)->unk_25;
        var_a2 = 0x3000;
        if (temp_flags & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(var_a0, var_a1, var_a2);
    }
    func_8009A028(arg3_local);
    ((S_800AD058_2_pre *)arg3_local)[-1].unk_00 = (u16) (((S_800AD058_2_pre *)arg3_local)[-1].unk_00 | 0x8000);
    var_v0 = 1;
    D_800814A0[0] |= 0x8000;
    return var_v0;
}
