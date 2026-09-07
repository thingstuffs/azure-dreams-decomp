#include "common.h"

typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

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

void func_80094988(void *arg0, void *arg1, u16 arg2, u16 arg3) {
    s16 sp18;
    s16 sp1A;
    u8 sp1C;
    u8 sp1D;
    u16 sp20;
    u16 sp28;
    u16 sp30;
    register u8 *var_s4 ASM_REG("$20");
    register u8 *var_a3 ASM_REG("$7");
    register u8 *var_t6 ASM_REG("$14");
    u8 *var_a2;
    register u8 *var_t2 ASM_REG("$10");
    register u8 *var_t3 ASM_REG("$11");
    register u8 *var_t4 ASM_REG("$12");
    register u8 *var_t5 ASM_REG("$13");
    s32 temp_v0;
    register s16 var_s1 ASM_REG("$17");
    s32 var_s6;
    register s32 var_t1 ASM_REG("$9");
    s32 var_t1_2;
    register s32 var_t1_3 ASM_REG("$9");
    register u8 *var_s2 ASM_REG("$18");
    register void *temp_s1_2 ASM_REG("$17");
    void *temp_v0_2;
    register void *var_a0 ASM_REG("$4");
    void *var_v1;
    register u8 *page ASM_REG("$16");
    u8 idx0;
    register s32 idx1 ASM_REG("$2");
    register s32 idx1_copy ASM_REG("$3");
    register void *entry_ptr ASM_REG("$2");
    register S_800E3E48 *entries ASM_REG("$17");
    register s32 ff ASM_REG("$15");
    u8 *d3df0;
    S_800E3E48 *entries_src;
    register u8 *addr_temp ASM_REG("$2");
    register s32 *copy_src ASM_REG("$6");
    register s32 *copy_dst ASM_REG("$7");
    register s32 *copy_end ASM_REG("$8");
    register s32 copy0 ASM_REG("$2");
    register s32 copy1 ASM_REG("$3");
    register s32 copy2 ASM_REG("$4");
    register s32 copy3 ASM_REG("$5");
    register u8 *page2 ASM_REG("$3");
    register void **table2 ASM_REG("$5");
    register s32 ff2 ASM_REG("$6");
    register s32 scaled ASM_REG("$2");
    register u8 *var_v1_2 ASM_REG("$3");
    register u32 dispatch_probe ASM_REG("$3");
    register u8 *dispatch_page ASM_REG("$4");
    register u32 dispatch_idx ASM_REG("$2");
    register s32 sign_temp ASM_REG("$2");
    register s32 signed_index ASM_REG("$21");
    register s32 scaled_index ASM_REG("$19");

    page = (u8 *)0x80010000;
    sp30 = (s16)M2C_FIELD(page, s16 *, 0x3714) & 2;
    M2C_FIELD(page, s16 *, 0x3714) =
        (s16)((u16)M2C_FIELD(page, s16 *, 0x3714) | 2);
    sp20 = arg2;
    sp28 = arg3;
    func_800A6A9C();
    func_80041E28(arg1, (s32)page | 0x2194);
    var_t1 = 0;
    ff = 0xFF;
    ASM_KEEP(ff);
    addr_temp = (u8 *)0x800E0000;
    ASM_KEEP(addr_temp);
    var_t5 = addr_temp + 0x3DF0;
    var_t3 = page;
    var_t4 = var_t3;
    addr_temp = (u8 *)0x800E0000;
    ASM_KEEP(addr_temp);
    entries = (S_800E3E48 *)(addr_temp + 0x3E48);
    var_t6 = (u8 *)entries;
    M2C_FIELD(arg0, u16 *, 0xF8) = (u16)M2C_FIELD(page, u16 *, 0x2D50);
    var_t2 = var_t3;
    M2C_FIELD(arg0, s32 *, 0xFC) = (s32)M2C_FIELD(page, s32 *, 0x2D58);

loop_1:
    M2C_FIELD(var_t2, Unaligned4 *, 0x248) =
        M2C_FIELD(var_t2, Unaligned4 *, 0x21E8);
    idx0 = M2C_FIELD(var_t3, u8 *, 0x2238);
    if (idx0 != ff) {
        M2C_FIELD(var_t2, s32 *, 0x29C) =
            (s32)((void **)0x80010248 + idx0);
    } else {
        M2C_FIELD(var_t2, s32 *, 0x29C) = 0;
    }
    M2C_FIELD(var_t6, S_800E3E48 *, 0) =
        M2C_FIELD(var_t4, S_800E3E48 *, 0x2260);
    idx1 = M2C_FIELD(var_t3, u8 *, 0x224C);
    ASM_KEEP(idx1);
    if (idx1 != ff) {
        idx1_copy = idx1;
        entry_ptr = (void *)((u32)(idx1_copy * sizeof(S_800E3E48)) +
                             (u32)entries);
        M2C_FIELD(var_t5, s32 *, 0) = (s32)entry_ptr;
    } else {
        M2C_FIELD(var_t5, s32 *, 0) = 0;
    }
    var_t5 += 4;
    var_t3 += 1;
    var_t4 += 0x8C;
    var_t6 += 0x8C;
    var_t1 += 1;
    ASM_KEEP(var_t1);
    var_t2 += 4;
    if (var_t1 < 0x14) {
        goto loop_1;
    }

    page2 = (u8 *)0x80010000;
    scaled = var_t1 * 4;
    M2C_FIELD(page2 + scaled, s32 *, 0x29C) = 0;
    var_t1 = 0;
    var_a3 = page2;
    ff2 = 0xFF;
    table2 = (void **)(page2 + 0x248);
    var_a0 = arg0;
    do {
        var_v1_2 = (u8 *)(var_t1 + (u32)var_a3);
        idx0 = M2C_FIELD(var_v1_2, u8 *, 0x2D52);
        if (idx0 != ff2) {
            M2C_FIELD(var_a0, s32 *, 0xD0) =
                (s32)((idx0 * 4) + (u32)table2);
        } else {
            M2C_FIELD(var_a0, s32 *, 0xD0) = 0;
        }
        var_t1 += 1;
        var_a0 += 4;
    } while (var_t1 < 2);

    dispatch_probe = 0x80010000;
    ASM_KEEP(dispatch_probe);
    dispatch_probe = M2C_FIELD((void *)dispatch_probe, volatile u8 *, 0x21E0);
    if (dispatch_probe != 0xFF) {
        dispatch_page = (u8 *)0x80010000;
        dispatch_probe = (u32)dispatch_page;
        dispatch_idx = M2C_FIELD(dispatch_page, volatile u8 *, 0x21E0);
        dispatch_probe |= 0x248;
        dispatch_idx <<= 2;
        var_s2 = (u8 *)(dispatch_idx + dispatch_probe);
    } else {
        var_s2 = NULL;
    }
    func_800982A8(arg1, var_s2);
    dispatch_probe = 0x80010000;
    ASM_KEEP(dispatch_probe);
    dispatch_probe = M2C_FIELD((void *)dispatch_probe, volatile u8 *, 0x21E1);
    if (dispatch_probe != 0xFF) {
        dispatch_page = (u8 *)0x80010000;
        dispatch_probe = (u32)dispatch_page;
        dispatch_idx = M2C_FIELD(dispatch_page, volatile u8 *, 0x21E1);
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
                if (M2C_FIELD(var_s4, u8 *, -2) == 0x13) {
                    var_t1_3 = 0;
                    if (M2C_FIELD(var_s4, u8 *, 0) & 0x20) {
                        var_s1 = 0;
                        var_v1 = arg0;
                        do {
                            if (M2C_FIELD(var_v1, s32 *, 0xD0) == var_s2) {
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
                                    M2C_FIELD(arg1, s16 *, 0x88));
                                sign_temp = var_s1 << 16;
                                ASM_KEEP(sign_temp);
                                signed_index = sign_temp >> 16;
                                ASM_KEEP(signed_index);
                                scaled_index = signed_index * 4;
                                ASM_KEEP(scaled_index);
                                temp_s1_2 = (void *)((u32)scaled_index +
                                                     (u32)arg0);
                                ASM_KEEP(temp_s1_2);
                                M2C_FIELD(temp_s1_2, void **, 0xAC) = temp_v0_2;
                                if (temp_v0_2 != NULL) {
                                    func_80042640(temp_v0_2,
                                                  M2C_FIELD(temp_v0_2, u8 *, 0x13));
                                    func_800424E0(temp_v0_2,
                                                  M2C_FIELD(temp_v0_2, u8 *, 0x13),
                                                  var_s2);
                                    M2C_FIELD(temp_s1_2, void ***, 0xD0) = var_s2;
                                    M2C_FIELD(var_s4, u8 *, 0) =
                                        (u8)(M2C_FIELD(var_s4, u8 *, 0) | 0x20);
                                    ASM_KEEP(var_s4);
                                    addr_temp =
                                        (u8 *)&D_800E3D74 + scaled_index;
                                    ASM_KEEP(addr_temp);
                                    M2C_FIELD(addr_temp, s32 *, 0) = 0;
                                    if (M2C_FIELD(temp_v0_2, u8 *, 0x25) == 0) {
                                        M2C_FIELD(temp_v0_2, s32 *, 0x1C) =
                                            (s32)(M2C_FIELD(temp_v0_2, s32 *, 0x1C) | 8);
                                    }
                                    D_800E3DF0[M2C_FIELD(var_s4, u8 *, 0) & 0x1F] =
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
                M2C_FIELD(page2, s16 *, 0x3714) =
                    (s16)((u16)M2C_FIELD(page2, s16 *, 0x3714) & 0xFFFD);
            }
            func_80035208(D_800E045C);
            return;
}
