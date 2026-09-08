#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80023260_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    union { s32 s; volatile s32 u; } unk_0C;   /* accessed as both */
    union { s32 s; volatile s32 u; } unk_10;   /* accessed as both */
    u8 pad_14[0x4];
    union { volatile u16 s; s16 u; u16 p; } unk_18;   /* accessed as both */
    u16 unk_1A;
    s16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
    s16 unk_24;
    u8 pad_26[0x4];
    s16 unk_2A;
} S_80023260_0;   /* arg0 in func_80023260 */

typedef struct S_80023260_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80023260_1;   /* arg1 in func_80023260 */


typedef struct S_80023260_3 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    u16 unk_06;
    u8 pad_08[0x6];
    u16 unk_0E;
} S_80023260_3;   /* temp_s2 in func_80023260 */

typedef struct S_80023260_4 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80023260_4;   /* temp_s5 in func_80023260 */

typedef struct S_80023260_5 {
    u8 pad_00[0x3C];
    s16 unk_3C;
} S_80023260_5;   /* ((((S_80023260_0 *)arg0)->unk_24 * 2) + temp_fp) in func_80023260 */


M2C_UNK func_800211C4();      /* extern */
M2C_UNK func_80022F34();              /* extern */
M2C_UNK func_800239A0();            /* extern */
M2C_UNK func_80047784();         /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();              /* extern */
M2C_UNK func_8009539C();                      /* extern */
M2C_UNK func_800ABD74();                 /* extern */
s16 func_800C2AE8();                      /* extern */
typedef struct {
    void *ptr;
    s16 field4;
    u16 flags;
    s16 field8;
    s16 padA;
} Record12;

typedef struct {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
    s32 field10;
    s32 field14;
} Stack24;

extern Record12 D_800242D8[];
extern s32 D_80081458[];
extern s16 D_80083228;
extern u8 D_800D2388[];

void func_80023260(void *arg0, void *arg1, void *arg2) {
    s16 temp_a0_2;
    s16 temp_a0_3;
    s16 temp_a0_4;
    s16 temp_a0_5;
    s16 temp_s0_2;
    s32 temp_v1;
    s16 temp_v1_4;
    s16 temp_v1_5;
    s16 temp_v1_6;
    s32 temp_v1_7;
    s32 temp_v1_8;
    s32 var_a2;
    s32 var_v0_4;
    s32 temp_a0_6;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_fp;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_9;
    s32 constant2;
    s32 old_c;
    register s32 old_10 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 angle_obj;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 angle_base;
    s32 final_kind;
    s32 case_value;
    s32 var_a1;
    s32 var_a3;
    s32 var_s0;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_a0;
    u16 temp_a1;
    s32 temp_v1_3;
    register s32 var_v0_3 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    Record12 *record_base;
    void *temp_s0;
    void *temp_s2;
    void *temp_s5;
    u8 *case_base;

    temp_s5 = arg0;
    record_base = D_800242D8;
    temp_fp = ((S_80023260_0 *)arg0)->unk_00;
    temp_s2 = record_base[((S_80023260_0 *)arg0)->unk_22].ptr + (((S_80023260_0 *)arg0)->unk_1C * 8);
    func_800478B8(arg2);
    temp_s0 = arg0 + 0x14;
    func_80022F34(arg1, temp_s0);
    func_800239A0(temp_fp, temp_s0, ((S_80023260_0 *)arg0)->unk_24);
    func_8009539C(arg1);
    var_s0 = 0;
    ((S_80023260_1 *)arg1)->unk_00.at00.v = (s32) (((S_80023260_1 *)arg1)->unk_00.at00.v + ((S_80023260_0 *)arg0)->unk_0C.s);
    ((S_80023260_1 *)arg1)->unk_04.at00.v = (s32) (((S_80023260_1 *)arg1)->unk_04.at00.v + ((S_80023260_0 *)arg0)->unk_10.s);
    old_c = ((S_80023260_0 *)arg0)->unk_0C.u;
    old_10 = ((S_80023260_0 *)arg0)->unk_10.u;
    temp_a0 = ((S_80023260_0 *)arg0)->unk_18.s;
    ((S_80023260_0 *)arg0)->unk_10.s = old_10 >> 1;
    temp_v1 = ((S_80023260_0 *)arg0)->unk_18.u;
    ((S_80023260_0 *)arg0)->unk_0C.s = old_c >> 1;
    constant2 = 2;
    if (temp_v1 == constant2) {
        goto block_69;
    }
    if (temp_v1 >= 3) {
        goto check_high;
    }
    if (temp_v1 == 0) {
        goto kind_0;
    }
    if (temp_v1 == 1) {
        goto kind_1;
    }
    goto block_69;
check_high:
    if (temp_v1 == 0x100) {
        goto kind_100;
    }
    if (temp_v1 > 0x100) {
        goto block_69;
    }
    if (temp_v1 == 3) {
        goto kind_3;
    }
    goto block_69;
kind_0:
    ((S_80023260_0 *)arg0)->unk_18.p = temp_a0 + 1;
    return;
kind_1:
    ((S_80023260_0 *)arg0)->unk_2A = 0x800;
    case_value = D_80081458[0];
    case_base = D_800D2388;
    ((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 = case_base;
    ((Rec_D_80082E80 *)arg2)->unk_28.at00_s32.v = case_value;
    func_80047784(arg2, D_800D2388[((D_80083228 + ((S_80023260_0 *)arg0)->unk_2A + 0x100) >> 9) & 7], 0);
    ((S_80023260_0 *)arg0)->unk_18.p = (u16) (((S_80023260_0 *)arg0)->unk_18.p + 1);
    goto block_69;
kind_3:
    (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800D2388 - 8;
    func_80047784(arg2, (D_800D2388 - 8)[((D_80083228 + ((S_80023260_0 *)arg0)->unk_2A + 0x100) >> 9) & 7], 0);
    ((S_80023260_0 *)arg0)->unk_18.p = constant2;
    goto block_69;
kind_100:
            temp_a1 = ((S_80023260_0 *)arg0)->unk_1A + 1;
            ((S_80023260_0 *)arg0)->unk_1A = temp_a1;
            if ((((S_80023260_0 *)arg0)->unk_04 <= 0x200000) && (((S_80023260_3 *)temp_s2)->unk_06 & 2)) {
                if (((s16) temp_a1 % (s16) record_base[((S_80023260_0 *)arg0)->unk_22].flags) == 0) {
                    func_800ABD74(arg1);
                    ((S_80023260_0 *)arg0)->unk_04 = (s32) (((S_80023260_0 *)arg0)->unk_04 + 0x80000);
                }
            }
            temp_v1_2 = ((S_80023260_0 *)arg0)->unk_04;
            if ((temp_v1_2 <= 0xFFFFF) && (((S_80023260_3 *)temp_s2)->unk_06 & 1)) {
                ((S_80023260_0 *)arg0)->unk_04 = (s32) (temp_v1_2 + 0x20000);
            }
            angle_obj = ((S_80023260_4 *)temp_s5)->unk_2A;
            angle_base = ((S_80023260_3 *)temp_s2)->unk_04;
            var_a1 = angle_obj - angle_base;
            var_a3 = 0;
            while (var_a1 >= 0x801) {
                var_a1 -= 0x1000;
            }
            while (var_a1 < -0x800) {
                var_a1 += 0x1000;
            }
            temp_a1_2 = var_a1;
            temp_v1_3 = ((S_80023260_3 *)temp_s2)->unk_06;
            temp_v0 = temp_v1_3 & 8;
            if (temp_v0 != 0) {
                temp_v0 = temp_v1_3 & 0x10;
                if (temp_v0 != 0) {
                    temp_a0_2 = ((S_80023260_3 *)temp_s2)->unk_00;
                    var_a2 = D_800242D8[((S_80023260_0 *)arg0)->unk_22].field8;
                    if (((S_80023260_1 *)arg1)->unk_00.at02.v >= temp_a0_2) {
                        var_s0 = 1;
                    }
                    goto block_38;
                }
                var_a2 = 0 - D_800242D8[((S_80023260_0 *)arg0)->unk_22].field8;
                if (((S_80023260_1 *)arg1)->unk_00.at02.v <= ((S_80023260_3 *)temp_s2)->unk_00) {
                    var_s0 = 1;
                }
block_38:
                temp_a0_3 = ((S_80023260_3 *)temp_s2)->unk_02;
                temp_v1_4 = ((S_80023260_1 *)arg1)->unk_04.at02.v;
                var_v0 = temp_a0_3 - temp_v1_4;
                if (var_v0 < 0) {
                    var_v0 = 0 - var_v0;
                }
                if (var_v0 >= 5) {
                    var_a3 = 0x20;
                    if (temp_v1_4 >= temp_a0_3) {
                        if ((0 - var_a2) < temp_a1_2) {
                            var_a3 = -0x20;
                        }
                        goto block_58;
                    }
                    goto block_56;
                }
                goto block_58;
            }
            temp_v0 = temp_v1_3 & 0x10;
            if (temp_v0 != 0) {
                temp_a0_4 = ((S_80023260_3 *)temp_s2)->unk_02;
                var_a2 = D_800242D8[((S_80023260_0 *)arg0)->unk_22].field8;
                if (((S_80023260_1 *)arg1)->unk_04.at02.v >= temp_a0_4) {
                    var_s0 = 1;
                }
                goto block_50;
            }
            var_a2 = 0 - D_800242D8[((S_80023260_0 *)arg0)->unk_22].field8;
            if (((S_80023260_1 *)arg1)->unk_04.at02.v <= ((S_80023260_3 *)temp_s2)->unk_02) {
                var_s0 = 1;
            }
block_50:
            temp_a0_5 = ((S_80023260_3 *)temp_s2)->unk_00;
            temp_v1_5 = ((S_80023260_1 *)arg1)->unk_00.at02.v;
            var_v0_2 = temp_a0_5 - temp_v1_5;
            if (var_v0_2 < 0) {
                var_v0_2 = 0 - var_v0_2;
            }
            if (var_v0_2 >= 5) {
                var_a3 = 0x20;
                if (temp_v1_5 < temp_a0_5) {
                    if ((0 - var_a2) < temp_a1_2) {
                        var_a3 = -0x20;
                    }
                    goto block_58;
                }
block_56:
                if (var_a2 < temp_a1_2) {
                    var_a3 = -0x20;
                }
                goto block_58;
            }
block_58:
            if ((((S_80023260_3 *)temp_s2)->unk_06 & 4) && (var_s0 != 0)) {
                ((S_80023260_1 *)arg1)->unk_14 = -0x140000;
            }
            temp_a0_6 = var_a3 >> 4;
            ((S_80023260_4 *)temp_s5)->unk_2A = (s16) ((u16) ((S_80023260_4 *)temp_s5)->unk_2A + var_a3);
            ((S_80023260_0 *)arg0)->unk_1E = (u16) (((S_80023260_0 *)arg0)->unk_1E + temp_a0_6);
            ((S_80023260_0 *)arg0)->unk_1C = (s16) ((u16) ((S_80023260_0 *)arg0)->unk_1C + var_s0);
            if ((var_s0 != 0) && (((S_80023260_3 *)temp_s2)->unk_06 & 0x20)) {
                if (rand(temp_a0_6, temp_a1_2, var_a2, var_a3) & 1) {
                    ((S_80023260_3 *)temp_s2)->unk_0E = (u16) (((S_80023260_3 *)temp_s2)->unk_0E | 2);
                    goto block_67;
                }
                ((S_80023260_3 *)temp_s2)->unk_0E = (u16) (((S_80023260_3 *)temp_s2)->unk_0E & 0xFFFD);
                goto block_67;
            }
block_67:
            if (((S_80023260_0 *)arg0)->unk_1C >= 0xF) {
                ((S_80023260_0 *)arg0)->unk_1A = 0U;
                ((S_80023260_0 *)arg0)->unk_1C = 0;
            }
            goto block_69;
block_69:
        temp_v1_6 = (s16) ((S_80023260_0 *)arg0)->unk_1E;
        if (temp_v1_6 > 0) {
            ((S_80023260_0 *)arg0)->unk_1E = (u16) (((S_80023260_0 *)arg0)->unk_1E - 1);
        } else if (temp_v1_6 < 0) {
            ((S_80023260_0 *)arg0)->unk_1E = (u16) (((S_80023260_0 *)arg0)->unk_1E + 1);
        }
        temp_v1_7 = (s16) ((S_80023260_0 *)arg0)->unk_1E;
        if (temp_v1_7 < -9) {
            var_v0_3 = -9;
            goto clamp_store;
        }
        var_v0_3 = temp_v1_7 < 0xA;
        if (var_v0_3 != 0) {
            goto clamp_done;
        }
        var_v0_3 = 9;
clamp_store:
        ((S_80023260_0 *)arg0)->unk_1E = var_v0_3;
clamp_done:
        var_v0_4 = (s16) ((S_80023260_0 *)arg0)->unk_1E;
        if (var_v0_4 < 0) {
            var_v0_4 = 0 - var_v0_4;
        }
        if ((var_v0_4 >= 6) && (((u16) ((S_80023260_0 *)arg0)->unk_1A >> 1) & 1)) {
            func_800ABD74(arg1);
        }
        {
        Stack24 sp = *(Stack24 *)arg1;
        temp_v1_8 = ((S_80023260_5 *)(((((S_80023260_0 *)arg0)->unk_24 * 2) + temp_fp)))->unk_3C;
        if ((temp_v1_8 == 2) || (temp_v1_8 == 6)) {
            sp.field8 = 0xFE000000;
        }
        temp_s0_2 = func_800C2AE8(&sp);
        ((S_80023260_1 *)arg1)->unk_0C = (s32) (func_80064584(((S_80023260_4 *)temp_s5)->unk_2A) * ((s32) ((S_80023260_0 *)arg0)->unk_04 >> 0xC));
        ((S_80023260_1 *)arg1)->unk_10 = (s32) (func_800644B8(((S_80023260_4 *)temp_s5)->unk_2A) * ((s32) ((S_80023260_0 *)arg0)->unk_04 >> 0xC));
        if (temp_s0_2 < ((S_80023260_1 *)arg1)->unk_0A) {
            ((S_80023260_1 *)arg1)->unk_0A = temp_s0_2;
            if (((S_80023260_1 *)arg1)->unk_14 >= 0) {
                ((S_80023260_1 *)arg1)->unk_14 = 0;
            }
            if (((S_80023260_0 *)arg0)->unk_08 & 1) {
                func_800ABD74(arg1);
            }
            ((S_80023260_0 *)arg0)->unk_08 = (s32) (((S_80023260_0 *)arg0)->unk_08 & -2);
        } else {
            ((S_80023260_0 *)arg0)->unk_08 = (s32) (((S_80023260_0 *)arg0)->unk_08 | 1);
        }
        temp_v1_9 = ((S_80023260_0 *)arg0)->unk_04;
        if (temp_v1_9 < -0x10000) {
            ((S_80023260_0 *)arg0)->unk_04 = temp_v1_9 + 0x10000;
        } else if (temp_v1_9 > 0x10000) {
            ((S_80023260_0 *)arg0)->unk_04 = temp_v1_9 - 0x10000;
        } else {
            ((S_80023260_0 *)arg0)->unk_04 = 0;
        }
        ((S_80023260_1 *)arg1)->unk_14 = (s32) (((S_80023260_1 *)arg1)->unk_14 + 0x20000);
        final_kind = ((S_80023260_0 *)arg0)->unk_18.u;
        if (final_kind != 0) {
            func_800211C4(temp_s5, arg0, arg2);
        }
        }
}
