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

void *func_8003FD64();                  /* extern */
M2C_UNK func_8004491C(); /* extern */
M2C_UNK func_80047784();         /* extern */
M2C_UNK func_800BC26C(); /* extern */
extern M2C_UNK D_80045340;
extern s8 D_80083160[];
extern s8 D_800DCECC[];
extern M2C_UNK D_80172610;
extern u8 D_80174C74[];

typedef struct {
    s32 words[4];
} CopyBlock;

void func_80172B00(void *arg0, void *arg1, void *arg2) {
    s32 temp_s0;
    void *temp_s1;
    void *temp_s3;
    void *temp_v0;
    void *temp_v1;
    s8 *base_83160;
    register CopyBlock *var_a2 ASM_REG("$6");
    register CopyBlock *var_a3 ASM_REG("$7");
    register CopyBlock *copy_end ASM_REG("$8");
    register s32 word0 ASM_REG("$2");
    register s32 word1 ASM_REG("$3");
    register s32 word2 ASM_REG("$4");
    register s32 word3 ASM_REG("$5");
    register u16 field_1c ASM_REG("$2");
    register void *call_arg0 ASM_REG("$4");
    register s32 table_index ASM_REG("$3");
    register s32 angle ASM_REG("$2");
    register s32 call_arg1 ASM_REG("$5");

    temp_s0 = arg0 - 0x20;
    temp_v0 = func_8003FD64(0x112, temp_s0);
    temp_s3 = temp_v0 + 0x20;
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_s3, s16 *, 0x96) = 0x78;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80172610;
        M2C_FIELD(temp_s3, s32 *, 0xAC) = temp_s0;
        M2C_FIELD(temp_s3, u16 *, 0x94) = (u16) M2C_FIELD(arg0, u16 *, 0x2A);
        var_a3 = (CopyBlock *) arg2;
        M2C_FIELD(temp_s3, u16 *, 0x2A) = (u16) M2C_FIELD(arg0, u16 *, 0x2A);
        temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
        copy_end = (CopyBlock *) (arg2 + 0x30);
        var_a2 = (CopyBlock *) temp_s1;
        do {
            word0 = var_a3->words[0];
            word1 = var_a3->words[1];
            word2 = var_a3->words[2];
            word3 = var_a3->words[3];
            ASM_KEEP(word0);
            ASM_KEEP(word1);
            ASM_KEEP(word2);
            ASM_KEEP(word3);
            var_a2->words[0] = word0;
            var_a2->words[1] = word1;
            var_a2->words[2] = word2;
            var_a2->words[3] = word3;
            ASM_KEEP(var_a3);
            var_a3++;
            var_a2++;
        } while (var_a3 != copy_end);
        ASM_KEEP(var_a2);
        ASM_KEEP(copy_end);
        func_8004491C(temp_v0, &D_80045340, var_a2, var_a3);
        M2C_FIELD(temp_s1, u8 **, 0x2C) = D_80174C74;
        base_83160 = D_80083160;
        func_80047784(temp_s1, D_80174C74[((s32) (M2C_FIELD(base_83160, s16 *, 0xC8) + (s16) M2C_FIELD(arg0, u16 *, 0x2A) + 0x100) >> 9) & 7], 0);
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(temp_v1, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
        M2C_FIELD(temp_v1, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
        field_1c = M2C_FIELD(arg2, u16 *, 0x1C);
        ASM_KEEP(field_1c);
        call_arg0 = temp_v0;
        ASM_KEEP(call_arg0);
        M2C_FIELD(temp_s1, u16 *, 0x1C) = field_1c;
        M2C_FIELD(temp_s1, u16 *, 0x1E) = (u16) M2C_FIELD(arg2, u16 *, 0x1E);
        M2C_FIELD(temp_s1, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_s1, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s1, u8 *, 0xC) = 0x80;
        table_index = M2C_FIELD(base_83160, s16 *, 0xC8);
        angle = M2C_FIELD(arg0, s16 *, 0x2A);
        ASM_KEEP(angle);
        call_arg1 = 0;
        ASM_KEEP(call_arg1);
        table_index += angle;
        ASM_KEEP(table_index);
        table_index += 0x100;
        ASM_KEEP(table_index);
        table_index >>= 9;
        ASM_KEEP(table_index);
        table_index &= 7;
        ASM_KEEP(table_index);
        M2C_FIELD(temp_s1, s16 *, 6) = (s16) (D_800DCECC[table_index] * 4);
        M2C_FIELD(arg0, u8 *, 0xB0) = (u8) (M2C_FIELD(arg0, u8 *, 0xB0) + 1);
        func_800BC26C(call_arg0, call_arg1, temp_s1 + 0x2C, temp_s3 + 0x2A);
    }
}
/* MECHANISM: The 0x30 frame follows seven held callee-saved roles, including a reused &D_80083160 base.
   The 16-byte loop pins a3/a2/t0 and v0/v1/a0/a1 roles; guarded seams preserve load-all/store-all order.
   Byte-table types plus pinned call arguments and split v1 accumulator updates close the tail exactly. */
