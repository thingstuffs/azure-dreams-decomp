#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
/* m2c compatibility helpers used by the validated warm seed. */
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

s32 func_8003DE58(s32, void *, s16 *, s16);
void *func_8003FD64(s32, void *);
void func_8004491C(void *, void *);
void func_80047784(void *, u8, s32);
void func_8009C12C(void *, void *, s16, s32);
void func_800A2B04(void *, u8, u8);
void func_800A4ACC(void *);
void func_800A56E0(s32);
void func_800AD594(void *, s32);
s32 func_800BCB04(s32, s32, s16);
void func_80172990(void) __attribute__((noreturn));
void func_80172994(void) __attribute__((noreturn));
void func_80172ACC(void) __attribute__((noreturn));
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80083498[];
extern void *D_800E3DE8;
extern u8 D_80170E70;
extern u8 D_80173F38[];
extern u8 D_80173FDC[];
extern u8 D_80175A4C[];
extern u8 D_80175A8C[];

void func_80172654(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 pos[3];
    s32 temp_s5;
    s32 temp_s6;
    s32 offset;
    s32 state;
    s32 count;
    s32 next_state;
    s32 shifted_count;
    register void *call_a0 ASM_REG("$4");
    void *obj;
    u8 *tail;

    state = M2C_FIELD(arg0, u8 *, 0x9B);
    offset = (M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
    temp_s5 = *(s16 *)((u8 *)&D_8006CCD8 + offset);
    temp_s6 = *(s16 *)((u8 *)&D_8006CCE8 + offset);
    count = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = count;

    if (state == 2) goto state_2;
    if (state < 3) {
        if (state == 0) goto state_0;
        if (state == 1) {
            shifted_count = count << 16;
            goto state_1;
        }
        func_80172ACC();
    }
    if (state == 4) goto state_4;
    if (state < 4) goto state_3;
    if (state == 0xFF) goto state_255;
    func_80172ACC();

state_0:
    call_a0 = arg3;
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        M2C_FIELD(arg0, u8 *, 0x9B) = 0xFF;
        M2C_FIELD(arg2, u16 *, 0x14) |= 0x6000;
        func_8009C12C(call_a0, arg2, M2C_FIELD(call_a0, s16 *, 0x2A), 1);
        func_80172ACC();
    }
    M2C_FIELD(arg1, s32 *, 0xC) = (-temp_s5) << 17;
    M2C_FIELD(arg1, s32 *, 0x10) = (-temp_s6) << 17;
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg2, void **, 0x2C) = D_80175A4C;
    func_80047784(arg2,
        D_80175A4C[((D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7],
        0);
    (void)M2C_FIELD(arg0, volatile u8 *, 0x9B);
    count = 8;
    M2C_FIELD(arg0, u16 *, 0x96) = count;
    func_80172994();

state_1:
    if (shifted_count > 0) goto done;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    M2C_FIELD(arg2, void **, 0x2C) = D_80175A8C;
    func_80047784(arg2,
        D_80175A8C[((D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7],
        0);
    func_80172990();

state_2:
    if (((M2C_FIELD(arg2, s8 *, 4) == 4) &&
         (M2C_FIELD(arg2, u16 *, 0x14) & 0x1000)) ||
        (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        M2C_FIELD(arg2, u16 *, 0x14) |= 0x800;
        M2C_FIELD(arg0, u16 *, 0x96) = 0x10;
        if (func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, pos, 0) == 0) {
            pos[2] = 0;
            pos[1] = 0;
            pos[0] = 0;
        }
        obj = func_8003FD64(0x12, D_80083498);
        if (obj != NULL) {
            func_8004491C(obj, D_80173FDC);
            M2C_FIELD(obj, void **, 0x10) = D_80173F38;
            M2C_FIELD(obj, u16 *, 0x20) = M2C_FIELD(arg1, u16 *, 2) + pos[0];
            tail = (u8 *)obj + 0x20;
            M2C_FIELD(tail, u16 *, 2) = M2C_FIELD(arg1, u16 *, 6) + pos[1];
            M2C_FIELD(tail, u16 *, 4) = M2C_FIELD(arg1, u16 *, 0xA) + pos[2];
            M2C_FIELD(tail, s32 *, 8) = 0xC0C0C0;
            M2C_FIELD(tail, u16 *, 0xE) = 8;
            M2C_FIELD(tail, u16 *, 0x12) =
                func_800BCB04(((M2C_FIELD(arg2, u8 *, 0x24) + temp_s5) << 6) & 0xFFC0,
                              ((M2C_FIELD(arg2, u8 *, 0x25) + temp_s6) << 6) & 0xFFC0,
                              (s16)(M2C_FIELD(arg1, u16 *, 0xA) - 0x80)) -
                M2C_FIELD(arg1, u16 *, 0xA);
            M2C_FIELD(tail, u16 *, 0x10) = M2C_FIELD(arg3, u16 *, 0x2A);
            func_80172990();
        }
        goto increment_state;
    }
    goto done;

state_3:
    if ((s16)count == 0xA) {
        func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
        func_800A56E0(0x813);
    }
    if (M2C_FIELD(arg0, s16 *, 0x96) > 0) goto done;
    M2C_FIELD(arg0, u16 *, 0x96) = 8;
    M2C_FIELD(arg2, u16 *, 0x14) &= 0xF7FF;
    goto increment_state;

increment_state:
    next_state = M2C_FIELD(arg0, volatile u8 *, 0x9B);
    next_state += 1;
    M2C_FIELD(arg0, u8 *, 0x9B) = next_state;
    func_80172ACC();

state_4:
    if ((count << 16) > 0) goto done;
    M2C_FIELD(arg2, void **, 0x2C) = D_80175A4C;
    func_80047784(arg2,
        D_80175A4C[((D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7],
        0);
    M2C_FIELD(arg0, u16 *, 0x96) = state;
    M2C_FIELD(arg0, u8 *, 0x9B) = 0xFF;
    func_80172ACC();

state_255:
    M2C_FIELD(arg1, s32 *, 0xC) =
        (s32)((((M2C_FIELD(arg2, u8 *, 0x24) << 6) + 0x20) << 16) -
              M2C_FIELD(arg1, s32 *, 0)) >> 1;
    M2C_FIELD(arg1, s32 *, 0x10) =
        (s32)((((M2C_FIELD(arg2, u8 *, 0x25) << 6) + 0x20) << 16) -
              M2C_FIELD(arg1, s32 *, 4)) >> 1;
    if ((M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) ||
        (M2C_FIELD(arg0, s16 *, 0x96) <= 0)) {
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24),
                     M2C_FIELD(arg2, u8 *, 0x25));
        func_800AD594(arg3, 0x100);
        M2C_FIELD(arg0, void **, 0x8C) = &D_80170E70;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        if (M2C_FIELD(arg3, s8 *, 0x6D) == 0) {
            M2C_FIELD(arg3, u16 *, 0x46) &= 0x7FFF;
            func_80172ACC();
        }
        D_800E3DE8 = (u8 *)arg3 - 0x20;
    }

done:
    return;
}
