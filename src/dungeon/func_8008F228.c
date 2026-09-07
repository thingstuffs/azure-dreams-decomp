#include "common.h"
#include "m2c_compat.h"

struct S_800E3E48 {
    u8 pad00[0x14];
    s32 unk14;
    u8 pad18[0x1C - 0x18];
    s32 unk1C;
    u8 pad20[0x8C - 0x20];
};
typedef struct S_800E3E48 S_800E3E48;

typedef struct {
    u8 bytes[4];
} Unaligned4;

extern volatile s16 D_80013714[8];
extern s32 D_800E3DF0[];
extern S_800E3E48 D_800E3E48[];
extern void *D_80010248[];
extern s32 D_800E3D74;
extern s16 D_800DCED4[];
extern u8 D_800E045C[];
extern M2C_UNK D_8001024B;
extern volatile u8 D_800121E0;
extern volatile u8 D_800121E1;

extern M2C_UNK func_80041E28();
extern M2C_UNK func_800424E0();
extern M2C_UNK func_80035208();
extern M2C_UNK func_80042560();
extern M2C_UNK func_80042640();
extern M2C_UNK func_80042984();
extern M2C_UNK func_800429E4();
extern M2C_UNK func_80094A64();
extern M2C_UNK func_80094AE8();
extern M2C_UNK func_80094B54();
extern M2C_UNK func_80094B94();
extern M2C_UNK func_80094BD0();
extern M2C_UNK func_800982A8();
extern M2C_UNK func_80098614();
extern s32 func_8009B88C();
extern void *(*func_800A0B94())(M2C_UNK, s16, s16, s16);
extern M2C_UNK func_800A152C();
extern s32 func_800A1618();
extern s32 func_800A4E2C();
extern M2C_UNK func_800A6A9C();
extern M2C_UNK func_800C542C();

typedef struct S_80094988_0 {
    u8 pad_00[0x2D50];
    u16 unk_2D50;
    u8 pad_2D52[0x6];
    s32 unk_2D58;
    u8 pad_2D5C[0x9B8];
    s16 unk_3714;
} S_80094988_0;   /* page in func_80094988 */

typedef struct S_80094988_1 {
    u8 pad_00[0xF8];
    u16 unk_F8;
    u8 pad_FA[0x2];
    s32 unk_FC;
} S_80094988_1;   /* arg0 in func_80094988 */

typedef struct S_80094988_2 {
    u8 pad_00[0x2238];
    u8 unk_2238;
    u8 pad_2239[0x13];
    u8 unk_224C;
} S_80094988_2;   /* var_t3 in func_80094988 */

typedef struct S_80094988_3 {
    s32 unk_00;
} S_80094988_3;   /* var_t5 in func_80094988 */

typedef struct S_80094988_4 {
    u8 pad_00[0x29C];
    s32 unk_29C;
} S_80094988_4;   /* page2 + scaled in func_80094988 */

typedef struct S_80094988_5 {
    u8 pad_00[0x2D52];
    u8 unk_2D52;
} S_80094988_5;   /* var_v1_2 in func_80094988 */

typedef struct S_80094988_6 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_80094988_6;   /* var_a0 in func_80094988 */

typedef struct S_80094988_7 {
    u8 pad_00[0x21E0];
    volatile u8 unk_21E0;
    volatile u8 unk_21E1;
} S_80094988_7;   /* (void *)dispatch_probe in func_80094988 */

typedef struct S_80094988_8 {
    u8 pad_00[0x21E0];
    volatile u8 unk_21E0;
    volatile u8 unk_21E1;
} S_80094988_8;   /* dispatch_page in func_80094988 */

typedef struct S_80094988_9_pre {
    u8 unk_00;
    u8 pad_01[0x1];
} S_80094988_9_pre;   /* the 0x2 bytes before var_s4 in func_80094988, addressed as var_s4[-1] */

typedef struct S_80094988_9 {
    u8 unk_00;
} S_80094988_9;   /* var_s4 in func_80094988 */

typedef struct S_80094988_10 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_80094988_10;   /* var_v1 in func_80094988 */

typedef struct S_80094988_11 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_80094988_11;   /* arg1 in func_80094988 */

typedef struct S_80094988_12 {
    u8 pad_00[0xAC];
    void * unk_AC;
    u8 pad_B0[0x20];
    void ** unk_D0;
} S_80094988_12;   /* temp_s1_2 in func_80094988 */

typedef struct S_80094988_13 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
} S_80094988_13;   /* temp_v0_2 in func_80094988 */

typedef struct S_80094988_14 {
    s32 unk_00;
} S_80094988_14;   /* addr_temp in func_80094988 */

typedef struct S_80094988_15 {
    u8 pad_00[0x3714];
    s16 unk_3714;
} S_80094988_15;   /* page2 in func_80094988 */

void func_80094988(S_80094988_1 *arg0, S_80094988_11 *arg1, u16 arg2, u16 arg3) {
    s16 sp18;
    s16 sp1A;
    u8 sp1C;
    u8 sp1D;
    u16 sp20;
    u16 sp28;
    u16 sp30;
    u8 *var_s4;
    u8 *var_a3;
    u8 *var_t6;
    u8 *var_a2;
    u8 *var_t2;
    u8 *var_t3;
    register u8 *var_t4 ASM_REG("$12");   /* MATCH pin: retail register colouring depends on it */
    u8 *var_t5;
    s32 temp_v0;
    s16 var_s1;
    s32 var_s6;
    register s32 var_t1 ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */
    s32 var_t1_2;
    register s32 var_t1_3 ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */
    u8 *var_s2;
    S_80094988_12 *temp_s1_2;
    S_80094988_13 *temp_v0_2;
    register void *var_a0 ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    void *var_v1;
    register u8 *page ASM_REG("$16");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 idx0;
    register s32 idx1 ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 idx1_copy ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    void *entry_ptr;
    register S_800E3E48 *entries ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 ff ASM_REG("$15");   /* MATCH pin: retail register colouring depends on it */
    u8 *d3df0;
    S_800E3E48 *entries_src;
    register u8 *addr_temp ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 *copy_src;
    s32 *copy_dst;
    s32 *copy_end;
    s32 copy0;
    s32 copy1;
    s32 copy2;
    s32 copy3;
    u8 *page2;
    void **table2;
    s32 ff2;
    register s32 scaled ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    register u8 *var_v1_2 ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    register u32 dispatch_probe ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    register u8 *dispatch_page ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    u32 dispatch_idx;
    s32 sign_temp;   /* MATCH pin: retail delay-slot fill depends on it */
    s32 signed_index;
    register s32 scaled_index ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */

    page = (u8 *)0x80010000;
    sp30 = (s16)((S_80094988_0 *)page)->unk_3714 & 2;
    ((S_80094988_0 *)page)->unk_3714 =
        (s16)((u16)((S_80094988_0 *)page)->unk_3714 | 2);
    sp20 = arg2;
    sp28 = arg3;
    func_800A6A9C();
    func_80041E28(arg1, (s32)page | 0x2194);
    var_t1 = 0;
    ff = 0xFF;
    ASM_KEEP(ff);   /* MATCH pin: retail schedule: same instructions, different order without it */
    addr_temp = (u8 *)0x800E0000;
    ASM_KEEP(addr_temp);   /* MATCH pin: retail immediate-load split depends on it */
    var_t5 = addr_temp + 0x3DF0;
    var_t3 = page;
    var_t4 = var_t3;
    addr_temp = (u8 *)0x800E0000;
    ASM_KEEP(addr_temp);   /* MATCH pin: retail immediate-load split depends on it */
    entries = (S_800E3E48 *)(addr_temp + 0x3E48);
    var_t6 = (u8 *)entries;
    arg0->unk_F8 = (u16)((S_80094988_0 *)page)->unk_2D50;
    var_t2 = var_t3;
    arg0->unk_FC = (s32)((S_80094988_0 *)page)->unk_2D58;

loop_1:
    (*(Unaligned4 *)((u8 *)var_t2 + 0x248)) =
        (*(Unaligned4 *)((u8 *)var_t2 + 0x21E8));
    idx0 = ((S_80094988_2 *)var_t3)->unk_2238;
    if (idx0 != ff) {
        (*(s32 *)((u8 *)var_t2 + 0x29C)) =
            (s32)((void **)0x80010248 + idx0);
    } else {
        (*(s32 *)((u8 *)var_t2 + 0x29C)) = 0;
    }
    (*(S_800E3E48 *)((u8 *)var_t6 + 0)) =
        (*(S_800E3E48 *)((u8 *)var_t4 + 0x2260));
    idx1 = ((S_80094988_2 *)var_t3)->unk_224C;
    ASM_KEEP(idx1);   /* MATCH pin: retail delay-slot fill depends on it */
    if (idx1 != ff) {
        idx1_copy = idx1;
        entry_ptr = (void *)((u32)(idx1_copy * sizeof(S_800E3E48)) +
                             (u32)entries);
        ((S_80094988_3 *)var_t5)->unk_00 = (s32)entry_ptr;
    } else {
        ((S_80094988_3 *)var_t5)->unk_00 = 0;
    }
    var_t5 += 4;
    var_t3 += 1;
    var_t4 += 0x8C;
    var_t6 += 0x8C;
    var_t1 += 1;
    ASM_KEEP(var_t1);   /* MATCH pin: retail delay-slot fill depends on it */
    var_t2 += 4;
    if (var_t1 < 0x14) {
        goto loop_1;
    }

    page2 = (u8 *)0x80010000;
    scaled = var_t1 * 4;
    ((S_80094988_4 *)(page2 + scaled))->unk_29C = 0;
    var_t1 = 0;
    var_a3 = page2;
    ff2 = 0xFF;
    table2 = (void **)(page2 + 0x248);
    var_a0 = arg0;
    do {
        var_v1_2 = (u8 *)(var_t1 + (u32)var_a3);
        idx0 = ((S_80094988_5 *)var_v1_2)->unk_2D52;
        if (idx0 != ff2) {
            ((S_80094988_6 *)var_a0)->unk_D0 =
                (s32)((idx0 * 4) + (u32)table2);
        } else {
            ((S_80094988_6 *)var_a0)->unk_D0 = 0;
        }
        var_t1 += 1;
        var_a0 += 4;
    } while (var_t1 < 2);

    dispatch_probe = 0x80010000;
    dispatch_probe = ((S_80094988_7 *)((void *)dispatch_probe))->unk_21E0;
    if (dispatch_probe != 0xFF) {
        dispatch_page = (u8 *)0x80010000;
        dispatch_probe = (u32)dispatch_page;
        dispatch_idx = ((S_80094988_8 *)dispatch_page)->unk_21E0;
        dispatch_probe |= 0x248;
        dispatch_idx <<= 2;
        var_s2 = (u8 *)(dispatch_idx + dispatch_probe);
    } else {
        var_s2 = NULL;
    }
    func_800982A8(arg1, var_s2);
    dispatch_probe = 0x80010000;
    dispatch_probe = ((S_80094988_7 *)((void *)dispatch_probe))->unk_21E1;
    if (dispatch_probe != 0xFF) {
        dispatch_page = (u8 *)0x80010000;
        dispatch_probe = (u32)dispatch_page;
        dispatch_idx = ((S_80094988_8 *)dispatch_page)->unk_21E1;
        dispatch_probe |= 0x248;
        dispatch_idx <<= 2;
        var_s2 = (u8 *)(dispatch_idx + dispatch_probe);
    } else {
        var_s2 = NULL;
    }
    func_80098614(arg1, var_s2);
    var_s2 = (u8 *)0x80010248;
    var_s6 = 0;
    var_s4 = (u8 *)0x8001024B;
            do {
                if (((S_80094988_9_pre *)var_s4)[-1].unk_00 == 0x13) {
                    var_t1_3 = 0;
                    if (((S_80094988_9 *)var_s4)->unk_00 & 0x20) {
                        var_s1 = 0;
                        var_v1 = arg0;
                        do {
                            if (((S_80094988_10 *)var_v1)->unk_D0 == var_s2) {
                                var_s1 = var_t1_3 + 1;
                            }
                            var_t1_3 += 1;
                            var_v1 += 4;
                        } while (var_t1_3 < 2);
                        if ((var_s1 << 0x10) != 0) {
                            var_s1 -= 1;
                            temp_v0 = func_800A1618(*var_s2, 3);
                            if (temp_v0 != 0) {
                                if ((func_8009B88C(0, (s16)sp20, (s16)sp28,
                                                   &sp18, &sp1A) << 0x10) == 0) {
                                    do {
                                    } while ((func_800A4E2C(&sp1C, &sp1D) << 16) < 0);
                                    sp18 = (s16)sp1C;
                                    sp1A = (s16)sp1D;
                                }
                                temp_v0_2 = func_800A0B94(*var_s2, temp_v0, 1)(
                                    1, sp18, sp1A,
                                    arg1->unk_88);
                                sign_temp = var_s1 << 16;
                                signed_index = sign_temp >> 16;
                                scaled_index = signed_index * 4;
                                temp_s1_2 = (void *)((u32)scaled_index +
                                                     (u32)arg0);
                                temp_s1_2->unk_AC = temp_v0_2;
                                if (temp_v0_2 != NULL) {
                                    func_80042640(temp_v0_2,
                                                  temp_v0_2->unk_13);
                                    func_800424E0(temp_v0_2,
                                                  temp_v0_2->unk_13,
                                                  var_s2);
                                    temp_s1_2->unk_D0 = var_s2;
                                    ((S_80094988_9 *)var_s4)->unk_00 =
                                        (u8)(((S_80094988_9 *)var_s4)->unk_00 | 0x20);
                                    ASM_KEEP(var_s4);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                                    addr_temp =
                                        (u8 *)&D_800E3D74 + scaled_index;
                                    ASM_KEEP(addr_temp);   /* MATCH pin: retail immediate-load split depends on it */
                                    ((S_80094988_14 *)addr_temp)->unk_00 = 0;
                                    if (temp_v0_2->unk_25 == 0) {
                                        temp_v0_2->unk_1C =
                                            (s32)(temp_v0_2->unk_1C | 8);
                                    }
                                    D_800E3DF0[((S_80094988_9 *)var_s4)->unk_00 & 0x1F] =
                                        (s32)temp_v0_2;
                                    func_80042984(temp_v0_2);
                                    func_800A152C(*var_s2, 3);
                                    func_80042560(temp_v0_2);
                                    func_800C542C(
                                        temp_v0_2,
                                        D_800DCED4[func_800429E4(temp_v0_2)],
                                        signed_index, 1);
                                }
                            }
                        }
                    }
                }
                var_s6 += 1;
                var_s4 += 4;
                var_s2 += 4;
            } while (var_s6 < 0x14);
            if (sp30 == 0) {
                page2 = (u8 *)0x80010000;
                ((S_80094988_15 *)page2)->unk_3714 =
                    (s16)((u16)((S_80094988_15 *)page2)->unk_3714 & 0xFFFD);
            }
            func_80035208(D_800E045C);
            return;
}
