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

typedef struct {
    s32 words[3];
} __attribute__((packed)) Packed12;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

#ifndef NON_MATCHING
void func_80024B18(void) __attribute__((noreturn));
#else
void *func_80024B18(void *);
#endif
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_800249A0;
extern M2C_UNK D_80045340;

void *func_800249F0(void *arg0, s32 arg1, s32 arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    u16 temp_v0_2;
    register u16 temp_v1_2 ASM_REG("$3");
    register s32 arg4_copy ASM_REG("$2");
    void *temp_a0;
    register void *temp_a3 ASM_REG("$7");
    register void *temp_a3_2 ASM_REG("$7");
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;
#ifndef NON_MATCHING
    register void *dispatch_result ASM_REG("$2");
    register void *dispatch_arg ASM_REG("$4");
#endif

    temp_v0 = func_8003FC64(0x212);
#ifndef NON_MATCHING
    dispatch_arg = temp_v0;
#endif
    if (temp_v0 == NULL) {
#ifndef NON_MATCHING
        dispatch_result = NULL;
        ASM_TAILSLOT_PIN(dispatch_result);
        func_80024B18();
#else
        return func_80024B18(temp_v0);
#endif
    }
    temp_s0 = temp_v0 + 0x20;
    M2C_FIELD(temp_s0, s16 *, 0x2A) = 0x3C;
    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800249A0;
    func_8004491C(temp_v0, &D_80045340);
    temp_a3 = M2C_FIELD(temp_v0, void **, 0xC);
    temp_v0_2 = M2C_FIELD(temp_a3, volatile u16 *, 0x14) | 0xC;
    M2C_FIELD(temp_a3, volatile u16 *, 0x14) = temp_v0_2;
    ASM_MEM_BARRIER();
    ASM_CLOBBER("$3");
    temp_v1_2 = temp_v0_2;
    ASM_KEEP(temp_v1_2);
    arg4_copy = arg4;
    ASM_KEEP(arg4_copy);
    M2C_FIELD(temp_a3, volatile u16 *, 0x14) = (u16) (temp_v1_2 | 0x80);
    ASM_KEEP(arg4_copy);
    M2C_FIELD(temp_a3, s16 *, 0x10) = (s16) (arg4_copy << 5);
    temp_v1 = M2C_FIELD(arg0, void **, -0x18);
    temp_a0 = M2C_FIELD(temp_v0, void **, 8);
    M2C_FIELD(temp_a0, s32 *, 0) = (s32) M2C_FIELD(temp_v1, s32 *, 0);
    M2C_FIELD(temp_a0, s32 *, 4) = (s32) M2C_FIELD(temp_v1, s32 *, 4);
    M2C_FIELD(temp_a0, s32 *, 8) = (s32) M2C_FIELD(temp_v1, s32 *, 8);
    temp_a3_2 = M2C_FIELD(temp_v0, void **, 0xC);
    M2C_FIELD(temp_a3_2, s16 *, 0x1C) = (s16) arg5;
    M2C_FIELD(temp_a3_2, s16 *, 0x1E) = (s16) arg6;
    M2C_FIELD(temp_a3_2, u8 *, 0xE) = 0x80;
    M2C_FIELD(temp_a3_2, u8 *, 0xD) = 0x80;
    M2C_FIELD(temp_a3_2, s8 *, 0xC) = (s8) arg7;
    M2C_FIELD(temp_v0, Packed12 *, 0x92) = *(Packed12 *)arg3;
    M2C_FIELD(temp_a3_2, void **, 8) = (void *) (temp_v0 + 0x92);
    return temp_s0;
}

/* MECHANISM: The 0x28 frame follows from held s2/s3 arguments plus s1 object and s0 return.
   Local a0/v0 dispatcher carriers and the tail-slot pin reproduce the noreturn j path.
   A fenced split RMW preserves both flag stores and the retail v0/v1 argument lifetimes.
   Disjoint a3 pointer roles free a0/a1 for the packed copy; u8 fields retain li 0x80. */
