/* cfail-repair: tf7-phase1-cache-v3 */
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
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
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

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern u16 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);
extern u8 D_80083160[];

#ifdef __mips__
static const u32 func_81970800_prefix[] __asm__("func_81970800")
    __attribute__((section(".text.func_81970800"))) = {
    0x8002512C,
    0x00000000,
    0x80024D5C,
    0x80024D64,
    0x80024D6C,
    0x80024D74,
    0x80024D7C,
    0x80024D7C,
    0x80024D74,
    0x80024D6C,
    0x80024D64,
    0x80024D5C,
    0x80024D5C,
    0x80024D64,
    0x80024D6C,
    0x80024D74,
    0x80024D7C,
    0x80024D7C,
    0x80024D74,
    0x80024D6C,
    0x80024D64,
    0x80024D5C,
    0x80025190,
    0x800251EC,
    0x80025258,
    0x80025E74,
    0x80025F44,
};
__asm__(".globl func_81970800\n"
        ".type func_81970800,@function\n"
        ".size func_81970800,1348");
#define BODY_NAME func_8197086C
#else
#define BODY_NAME func_81970800
#endif

#define FIELD(base, type, off) M2C_FIELD(base, type *, off)
#define SVAL(type, off) (*(type *)(scratch + (off)))

void BODY_NAME(void *arg0, void *arg1, void *arg2, s16 arg3)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    u8 *texture;
    s32 index;
    u16 flags;
    u8 texFlags;
    u8 **global = (u8 **)D_80083160;
    MATRIX matrix;

    FIELD(scratch, u8 *, 0x24) = *(u8 **)D_80083160 + 0xB0;
    FIELD(scratch, s32, 0x88) = FIELD(arg1, s16, 2);
    FIELD(scratch, s32, 0x8C) = FIELD(arg1, s16, 6);
    FIELD(scratch, s32, 0x90) = FIELD(arg1, s16, 0xA);
    FIELD(arg2, u16, 0x14) |= 0x8000;

    func_800649A0();

    FIELD(scratch, s32, 0x3C) = 0x2000;
    FIELD(scratch, s32, 0x38) = 0x2000;
    FIELD(scratch, s32, 0x34) = 0x2000;
    FIELD(scratch, u16, 0xA4) = FIELD(arg2, u16, 0x16);
    FIELD(scratch, u16, 0xA8) = FIELD(arg2, u16, 0x1A);
    FIELD(scratch, u16, 0xA6) = FIELD(arg2, u16, 0x18);
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&matrix);
    func_80064840(&matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    texture = FIELD(arg2, u8 *, 8);
    FIELD(scratch, u16, 0x28) = FIELD(arg2, u16, 0x14);

    packet = FIELD(*(u8 **)D_80083160, u8 *, 0x8D0);
    FIELD(*(u8 **)D_80083160, u8 *, 0x8D0) = packet + 0xC;
    func_80067F20(packet, 0, 0, func_80066460(0, 0, 0, 0) & 0xFFFF, 0);
    FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & 0xFF000000) |
        (FIELD(*(u8 **)D_80083160, u32, 0xB0) & 0x00FFFFFF);
    FIELD(*(u8 **)D_80083160, u32, 0xB0) =
        (FIELD(*(u8 **)D_80083160, u32, 0xB0) & 0xFF000000) |
        ((u32)packet & 0x00FFFFFF);

    {
        u8 *context;

        context = *(u8 * volatile *)D_80083160;
        packet = FIELD(context, u8 *, 0x8D0);
        FIELD(context, u8 *, 0x8D0) = packet + 0x24;
    }

    FIELD(scratch, u16, 0xB0) = FIELD(arg0, u16, 0x4C);
    FIELD(scratch, u16, 0xB8) = FIELD(arg0, u16, 0x52);
    FIELD(scratch, u16, 0xC0) = FIELD(arg0, u16, 0x58);
    FIELD(scratch, u16, 0xC8) = FIELD(arg0, u16, 0x5E);
    FIELD(scratch, u16, 0xB2) = FIELD(arg0, u16, 0x4E);
    FIELD(scratch, u16, 0xBA) = FIELD(arg0, u16, 0x54);
    FIELD(scratch, u16, 0xC2) = FIELD(arg0, u16, 0x5A);
    FIELD(scratch, u16, 0xCA) = FIELD(arg0, u16, 0x60);
    FIELD(scratch, u16, 0xB4) = FIELD(arg0, u16, 0x50);
    FIELD(scratch, u16, 0xBC) = FIELD(arg0, u16, 0x56);
    FIELD(scratch, u16, 0xC4) = FIELD(arg0, u16, 0x5C);
    FIELD(scratch, u16, 0xCC) = FIELD(arg0, u16, 0x62);

    index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                          scratch + 0xC0, scratch + 0xC8,
                          packet + 8, packet + 0x10,
                          packet + 0x18, packet + 0x20,
                          scratch + 0xD0, scratch + 0xD4) - arg3 - 6;
    FIELD(scratch, s32, 0x100) = index;

    if ((u32)index < 0x1E0) {
        if ((((u16)(FIELD(packet, u16, 8) + 0x20) < 0x181) &&
             ((u16)(FIELD(packet, u16, 0xA) + 0x20) < 0x121)) |
            (((u16)(FIELD(packet, u16, 0x10) + 0x20) < 0x181) &&
             ((u16)(FIELD(packet, u16, 0x12) + 0x20) < 0x121)) |
            (((u16)(FIELD(packet, u16, 0x18) + 0x20) < 0x181) &&
             ((u16)(FIELD(packet, u16, 0x1A) + 0x20) < 0x121)) |
            (((u16)(FIELD(packet, u16, 0x20) + 0x20) < 0x181) &&
             ((u16)(FIELD(packet, u16, 0x22) + 0x20) < 0x121))) {
            FIELD(arg2, u16, 0x14) &= 0x7FFF;
            texFlags = texture[1];
            FIELD(arg2, u8, 0xF) = texFlags;
            flags = FIELD(scratch, u16, 0x28);
            if (flags & 8) {
                FIELD(arg2, u8, 0xF) = (flags & 4) ?
                    (texFlags | 2) : (texFlags & 0xFD);
            }

            FIELD(packet, u32, 4) = FIELD(arg0, u32, 0xC);
            FIELD(packet, u32, 0xC) = FIELD(arg0, u32, 0x10);
            FIELD(packet, u32, 0x14) = FIELD(arg0, u32, 0x14);
            FIELD(packet, u32, 0x1C) = FIELD(arg0, u32, 0x18);
            FIELD(packet, u8, 3) = 8;
            FIELD(packet, u8, 7) = 0x3A;

            FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & 0xFF000000) |
                (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                       FIELD(scratch, s32, 0x100) * 4) & 0x00FFFFFF);
            FIELD(FIELD(scratch, u32 *, 0x24), u32,
                  FIELD(scratch, s32, 0x100) * 4) =
                (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                       FIELD(scratch, s32, 0x100) * 4) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);

            packet = FIELD(*global, u8 *, 0x8D0);
            FIELD(*global, u8 *, 0x8D0) = packet + 0xC;
            func_80067F20(packet, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
            FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & 0xFF000000) |
                (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                       FIELD(scratch, s32, 0x100) * 4) & 0x00FFFFFF);
            FIELD(FIELD(scratch, u32 *, 0x24), u32,
                  FIELD(scratch, s32, 0x100) * 4) =
                (FIELD(FIELD(scratch, u32 *, 0x24), u32,
                       FIELD(scratch, s32, 0x100) * 4) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    func_80064A40();
}
