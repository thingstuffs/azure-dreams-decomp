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
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define BSWAP32(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

typedef struct {
    u8 pad0[0x0C];
    M2C_UNK * volatile field0c;
    u8 pad10[0x40];
    M2C_UNK (* volatile callback)(void *, s32, void *);
    u8 pad54[0x10];
    s16 field64;
    u8 pad66[0x0A];
    u8 state70;
    u8 flags71;
    s16 field72;
    s16 field74;
    u8 pad76[2];
    M2C_UNK **table78;
} TargetObj;

M2C_UNK func_800C2C80(TargetObj *, void *, s32, s32);
M2C_UNK func_800C2CB0();
s32 func_800C2E1C();
s32 func_800C2F14();
extern void func_800C326C(void) __attribute__((noreturn));
M2C_UNK func_800C3348();
extern M2C_UNK D_800D5028;
extern M2C_UNK D_800D5040;
extern M2C_UNK D_800D5058;

void func_800C321C(s32 arg0, s32 arg1, void *arg2) {
    s32 temp_v0;
    u8 temp_v1;
    register TargetObj *obj ASM_REG("$17") = (TargetObj *)arg0;
    void *motion = arg2;

    temp_v1 = obj->state70;
    if (temp_v1 == 0) {
        register void *ret ASM_REG("$2") = &D_800D5028;
        ASM_TAILSLOT_PIN_TIED(ret);
        func_800C326C();
    }
    if (temp_v1 == 1) {
        register u32 ret ASM_REG("$2") = 0x800d0000;
        ASM_KEEP_NV(ret);
        ret += 0x5040;
        ASM_TAILSLOT_PIN_TIED(ret);
        func_800C326C();
    }
    obj->field0c = &D_800D5058;
    ASM_KEEP_NV(obj);
    obj->callback(obj, arg1, arg2);
    if (!(*(u16 *)((u8 *)obj - 2) & 0x8000)) {
        temp_v0 = func_800C2E1C(obj->field72, obj->field64);
        if (obj->field74 != temp_v0) {
            func_800C2CB0(obj, arg2, obj->table78[temp_v0], *(s8 *)((u8 *)arg2 + 4));
            obj->field74 = temp_v0;
        }
        if (!(obj->flags71 & 1)) {
            if ((func_800C2F14(obj->field72, obj->field64) << 0x10) == 0) {
                register u32 tail_result ASM_REG("$2") = *(u16 *)((u8 *)motion + 0x14);
                tail_result &= 0xfffe;
                ASM_TAILSLOT_PIN_TIED(tail_result);
                func_800C3348();
                return;
            }
            goto block_16;
        }
        if ((func_800C2F14(obj->field72, obj->field64) << 0x10) != 0) {
            register u32 tail_result ASM_REG("$2") = *(u16 *)((u8 *)motion + 0x14);
            tail_result &= 0xfffe;
            ASM_TAILSLOT_PIN_TIED(tail_result);
            func_800C3348();
            return;
        }
block_16:
        *(u16 *)((u8 *)motion + 0x14) = (s16) (*(u16 *)((u8 *)motion + 0x14) | 1);
        ASM_SCHED_BARRIER();
        func_800C2C80(obj, motion, 0, 0);
    }
}
