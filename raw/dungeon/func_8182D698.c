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
 * which can be enabled by passing `--valid-syntax` on the m2c command line.
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

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80045340[];
extern s32 D_800814A0[];
extern void func_80025010(void) __attribute__((noreturn));
s32 func_800478B8();
s32 func_80069EF8();

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

typedef struct {
    void *child;
    u8 pad[0x44];
    u16 count;
    u16 pad4a;
    s16 kind;
} Object;

typedef struct {
    u8 pad[0x0C];
    u8 limit;
    u8 value_d;
    u8 value_e;
    u8 pad_f[5];
    u16 flags;
} Effect;

void func_8182D698(Object *arg0, Motion *arg1, Effect *arg2) {
    s16 state;

    ((s32 *)arg0->child)[3] |= 0x8000;
    {
        register s32 y ASM_REG("$3");
        register s32 dy ASM_REG("$5");

        {
            register s32 x ASM_REG("$2");
            register s32 dx0 ASM_REG("$4");

            x = arg1->x;
            dx0 = arg1->dx;
            y = arg1->y;
            dy = arg1->dy;
            ASM_KEEP4(x, dx0, y, dy);
            x += dx0;
            arg1->x = x;
        }
        {
            register s32 z ASM_REG("$2");
            register s32 dz ASM_REG("$4");
            register s32 dx ASM_REG("$3");
            volatile s32 *dx_addr = &arg1->dx;
            s32 dx_step;
            s32 random;
            s32 scaled;
            s32 tail;

            z = arg1->z;
            dz = arg1->dz;
            ASM_KEEP4(z, dz, y, dy);
            y += dy;
            arg1->y = y;
            ASM_SCHED_BARRIER();
            dx = *dx_addr;
            ASM_KEEP(dx);
            z += dz;
            dx_step = dx >> 3;
            arg1->z = z;
            ASM_SCHED_BARRIER();
            {
                register s32 dy_copy ASM_REG("$2");

                dy_copy = dy;
                ASM_KEEP(dy_copy);
                arg1->dx = dx - dx_step;
                arg1->dy = dy_copy - (dy_copy >> 3);
            }
            random = func_80069EF8(dx_step, dy);
            scaled = random * 4;
            tail = arg1->dz;
            tail -= 0x4000;
            ASM_KEEP(tail);
            arg1->dz = tail - scaled;
        }
    }

    state = arg0->kind;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    func_80025010();

state_zero: {
        u16 count = arg0->count - 1;
        arg0->count = count;
        if ((count << 0x10) <= 0) {
            func_8004491C((u8 *)arg0 - 0x20, D_80045340);
            arg0->kind++;
            func_80025010();
        }
    }
    return;

state_one:
        func_800478B8(arg2);
        if (arg2->flags & 0x6000) {
            arg2->pad[4] = 0;
            arg2->pad[5] = 0;
        }
        {
            s32 amount = (func_80069EF8() & 0xF) + 4;
            if (amount >= arg2->limit) {
                *(s32 *)((u8 *)arg2 + 0xC) = 0;
                *((u16 *)((u8 *)arg0 - 2)) |= 0x8000;
                D_800814A0[0] |= 0x8000;
                func_80025010();
            } else {
                u8 value = arg2->value_e - amount;
                arg2->value_e = value;
                arg2->value_d = value;
                arg2->limit = value;
            }
        }
}
