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

typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

typedef struct DungeonEnv {
    u8 pad0[0x24];
    u8 x;
    u8 y;
} DungeonEnv;

typedef struct EmptyArg {
} EmptyArg;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() 0
#define M2C_SYNC() 0
#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern void *D_80170808[];
void func_80047784();
s32 func_8009A180();
s8 func_8009FB34();
s32 func_8009FD7C();
s16 func_800A0818();
s32 func_800A1C58();
M2C_UNK func_800A9A0C();
M2C_UNK func_800AA258();
s32 func_800AA6B4();
M2C_UNK func_800AA79C();
M2C_UNK func_800AA888();
s32 func_800AA924();
M2C_UNK func_800AAB10();
M2C_UNK func_800AAF00();
M2C_UNK func_801716CC();
M2C_UNK func_80171884();
s32 func_80171FCC();
M2C_UNK func_80172190();
s32 func_801722B8();
M2C_UNK func_80173D10();
extern void *D_800814A8;
extern DungeonEnv D_80082E80;
extern u16 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern DungeonRecord D_800E2970[];
extern M2C_UNK D_801711A4;
extern M2C_UNK D_8017418C;
extern M2C_UNK D_80174194;
extern M2C_UNK D_801741AC;
extern M2C_UNK D_801741C4;
extern M2C_UNK D_801741CC;

void func_801711A4(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    M2C_UNK sp18;
    M2C_UNK *var_v0;
    s32 temp_a1;
    s32 temp_v0_3;
    s8 temp_v0;
    s16 temp_calc;
    u16 temp_v0_2;
    void *temp_env;
    DungeonEnv *dungeon_env;
    M2C_UNK *sp18p;
    EmptyArg empty_arg;

    if (!(D_80083462 & 0x1000)) {
        goto block_3;
    }
    M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
    func_801716CC();
    goto block_55;
block_3:
    ASM_CLOBBER("$4");
    if (M2C_FIELD(arg3, u8 *, 0x25) != 0) {
        goto block_7;
    }
    func_800AA79C(arg0, arg1, arg2, arg3);
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_801741CC) {
        goto block_55;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801741C4;
    func_80047784(arg2, *(((u8 *)&D_801741C4) + (((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7)), 0);
    goto block_55;
block_7:
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x200)) {
        goto block_12;
    }
    {
        register void *common_a0 ASM_REG("$4") = arg0;
        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_801741CC) {
            goto block_11;
        }
        {
            register void *saved0 ASM_REG("$16") = arg0;
            register void *saved2 ASM_REG("$18") = arg3;
            register s32 mask ASM_REG("$3") = (s32)0xFFFB0000;
            s32 flags;
            M2C_FIELD(saved0, u8 *, 0x9A) = 0xDU;
            M2C_FIELD(saved0, s8 *, 0x9B) = 1;
            M2C_FIELD(saved0, s32 *, 0x8C) = 0;
            flags = M2C_FIELD(saved2, s32 *, 0x1C);
            ASM_KEEP_DEP_NV(mask, flags);
            mask |= 0xFFFF;
            flags &= mask;
            M2C_FIELD(saved2, s32 *, 0x1C) = flags;
            goto block_55;
        }
block_11:
        if (func_800AA924(common_a0, arg1, arg2, &D_801741C4) != 0) {
            goto block_55;
        }
    }
block_12:
    if (D_80083462 & 0x2000) {
        goto block_27;
    }
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x100)) {
        goto block_16;
    }
    func_800AA258(arg0, arg1, arg2, arg3);
    goto block_55;
block_16:
    ASM_SCHED_BARRIER();
    if (M2C_FIELD(arg0, u8 *, 0x9A) == 0xE) {
        goto block_18;
    }
    M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
block_18:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_8017418C) {
        goto block_20;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8017418C;
    func_80047784(arg2, *(((u8 *)&D_8017418C) + (((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7)), 0);
    M2C_FIELD(arg2, s8 *, 5) = 1;
    M2C_FIELD(arg0, s16 *, 0xAE) = 0;
    M2C_FIELD(arg0, s16 *, 0xA8) = 0;
block_20:
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000);
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
    if (M2C_FIELD(arg3, s16 *, 0x64) == 0) {
        goto block_22;
    }
    if (func_800AA6B4(arg0, arg1, arg2, &D_80174194) != 0) {
        goto block_55;
    }
block_22:
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x80000)) {
        goto block_25;
    }
    func_800AA888(arg0, arg1, arg2, arg3);
    M2C_FIELD(arg0, s16 *, 0xA8) = 0;
    func_80173D10(arg0, arg1, arg2, arg3);
    goto block_55;
block_25:
    if ((func_800A1C58(arg3) << 0x10) == 0) {
        goto block_27;
    }
    func_800AAB10(arg0, arg1, arg2, arg3);
block_27:
    temp_v0 = func_8009FB34(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    M2C_FIELD(arg2, s8 *, 0x26) = temp_v0;
    if (M2C_FIELD(arg3, s8 *, 0x6D) <= 0) {
        goto block_49;
    }
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x20) {
        goto block_41;
    }
    if (M2C_FIELD(arg2, u16 *, 0x24) == D_80082EA4) {
        goto block_47;
    }
    if (M2C_FIELD(arg3, u16 *, 0x46) & 0x8000) {
        goto block_35;
    }
    if (!(D_80083462 & 0x2000)) {
        goto block_33;
    }
    if ((func_8009A180(arg3, M2C_FIELD(D_800814A8, s32 *, 0x58) + 0x20) << 0x10) != 0) {
        goto block_55;
    }
block_33:
    if ((func_801722B8(arg0, arg1, arg2, 0) << 0x10) == 0) {
        goto block_55;
    }
    temp_v0_2 = M2C_FIELD(arg3, u16 *, 0x46) | 0x4000;
    M2C_FIELD(arg3, u16 *, 0x46) = temp_v0_2;
    if (!(temp_v0_2 & 0x8000)) {
        goto block_47;
    }
block_35:
    temp_v0_3 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
    if ((u32) (temp_v0_3 - 1) >= 0xCU) {
        goto block_46;
    }
    (void)jt_keep; goto *D_80170808[(u32)((temp_v0_3) - 1)];
jt_c8:
jt_c9:
    if ((func_80171FCC(arg0, arg1, arg2, arg3) << 0x10) != 0) {
        goto block_55;
    }
    func_80172190(arg0, arg1, arg2, arg3);
    goto block_55;
jt_c5:
jt_c6:
jt_c7:
    temp_calc = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), D_80082E80.x, D_80082E80.y, &sp18);
    temp_env = D_800814A8;
    M2C_FIELD(arg3, s16 *, 0x2A) = temp_calc;
    if (M2C_FIELD(temp_env, u8 *, 0x9A) == 0x11) {
        var_v0 = &D_801711A4;
        goto block_44;
    }
jt_c12:
block_41:
    func_800A9A0C(arg3);
    goto block_55;
jt_c1:
jt_c2:
jt_c3:
    var_v0 = &D_801711A4;
block_44:
    func_800AAF00(arg0, arg1, arg2, &D_801741AC, var_v0);
    goto block_55;
jt_c4:
jt_c10:
jt_c11:
block_46:
block_47:
    func_80171884(arg0, arg1, arg2, arg3);
    goto block_55;
block_49:
    temp_a1 = M2C_FIELD(arg3, s32 *, 0x1C);
    if (temp_a1 & 0x2000) {
        goto block_55;
    }
    if (temp_v0 < 0) {
        goto block_52;
    }
    if (D_800E2970[temp_v0].flags & 2) {
        goto block_55;
    }
block_52:
    if (temp_a1 & 0x430) {
        goto block_55;
    }
    dungeon_env = &D_80082E80;
    if ((func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), dungeon_env->x, dungeon_env->y) << 0x10) == 0) {
        goto block_55;
    }
    sp18p = &sp18;
    ASM_SCHED_BARRIER();
    temp_calc = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), dungeon_env->x, dungeon_env->y, sp18p, ({ ASM_SCHED_BARRIER(); empty_arg; }));
    M2C_FIELD(arg3, s16 *, 0x2A) = temp_calc;
block_55:
    return;
}
