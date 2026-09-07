#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
/*
 * This header contains macros emitted by m2c in "valid syntax" mode,
 * which can be enabled by passing `--valid-syntax` on the command line.
 *
 * In this mode, unhandled types and expressions are emitted as macros so
 * that the output is compilable without human intervention.
 */


/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)

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

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *const D_80170808[];
void func_80047784();         /* extern */
s32 func_8009A180();                     /* extern */
s8 func_8009FB34();                           /* extern */
s32 func_8009FD7C();                  /* extern */
s32 func_800A0818();       /* extern */
s32 func_800A1C58();                          /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
M2C_UNK func_800AA258(); /* extern */
s32 func_800AA6B4(); /* extern */
M2C_UNK func_800AA79C(); /* extern */
M2C_UNK func_800AA888(); /* extern */
s32 func_800AA924(); /* extern */
M2C_UNK func_800AAB10(); /* extern */
M2C_UNK func_800AAF00(); /* extern */
void func_80172CC0();                            /* extern */
M2C_UNK func_80172F58(); /* extern */
s32 func_80173734(); /* extern */
void func_80173B48(); /* extern */
s32 func_80173EAC(); /* extern */
void func_801759A0(); /* extern */
extern void *D_800814A8;
extern u8 D_80082E80[];
extern u16 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} D_800E2970_entry;
extern D_800E2970_entry D_800E2970[];
extern M2C_UNK D_801724BC;
extern M2C_UNK D_80175DF4;
extern M2C_UNK D_80175DFC;
extern M2C_UNK D_80175E04;
extern M2C_UNK D_80175E24;
extern M2C_UNK D_80175E2C;
extern M2C_UNK D_80175E34;
extern M2C_UNK D_80175E3C;
extern M2C_UNK D_80175E44;
extern M2C_UNK D_80175E4C;
extern M2C_UNK D_80175E54;
extern M2C_UNK D_80175E5C;
extern M2C_UNK D_80175E64;
extern M2C_UNK D_80175E84;
extern M2C_UNK D_80175E8C;
extern M2C_UNK D_80175E94;

void func_801724BC(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    M2C_UNK sp18;
    u8 *var_a1;
    u8 *var_a1_2;
    u8 *var_a3;
    u8 *var_a3_2;
    M2C_UNK *current_row;
    s32 temp_a1;
    s32 temp_v0_3;
    s32 temp_path;
    s32 default_state;
    void *temp_actor;
    s8 temp_v0;
    u16 *var_v0;
    u16 *var_v0_2;
    u16 temp_v0_2;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;

    if (!(D_80083462 & 0x1000)) {
        goto block_2;
    }
    M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
    func_80172CC0();
    return;
block_2:
    if (M2C_FIELD(arg3, u8 *, 0x25) != 0) {
        goto block_15;
    }
    func_800AA79C(arg0, arg1, arg2, arg3);
    temp_v1 = M2C_FIELD(arg3, u8 *, 0x48);
    if (temp_v1 == 0xE) {
        goto block_11;
    }
    if ((s32) temp_v1 >= 0xF) {
        goto block_7;
    }
    if (temp_v1 == 0xD) {
        goto block_9;
    }
    return;
block_7:
    if (temp_v1 == 0xF) {
        goto block_13;
    }
    return;
block_9:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_80175E54) {
        goto block_109;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80175E84;
    func_80047784(arg2, ((u8 *)&D_80175E84)[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    return;
block_11:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_80175E5C) {
        goto block_109;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80175E8C;
    func_80047784(arg2, ((u8 *)&D_80175E8C)[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    return;
block_13:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_80175E64) {
        goto block_109;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80175E94;
    func_80047784(arg2, ((u8 *)&D_80175E94)[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    return;
block_15:
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x200)) {
        goto block_32;
    }
    temp_a0 = M2C_FIELD(arg3, u8 *, 0x48);
    if (temp_a0 == 0xE) {
        goto block_25;
    }
    if ((s32) temp_a0 >= 0xF) {
        goto block_20;
    }
    if (temp_a0 == 0xD) {
        goto block_22;
    }
    var_v0 = (u16 *)0x80080000;
    goto block_33;
block_20:
    if (temp_a0 == 0xF) {
        goto block_27;
    }
    var_v0 = (u16 *)0x80080000;
    goto block_33;
block_22:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80175E54) {
        goto block_24;
    }
    M2C_FIELD(arg0, u8 *, 0x9A) = temp_a0;
    M2C_FIELD(arg0, s8 *, 0x9B) = 1;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xFFFBFFFF);
    return;
block_24:
    if (func_800AA924(arg0, arg1, arg2, &D_80175E84) != 0) {
        goto block_109;
    }
    goto block_32;
block_25:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_80175E5C) {
        goto block_28;
    }
    if (func_800AA924(arg0, arg1, arg2, &D_80175E8C) != 0) {
        goto block_109;
    }
    goto block_32;
block_27:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80175E64) {
        goto block_30;
    }
block_28:
    M2C_FIELD(arg0, u8 *, 0x9A) = 0xDU;
block_29:
    M2C_FIELD(arg0, s8 *, 0x9B) = 1;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xFFFBFFFF);
    return;
block_30:
    if (func_800AA924(arg0, arg1, arg2, &D_80175E94) != 0) {
        goto block_109;
    }
block_32:
    var_v0 = (u16 *)0x80080000;
block_33:
    if (var_v0[0x1A31] & 0x2000) {
        goto block_64;
    }
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x100)) {
        goto block_36;
    }
    func_800AA258(arg0, arg1, arg2, arg3);
    return;
block_36:
    if (M2C_FIELD(arg0, u8 *, 0x9A) == 0xE) {
        goto block_49;
    }
    temp_v1_2 = M2C_FIELD(arg3, u8 *, 0x48);
    switch (temp_v1_2) {
    case 0xD:
        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80175E24) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80175E24;
            func_80047784(arg2, ((u8 *)&D_80175E24)[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
        }
        break;
    case 0xE:
        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80175E2C) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80175E2C;
            func_80047784(arg2, ((u8 *)&D_80175E2C)[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
        }
        break;
    case 0xF:
        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80175E34) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80175E34;
            func_80047784(arg2, ((u8 *)&D_80175E34)[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
        }
        break;
    default:
        M2C_FIELD(arg0, u8 *, 0x9A) = 0xE;
        goto block_49;
    }
block_48:
    M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
block_49:
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF3);
    if (M2C_FIELD(arg3, s16 *, 0x64) == 0) {
        goto block_60;
    }
    temp_v1_3 = M2C_FIELD(arg3, u8 *, 0x48);
    if (temp_v1_3 == 0xE) {
        goto block_57;
    }
    if ((s32) temp_v1_3 >= 0xF) {
        goto block_54;
    }
    if (temp_v1_3 == 0xD) {
        goto block_56;
    }
    goto block_60;
block_54:
    if (temp_v1_3 == 0xF) {
        goto block_58;
    }
    goto block_60;
block_56:
    if (func_800AA6B4(arg0, arg1, arg2, &D_80175E3C) != 0) {
        goto block_109;
    }
    goto block_60;
block_57:
    if (func_800AA6B4(arg0, arg1, arg2, &D_80175E44) != 0) {
        goto block_109;
    }
    goto block_60;
block_58:
    if (func_800AA6B4(arg0, arg1, arg2, &D_80175E4C) != 0) {
        goto block_109;
    }
block_60:
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x80000)) {
        goto block_62;
    }
    func_800AA888(arg0, arg1, arg2, arg3);
    func_801759A0(arg0, arg1, arg2, arg3);
    return;
block_62:
    if ((func_800A1C58(arg3) << 0x10) == 0) {
        goto block_64;
    }
    func_800AAB10(arg0, arg1, arg2, arg3);
block_64:
    temp_v0 = func_8009FB34(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    M2C_FIELD(arg2, s8 *, 0x26) = temp_v0;
    if (M2C_FIELD(arg3, s8 *, 0x6D) <= 0) {
        goto block_89;
    }
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x20) {
        goto block_77;
    }
    if (M2C_FIELD(arg2, u16 *, 0x24) == D_80082EA4) {
        goto block_88;
    }
    if (M2C_FIELD(arg3, u16 *, 0x46) & 0x8000) {
        goto block_72;
    }
    if (!(D_80083462 & 0x2000)) {
        goto block_70;
    }
    if ((func_8009A180(arg3, M2C_FIELD(D_800814A8, s32 *, 0x58) + 0x20) << 0x10) != 0) {
        goto block_109;
    }
block_70:
    if ((func_80173EAC(arg0, arg1, arg2, 0) << 0x10) == 0) {
        goto block_109;
    }
    temp_v0_2 = M2C_FIELD(arg3, u16 *, 0x46) | 0x4000;
    M2C_FIELD(arg3, u16 *, 0x46) = temp_v0_2;
    if (!(temp_v0_2 & 0x8000)) {
        goto block_88;
    }
block_72:
    temp_v0_3 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
    if ((u32) (temp_v0_3 - 1) >= 0xCU) {
        goto block_87;
    }
    (void)jt_keep; goto *D_80170808[(u32)((temp_v0_3) - 1)];
jt_c8:
jt_c9:
    if ((func_80173734(arg0, arg1, arg2, arg3) << 0x10) != 0) {
        goto block_109;
    }
    func_80173B48(arg0, arg1, arg2, arg3);
    return;
jt_c5:
jt_c6:
jt_c7:
    {
        u8 *map = D_80082E80;
        temp_path = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), map[0x24], map[0x25], &sp18);
    }
    temp_actor = D_800814A8;
    M2C_FIELD(arg3, s16 *, 0x2A) = temp_path;
    if (M2C_FIELD(temp_actor, u8 *, 0x9A) == 0x11) {
        goto block_78;
    }
jt_c12:
block_77:
    func_800A9A0C(arg3);
    return;
jt_c1:
jt_c2:
jt_c3:
block_78:
    temp_a0_2 = M2C_FIELD(arg3, u8 *, 0x48);
    if (temp_a0_2 == 0xE) {
        goto block_85;
    }
    if ((s32) temp_a0_2 >= 0xF) {
        goto block_82;
    }
    if (temp_a0_2 == 0xD) {
        goto block_84;
    }
    return;
block_82:
    if (temp_a0_2 == 0xF) {
        goto block_86;
    }
    return;
block_84:
    func_800AAF00(arg0, arg1, arg2, &D_80175DF4, &D_801724BC);
    return;
block_85:
    func_800AAF00(arg0, arg1, arg2, &D_80175DFC, &D_801724BC);
    return;
block_86:
    func_800AAF00(arg0, arg1, arg2, &D_80175E04, &D_801724BC);
    return;
jt_c4:
jt_c10:
jt_c11:
block_87:
block_88:
    func_80172F58(arg0, arg1, arg2, arg3);
    return;
block_89:
    temp_a1 = M2C_FIELD(arg3, s32 *, 0x1C);
    if (temp_a1 & 0x2000) {
        if (D_80083462 & 0x2000) {
            goto block_109;
        }
        goto block_97;
    }
    if (temp_v0 < 0) {
        goto block_92;
    }
    if (D_800E2970[temp_v0].flags & 2) {
        if (D_80083462 & 0x2000) {
            goto block_109;
        }
        goto block_97;
    }
block_92:
    if (temp_a1 & 0x430) {
        if (D_80083462 & 0x2000) {
            goto block_109;
        }
        goto block_97;
    }
    {
        u8 *map = D_80082E80;
        if ((func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), map[0x24], map[0x25]) << 0x10) == 0) {
            goto block_95;
        }
        M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), map[0x24], map[0x25], &sp18);
    }
block_95:
    if (D_80083462 & 0x2000) {
        goto block_109;
    }
block_97:
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x40) {
        goto block_109;
    }
    temp_v1_4 = M2C_FIELD(arg3, u8 *, 0x48);
    if (temp_v1_4 == 0xE) {
        goto block_105;
    }
    if ((s32) temp_v1_4 >= 0xF) {
        goto block_102;
    }
    if (temp_v1_4 == 0xD) {
        goto block_104;
    }
    return;
block_102:
    if (temp_v1_4 == 0xF) {
        goto block_106;
    }
    return;
block_104:
    current_row = M2C_FIELD(arg2, M2C_UNK **, 0x2C);
    var_a1 = (u8 *)&D_80175E24;
    goto block_107;
block_105:
    current_row = M2C_FIELD(arg2, M2C_UNK **, 0x2C);
    var_a1 = (u8 *)&D_80175E2C;
    goto block_107;
block_106:
    current_row = M2C_FIELD(arg2, M2C_UNK **, 0x2C);
    var_a1 = (u8 *)&D_80175E34;
block_107:
    if (current_row == var_a1) {
        goto block_109;
    }
block_108:
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
    func_80047784(arg2, *(u8 *)((unsigned long)(((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + (unsigned long)var_a1), 0);
block_109:
    return;
}
