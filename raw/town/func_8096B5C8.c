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

M2C_UNK func_80067014();                     /* extern */
M2C_UNK func_800671A8(); /* extern */
s32 func_80123200();                             /* extern */
M2C_UNK func_80123928();               /* extern */
M2C_UNK func_801239B8(); /* extern */
extern M2C_UNK D_8011ACD8;
typedef struct {
    void *image;
    void **image_ref;
    u16 unused;
    u16 width;
} ImageEntry;
extern ImageEntry D_80126E98[];

void func_80123A60(void *arg0) {
    register void *object ASM_REG("$16") = arg0;
    s16 sp10[4];
    ImageEntry *var_s2;
    u8 *loop_image_base;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 var_s0;
    s32 var_s1;
    s32 temp_v0;
    s32 temp_v1;

    sp10[0] = 0x180;
    sp10[1] = 0x80;
    sp10[2] = 0x36;
    sp10[3] = 0x60;
    func_800671A8(sp10, 0, 0, 0);
    func_801239B8(&D_8011ACD8, 0x192, 0xD0);
    func_80067014(0);
    ASM_KEEP(object);
    temp_v1 = M2C_FIELD(object, u8 *, 0xF);
    var_s1 = 0;
    if (temp_v1 == 3) {
        ASM_KEEP(temp_v1);
        var_s1 = temp_v1;
        temp_s0 = var_s1 * 0x10;
        ASM_KEEP(temp_s0);
        if (func_80123200(temp_s0 & 0xF0) & 0xFF) {
            u8 *image_base = (u8 *)D_80126E98;
            register void **image_ptr ASM_REG("$2");
            ASM_KEEP(image_base);
            image_ptr = (void **)((((var_s1 << 5) + temp_s0) << 2) +
                                  (u32)image_base);
            ASM_KEEP(image_ptr);
            func_80123928(*image_ptr, 0x180, 0x80);
        }
        temp_s0_2 = temp_s0 + 1;
        if (func_80123200(temp_s0_2 & 0xFF) & 0xFF) {
            func_80123928(D_80126E98[temp_s0_2].image, 0x1A4, 0xA0);
        }
        goto done;
    }
    ASM_MEM_BARRIER();
    temp_v0 = M2C_FIELD(object, u8 *, 0xF);
    ASM_KEEP(temp_v0);
    loop_image_base = (u8 *)D_80126E98;
    ASM_KEEP(loop_image_base);
    var_s0 = temp_v0 * 0x10;
    var_s2 = (ImageEntry *)(((((temp_v0 << 5) + var_s0) << 2)) +
                            (u32)loop_image_base);
    do {
        if (func_80123200(var_s0 & 0xFF) & 0xFF) {
            func_80123928(var_s2->image, (s16) (((var_s1 % 3) * 0x12) + 0x180), (s16) (((var_s1 / 3) * 0x10) + 0x80));
        }
        var_s1 += 1;
        var_s2 += 1;
        var_s0 += 1;
    } while (var_s1 < 0x10);
done:
    func_80067014(0);
}
/* MECHANISM: A four-halfword array establishes the 0x28 frame and exact store schedule.
   Guarded s0 holds the argument; scoped s32 keeps preserve the category/shifted roles.
   Named ImageEntry bases and byte-scaled expressions reproduce both address chains.
   A memory fence plus reload keep yields lbu/lui/addiu with no load-delay nop. */
