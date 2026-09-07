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

extern u16 D_80083462[5];
typedef struct {
    u8 pad_00[0xC];
    u16 flags;
    u8 pad_0E[6];
} DungeonTableEntry;

extern DungeonTableEntry D_800E2970[];
extern s16 D_8006CD00[];
extern u16 D_80082E80[];
extern u16 D_80083460[];
extern int D_800814A8[4];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
M2C_UNK func_800A0E6C();
M2C_UNK func_800A19E4();
M2C_UNK func_800A9A0C();
s32 func_8009A180();
s16 func_800BCB04();
s32 func_800CA1E0();
M2C_UNK func_800CA598();

void func_800CA444(void *input0, s32 arg1, void *input2, void *input3) {
    register void *arg0 ASM_REG("$21");
    register void *arg2 ASM_REG("$19");
    register void *arg3 ASM_REG("$18");
    register s16 temp_s0 ASM_REG("$16");
    s16 temp_v0;
    register s32 temp_v1 ASM_REG("$3");
    s32 table_value;
    register s32 state_idx ASM_REG("$2");
    register s16 next_s1 ASM_REG("$2");
    register s16 var_s1 ASM_REG("$17");
    M2C_UNK temp_a0_2;
    s8 temp_a0;
    s16 *temp_s4;
    u16 *temp_s6;
    register void *tail_arg ASM_REG("$4");
    register unsigned long first_dir ASM_REG("$3");
    register u32 hit_counter ASM_REG("$2");
    s32 remaining;

    arg0 = input0;
    arg2 = input2;
    arg3 = input3;

    if (*D_80083462 & 0x4000) {
        func_800A9A0C(arg3);
        goto done;
    }
    if (!(*D_80083462 & 0x2000)) {
        goto done;
    }
    func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
    temp_a0 = M2C_FIELD(arg2, s8 *, 0x26);
    if (temp_a0 < 0) {
        goto scan_start;
    }
    tail_arg = arg2;
    if (!(D_800E2970[temp_a0].flags & 2)) {
        goto scan_start;
    }
    ASM_KEEP(tail_arg);
    func_800CA598(tail_arg);
    goto done;

write_hit:
    M2C_FIELD(arg3, s16 *, 0x2A) = temp_s0;
    M2C_FIELD((arg3 + (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F)), u8 *, 0x74) = (u8) M2C_FIELD(arg2, u8 *, 0x24);
    M2C_FIELD((arg3 + (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F)), u8 *, 0x7C) = (u8) M2C_FIELD(arg2, u8 *, 0x25);
    ASM_SCHED_BARRIER();
    first_dir = (unsigned long) D_8006CCD8;
    ASM_KEEP_NV(first_dir);
    hit_counter = M2C_FIELD(arg3, u8 *, 0x71);
    ASM_KEEP(hit_counter);
    temp_a0_2 = ((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE;
    hit_counter++;
    first_dir = temp_a0_2 + first_dir;
    ASM_KEEP(first_dir);
    M2C_FIELD(arg3, u8 *, 0x71) = (u8) hit_counter;
    M2C_FIELD(arg2, u8 *, 0x24) = (u8) (M2C_FIELD(arg2, u8 *, 0x24) + *(u8 *) first_dir);
    M2C_FIELD(arg2, u8 *, 0x25) = (u8) (M2C_FIELD(arg2, u8 *, 0x25) + D_8006CCE8[temp_a0_2]);
    goto state_done;

scan_start:
    if (M2C_FIELD(arg3, u16 *, 0x46) & 0x8000) {
        var_s1 = 0;
    } else {
        func_800A0E6C(arg2, M2C_FIELD(arg0, s8 *, 0x9C), arg3, arg0 + 0x98);
        var_s1 = 0;
    }
    temp_s4 = D_8006CD00;
    temp_s6 = D_80082E80;
scan_loop:
    temp_v1 = M2C_FIELD(arg3, s16 *, 0x2A);
    if (M2C_FIELD(arg0, u16 *, 0x98) & 2) {
        table_value = M2C_FIELD(((s32) (var_s1 << 0x10) >> 0xF) + (u32) temp_s4, s16 *, 0);
        temp_s0 = temp_v1 - table_value;
        goto calc_call;
    }
    table_value = M2C_FIELD(((s32) (var_s1 << 0x10) >> 0xF) + (u32) temp_s4, s16 *, 0);
    temp_s0 = temp_v1 + table_value;
    goto calc_call;
calc_call:
    if ((func_800CA1E0(temp_s0, arg2, arg3, 0x20) << 0x10) > 0) {
        goto write_hit;
    }
    if (var_s1 != 0) {
        next_s1 = var_s1 + 1;
        goto scan_increment;
    }
    if (temp_s6[0x12] == M2C_FIELD(arg2, u16 *, 0x24)) {
        next_s1 = var_s1 + 1;
        goto scan_increment;
    }
    ASM_SCHED_BARRIER();
    if ((func_8009A180(arg3, M2C_FIELD(*D_800814A8, s32 *, 0x58) + 0x20) << 0x10) != 0) {
        goto done;
    }
    next_s1 = var_s1 + 1;
scan_increment:
    var_s1 = next_s1;
    if (next_s1 < 8) {
        goto scan_loop;
    }
    goto state_done;

state_done:
    state_idx = ((s32) (var_s1 << 0x10)) >> 0x10;
    if (state_idx < 8) {
        goto state_long;
    }
    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
    func_800A9A0C(arg3);
    goto done;

state_long:
    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
    M2C_FIELD(arg0, s8 *, 0x9C) = (s8) (u8) M2C_FIELD(arg2, s8 *, 0x26);
    M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
    D_80083460[4] = (u16) (D_80083460[4] + 1);
    remaining = M2C_FIELD(arg3, s8 *, 0x6D);
    ASM_KEEP(remaining);
    if (remaining == 0) {
        ASM_SCHED_BARRIER();
        M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
        goto done;
    }
    var_s1 = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
    temp_v0 = (s16) (((s32) var_s1 << 0x10) >> 0x10);
    if (temp_v0 < 0x200) {
        M2C_FIELD(arg3, u16 *, 0x88) = (u16) var_s1;
    }

done:
    return;
}
