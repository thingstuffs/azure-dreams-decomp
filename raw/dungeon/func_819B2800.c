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
extern int D_800814A8[4];
extern u8 D_80083498[];
extern u8 D_80082E80[];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u16 D_80082E94;
extern s32 D_80083460[3];
extern s32 D_800814A0[3];
extern void *D_80024008[];
M2C_UNK func_80024300();                            /* extern */
M2C_UNK func_80024308();                            /* extern */
M2C_UNK func_80024340();                            /* extern */
M2C_UNK func_8002441C();                        /* extern */
s32 func_8003DE58();     /* extern */
u8 *func_8003FD64();                   /* extern */
M2C_UNK func_8004491C();             /* extern */
M2C_UNK func_8009CE1C(); /* extern */
void *func_800A3F28();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_80024440;
extern M2C_UNK D_8002466C;
extern M2C_UNK D_80024B48;
extern M2C_UNK D_80024C14;

#ifdef __mips__
/* Existing-identity DATA-BANK composite: the row owns these seven retail words;
 * the C body begins at the true interior entry 0x819B281C. */
static const u32 bank_words[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
    0x8002401C, 0x00000000, 0x80024080, 0x800240E8,
    0x800241E8, 0x80024224, 0x80024310
};
__asm__(".globl func_80024000\n.type func_80024000,@function\n.size func_80024000,1088\n");
#define BODY_NAME composite_body
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_80024000")))
#else
#define BODY_NAME func_80024000
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void BODY_NAME(void *arg0, void *arg1) BODY_ATTR;
BODY_STORAGE void BODY_NAME(void *arg0, void *arg1) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    s16 sp20[3];
    u16 temp_counter;
    u16 temp_state;
    M2C_UNK var_a0;
    s16 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_s0;
    u8 *temp_s0;
    u8 *var_a0_2;
    void *temp_a1;
    void *global_obj;
    s32 *global_state;
    void *temp_s1;
    void *temp_s2;

    temp_state = M2C_FIELD(arg0, volatile u16 *, 0x50);
    temp_s1 = M2C_FIELD(arg0, void * volatile *, 0);
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xA);
    M2C_FIELD(arg0, u16 *, 0x50) = (u16) (temp_state - 1);
    temp_s2 = temp_s1 - 0x20;
    if ((u32) temp_v1 >= 5U) {
        goto block_36;
    }
    (void)jt_keep; goto *D_80024008[(u32)(temp_v1)];
jt_c0:
    M2C_FIELD(((s32*)&D_800814A8)[0], s8 *, 0x102) = 1;
    M2C_FIELD(((s32*)&D_800814A8)[0], s32 *, 0xF4) = 0;
    M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(M2C_FIELD(temp_s2, void **, 8), s32 *, 0);
    M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(M2C_FIELD(temp_s2, void **, 8), s32 *, 4);
    M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(M2C_FIELD(temp_s2, void **, 8), s32 *, 8);
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
jt_c1:
    if (!(*M2C_FIELD(arg0, u16 **, 4) & 0x80)) {
        goto block_36;
    }
    global_obj = (void *) ((s32*)&D_800814A8)[0];
    M2C_FIELD(arg0, u16 *, 0x50) = 0xAU;
    M2C_FIELD(global_obj, u16 *, 0xA6) = (u16) (M2C_FIELD(global_obj, u16 *, 0xA6) - 1);
    M2C_FIELD(global_obj, u8 *, 0xA8) = (u8) M2C_FIELD(arg0, u8 *, 8);
    temp_s1 = func_8003FD64(0x302, D_80083498);
    if (temp_s1 == NULL) {
        goto block_8;
    }
    temp_a1 = M2C_FIELD(temp_s2, void **, 0xC);
    if (func_8003DE58(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, sp20, 0) != 0) {
        goto block_7;
    }
    sp20[2] = 0;
    sp20[1] = 0;
    sp20[0] = 0;
block_7:
    temp_s0 = temp_s1 + 0x20;
    M2C_FIELD(temp_s1, M2C_UNK **, 0x10) = &D_8002466C;
    func_8004491C(temp_s1, &D_80024440);
    temp_v1_2 = M2C_FIELD(M2C_FIELD(temp_s2, void **, 8), s32 *, 0) + (sp20[0] << 0x10);
    M2C_FIELD(arg1, s32 *, 0) = temp_v1_2;
    M2C_FIELD(temp_s0, s32 *, 0x1C) = temp_v1_2;
    temp_v1_3 = M2C_FIELD(M2C_FIELD(temp_s2, void **, 8), s32 *, 4) + (sp20[1] << 0x10);
    M2C_FIELD(arg1, s32 *, 4) = temp_v1_3;
    M2C_FIELD(temp_s0, s32 *, 0x20) = temp_v1_3;
    temp_v1_4 = M2C_FIELD(M2C_FIELD(temp_s2, void **, 8), s32 *, 8) + (sp20[2] << 0x10);
    M2C_FIELD(arg1, s32 *, 8) = temp_v1_4;
    M2C_FIELD(temp_s0, s32 *, 0x24) = temp_v1_4;
    M2C_FIELD(temp_s1, void **, 0x20) = arg0;
block_8:
    temp_counter = M2C_FIELD(arg0, u16 *, 0xA);
    temp_counter++;
    goto block_store_counter;
jt_c2:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x50) > 0) {
        goto block_36;
    }
    if (func_80053EF0(4) != 2) {
        var_a0 = 0x300;
    } else {
        var_a0 = 0x4300;
    }
    func_800A56E0(var_a0);
    temp_counter = M2C_FIELD(arg0, u16 *, 0xA);
    temp_v1 = 0xD;
    goto block_state_increment;
jt_c3:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x50) != 2) {
        goto block_17;
    }
    func_800419EC(0x18, 0x10);
block_17:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x50) > 0) {
        goto block_36;
    }
    temp_s1 = func_8003FD64(0x302, D_80083498);
    var_a0_2 = temp_s1;
    if (temp_s1 == NULL) {
        goto block_20;
    }
    temp_s0 = temp_s1 + 0x20;
    M2C_FIELD(temp_s1, M2C_UNK **, 0x10) = &D_80024B48;
    func_8004491C(var_a0_2, &D_80024C14);
    var_a0_2 = D_80082E80;
    temp_v0_3 = ((u16) M2C_FIELD(((s32*)&D_800814A8)[0], u16 *, 0x2A) >> 9) & 7;
    sp20[0] = temp_v0_3;
    M2C_FIELD(temp_s0, s16 *, 0xC) = (s16) (M2C_FIELD(D_80082E80, u8 *, 0x24) + D_8006CCD8[temp_v0_3]);
    M2C_FIELD(temp_s0, s16 *, 0xE) = (s16) (M2C_FIELD(D_80082E80, u8 *, 0x25) + D_8006CCE8[sp20[0]]);
    M2C_FIELD(temp_s0, u16 *, 0x10) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
    M2C_FIELD(temp_s1, void **, 0x20) = arg0;
block_20:
    temp_counter = M2C_FIELD(arg0, u16 *, 0xA);
    temp_v1 = 0x10;
block_state_increment:
    M2C_FIELD(arg0, u16 *, 0x50) = temp_v1;
    temp_counter++;
block_store_counter:
    M2C_FIELD(arg0, u16 *, 0xA) = temp_counter;
    goto block_36;
jt_c4:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x50) != 8) {
        goto block_30;
    }
    var_s0 = ((s32*)&D_800814A8)[0];
    arg1 = (void *) var_s0;
    if (var_s0 == 0) {
        goto block_30;
    }
    temp_s2 = D_80082E80;
loop_25:
    var_s0 = func_800A3F28(M2C_FIELD(temp_s2, u8 *, 0x24), M2C_FIELD(temp_s2, u8 *, 0x25), arg1, (void *) var_s0);
    if (var_s0 == 0) {
        goto block_30;
    }
    if (M2C_FIELD(var_s0, s32 *, 0x1C) & 0x2000) {
        goto loop_25;
    }
    func_8009CE1C((void *) var_s0, 0x10, M2C_FIELD(arg0, u8 *, 9), 0xC, (s32) M2C_FIELD(temp_s1, s16 *, 0x2A), temp_s1, 2);
    goto loop_25;
block_30:
    if (D_80082E94 & 0x8000) {
        goto block_32;
    }
    if ((s16) M2C_FIELD(arg0, u16 *, 0x50) >= 0) {
        goto block_36;
    }
block_32:
    if (!(M2C_FIELD(arg0, s16 *, 0x52) & 0x8000)) {
        goto block_35;
    }
    M2C_FIELD(arg0, u16 *, 0x52) = (u16) (M2C_FIELD(arg0, u16 *, 0x52) & 0x7FFF);
    goto block_36;
block_35:
    global_state = D_80083460;
    M2C_FIELD(global_state, s32 *, 0xC) = 0;
    M2C_FIELD(global_state, u16 *, 0xA) = (u16) (M2C_FIELD(global_state, u16 *, 0xA) - 1);
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    D_800814A0[0] |= 0x8000;
block_36:
    return;
}
