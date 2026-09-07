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
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
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
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern void *D_800F6000[];
M2C_UNK func_8003E4FC();
s32 func_8003F270();
void func_8003F540();
int func_800445E0();
s32 func_80053EF0();
M2C_UNK func_800A56E0();
M2C_UNK func_800F62E8() __attribute__((noreturn));
M2C_UNK func_800F635C() __attribute__((noreturn));
extern M2C_UNK D_80010000;
extern u16 D_8001371A;
extern s32 D_8006CD58;
extern u8 D_80082EA5;
extern M2C_UNK D_80083160;
extern s16 D_8008346A;

void func_807AE960(void *arg0, void *arg1, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19 };
    s16 temp_a0;
    s32 dispatch_index;
    s16 temp_v1_2;
    register s32 countdown ASM_REG("$2");
    register u16 countdown_u ASM_REG("$3");
    register s32 actor_pos ASM_REG("$3");
    register u8 *state ASM_REG("$17") = arg0;
    register u8 *actor ASM_REG("$20") = arg1;
    register u8 *target ASM_REG("$19") = arg2;
    register u8 *global ASM_REG("$16");
    register s32 temp_s2 ASM_REG("$18");
    register s32 temp_s5 ASM_REG("$21");
    register u8 *global_end ASM_REG("$22");
    register u8 *dungeon_data ASM_REG("$2");
    void *temp_v0_2;

    dungeon_data = (u8 *)&D_80083160;
    ASM_KEEP4_NV(state, actor, target, dungeon_data);
    global_end = dungeon_data + 0x1DC;
    temp_s5 = M2C_FIELD(dungeon_data, s32 *, 0x1DC);
    dispatch_index = (s16)(M2C_FIELD(state, u16 *, 0) - 1);
    if ((u32) dispatch_index >= 0x14U) {
        goto block_28;
    }
    (void)jt_keep; goto *D_800F6000[(u32)dispatch_index];
jt_c0:
jt_c1:
    if (func_8003F270(dispatch_index) != 0) {
        goto block_37;
    }
    if (M2C_FIELD(state, s16 *, 0x10) != 0) {
        goto block_5;
    }
    func_800A56E0(0x300);
block_5:
    M2C_FIELD(state, s16 *, 0) = 3;
    func_800F635C();
    return;
jt_c16:
    M2C_FIELD(state, s16 *, 0xA) = 0x400;
    func_800F62E8();
    return;
jt_c2:
    temp_a0 = M2C_FIELD(state, s16 *, 4);
    if (temp_a0 <= 0) {
        goto block_11;
    }
    M2C_FIELD(target, s16 *, 0x1A) = (s16) ((u16) M2C_FIELD(target, s16 *, 0x1A) + ((s32) (M2C_FIELD(state, s16 *, 0xA) - M2C_FIELD(target, s16 *, 0x1A)) / temp_a0));
block_11:
    temp_v1_2 = (u16) M2C_FIELD(state, s16 *, 4) - 1;
    M2C_FIELD(state, volatile s16 *, 4) = temp_v1_2;
    ASM_SCHED_BARRIER();
    global = (u8 *)0x80010000;
    if ((u16) D_8001371A >= 4U) {
        goto block_15;
    }
    if (temp_v1_2 >= 0) {
        goto block_28;
    }
block_13:
    M2C_FIELD(state, s16 *, 4) = 0;
    func_800F635C();
    return;
block_15:
    if (M2C_FIELD(global, volatile s32 *, 0x2090) != 1) {
        goto block_17;
    }
    D_8008346A = 1;
block_17:
    if (M2C_FIELD(state, s16 *, 4) > 0) {
        goto block_28;
    }
    temp_s2 = M2C_FIELD(global, volatile s32 *, 0x2090);
    if (temp_s2 != 1) {
        goto block_22;
    }
    if (func_80053EF0(4) != 0) {
        goto block_13;
    }
    if (M2C_FIELD(global, volatile s32 *, 0x2090) != temp_s2) {
        goto block_22;
    }
    D_8008346A = 0;
block_22:
    M2C_FIELD(target, s16 *, 0x1A) = (s16) (u16) M2C_FIELD(state, s16 *, 0xA);
    M2C_FIELD(state, s16 *, 0) = 0;
    func_800F635C();
    return;
jt_c3:
    if (M2C_FIELD(state, s16 *, 0x10) != 0) {
        goto block_26;
    }
    func_8003F540(0, D_8006CD58, 0x0600065E, 0x030008B6);
    func_8003E4FC(0x15, func_800445E0(), 0);
block_26:
    M2C_FIELD(state, s16 *, 4) = 0x60;
    M2C_FIELD(state, s16 *, 0xC) = 0x60;
jt_c19:
    M2C_FIELD(state, u16 *, 0) = 2U;
    M2C_FIELD(state, s16 *, 0xA) = (s16) M2C_FIELD(state, u16 *, 2);
jt_c4:
jt_c5:
jt_c6:
jt_c7:
jt_c8:
jt_c9:
jt_c10:
jt_c11:
jt_c12:
jt_c13:
jt_c14:
jt_c15:
jt_c17:
jt_c18:
block_28:
    countdown = M2C_FIELD(state, s16 *, 0xC);
    countdown_u = M2C_FIELD(state, volatile u16 *, 0xC);
    if (countdown == 0) {
        goto block_33;
    }
    countdown = countdown_u - 1;
    M2C_FIELD(state, s16 *, 0xC) = countdown;
    actor_pos = M2C_FIELD(actor, s16 *, 0xA);
    if (countdown & 1) {
        countdown = actor_pos + 1;
    } else {
        countdown = actor_pos - 1;
    }
block_31:
    M2C_FIELD(actor, s16 *, 0xA) = countdown;
    if (M2C_FIELD(state, s16 *, 0xC) != 0) {
        goto block_33;
    }
    M2C_FIELD(actor, s16 *, 0xA) = (s16) M2C_FIELD(state, u16 *, 0xE);
block_33:
    if (M2C_FIELD(state, s16 *, 0) != 0) {
        goto block_37;
    }
    if ((u8) D_80082EA5 >= 0x3DU) {
        goto block_37;
    }
    if (M2C_FIELD(state, s16 *, 0xA) == (s16) M2C_FIELD(state, u16 *, 2)) {
        goto block_37;
    }
    M2C_FIELD(state, u16 *, 0) = 4U;
    temp_v0_2 = ((0x3E << M2C_FIELD(global_end, s16 *, 0x14)) * 6) + temp_s5 + 0xBA;
    M2C_FIELD(temp_v0_2, u16 *, 4) = (u16) (M2C_FIELD(temp_v0_2, u16 *, 4) | 0x8000);
block_37:
    return;
}
