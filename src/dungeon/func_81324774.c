#include "common.h"
#include "m2c_compat.h"

typedef struct S_8016BF74_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_8016BF74_0;   /* state in func_8016BF74 */

typedef struct S_8016BF74_1 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x1];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x19];
    u8 unk_45;
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
} S_8016BF74_1;   /* arg3 in func_8016BF74 */

typedef struct S_8016BF74_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
} S_8016BF74_2;   /* arg2 in func_8016BF74 */

typedef struct S_8016BF74_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8016BF74_3_pre;   /* the 0x14 bytes before temp_v0 in func_8016BF74, addressed as temp_v0[-1] */

typedef struct S_8016BF74_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016BF74_4;   /* temp_v0_2 in func_8016BF74 */

typedef struct S_8016BF74_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    s8 unk_9C;
    u8 pad_9D[0x15];
    u8 unk_B2;
} S_8016BF74_5;   /* arg0 in func_8016BF74 */

typedef struct S_8016BF74_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x2C];
    s32 unk_58;
} S_8016BF74_6;   /* D_800814A8 in func_8016BF74 */

typedef struct S_8016BF74_7 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8016BF74_7;   /* temp_v0_5 in func_8016BF74 */

typedef struct S_8016BF74_8 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8016BF74_8;   /* state2 in func_8016BF74 */

typedef struct S_8016BF74_9 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8016BF74_9;   /* (arg3 + ((u8) ((S_8016BF74_1 *)arg3)->unk_71.s & 0x7F)) in func_8016BF74 */


s32 func_8009A180();                     /* extern */
M2C_UNK func_8009A21C();             /* extern */
M2C_UNK func_8009A3D0();             /* extern */
s32 func_8009A540();                /* extern */
s32 func_8009A66C();    /* extern */
s32 func_8009FD7C();                  /* extern */
s16 func_800A0134();                  /* extern */
void *func_800A02AC();                /* extern */
void *func_800A04F0();           /* extern */
u16 func_800A0818();          /* extern */
M2C_UNK func_800A0E6C();  /* extern */
M2C_UNK func_800A19E4(); /* extern */
M2C_UNK func_800A6D30();                            /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
s16 func_800BCB04();                   /* extern */
s32 func_8016C720();          /* extern */
typedef struct {
    u8 pad[0xC];
    u16 flags;
    u8 tail[6];
} D_800E2970Entry;
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern s16 D_8006CD00;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern u16 D_80082EA4;
extern M2C_UNK D_80083460;
extern D_800E2970Entry D_800E2970[];

void func_8016BF74(void *raw_arg0, void *arg1, void *raw_arg2, void *raw_arg3) {
    void *arg0;
    S_8016BF74_2 *arg2;
    void *arg3;
    register s32 var_s3 ASM_REG("$19");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 var_s6;
    register u8 *var_s7 ASM_REG("$23");   /* MATCH pin: retail register colouring depends on it */
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    register s8 *var_s1 ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
    register s8 *loop_page ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_w1;
    s32 temp_w2;
    s16 temp_v0_4;
    s16 temp_v0_6;
    register s32 temp_a0_2 ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
    u8 *temp_v1_ptr;
    s32 temp_v0_3;
    register s32 temp_high_bit ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_v0;
    s8 temp_a0;
    s8 *state;
    s32 state_flags;
    register void *temp_v0 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    S_8016BF74_4 *temp_v0_2;
    void *temp_v0_7;
    register void *temp_v0_5 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 temp_c008;
    s32 temp_call_a1;
    s32 loop_angle;
    s16 loop_sum;
    void *first_position;
    s32 first_a0;
    s32 first_a1;
    s32 first_a2;
    s32 first_a3;
    register s32 loop_flags ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 loop_flags2;
    s32 loop_table_y;
    s32 loop_call_a0;
    s32 first_compare_x;
    register s32 loop_next ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 loop_y ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    register u8 *loop_table_base ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 *loop_table_ptr;
    u8 *world_call;

    arg0 = raw_arg0;
    arg2 = raw_arg2;
    arg3 = raw_arg3;
    state = (s8 *)&D_80083460;
    ASM_KEEP(arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    state_flags = ((S_8016BF74_0 *)state)->unk_02;
    var_s6 = 0;
    if ((state_flags & 0x4000) || (((S_8016BF74_1 *)arg3)->unk_71.s >= 0)) {
        if (((u8) ((S_8016BF74_1 *)arg3)->unk_12 >= 2U) || ((func_8016C720(arg0, arg1, arg2, arg3) << 0x10) == 0)) {
            func_800A9A0C(arg3);
            return;
        }
        temp_c008 = ((S_8016BF74_0 *)state)->unk_0C;
        if ((void *)temp_c008 == arg3) {
            temp_c008 = 0xC008;
            ((S_8016BF74_1 *)arg3)->unk_46 = (u16) temp_c008;
            return;
        }
        return;
    }
    if (state_flags & 0x2000) {
        func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
        temp_v1 = ((S_8016BF74_1 *)arg3)->unk_1C;
        if (temp_v1 & 0x410) {
            if (temp_v1 & 0x400) {
                temp_v0 = func_800A02AC(arg3, arg2->unk_24.at00.v, arg2->unk_24.at01.v);
                if (temp_v0 != NULL) {
                    first_a0 = arg2->unk_24.at00.v;
                    temp_v0_2 = ((S_8016BF74_3_pre *)temp_v0)[-1].unk_00;
                    first_a1 = arg2->unk_24.at01.v;
                    first_a2 = temp_v0_2->unk_24;
                    first_a3 = temp_v0_2->unk_25;
                    first_position = arg0 + 0x98;
                    ((S_8016BF74_1 *)arg3)->unk_2A.u = func_800A0818(first_a0, first_a1, first_a2, first_a3, first_position);
                    ((S_8016BF74_1 *)arg3)->unk_71.u &= 0x7F;
                    return;
                }
                temp_v0_3 = ((S_8016BF74_1 *)arg3)->unk_14;
                if (temp_v0_3 >= 0) {
                    temp_high_bit = 0x80000000;
                    temp_v0_3 |= temp_high_bit;
                    ((S_8016BF74_1 *)arg3)->unk_14 = temp_v0_3;
                    var_v0 = func_800A6D30();
                    ((S_8016BF74_1 *)arg3)->unk_2A.u += (var_v0 & 7) << 9;
                    goto block_46;
                }
                goto block_46;
            }
            temp_v0_7 = func_800A04F0(arg3, arg2->unk_24.at00.v, arg2->unk_24.at01.v, (s16) ((S_8016BF74_1 *)arg3)->unk_2A.u);
            var_s3 = 0;
            if (temp_v0_7 == NULL) {
                goto block_47;
            }
            goto block_clear_71;
        }
        if (((S_8016BF74_5 *)arg0)->unk_B2 != 0) {
                var_s3 = 0;
                if (!(((S_8016BF74_1 *)arg3)->unk_46 & 0x8000)) {
                    if (temp_v1 & 0x20000) {
                    temp_v1_2 = ((((S_8016BF74_1 *)arg3)->unk_45 + ((s32) (((S_8016BF74_6 *)D_800814A8)->unk_2A << 0x10) >> 0x19)) & 7) * 2;
                    temp_w2 = D_80082E80[0x24];
                    temp_w1 = D_80082E80[0x25];
                    temp_t2 = (*(u16 *)((u8 *)(&D_8006CCD8) + temp_v1_2));
                    temp_t1 = (*(u16 *)((u8 *)(&D_8006CCE8) + temp_v1_2));
                    ASM_MEM_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
                    first_compare_x = arg2->unk_24.at00.v;
                    temp_a2 = temp_w2 + temp_t2;
                    temp_a1 = temp_w1 + temp_t1;
                    ASM_KEEP(first_compare_x);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    ASM_USE_NV(temp_t2);   /* MATCH pin: load-bearing for the whole function shape */
                    if ((first_compare_x != (temp_a2 & 0xFFFF)) || (arg2->unk_24.at01.v != (temp_a1 & 0xFFFF))) {
                        temp_v0_4 = func_800A0818(arg2->unk_24.at00.v, arg2->unk_24.at01.v, (s16) temp_a2, (s16) temp_a1, arg0 + 0x98);
                        ((S_8016BF74_1 *)arg3)->unk_2A.u = (u16) temp_v0_4;
                        if ((func_8009A66C(temp_v0_4, arg2, arg3, 0x20) << 0x10) <= 0) {
                            u8 *wcf;

                            wcf = (u8 *)&D_80082EA4 - 0x24;
                            ((S_8016BF74_1 *)arg3)->unk_2A.u = func_800A0818(arg2->unk_24.at00.v, arg2->unk_24.at01.v, wcf[0x24], wcf[0x25], arg0 + 0x98);
                        }
                        world_call = (u8 *)&D_80082EA4 - 0x24;
                        var_v0 = func_8009FD7C(arg2->unk_24.at00.v, arg2->unk_24.at01.v, world_call[0x24], world_call[0x25]);
                        ASM_CLOBBER("$19");   /* MATCH pin: keeps a constant in a register as retail does */
                        var_s3 = 0;
                        if ((var_v0 << 0x10) == 0) {
                            goto block_47;
                        }
                        var_s6 = 1;
                        goto block_47;
                    }
                    goto block_clear_71;
                }
                goto block_44;
            }
            goto block_47;
        }
        temp_a0 = arg2->unk_26;
        if ((temp_a0 < 0) || !(D_800E2970[temp_a0].flags & 2)) {
            var_s3 = 0;
            if (!(((S_8016BF74_1 *)arg3)->unk_46 & 0x8000)) {
                temp_v0_5 = func_800A04F0(arg3, arg2->unk_24.at00.v, arg2->unk_24.at01.v, (s16) ((S_8016BF74_1 *)arg3)->unk_2A.u);
                if ((temp_v0_5 == NULL) || !(((S_8016BF74_7 *)temp_v0_5)->unk_1C & 0x2000) || (func_800A0134(temp_v0_5, arg3) >= 0x81) || ((func_8009A540(((s32) (((S_8016BF74_1 *)arg3)->unk_2A.u << 0x10) >> 0x19) & 0xFFFF, arg2->unk_24.at00.v, arg2->unk_24.at01.v, (s16) (((S_8016BF74_1 *)arg3)->unk_88 - 0x20)) << 0x10) == 0)) {
                    if (((S_8016BF74_1 *)arg3)->unk_1C & 0x20000) {
                        u8 *world2;

                        world2 = (u8 *)&D_80082E80;
                        ((S_8016BF74_1 *)arg3)->unk_2A.u = func_800A0818(arg2->unk_24.at00.v, arg2->unk_24.at01.v, world2[0x24], world2[0x25], arg0 + 0x98);
                        if ((func_8009FD7C(arg2->unk_24.at00.v, arg2->unk_24.at01.v, world2[0x24], world2[0x25]) << 0x10) != 0) {
                            temp_v0_6 = func_800A0134(D_800814A8, arg3);
                            var_s3 = 0;
                            if (temp_v0_6 < 0x81) {
                                var_v0 = func_8009A540(((s32) (((S_8016BF74_1 *)arg3)->unk_2A.u << 0x10) >> 0x19) & 0xFFFF, arg2->unk_24.at00.v, arg2->unk_24.at01.v, (s16) (((S_8016BF74_1 *)arg3)->unk_88 - 0x20));
                                ASM_CLOBBER("$19");   /* MATCH pin: keeps a constant in a register as retail does */
                                var_s3 = 0;
                                if ((var_v0 << 0x10) == 0) {
                                    goto block_47;
                                }
                                goto block_clear_71;
                            }
                            goto block_47;
                        }
                        goto block_46;
                    }
block_44:
                    goto block_45;
                }
                goto block_clear_71;
            }
            goto block_47;
        }
block_45:
        func_800A0E6C(arg2, ((S_8016BF74_5 *)arg0)->unk_9C, arg3, arg0 + 0x98);
block_46:
        var_s3 = 0;
block_47:
#ifdef __mips__
        loop_page = (s8 *)0x80070000;
#else
        loop_page = (s8 *)&D_8006CCD8 + 0x3328;
#endif
        ASM_KEEP(loop_page);   /* MATCH pin: load-bearing for the whole function shape */
        var_s7 = (u8 *)(loop_page - 0x3328);
#ifdef __mips__
        loop_page = (s8 *)0x80070000;
#else
        loop_page = (s8 *)&D_8006CD00 + 0x3300;
#endif
        ASM_KEEP(loop_page);   /* MATCH pin: load-bearing for the whole function shape */
        var_s1 = loop_page - 0x3300;
loop_48:
        loop_angle = ((S_8016BF74_1 *)arg3)->unk_2A.s;
        if (((S_8016BF74_5 *)arg0)->unk_98 & 2) {
            temp_v0_3 = *(s16 *)var_s1;
            loop_sum = loop_angle - temp_v0_3;
            goto block_444;
        }
        temp_v0_3 = *(s16 *)var_s1;
        loop_sum = loop_angle + temp_v0_3;
block_444:
        if ((func_8009A66C(loop_sum, arg2, arg3, 0x20) << 0x10) > 0) {
            if (var_s3 < 3) {
                goto block_step_loop;
            }
            temp_v0_3 = var_s6;
            if (temp_v0_3 != 0) {
                goto block_cleanup_loop;
            }
block_step_loop:
                ((S_8016BF74_1 *)arg3)->unk_2A.u = (u16) loop_sum;
                ((S_8016BF74_9 *)((arg3 + ((u8) ((S_8016BF74_1 *)arg3)->unk_71.s & 0x7F))))->unk_74 = (u8) arg2->unk_24.at00.v;
                ((S_8016BF74_9 *)((arg3 + ((u8) ((S_8016BF74_1 *)arg3)->unk_71.s & 0x7F))))->unk_7C = (u8) arg2->unk_24.at01.v;
                loop_next = (u8) ((S_8016BF74_1 *)arg3)->unk_71.s + 1;
                loop_flags = ((S_8016BF74_1 *)arg3)->unk_1C & 0x2000;
                ((S_8016BF74_1 *)arg3)->unk_71.s = (s8) loop_next;
                temp_a0_2 = arg2->unk_24.at00.v;
                temp_call_a1 = arg2->unk_24.at01.v;
                var_a2 = 0x3000;
                if (loop_flags) {
                    var_a2 = 0x300;
                }
                func_8009A3D0(temp_a0_2, temp_call_a1, var_a2);
                temp_a0_2 = ((u16) ((S_8016BF74_1 *)arg3)->unk_2A.u >> 8) & 0xE;
                temp_v1_ptr = (u8 *)((u32) temp_a0_2 + (u32) var_s7);
                arg2->unk_24.at00.v = (u8) (arg2->unk_24.at00.v + *temp_v1_ptr);
                ASM_KEEP(var_s7);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                loop_table_base = (u8 *)&D_8006CCE8;
                loop_table_ptr = (u8 *)((u32) temp_a0_2 + (u32) loop_table_base);
                loop_y = arg2->unk_24.at01.v;
                loop_table_y = *loop_table_ptr;
                loop_call_a0 = arg2->unk_24.at00.v;
                arg2->unk_24.at01.v = (u8) (loop_y + loop_table_y);
                var_a2_2 = 0x3000;
                loop_flags2 = ((S_8016BF74_1 *)arg3)->unk_1C & 0x2000;
                temp_call_a1 = arg2->unk_24.at01.v;
                if (loop_flags2) {
                    var_a2_2 = 0x300;
                }
                func_8009A21C(loop_call_a0, temp_call_a1, var_a2_2);
                var_v0 = var_s3 < 8;
                goto block_594;
block_cleanup_loop:
            goto block_clear_71;
        }
        if ((var_s3 != 0) || (D_80082EA4 == arg2->unk_24.at00u.v) || (var_v0 = func_8009A180(arg3, ((S_8016BF74_6 *)D_800814A8)->unk_58 + 0x20) << 0x10, (var_v0 == 0))) {
            var_s3 += 1;
            var_s1 += 2;
            if (var_s3 >= 8) {
                s8 *state2;

                ASM_KEEP(var_s3);   /* MATCH pin: load-bearing for the whole function shape */
                var_v0 = var_s3 < 8;
block_594:
                if (var_v0 == 0) {
                    ((S_8016BF74_1 *)arg3)->unk_71.s = (s8) ((u8) ((S_8016BF74_1 *)arg3)->unk_71.s & 0x7F);
                    ((S_8016BF74_1 *)arg3)->unk_46 = (u16) (((S_8016BF74_1 *)arg3)->unk_46 & 0x7FFF);
                    func_800A9A0C(arg3);
                    return;
                }
                ((S_8016BF74_1 *)arg3)->unk_46 = (u16) (((S_8016BF74_1 *)arg3)->unk_46 & 0x7FFF);
                ((S_8016BF74_5 *)arg0)->unk_9C = (s8) (u8) arg2->unk_26;
                ((S_8016BF74_1 *)arg3)->unk_6D.u = (u8) (((S_8016BF74_1 *)arg3)->unk_6D.u - 1);
                state2 = (s8 *)&D_80083460;
                ((S_8016BF74_8 *)state2)->unk_08 = (u16) (((S_8016BF74_8 *)state2)->unk_08 + 1);
                if (((S_8016BF74_1 *)arg3)->unk_6D.s == 0) {
block_clear_71:
                    ((S_8016BF74_1 *)arg3)->unk_71.u &= 0x7F;
                    return;
                }
                var_s3 = func_800BCB04((arg2->unk_24.at00.v << 6) | 0x20, (arg2->unk_24.at01.v << 6) | 0x20, (s16) (((S_8016BF74_1 *)arg3)->unk_88 - 0x20));
                var_v0 = var_s3 < 0x200;
                if (var_v0 != 0) {
                    ((S_8016BF74_1 *)arg3)->unk_88 = (u16) var_s3;
                }
                /* Duplicate return node #72. Try simplifying control flow for better match */
                return;
            }
            goto loop_48;
        }
        /* Duplicate return node #72. Try simplifying control flow for better match */
        return;
    }
    return;
}
