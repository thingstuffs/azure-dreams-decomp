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

M2C_UNK func_800353F4(); /* extern */
M2C_UNK func_80042B68();                /* extern */
M2C_UNK func_80047738();              /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
M2C_UNK func_800A020C();                 /* extern */
s32 func_800A2C34();                          /* extern */
M2C_UNK func_800A48F0();       /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
s32 func_800A9E70();  /* extern */
M2C_UNK func_800AA36C(); /* extern */
s32 func_800BCB04();                   /* extern */
s32 func_800F6D28();    /* extern */
void *func_800F6DFC();                /* extern */
void func_80170CE8() __attribute__((noreturn));     /* extern */
void func_801713EC() __attribute__((noreturn));     /* extern */
void func_80171468() __attribute__((noreturn));     /* extern */
void func_801714E4() __attribute__((noreturn));     /* extern */
void func_80171968() __attribute__((noreturn));     /* extern */
void func_80171AD8() __attribute__((noreturn));     /* extern */
void func_80171B6C() __attribute__((noreturn));     /* extern */
void func_80171BEC() __attribute__((noreturn));     /* extern */
void func_80171CD4() __attribute__((noreturn));     /* extern */
void func_80171E8C() __attribute__((noreturn));     /* extern */
void func_80171ECC() __attribute__((noreturn));     /* extern */
void func_80171ED0() __attribute__((noreturn));     /* extern */
void func_80171F74() __attribute__((noreturn));     /* extern */
extern u8 D_80010248[];
extern u16 D_80013714[8];
extern u8 D_8006CCF8[16];
extern u8 D_8006EE9C[16];
extern u8 D_8006F47A[16];
extern u8 D_8006F50D[16];
extern u8 D_8006F6B9[16];
extern u8 D_8006F9D0[16];
extern u8 D_8006FD01[16];
extern u8 D_8006FFB7[16];
extern u8 D_800703D9[16];
extern u8 D_80070684[16];
extern u8 D_80070AF8[16];
extern u8 D_80070C11[16];
extern u8 D_80070E63[16];
extern u8 D_80082E80[64];
extern u16 D_80082EA4[8];
extern u8 D_80083160[16];
extern s16 D_80083228[8];
extern u16 D_80083462[8];
extern u8 D_80083780[16];
extern u8 D_800E296C[16];
extern u8 D_800E3D7C[16];
extern u8 D_800FB3C8[16];
extern u8 D_800FB8DF[16];
extern u8 D_800FBAD7[16];
extern u8 D_800FBD96[16];
extern u8 D_800FBE20[16];
extern u8 D_800FBE22[16];
extern u8 D_800FBE54[16];
typedef struct {
    u8 bytes[16];
} __attribute__((packed)) Packed16;
extern Packed16 D_80170804;
extern u8 D_80171FA4[16];
extern u8 D_80175C30[16];
extern void (*D_80175CC8[])(void *, void *, void *, void *);

#define event_base ((u8 *)&D_80082E80)
#define position_base ((u8 *)&D_80083780)

void func_812A524C(void *in0, void *in1, void *in2) {
    Packed16 stack_copy;
    Packed16 *copy_src;
    register void *arg0 ASM_REG("$17") = in0;
    register void *arg1 ASM_REG("$22") = in1;
    register void *arg2 ASM_REG("$20") = in2;
    register void *arg3 ASM_REG("$19");
    register u16 *copy_base ASM_REG("$21");
    register s32 tail_value ASM_REG("$2");
    register s32 tail_acc ASM_REG("$3");
    register u32 early_page ASM_REG("$18");
    u8 *flag_base;
    u8 *ev0;
    u8 *pos0;
    u8 *ev1;
    u8 *pos1;
    u8 *ev2;
    u8 *pos2;
    u8 *ev3;
    u8 *pos3;
    u8 *ev4;
    u8 *pos4;
    u8 *ev5;
    u8 *pos5;
    u8 *ev6;
    u8 *pos6;
    u8 *ev7;
    u8 *pos7;
    u8 *ev8;
    u8 *pos8;
    u8 *ev9;
    u8 *pos9;
    u8 *ev10;
    u8 *pos10;
    u8 *ev11;
    u8 *pos11;
    u8 *pos12;
    M2C_UNK (*temp_v0_4)(void *, void *, void *, void *);
    M2C_UNK (*temp_v1_4)(void *, void *, void *, void *);
    M2C_UNK *var_v0_10;
    M2C_UNK *var_v0_6;
    M2C_UNK *var_v0_7;
    u8 *var_v1;
    u8 *var_v1_2;
    u8 *var_v1_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s16 temp_a0_6;
    s16 temp_s2;
    s16 temp_v0_6;
    s32 temp_a0;
    s32 temp_a0_3;
    s32 temp_a1_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_5;
    s32 temp_v1_12;
    s32 temp_v1_6;
    s32 temp_v1_9;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 loop_hi;
    s32 loop_lo;
    s32 clear_flags;
    register s32 motion_x ASM_REG("$2");
    register s32 motion_y ASM_REG("$3");
    s32 var_v0_11;
    s32 var_v0_8;
    s32 var_v0_9;
    register s32 scaled_x ASM_REG("$2");
    register s32 event_x1 ASM_REG("$2");
    register s32 event_x2 ASM_REG("$2");
    register s32 event_x3 ASM_REG("$2");
    register s32 event_x4 ASM_REG("$2");
    register s32 event_x5 ASM_REG("$2");
    register s32 event_x6 ASM_REG("$2");
    register s32 event_x7 ASM_REG("$2");
    register s32 event_x8 ASM_REG("$2");
    register s32 event_x11 ASM_REG("$2");
    register s32 final_tail_value ASM_REG("$2");
    register s32 fixed_flags ASM_REG("$2");
    s16 temp_s0_3;
    s16 temp_s0_4;
    u16 *var_v0;
    u16 temp_v1_10;
    u16 temp_v1_11;
    register s32 temp_v1_5 ASM_REG("$3");
    u16 first_flags;
    u16 temp_v1_7;
    u16 temp_v1_8;
    u16 var_v0_12;
    u8 temp_a0_2;
    u8 temp_a1;
    u8 temp_s0;
    register u8 temp_s0_2 ASM_REG("$16");
    u8 temp_v1;
    u8 temp_v1_2;
    void **var_v0_2;
    void **var_v0_3;
    void **var_v0_4;
    void **var_v0_5;
    void *temp_v0_3;
    void *temp_v1_3;
    void *temp_actor;

    copy_src = &D_80170804;
    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    stack_copy = *copy_src;
    arg3 = arg0;
    flag_base = D_80083160;
    copy_base = (u16 *)&stack_copy;
    if (M2C_FIELD(&D_800FBE22, s16 *, 0) != M2C_FIELD(&D_800FBE20, s16 *, 0)) {
        M2C_FIELD(&D_800FBE22, u16 *, 0) = (u16) M2C_FIELD(&D_800FBE20, u16 *, 0);
    }
    if (M2C_FIELD(&D_800FBE20, s16 *, 0) != M2C_FIELD(M2C_FIELD(D_800E3D7C, void **, 0), u8 *, 0x9A)) {
        M2C_FIELD(&D_800FBE20, u16 *, 0) = (u16) M2C_FIELD(M2C_FIELD(D_800E3D7C, void **, 0), u8 *, 0x9A);
    }
    temp_s0 = M2C_FIELD(arg0, u8 *, 0xB8);
    if (temp_s0 == 2) {
        temp_v0 = func_800F6D28(arg1);
        M2C_FIELD(arg0, s16 *, 0x2A) = (s16) (temp_v0 << 9);
        if ((M2C_FIELD(arg0, u8 *, 0xB8) == temp_s0) && (M2C_FIELD(M2C_FIELD(D_800E3D7C, void **, 0), u8 *, 0x9A) == 0xE)) {
            M2C_FIELD(M2C_FIELD(D_800E3D7C, void **, 0), s16 *, 0x2A) = (s16) (copy_base[temp_v0 & 7] << 9);
        }
    }
    if (M2C_FIELD(arg0, u8 *, 0xB8) == 3) {
        M2C_FIELD(arg0, u8 *, 0xB8) = 0U;
        func_800AA36C(arg0, arg1, arg2, arg3);
    }
    if (M2C_FIELD(arg0, u8 *, 0xB8) != 0) {
        func_800A9A0C(arg3);
        if (D_80083462[0] & 0x2000) {
            M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
        }
    }
    if ((u32) (D_80082EA4[0] - 0x2536) < 2U) {
        M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 0x20000);
    }
    if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 0x20000)) {
        if (M2C_FIELD(&D_800FBE54, void **, 0) == NULL) goto block_27;
        func_800A48F0(M2C_FIELD(&D_800FBE54, void **, 0) + 0x20, 1, 0xA);
        early_page = 0x80010000;
        ASM_PAGEBASE_PIN(early_page);
        func_80170CE8();
    }
    goto block_26;
action_10:
    func_800353F4(&D_8006F6B9);
    M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
    M2C_FIELD(arg0, s32 *, 0xB0) |= 0x10;
    func_801713EC();
action_80:
    func_800353F4(&D_8006FFB7);
    M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
    M2C_FIELD(arg0, s32 *, 0xB0) |= 0x80;
    func_80171468();
action_100:
    func_800353F4(&D_800703D9);
    M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, u8 *, 0xB8) = temp_s0_2;
    M2C_FIELD(arg0, s32 *, 0xB0) |= 0x100;
    func_801714E4();
block_26:
    temp_a0 = (s32) M2C_FIELD(&D_800FBE54, void **, 0);
    if (temp_a0 != 0) {
        func_80042B68(temp_a0 + 0x20, 1);
        M2C_FIELD(&D_800FBE54, void **, 0) = NULL;
    }
block_27:
    ASM_CLOBBER("$18");
    if (!(M2C_FIELD(&D_80013714, u16 *, 0) & 1)) {
        if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
            if (!(D_80083462[0] & 0x2000) && ((func_800A2C34(arg3) << 0x10) == 0) && (ev0 = (u8 *)&D_80082E80, pos0 = (u8 *)&D_80083780, (((M2C_FIELD(ev0, u8 *, 0x24) << 6) + 0x20) == M2C_FIELD(pos0, s16 *, 2))) && (((M2C_FIELD(ev0, u8 *, 0x25) << 6) + 0x20) == M2C_FIELD(pos0, s16 *, 6))) {
                temp_v1 = M2C_FIELD(M2C_FIELD(D_800E3D7C, void **, 0), u8 *, 0x9A);
                if ((temp_v1 != 0x19) && (temp_v1 != 0x1B) && !(M2C_FIELD(arg3, s32 *, 0x1C) & 0x80000)) {
                    if ((M2C_FIELD(arg0, u8 *, 0xB9) == 0) && !(D_80013714[0] & 1)) {
                        M2C_FIELD(arg0, u8 *, 0xB9) = 1U;
                        func_800353F4(&D_8006EE9C);
                        M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                        M2C_FIELD(arg0, u8 *, 0xB8) = 2U;
                        temp_v0_2 = func_800F6D28(arg1);
                        temp_actor = M2C_FIELD(D_800E3D7C, void **, 0);
                        M2C_FIELD(arg3, s16 *, 0x2A) = (s16) (temp_v0_2 << 9);
                        if (M2C_FIELD(temp_actor, u8 *, 0x9A) == 0xE) {
                            M2C_FIELD(temp_actor, s16 *, 0x2A) = (s16) (((u16 *)&stack_copy)[temp_v0_2 & 7] << 9);
                        }
                        M2C_FIELD(&D_800FBE54, void **, 0) = func_800F6DFC(arg3);
                    }
                    if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
                        if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 0x20)) {
                            ev1 = (u8 *)&D_80082E80;
                            if ((M2C_FIELD(ev1, u16 *, 0x24) == 0x519) || (M2C_FIELD(ev1, u16 *, 0x24) == 0x619)) {
                                pos1 = (u8 *)&D_80083780;
                                event_x1 = M2C_FIELD(ev1, u8 *, 0x24);
                                if (((event_x1 << 6) + 0x20) == M2C_FIELD(pos1, s16 *, 2)) {
                                    if (((M2C_FIELD(ev1, u8 *, 0x25) << 6) + 0x20) == M2C_FIELD(pos1, s16 *, 6)) {
                                        func_800353F4(&D_8006F9D0);
                                        M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                        M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                        M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 0x20);
                                    }
                                }
                            }
                            temp_v1_2 = M2C_FIELD(M2C_FIELD(D_800E3D7C, void **, 0), u8 *, 0x9A);
                            if ((temp_v1_2 != 0x19) && (temp_v1_2 != 0x1B) && ((M2C_FIELD(&D_800FBE22, s16 *, 0) == 0x1B) || (M2C_FIELD(&D_800FBE22, s16 *, 0) == 0x1F) || (M2C_FIELD(&D_800FBE22, s16 *, 0) == 0x20) || (M2C_FIELD(&D_800FBE20, s16 *, 0) == 0x1B) || (M2C_FIELD(&D_800FBE20, s16 *, 0) == 0x1F) || (M2C_FIELD(&D_800FBE20, s16 *, 0) == 0x20))) {
                                func_800353F4(&D_8006F9D0);
                                M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 0x20);
                            }
                        }
                        if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
                            if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 0x4000)) {
                                ev2 = (u8 *)&D_80082E80;
                                if ((M2C_FIELD(ev2, u16 *, 0x24) == 0x2B2D) || (M2C_FIELD(ev2, u16 *, 0x24) == 0x2C2D)) {
                                    pos2 = (u8 *)&D_80083780;
                                    event_x2 = M2C_FIELD(ev2, u8 *, 0x24);
                                    if (((event_x2 << 6) + 0x20) == M2C_FIELD(pos2, s16 *, 2)) {
                                        if (((M2C_FIELD(ev2, u8 *, 0x25) << 6) + 0x20) == M2C_FIELD(pos2, s16 *, 6)) {
                                            func_800353F4(&D_800FB8DF);
                                            M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                            M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                            M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                            M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 0x4000);
                                        }
                                    }
                                }
                                if (M2C_FIELD(M2C_FIELD(D_800E3D7C, void **, 0), u8 *, 0x9A) == 0x1C) {
                                    func_800353F4(&D_800FB8DF);
                                    M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                    M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                    M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 0x4000);
                                }
                            }
                            if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
                                if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 0x200) && (ev3 = (u8 *)&D_80082E80, ((u32) (M2C_FIELD(ev3, u16 *, 0x24) - 0xB36) < 2U)) && (pos3 = (u8 *)&D_80083780, event_x3 = M2C_FIELD(ev3, u8 *, 0x24), (((event_x3 << 6) + 0x20) == M2C_FIELD(pos3, s16 *, 2))) && (((M2C_FIELD(ev3, u8 *, 0x25) << 6) + 0x20) == M2C_FIELD(pos3, s16 *, 6))) {
                                    func_800353F4(&D_80070684);
                                    M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                    M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                    M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 0x200);
                                }
                                if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
                                    if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 0x8000) && (ev4 = (u8 *)&D_80082E80, ((u32) (M2C_FIELD(ev4, u16 *, 0x24) - 0x1236) < 2U)) && (pos4 = (u8 *)&D_80083780, event_x4 = M2C_FIELD(ev4, u8 *, 0x24), (((event_x4 << 6) + 0x20) == M2C_FIELD(pos4, s16 *, 2))) && (((M2C_FIELD(ev4, u8 *, 0x25) << 6) + 0x20) == M2C_FIELD(pos4, s16 *, 6))) {
                                        func_800353F4(&D_800FBAD7);
                                        M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                        M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                        M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 0x8000);
                                    }
                                    if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
                                        if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 2)) {
                                            ev5 = (u8 *)&D_80082E80;
                                            if ((u32) (M2C_FIELD(ev5, u16 *, 0x24) - 0x1D07) < 2U) {
                                                pos5 = (u8 *)&D_80083780;
                                                event_x5 = M2C_FIELD(ev5, u8 *, 0x24);
                                                if (((event_x5 << 6) + 0x20) == M2C_FIELD(pos5, s16 *, 2)) {
                                                    if (((M2C_FIELD(ev5, u8 *, 0x25) << 6) + 0x20) == M2C_FIELD(pos5, s16 *, 6)) {
                                                        func_800353F4(&D_8006F47A);
                                                        M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                                        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                                        M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                                        M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 2);
                                                    }
                                                }
                                            }
                                            if ((M2C_FIELD(M2C_FIELD(D_800E3D7C, void **, 0), u8 *, 0x9A) != 0x19) && (M2C_FIELD(flag_base, s32 *, 0x10) & 0x20)) {
                                                func_800353F4(&D_8006F47A);
                                                M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                                M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                                M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                                M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 2);
                                            }
                                        }
                                        if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
                                            if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 4)) {
                                                ev6 = (u8 *)&D_80082E80;
                                                if ((u32) (M2C_FIELD(ev6, u16 *, 0x24) - 0x291E) < 3U) {
                                                    pos6 = (u8 *)&D_80083780;
                                                    event_x6 = M2C_FIELD(ev6, u8 *, 0x24);
                                                    if (((event_x6 << 6) + 0x20) == M2C_FIELD(pos6, s16 *, 2)) {
                                                        if (((M2C_FIELD(ev6, u8 *, 0x25) << 6) + 0x20) == M2C_FIELD(pos6, s16 *, 6)) {
                                                            func_800353F4(&D_8006F50D);
                                                            M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                                            M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                                            M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                                            M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 4);
                                                        }
                                                    }
                                                }
                                                if ((M2C_FIELD(M2C_FIELD(D_800E3D7C, void **, 0), u8 *, 0x9A) != 0x19) && (M2C_FIELD(flag_base, s32 *, 8) & 0x10)) {
                                                    func_800353F4(&D_8006F50D);
                                                    M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                                    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                                    M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                                    M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 4);
                                                }
                                            }
                                            if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
                                                if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 0x10) && (M2C_FIELD(M2C_FIELD(D_800E3D7C, void **, 0), u8 *, 0x9A) != 0x23)) {
                                                    var_a0 = 0;
                                                    loop_hi = 0xF;
                                                    loop_lo = 2;
                                                    var_v1 = (u8 *)0x80010000;
loop_102:
                                                    if ((var_v1[0x249] != loop_hi) || (var_v1[0x248] != loop_lo)) {
                                                        var_a0 += 1;
                                                        var_v1 += 4;
                                                        if (var_a0 >= 0x14) {
                                                            goto block_105;
                                                        }
                                                        goto loop_102;
                                                    }
                                                    goto action_10;
                                                }
block_105:
                                                if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
                                                    if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 0x80) && (M2C_FIELD(M2C_FIELD(D_800E3D7C, void **, 0), u8 *, 0x9A) != 0x23)) {
                                                        var_a0_2 = 0;
                                                        loop_hi = 0x12;
                                                        loop_lo = 0x15;
                                                        var_v1_2 = (u8 *)0x80010000;
loop_109:
                                                        if ((var_v1_2[0x249] != loop_hi) || (var_v1_2[0x248] != loop_lo)) {
                                                            var_a0_2 += 1;
                                                            var_v1_2 += 4;
                                                            if (var_a0_2 >= 0x14) {
                                                                goto block_112;
                                                            }
                                                            goto loop_109;
                                                        }
                                                        goto action_80;
                                                    }
block_112:
                                                    if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
                                                        if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 0x100) && (M2C_FIELD(M2C_FIELD(D_800E3D7C, void **, 0), u8 *, 0x9A) != 0x23)) {
                                                            var_a0_3 = 0;
                                                            loop_hi = 4;
                                                            loop_lo = 1;
                                                            var_v1_3 = (u8 *)0x80010000;
loop_116:
                                                            if ((var_v1_3[0x249] != loop_hi) || (temp_s0_2 = var_v1_3[0x248], (temp_s0_2 != loop_lo))) {
                                                                var_a0_3 += 1;
                                                                var_v1_3 += 4;
                                                                if (var_a0_3 >= 0x14) {
                                                                    goto block_119;
                                                                }
                                                                goto loop_116;
                                                            }
                                                            goto action_100;
                                                        }
block_119:
                                                        if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
                                                            if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 0x40) && (ev7 = (u8 *)&D_80082E80, ((u32) (M2C_FIELD(ev7, u16 *, 0x24) - 0x161C) < 7U)) && (pos7 = (u8 *)&D_80083780, event_x7 = M2C_FIELD(ev7, u8 *, 0x24), (((event_x7 << 6) + 0x20) == M2C_FIELD(pos7, s16 *, 2))) && (((M2C_FIELD(ev7, u8 *, 0x25) << 6) + 0x20) == M2C_FIELD(pos7, s16 *, 6))) {
                                                                func_800353F4(&D_8006FD01);
                                                                M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                                                M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                                                M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                                                M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 0x40);
                                                            }
                                                            if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
                                                                if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 0x400) && (ev8 = (u8 *)&D_80082E80, ((u32) (M2C_FIELD(ev8, u16 *, 0x24) - 0x2036) < 2U)) && (pos8 = (u8 *)&D_80083780, event_x8 = M2C_FIELD(ev8, u8 *, 0x24), (((event_x8 << 6) + 0x20) == M2C_FIELD(pos8, s16 *, 2))) && (((M2C_FIELD(ev8, u8 *, 0x25) << 6) + 0x20) == M2C_FIELD(pos8, s16 *, 6))) {
                                                                    func_800353F4(&D_80070AF8);
                                                                    M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                                                    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                                                    M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                                                    M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 0x400);
                                                                }
                                                                if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
                                                                    if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 0x800) && ((D_80082EA4[0] == 0x31E) || (D_80082EA4[0] == 0x41E) || (D_80082EA4[0] == 0x51E) || (D_80082EA4[0] == 0x61E) || (D_80082EA4[0] == 0x71E) || (D_80082EA4[0] == 0x81E)) && (ev9 = (u8 *)&D_80082E80, pos9 = (u8 *)&D_80083780, (((M2C_FIELD(ev9, u8 *, 0x24) << 6) + 0x20) == M2C_FIELD(pos9, s16 *, 2))) && (((M2C_FIELD(ev9, u8 *, 0x25) << 6) + 0x20) == M2C_FIELD(pos9, s16 *, 6))) {
                                                                        func_800353F4(&D_80070C11);
                                                                        M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                                                        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                                                        M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                                                        M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 0x800);
                                                                    }
                                                                    if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
                                                                        if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 0x1000)) {
                                                                            if (((u32) (D_80082EA4[0] - 0x2C1E) < 3U) || (D_80082EA4[0] == 0x2D1E) || (D_80082EA4[0] == 0x2D1F) || (D_80082EA4[0] == 0x2D20)) {
                                                                                ev10 = (u8 *)&D_80082E80;
                                                                                pos10 = (u8 *)&D_80083780;
                                                                                if ((((M2C_FIELD(ev10, u8 *, 0x24) << 6) + 0x20) == M2C_FIELD(pos10, s16 *, 2)) && (((M2C_FIELD(ev10, u8 *, 0x25) << 6) + 0x20) == M2C_FIELD(pos10, s16 *, 6))) {
                                                                                    func_800353F4(&D_80070E63);
                                                                                    M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                                                                    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                                                                    M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                                                                    M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 0x1000);
                                                                                }
                                                                            }
                                                                        }
                                                                        if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
                                                                            if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 0x2000) && (ev11 = (u8 *)&D_80082E80, ((u32) (M2C_FIELD(ev11, u16 *, 0x24) - 0x121C) < 7U)) && (pos11 = (u8 *)&D_80083780, event_x11 = M2C_FIELD(ev11, u8 *, 0x24), (((event_x11 << 6) + 0x20) == M2C_FIELD(pos11, s16 *, 2))) && (((M2C_FIELD(ev11, u8 *, 0x25) << 6) + 0x20) == M2C_FIELD(pos11, s16 *, 6))) {
                                                                                func_800353F4(&D_800FB3C8);
                                                                                M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                                                                M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                                                                M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                                                                M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (M2C_FIELD(arg0, s32 *, 0xB0) | 0x2000);
                                                                            }
                                                                            if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
                                                                                if (!(M2C_FIELD(arg0, s32 *, 0xB0) & 0x10000)) {
                                                                                    if (M2C_FIELD(&D_800FBE54, void **, 0) == NULL) {
                                                                                        temp_v0_3 = func_800F6DFC(arg3);
                                                                                        M2C_FIELD(&D_800FBE54, void **, 0) = temp_v0_3;
                                                                                        if (temp_v0_3 != NULL) {
                                                                                            goto block_163;
                                                                                        }
                                                                                    } else {
block_163:
                                                                                        temp_v1_3 = M2C_FIELD(M2C_FIELD(&D_800FBE54, void **, 0), void **, 0xC);
                                                                                        var_v0_7 = &D_80082E80;
                                                                                        temp_a0 = M2C_FIELD(var_v0_7, u8 *, 0x24);
                                                                                        var_v0_8 = temp_a0 - M2C_FIELD(temp_v1_3, u8 *, 0x24);
                                                                                        if (var_v0_8 < 0) {
                                                                                            var_v0_8 = 0 - var_v0_8;
                                                                                        }
                                                                                        if (var_v0_8 < 4) {
                                                                                            temp_a1_2 = M2C_FIELD(var_v0_7, u8 *, 0x25);
                                                                                            var_v0_9 = temp_a1_2 - M2C_FIELD(temp_v1_3, u8 *, 0x25);
                                                                                            if (var_v0_9 < 0) {
                                                                                                var_v0_9 = 0 - var_v0_9;
                                                                                            }
                                                                                            if (var_v0_9 < 4) {
                                                                                                scaled_x = temp_a0 << 6;
                                                                                                ASM_KEEP(scaled_x);
                                                                                                pos12 = (u8 *)&D_80083780;
                                                                                                if (((scaled_x + 0x20) == M2C_FIELD(pos12, s16 *, 2)) && (((temp_a1_2 << 6) + 0x20) == M2C_FIELD(pos12, s16 *, 6))) {
                                                                                                    func_800353F4(&D_800FBD96);
                                                                                                    M2C_FIELD(arg3, u8 *, 0x6D) = 0U;
                                                                                                    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                                                                                    M2C_FIELD(arg0, u8 *, 0xB8) = 1U;
                                                                                                    M2C_FIELD(arg0, s32 *, 0xB0) |= 0x10000;
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                                goto block_172;
                                                                            }
                                                                            goto active_return;
                                                                        }
                                                                        goto active_return;
                                                                    }
                                                                    goto active_return;
                                                                }
                                                                goto active_return;
                                                            }
                                                            goto active_return;
                                                        }
                                                        goto active_return;
                                                    }
                                                    goto active_return;
                                                }
                                                goto active_return;
                                            }
                                            goto active_return;
                                        }
                                        goto active_return;
                                    }
                                    goto active_return;
                                }
                                goto active_return;
                            }
                            goto active_return;
                        }
                        goto active_return;
                    }
                    goto active_return;
                }
            }
            goto block_172;
        }
        goto active_return;
    }
block_172:
    if (M2C_FIELD(arg0, u8 *, 0xB8) == 0) {
        goto inactive;
    }
active_return:
    M2C_FIELD(&D_800E296C, s32 *, 0) |= 0x200000;
    func_80171968();
inactive:
    clear_flags = M2C_FIELD(&D_800E296C, volatile s32 *, 0);
    clear_flags &= 0xFFDFFFFF;
    M2C_FIELD(&D_800E296C, volatile s32 *, 0) = clear_flags;
    ASM_KEEP(clear_flags);
    if (D_80083462[0] & 0x2000) {
        temp_v1_4 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
        if (temp_v1_4 == &D_80171FA4) {
            temp_v1_4(arg0, arg1, arg2, arg3);
            func_80171F74();
            return;
        }
        M2C_FIELD(arg3, u8 *, 0x71) &= 0x7F;
        func_80171F74(arg0);
        return;
    }
    temp_s0_3 = (s8) M2C_FIELD(arg3, u8 *, 0x6D);
    if (func_800A9E70(arg0, arg1, arg2, arg3) == 0) {
        temp_v0_4 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
        if (temp_v0_4 != NULL) {
            temp_v0_4(arg0, arg1, arg2, arg3);
        }
        D_80175CC8[M2C_FIELD(arg0, u8 *, 0x9A)](arg0, arg1, arg2, arg3);
        if ((s16) temp_s0_3 != (s8) M2C_FIELD(arg3, u8 *, 0x6D)) {
            func_800AA36C(arg0, arg1, arg2, arg3);
        }
        motion_x = M2C_FIELD(arg1, s32 *, 0);
        ASM_SCHED_BARRIER();
        temp_a0_3 = M2C_FIELD(arg1, s32 *, 0xC);
        ASM_SCHED_BARRIER();
        motion_y = M2C_FIELD(arg1, s32 *, 4);
        ASM_SCHED_BARRIER();
        temp_a1_2 = M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(arg1, s32 *, 0) = motion_x + temp_a0_3;
        M2C_FIELD(arg1, s32 *, 4) = motion_y + temp_a1_2;
        if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x40000) && !(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + (M2C_FIELD(arg0, s8 *, 0x9D) * 0x14000));
            M2C_FIELD(arg0, u8 *, 0x9D) += 1;
            func_80171AD8(temp_a0_3, temp_a1_2);
            return;
        }
        M2C_FIELD(arg0, s8 *, 0x9D) = 0;
        ASM_MEM_BARRIER();
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + M2C_FIELD(arg1, s32 *, 0x14));
        temp_s2 = ((s32) (D_80083228[0] + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7;
        temp_s0_4 = temp_s2;
        if (M2C_FIELD(arg0, s16 *, 0x94) != temp_s0_4) {
            func_80047738(arg2, M2C_FIELD(arg2, u8 **, 0x2C)[temp_s0_4], M2C_FIELD(arg2, s8 *, 4));
            M2C_FIELD(arg0, s16 *, 0x94) = temp_s2;
        }
        if (D_8006CCF8[temp_s0_4] != 0) {
            tail_value = M2C_FIELD(arg2, u16 *, 0x14);
            tail_value |= 1;
            ASM_TAILSLOT_PIN_TIED(tail_value);
            func_80171B6C();
            return;
        }
        first_flags = M2C_FIELD(arg2, volatile u16 *, 0x14);
        M2C_FIELD(arg2, volatile u16 *, 0x14) = first_flags & 0xFFFE;
        temp_v1_5 = M2C_FIELD(arg2, volatile u16 *, 0x14);
        fixed_flags = temp_v1_5 & 0x8000;
        if (fixed_flags == 0) {
            func_800A020C(M2C_FIELD(arg3, s32 *, 0x1C), arg2 + 0xC);
            if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x20)) {
                if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
                    func_800478B8(arg2);
                    tail_value = 0xF7FF0000;
                    ASM_TAILSLOT_PIN(tail_value);
                    func_80171BEC();
                    return;
                }
                goto block_201;
            }
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x7000);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xFFFBFFFF);
block_201:
            temp_v1_6 = M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF;
            M2C_FIELD(arg3, s32 *, 0x1C) = temp_v1_6;
            if (temp_v1_6 & 0x40000) {
                if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40) && (M2C_FIELD(arg2, s32 *, 0x2C) == &D_80175C30)) {
                    if (M2C_FIELD(arg2, u16 *, 4) == 0x100) {
                        M2C_FIELD(arg0, u16 *, 0x9E) = 0U;
                        M2C_FIELD(arg0, s32 *, 0xA0) = 0;
                    }
                    if ((u32) ((u8) M2C_FIELD(arg2, s8 *, 4) - 1) < 4U) {
                        temp_v1_7 = M2C_FIELD(arg0, u16 *, 0x9E);
                        M2C_FIELD(arg0, u16 *, 0x9E) = (u16) (temp_v1_7 + 1);
                        tail_value = func_800644B8((s16) temp_v1_7 * 0xAA);
                        tail_acc = M2C_FIELD(arg0, s32 *, 0xA0);
                        tail_value <<= 5;
                        ASM_KEEP(tail_acc);
                        ASM_TAILSLOT_PIN_TIED(tail_value);
                        func_80171CD4();
                        return;
                    }
                    temp_v1_8 = M2C_FIELD(arg0, u16 *, 0x9E);
                    M2C_FIELD(arg0, u16 *, 0x9E) = (u16) (temp_v1_8 + 1);
                    M2C_FIELD(arg0, s32 *, 0xA0) = (s32) (M2C_FIELD(arg0, s32 *, 0xA0) + (func_800644B8((s16) temp_v1_8 * 0xAA) << 6));
                    goto block_210;
                }
block_210:
                if (!(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
                    temp_a0_4 = M2C_FIELD(arg0, s16 *, 0x92);
                    tail_acc = M2C_FIELD(arg0, u16 *, 0x92);
                    if (temp_a0_4 >= -0x1F) {
                        tail_value = temp_a0_4 < -0x28;
                        ASM_KEEP(tail_value);
                        tail_value = tail_acc - 8;
                        ASM_TAILSLOT_PIN_TIED(tail_value);
                        func_80171ECC(temp_a0_4);
                        return;
                    }
                    goto block_233;
                }
                goto block_235;
            }
            goto block_217;
        }
        fixed_flags = temp_v1_5 & 0x800;
        if (fixed_flags != 0) {
            fixed_flags = temp_v1_5 & 0x8FFF;
            goto flags_ready;
        }
        fixed_flags = temp_v1_5 | 0x7000;
flags_ready:
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) fixed_flags;
        ASM_SCHED_BARRIER();
        temp_v1_9 = M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF;
        M2C_FIELD(arg3, s32 *, 0x1C) = temp_v1_9;
        if (!(temp_v1_9 & 0x40000)) {
block_217:
            temp_v0_5 = M2C_FIELD(arg0, s32 *, 0xA0);
            M2C_FIELD(arg0, u16 *, 0x9E) = 0U;
            M2C_FIELD(arg0, s32 *, 0xA0) = 0;
            M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) - temp_v0_5);
            if (!(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
                temp_a0_5 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20)) - M2C_FIELD(arg3, u16 *, 0x88);
                if ((s16) temp_a0_5 < M2C_FIELD(arg0, s16 *, 0x92)) {
                    M2C_FIELD(arg0, s16 *, 0x92) = (s16) temp_a0_5;
                    M2C_FIELD(arg0, s8 *, 0x9D) = 0;
                    M2C_FIELD(arg1, s32 *, 0x14) = 0;
                    M2C_FIELD(arg3, s32 *, 0x1C) |= 0x08000000;
                    func_80171ED0(temp_a0_5);
                    return;
                }
            }
            goto block_235;
        }
        if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40) && (M2C_FIELD(arg2, s32 *, 0x2C) == &D_80175C30)) {
            if (M2C_FIELD(arg2, u16 *, 4) == 0x100) {
                M2C_FIELD(arg0, u16 *, 0x9E) = 0U;
                M2C_FIELD(arg0, s32 *, 0xA0) = 0;
            }
            if ((u32) ((u8) M2C_FIELD(arg2, s8 *, 4) - 1) < 4U) {
                temp_v1_10 = M2C_FIELD(arg0, u16 *, 0x9E);
                M2C_FIELD(arg0, u16 *, 0x9E) = (u16) (temp_v1_10 + 1);
                tail_value = func_800644B8((s16) temp_v1_10 * 0xAA);
                tail_acc = M2C_FIELD(arg0, s32 *, 0xA0);
                tail_value <<= 5;
                ASM_KEEP(tail_acc);
                ASM_TAILSLOT_PIN_TIED(tail_value);
                func_80171E8C();
                return;
            }
            temp_v1_11 = M2C_FIELD(arg0, u16 *, 0x9E);
            M2C_FIELD(arg0, u16 *, 0x9E) = (u16) (temp_v1_11 + 1);
            M2C_FIELD(arg0, s32 *, 0xA0) = (s32) (M2C_FIELD(arg0, s32 *, 0xA0) + (func_800644B8((s16) temp_v1_11 * 0xAA) << 6));
            goto block_229;
        }
block_229:
        if (!(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
            temp_a0_4 = M2C_FIELD(arg0, s16 *, 0x92);
            tail_acc = M2C_FIELD(arg0, u16 *, 0x92);
            if (temp_a0_4 >= -0x1F) {
                tail_value = tail_acc - 8;
                ASM_TAILSLOT_PIN_TIED(tail_value);
                func_80171ECC(temp_a0_4);
                return;
            }
block_233:
            if (temp_a0_4 < -0x28) {
                final_tail_value = tail_acc + 8;
                M2C_FIELD(arg0, s16 *, 0x92) = (s16) final_tail_value;
            }
            goto block_235;
        }
block_235:
        temp_v1_12 = M2C_FIELD(arg3, s32 *, 0x1C);
        if (temp_v1_12 & 0x40000000) {
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (temp_v1_12 & 0xBFFFFFFF);
            temp_v0_6 = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
            if (temp_v0_6 < 0x200) {
                M2C_FIELD(arg0, s16 *, 0x92) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x92) + (M2C_FIELD(arg3, u16 *, 0x88) - temp_v0_6));
                M2C_FIELD(arg3, u16 *, 0x88) = (u16) temp_v0_6;
            }
        }
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((M2C_FIELD(arg3, u16 *, 0x88) + (u16) M2C_FIELD(arg0, s16 *, 0x92)) - M2C_FIELD(arg0, u16 *, 0xA2));
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x40);
    }
    return;
}
