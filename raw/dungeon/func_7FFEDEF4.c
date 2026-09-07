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
extern void *func_80033BE4(void);
extern void func_80033C1C(void *, s32);
extern void func_80033C84(void *);
extern void *func_8003FC64(s32);
extern void func_8003FFF0(void *);
extern void func_80040044(void *);
extern void func_8008B818(s32, void *, void *, void *);
extern s8 D_800CFC2C;
extern s8 D_800FC418;

s32 func_8008B654(s32 arg0, s32 arg1) {
    register s32 count;
    void *objects[11];
    void *resources[11];
    void **object_write;
    void **resource_write;
    void *allocated;
    void *resource;
    count = 0;
    object_write = objects;
    resource_write = resources;
    while (1) {
        allocated = func_8003FC64(0x11);
        if (allocated == 0) {
            break;
        }
        resource = func_80033BE4();
        if (resource == 0) {
            break;
        }
        func_80033C1C(resource, 0);
        *object_write++ = allocated;
        *resource_write++ = resource;
        count++;
        if (count >= 11) {
            break;
        }
    }

    if (count < 11) {
        if (object_write != objects) {
            do {
                --object_write;
                func_8003FFF0(*object_write);
                func_80040044(*object_write);
            } while (object_write != objects);
            ++object_write;
        }
        if (resource_write != resources) {
            do {
                --resource_write;
                func_80033C84(*resource_write);
            } while (resource_write != resources);
        }
        return 0;
    }

    object_write = objects;
    resource_write = resources;
    count = 0;
    {
        s8 *order = &D_800CFC2C;
        while (1) {
            s8 slot = *(s8 *)(count + (s32)order);
            void *other_data;
            if (slot == count) {
                other_data = 0;
            } else {
                other_data = (u8 *)objects[slot] + 0x20;
            }
            {
                struct object_data {
                    u8 pad[0x74];
                    s32 field_74;
                    s32 field_78;
                    s32 field_7c;
                } *data = (struct object_data *)((u8 *)*object_write + 0x20);
                data->field_74 = 0;
                data->field_78 = arg1;
                data->field_7c = arg0;
                func_8008B818(count++, other_data, *object_write++, *resource_write++);
            }
            if (count >= 11) {
                D_800FC418 = 0;
                return 1;
            }
        }
    }
}
