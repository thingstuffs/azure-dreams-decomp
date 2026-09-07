#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))

extern u16 D_80083462[5];
extern u8 D_801746A4[];
extern u8 D_80174684[];
extern s16 D_80083228[5];
extern volatile s16 D_80013714[8];
extern u8 D_801746C4[];
extern s32 D_80083460[3];
extern u8 D_8017467C[];
extern s32 D_8008346C[];
extern u16 D_80082EA4[8];
extern int D_800814A8[4];
extern u8 D_80082E80[];
extern u8 D_8016B778[];
extern s8 D_800E2970[];
extern void *D_8016A828[];
s8 func_8009FB34();
s32 func_8009FD7C();
s32 func_800A1C58();
M2C_UNK func_800A9A0C();
extern void func_800AA258(void *, void *, void *, void *);
s32 func_800AA6B4();
M2C_UNK func_800AA888();
s32 func_800AA924();
M2C_UNK func_800AAF00();
extern void func_8016B8AC() __attribute__((noreturn));
M2C_UNK func_8016BD14();
M2C_UNK func_8016BF74();
s32 func_8016C720();
M2C_UNK func_8016C8AC();
s32 func_8016C98C();
M2C_UNK func_8016DAA4();
M2C_UNK func_8016EF10();
extern M2C_UNK D_8017469C;
extern M2C_UNK D_801746BC;

void func_8016B778(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&state_store };
    M2C_UNK sp18;
    s32 temp_a1_value;
    s32 bits_100;
    s32 mask_100;
    s16 a0818_result;
    s32 temp_v0_3;
    s8 temp_v0;
    u16 temp_v0_2;
    register u8 *var_v0 ASM_REG("$2");
    register void *temp_v1_dispatch ASM_REG("$3");
    register u32 temp_v0_page ASM_REG("$2");
    register u8 *temp_a1 ASM_REG("$5");
    register void *call_obj ASM_REG("$4");
    register s32 clear_mask_hi ASM_REG("$3");
    u8 *dungeon_obj;
    u8 *entry_base;
    u8 *entry;
    u8 *global_814A8;
    s32 *global_83460;
    if (!(*D_80083462 & 0x1000)) {
        goto block_3;
    }
    M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
    func_8016BD14();
    return;
block_3:
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x200)) {
        goto block_8;
    }
    if (M2C_FIELD(arg2, u8 **, 0x2C) != D_801746A4) {
        goto block_7;
    }
    clear_mask_hi = (s32)0xFFFB0000;
    M2C_FIELD(arg0, u8 *, 0x9A) = 0xDU;
    M2C_FIELD(arg0, s8 *, 0x9B) = 1;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    ASM_KEEP(clear_mask_hi);
    M2C_FIELD(arg3, s32 *, 0x1C) &= clear_mask_hi | 0xFFFF;
    return;
block_7:
    if (func_800AA924(arg0, arg1, arg2, &D_8017469C) != 0) {
        goto block_65;
    }
block_8:
    if (*D_80083462 & 0x2000) {
        goto block_33;
    }
    bits_100 = M2C_FIELD(arg3, s32 *, 0x1C);
    mask_100 = bits_100 & 0x100;
    ASM_SCHED_BARRIER();
    call_obj = arg0;
    if (!mask_100) {
        goto block_12;
    }
    func_800AA258(call_obj, arg1, arg2, arg3);
    return;
block_12:
    if (M2C_FIELD(arg0, u8 *, 0x9A) != 0xE) {
        if (M2C_FIELD(arg0, u8 *, 0xB3) == 0) {
            temp_v1_dispatch = M2C_FIELD(arg2, void **, 0x2C);
            ASM_KEEP(temp_v1_dispatch);
            temp_v0_page = 0x80170000;
            ASM_KEEP(temp_v0_page);
            temp_a1 = (u8 *)temp_v0_page + 0x467C;
            ASM_TAILSLOT_PIN(temp_a1);
            func_8016B8AC();
            return;
        }
        if (M2C_FIELD(arg2, u8 **, 0x2C) != D_80174684) {
            M2C_FIELD(arg2, u8 **, 0x2C) = D_80174684;
            func_80047784(arg2, D_80174684[((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
        }
state_store:
        M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
    }
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF3);
    if (M2C_FIELD(arg0, u8 *, 0xB4) != 0) {
        goto block_25;
    }
    if ((u16) *D_80013714 & 8) {
        goto block_25;
    }
    if (M2C_FIELD(arg3, s16 *, 0x64) == 0) {
        goto block_28;
    }
    if (func_800AA6B4(arg0, arg1, arg2, D_801746C4) == 0) {
        goto block_28;
    }
    return;
block_25:
    if (M2C_FIELD(arg3, s16 *, 0x64) == 0) {
        goto block_28;
    }
    global_83460 = D_80083460;
    if (global_83460[4] != (arg3 - 0x20)) {
        goto block_28;
    }
    global_83460[4] &= 0x7FFFFFFF;
block_28:
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x80000)) {
        goto block_31;
    }
    func_800AA888(arg0, arg1, arg2, arg3);
    func_8016DAA4(arg0, arg1, arg2, arg3);
    M2C_FIELD(arg2, u8 **, 0x2C) = D_8017467C;
    func_80047784(arg2, D_8017467C[((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(arg0, s32 *, 0x90) = 0;
    return;
block_31:
    if ((func_800A1C58(arg3) << 0x10) == 0) {
        goto block_33;
    }
    M2C_FIELD(arg3, s32 *, 0x18) = 0;
    *D_8008346C = 0;
block_33:
    temp_v0 = func_8009FB34(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    M2C_FIELD(arg2, s8 *, 0x26) = temp_v0;
    if (M2C_FIELD(arg3, s8 *, 0x6D) <= 0) {
        goto block_58;
    }
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x20) {
        goto block_50;
    }
    if (M2C_FIELD(arg2, u16 *, 0x24) == *D_80082EA4) {
        goto block_56;
    }
    if (M2C_FIELD(arg3, u16 *, 0x46) & 0x8000) {
        goto block_44;
    }
    if (!(*D_80083462 & 0x2000)) {
        goto block_39;
    }
    if ((func_8009A180(arg3, M2C_FIELD(*D_800814A8, s32 *, 0x58) + 0x20) << 0x10) != 0) {
        goto block_65;
    }
block_39:
    if (!((u16) *D_80013714 & 8)) {
        goto block_42;
    }
    func_8016EF10(arg0, arg1, arg2);
    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    func_800A9A0C(arg3);
    M2C_FIELD(arg3, u16 *, 0x46) &= 0x7FFF;
    return;
block_42:
    if ((func_8016C98C(arg0, arg1, arg2, 0) << 0x10) == 0) {
        goto block_65;
    }
    temp_v0_2 = M2C_FIELD(arg3, u16 *, 0x46) | 0x4000;
    M2C_FIELD(arg3, u16 *, 0x46) = temp_v0_2;
    if (!(temp_v0_2 & 0x8000)) {
        goto block_56;
    }
block_44:
    temp_v0_3 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
    if ((u32) (temp_v0_3 - 1) >= 0xCU) {
        goto block_55;
    }
    (void)jt_keep; goto *D_8016A828[(u32)((temp_v0_3) - 1)];
jt_c8:
jt_c9:
    if ((func_8016C720(arg0, arg1, arg2, arg3) << 0x10) != 0) {
        goto block_65;
    }
    func_8016C8AC(arg0, arg1, arg2, arg3);
    return;
jt_c5:
jt_c6:
jt_c7:
    a0818_result = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), D_80082E80[0x24], D_80082E80[0x25], &sp18);
    global_814A8 = (u8 *)*D_800814A8;
    M2C_FIELD(arg3, s16 *, 0x2A) = a0818_result;
    if (M2C_FIELD(global_814A8, u8 *, 0x9A) == 0x11) {
        var_v0 = (u8 *)0x80170000;
        goto block_53_low;
    }
jt_c12:
block_50:
    func_800A9A0C(arg3);
    return;
jt_c1:
jt_c2:
jt_c3:
    var_v0 = (u8 *)0x80170000;
block_53_low:
    var_v0 -= 0x4888;
block_53:
    func_800AAF00(arg0, arg1, arg2, &D_801746BC, var_v0);
    return;
jt_c4:
jt_c10:
jt_c11:
block_55:
block_56:
    func_8016BF74(arg0, arg1, arg2, arg3);
    return;
block_58:
    temp_a1_value = M2C_FIELD(arg3, s32 *, 0x1C);
    if (temp_a1_value & 0x2000) {
        goto block_65;
    }
    ASM_SCHED_BARRIER();
    if ((u16) *D_80013714 & 8) {
        goto block_65;
    }
    if (temp_v0 < 0) {
        goto block_62;
    }
    entry_base = D_800E2970;
    entry = (temp_v0 * 0x14) + entry_base;
    if (M2C_FIELD(entry, u16 *, 0xC) & 2) {
        goto block_65;
    }
block_62:
    if (temp_a1_value & 0x430) {
        goto block_65;
    }
    dungeon_obj = D_80082E80;
    if ((func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), dungeon_obj[0x24], dungeon_obj[0x25]) << 0x10) == 0) {
        goto block_65;
    }
    M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), dungeon_obj[0x24], dungeon_obj[0x25], &sp18);
block_65:
    return;
}
