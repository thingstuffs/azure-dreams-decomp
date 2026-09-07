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

M2C_UNK func_80047784();
s32 func_800644B8();
s16 func_800A0818();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A9A04();
s32 func_800AD9B4();
void func_801706C0(void) __attribute__((noreturn));
void func_8017078C() __attribute__((noreturn));
typedef struct {
    u8 pad[0x24];
    u8 x;
    u8 y;
} Global82E80;
typedef struct {
    u8 pad[8];
    s16 count;
} Global83460;
extern Global82E80 D_80082E80;
extern s16 D_80083228[5];
extern Global83460 D_80083460;
extern u8 D_8016F78C[];
extern u8 D_80174A2C[];

void func_801704A0(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK sp18;
    s32 temp_a0;
    s32 temp_count;
    s32 temp_div;
    s32 temp_flag46;
    s32 temp_pos;
    s32 temp_v1_3;
    u16 temp_v0;
    s32 temp_v1;
    Global82E80 *temp_82E80;
    Global83460 *temp_83460;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 == 1) {
        goto block_10;
    }
    if (temp_v1 >= 2) {
        goto block_ge2;
    }
    if (temp_v1 == 0) {
        goto block_zero;
    }
    func_801706C0();
block_ge2:
    if (temp_v1 == 2) {
        goto block_14;
    }
    if (temp_v1 == 3) {
        goto block_three;
    }
    func_801706C0();
block_zero:
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF);
    M2C_FIELD(arg0, s16 *, 0x9E) = 5;
    M2C_FIELD(arg0, s32 *, 0xA4) = 0;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
block_10:
    temp_a0 = M2C_FIELD(arg0, s16 *, 0x9E);
    M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) - M2C_FIELD(arg0, s32 *, 0xA4));
    if (temp_a0 != 0) {
        s32 temp_coord;
        temp_div = M2C_FIELD(arg2, u8 *, 0x24);
        
        temp_coord = M2C_FIELD(arg1, s16 *, 2);
        temp_div <<= 6;
        temp_coord -= 0x20;
        
        temp_div = (s32) ((temp_div - temp_coord) << 0x10) / temp_a0;
        temp_v1_3 = M2C_FIELD(arg1, s16 *, 6) - 0x20;
        M2C_FIELD(arg1, s32 *, 0xC) = temp_div;
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - temp_v1_3) << 0x10) / (s16) M2C_FIELD(arg0, s16 *, 0x9E));
        M2C_FIELD(arg0, s32 *, 0xA4) = (s32) ((0 - func_800644B8(M2C_FIELD(arg0, s16 *, 0x9E) * 0x199)) << 0xA);
    }
    temp_pos = M2C_FIELD(arg0, s32 *, 0x90);
    temp_pos += M2C_FIELD(arg0, s32 *, 0xA4);
    temp_count = M2C_FIELD(arg0, u16 *, 0x9E) - 1;
    
    
    M2C_FIELD(arg0, s16 *, 0x9E) = temp_count;
    M2C_FIELD(arg0, s32 *, 0x90) = temp_pos;
    if ((temp_count << 0x10) < 0) {
        M2C_FIELD(arg0, s32 *, 0x90) = 0;
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x08000000);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    }
block_14:
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x08000000)) {
        goto block_19;
    }
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    M2C_FIELD(arg0, u8 *, 0x9B) = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
    func_801706C0();
block_three:
    if (M2C_FIELD(arg2, u8 **, 0x2C) != D_80174A2C) {
        M2C_FIELD(arg2, u8 **, 0x2C) = D_80174A2C;
        func_80047784(arg2, D_80174A2C[((s32) (D_80083228[0] + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    }
block_19:
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        func_800A4ACC(arg3);
        temp_83460 = &D_80083460;
        if (temp_83460->count != 0) {
            temp_83460->count = (u16) temp_83460->count - 1;
        }
        temp_v1_3 = M2C_FIELD(arg3, s32 *, 0x1C);
        if (!(temp_v1_3 & 0x2000)) {
            goto block_no_2000;
        }
        temp_flag46 = M2C_FIELD(arg3, u16 *, 0x46);
        if (!(temp_flag46 & 0x8000)) {
            goto block_29;
        }
        M2C_FIELD(arg3, u16 *, 0x46) = temp_flag46 & 0x7FFF;
        func_8017078C(temp_83460);
block_no_2000:
        if (temp_v1_3 & 0x410) {
            goto block_29;
        }
        if (!(temp_v1_3 & 0x20000)) {
            goto block_29;
        }
        temp_82E80 = &D_80082E80;
        M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), temp_82E80->x, temp_82E80->y, &sp18);
block_29:
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            M2C_FIELD(arg0, u8 **, 0x8C) = D_8016F78C;
            func_800A9A04(arg3);
        }
    }
}
