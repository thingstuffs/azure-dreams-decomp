#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

#ifdef __mips__
static const u32 data_bank[] __asm__("func_80024000")
    __attribute__((section(".text.func_80024000"), aligned(4))) = {
    0x8002401C, 0x00000000,
    0x800240C8, 0x8002467C, 0x80024AB0,
    0x80024C78, 0x80024CB8,
};
__asm__(".globl func_80024000\n.size func_80024000,3396");
#define BODY_NAME func_8002401C
#else
#define BODY_NAME func_80024000
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
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_800DEC28[];
extern u8 D_800DEC00[];
extern s32 D_800DEB70;
extern s32 D_8008346C[];
extern s32 D_800814A0[3];
M2C_UNK func_80024220();                            /* extern */
M2C_UNK func_80024368();                            /* extern */
M2C_UNK func_80024424();                            /* extern */
M2C_UNK func_80024744();                            /* extern */
M2C_UNK func_80024764();                            /* extern */
M2C_UNK func_80024C5C();                     /* extern */
M2C_UNK func_80024C9C();                            /* extern */
M2C_UNK func_80024D10();                    /* extern */
s32 func_8003DE58();     /* extern */
void *func_8003FD64();                 /* extern */
M2C_UNK func_8004491C();                /* extern */
s32 func_80069EF8(void);            /* extern */
void func_800478B8(void *);          /* extern */
M2C_UNK func_8009CE1C(); /* extern */
s32 func_800A05A4();        /* extern */
s32 func_800A3820();                    /* extern */
s32 func_800A4688();         /* extern */
M2C_UNK func_800A56E0();                /* extern */
s16 func_800BCB04();                   /* extern */
extern M2C_UNK D_80024D44;
extern M2C_UNK D_80024E98;
extern u8 D_800DEBD8;
extern void *D_80024008[];

typedef struct Func80024000Frame {
    s16 pad20;
    s16 sp22;
    s16 pad24;
    s16 sp26;
    union {
        s32 sp28;
        struct { s16 pad28; s16 sp2A; } half;
    } u28;
    u8 pad2C[12];
    s16 sp38;
    s16 sp3A;
    s16 sp3C;
    s16 pad3E;
    s16 *sp40;
    s16 *sp44;
    s16 sp48;
    s16 pad4A;
    s16 sp4C;
    s16 pad4E;
    s16 sp50;
    s16 sp52;
    s16 sp54;
    s16 pad56;
    s16 sp58;
    s16 sp5A;
    u8 pad5C[4];
    s16 sp60;
    s16 sp62;
    s16 sp64;
    s16 pad66;
} Func80024000Frame;

void BODY_NAME(void *arg0, void *arg1, void *arg2) __attribute__((section(".text.func_80024000")));
void BODY_NAME(void *arg0, void *arg1, void *arg2) {
    Func80024000Frame frame;
    void *sp68;
    s32 sp6C;
    s32 sp70;
    s32 byte_x;
    register s32 shift_x ASM_REG("$3");
    register s32 shift_y ASM_REG("$2");
    s32 h2a_x;
    register s32 sub_x ASM_REG("$3");
    register s32 sub_y ASM_REG("$2");
    u8 *page_a;
    s32 prod3;
    void *ap;
    s32 tmp48_x;
    s32 byte_y;
    u8 *page_e;
    s32 page_ev;
    u8 *page_b;
    s32 page_w;
    s32 bound_x;
    u8 *page_d;
    s32 page_dv;
    s32 temp_a0_9;
    s32 page_v;
    s32 page_c;
    s32 h48_x;
    s32 temp_v1_3;
    u16 hword_x;
    s16 temp_a0_2;
    s32 a1v;
    s32 a0v;
    s32 temp_a1;
    s16 temp_v0_2;
    s32 temp_v0_3;
    s32 var_v0;
    s32 var_v0_2;
    s16 var_v1;
    s32 temp_a0;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a1_5;
    s32 temp_a2;
    register M2C_UNK temp_lo ASM_REG("$5");
    register s32 temp_s1_2 ASM_REG("$17");
    s32 temp_s2;
    s32 temp_v0;
    s32 quotient_y;
    s32 temp_scale;
    s32 temp_v1;
    register s32 var_s1 ASM_REG("$17");
    s32 var_s1_2;
    s32 var_s3;
    register s32 var_s3_2 ASM_REG("$19");
    s32 var_s3_3;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    register s32 move_count ASM_REG("$19");
    s32 work_s5;
    register s32 move_y ASM_REG("$22");
    u8 *state1_tex;
    u16 temp_a0_8;
    register s32 ysum ASM_REG("$18");
    s32 temp_s0;
    register u16 temp_s1 ASM_REG("$17");
    u16 temp_v1_2;
    void *temp_a0_11;
    void *temp_a0_12;
    void *temp_a0_7;
    void *temp_a1_2;
    void *temp_a1_3;
    void *temp_a1_4;
    void *temp_fp;
    register void *temp_s0_2 ASM_REG("$16");
    register void *temp_s0_3 ASM_REG("$16");
    void *temp_s0_4;
    void *temp_s3;
    void *temp_s4;
    void *temp_s7;
    s16 *direction_x_table;

    work_s5 = (s32) arg2;

    direction_x_table = D_8006CCD8;
    temp_s7 = M2C_FIELD(arg0, void **, 0);
    temp_a1 = M2C_FIELD(arg0, s16 *, 0xA);
    temp_fp = M2C_FIELD(temp_s7, void **, -0x14);

    temp_s2 = (u16) M2C_FIELD(temp_s7, u16 *, 0x2A) >> 8;
    temp_a0 = temp_s2 & 0xE;
    sp6C = *(s16 *)((u8 *)direction_x_table + temp_a0);
    sp68 = temp_s7 - 0x20;
    temp_a0_2 = *(s16 *)((u8 *)D_8006CCE8 + temp_a0);
    sp70 = (s32) temp_a0_2;
    if ((u32) temp_a1 >= 5) {
        goto jt_end;
    }
    {
        static void *const jt_keep[] = {
            &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4
        };
        (void) jt_keep;
        goto *D_80024008[(u32) temp_a1];
    }
jt_c0:
        if (*M2C_FIELD(arg0, u16 **, 4) & 0x80) {
            temp_a1_2 = M2C_FIELD(sp68, void **, 0xC);
            if (func_8003DE58(M2C_FIELD(temp_a1_2, s32 *, 8), temp_a1_2, &frame.sp38, 0) == 0) {
                frame.sp3A = 0;
                frame.sp38 = 0;
                var_v1 = 0;
                if (M2C_FIELD(temp_fp, u16 *, 0x14) & 0x8000) {
                    var_v1 = -0x30;
                }
                frame.sp3C = var_v1;
            }
            M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(M2C_FIELD(sp68, void **, 8), s32 *, 0) + (frame.sp38 << 0x10));
            M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(M2C_FIELD(sp68, void **, 8), s32 *, 4) + (frame.sp3A << 0x10));
            M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(M2C_FIELD(sp68, void **, 8), s32 *, 8) + (frame.sp3C << 0x10));
            temp_s4 = arg0 - 0x20;
            func_8004491C(temp_s4, D_80045340);
            M2C_FIELD(work_s5, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(work_s5, s16 *, 0x1C) = 0x1000;
            page_a = &D_800DEBD8;
            M2C_FIELD(work_s5, u8 **, 0) = page_a;
            page_v = M2C_FIELD(page_a, s32 *, 4);
            page_c = 0x808080;
            ASM_SCHED_BARRIER();
            M2C_FIELD(work_s5, s32 *, 0xC) = page_c;
            M2C_FIELD(work_s5, s8 *, 4) = 0;
            M2C_FIELD(work_s5, s8 *, 5) = 0;
            M2C_FIELD(work_s5, s16 *, 0x10) = 0x20;
            M2C_FIELD(work_s5, s32 *, 8) = page_v;
            M2C_FIELD(work_s5, u16 *, 0x14) = (u16) (M2C_FIELD(work_s5, u16 *, 0x14) | 0xC);
            temp_v0 = func_800A05A4(temp_s7, M2C_FIELD(temp_fp, u8 *, 0x24), M2C_FIELD(temp_fp, u8 *, 0x25), M2C_FIELD(temp_s7, s16 *, 0x2A), (s16) func_800A3820(5, page_v));
            M2C_FIELD(temp_s7, s32 *, 0x60) = temp_v0;
            if (temp_v0 == 0) {
                move_count = 0;
                move_y = 0;
                work_s5 = 0;
                while (move_count < func_800A3820(5)) {
                    shift_x = (M2C_FIELD(temp_fp, u8 *, 0x24) + work_s5) << 6;
                    ASM_KEEP_NV(shift_x);
                    temp_s1 = shift_x + 0x20;
                    shift_y = (M2C_FIELD(temp_fp, u8 *, 0x25) + move_y) << 6;
                    ASM_KEEP_NV(shift_y);
                    ysum = shift_y + 0x20;
                    temp_s0 = (u16) ysum;
                    if ((func_800A4688(temp_s1, temp_s0, func_800BCB04(temp_s1, temp_s0, -0x400), M2C_FIELD(temp_s7, s16 *, 0x2A), M2C_FIELD(temp_s7, s32 *, 0x60)) << 0x10) != 0) {
                        break;
                    }
                    move_y += sp70;
                    ASM_KEEP(ysum);
                    move_count += 1;
                    work_s5 += sp6C;
                }
                M2C_FIELD(temp_s7, u8 *, 0x72) = (u8) (M2C_FIELD(temp_fp, u8 *, 0x24) + (sp6C * move_count));
                M2C_FIELD(temp_s7, u8 *, 0x73) = (u8) (M2C_FIELD(temp_fp, u8 *, 0x25) + (sp70 * move_count));
            } else {
                temp_s4 = temp_v0 - 0x20;
                temp_s0_2 = M2C_FIELD(temp_s4, void **, 0xC);
                ASM_USE_NV(temp_fp);
                if ((M2C_FIELD(temp_s0_2, u16 *, 0x14) & 0x8000) && (M2C_FIELD(work_s5, u16 *, 0x14) & 0x8000)) {
                    func_8009CE1C(M2C_FIELD(temp_s7, s32 *, 0x60), 8, M2C_FIELD(arg0, u8 *, 9), 2, (s32) M2C_FIELD(temp_s7, s16 *, 0x2A), temp_s7, 2);
                    M2C_FIELD(arg0, s16 *, 0xA) = 4;
                    goto jt_end;
                }
                M2C_FIELD(temp_s7, u8 *, 0x72) = (u8) M2C_FIELD(temp_s0_2, u8 *, 0x24);
                M2C_FIELD(temp_s7, u8 *, 0x73) = (u8) M2C_FIELD(temp_s0_2, u8 *, 0x25);
            }
            byte_x = M2C_FIELD(temp_s7, s8 *, 0x72);

            frame.sp22 = (byte_x << 6) + 0x20;
            byte_x = M2C_FIELD(temp_s7, s8 *, 0x73);

            frame.sp26 = (byte_x << 6) + 0x20;
            if (M2C_FIELD(temp_s7, s32 *, 0x60) == 0) {
                temp_v0_2 = func_800BCB04((u16) frame.sp22, (u16) frame.sp26, (s16) (M2C_FIELD(M2C_FIELD(sp68, void **, 8), u16 *, 0xA) - 0x30));
                frame.u28.half.sp2A = temp_v0_2;
                if (temp_v0_2 >= 0x200) {
                    frame.u28.half.sp2A = M2C_FIELD(M2C_FIELD(sp68, void **, 8), u16 *, 0xA);
                }
                frame.u28.half.sp2A -= 0x30;
            } else {
                frame.u28.half.sp2A = M2C_FIELD(M2C_FIELD(temp_s4, void **, 8), u16 *, 0xA) - 0x28;
            }
            a1v = frame.sp22;
            sub_x = M2C_FIELD(arg1, s16 *, 2);
            a0v = frame.sp26;
            sub_y = M2C_FIELD(arg1, s16 *, 6);
            temp_s1_2 = a1v - sub_x;
            temp_s2 = a0v - sub_y;
            ASM_SET(a1v);
            ASM_SET(a0v);
            var_s3_2 = temp_s1_2;
            if (temp_s1_2 < 0) {
                var_s3_2 = 0 - var_s3_2;
            }
            var_v1_2 = __builtin_abs(temp_s2);
            if (var_s3_2 < var_v1_2) {
                var_s3_2 = var_v1_2;
            }
            ASM_SCHED_BARRIER();
            var_v1_3 = 0;
            temp_a0_3 = var_s3_2 << 0x10;
            M2C_FIELD(arg0, u16 *, 0x50) = 0U;
            if (temp_a0_3 > 0) {
                do {
                    ap = arg0;
                    arg0 = ap;
                    var_v1_3 += 0xD6666;
                    M2C_FIELD(arg0, u16 *, 0x50) = (u16) (M2C_FIELD(arg0, u16 *, 0x50) + 1);
                } while (var_v1_3 < temp_a0_3);
            }
            ASM_USE_NV(var_s3_2);
            var_s3_2 = 0;
            temp_v0_3 = (s16) M2C_FIELD(arg0, u16 *, 0x50);
            var_v1_4 = 1;
            if (temp_v0_3 > 0) {
                bound_x = temp_v0_3;
                ASM_KEEP_NV(var_s3_2);
                ASM_KEEP_NV(var_v1_4);
                var_s3_3 = var_s3_2 + var_v1_4;
                do {
                    var_v1_4 += 1;
                    var_s3_3 += var_v1_4;
                } while (bound_x >= var_v1_4);
                var_s3_2 = var_s3_3 - var_v1_4;
            }
            temp_scale = (s16) M2C_FIELD(arg0, u16 *, 0x50) * 0x66666;
            prod3 = sp6C * temp_scale;
            temp_lo = (s32) ((temp_s1_2 << 0x10) - prod3) / var_s3_2;
            M2C_FIELD(arg0, s32 *, 0x44) = temp_lo;
            temp_scale = (s16) M2C_FIELD(arg0, u16 *, 0x50) * 0x66666;
            quotient_y = (s32) ((s32) ((temp_s2 << 0x10) - (sp70 * temp_scale)) / var_s3_2);
            M2C_FIELD(arg0, s32 *, 0x48) = quotient_y;
            M2C_FIELD(arg0, s32 *, 0x4C) = (s32) ((s32) ((s32) frame.u28.sp28 - M2C_FIELD(arg1, s32 *, 8)) / var_s3_2);
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((sp6C * 0x66666) + ((s16) M2C_FIELD(arg0, u16 *, 0x50) * M2C_FIELD(arg0, s32 *, 0x44)));
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((sp70 * 0x66666) + ((s16) M2C_FIELD(arg0, u16 *, 0x50) * M2C_FIELD(arg0, s32 *, 0x48)));
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) ((s16) M2C_FIELD(arg0, u16 *, 0x50) * M2C_FIELD(arg0, s32 *, 0x4C));
            M2C_FIELD(arg0, u16 *, 0x52) = (u16) M2C_FIELD(arg0, u16 *, 0x50);
            func_800A56E0(0x300, temp_lo);
            M2C_FIELD(arg0, s16 *, 0xA) += 1;
            goto jt_end;
        }
        goto jt_end;
jt_c1:
        var_s1 = 0x14;
        state1_tex = D_800DEC28;
loop_39:
        temp_s4 = func_8003FD64(0x312, D_80083498);
        if (temp_s4 != NULL) {
            temp_s0_3 = M2C_FIELD(temp_s4, void **, 0xC);
            M2C_FIELD(temp_s4, M2C_UNK **, 0x10) = &D_80024D44;
            frame.sp60 = 0 - (func_80069EF8() & 0x1FF);
            frame.sp64 = 0;
            frame.sp62 = 0;
            frame.sp40 = &frame.sp60;
            frame.sp44 = &frame.sp60;
            temp_v1 = (s16) M2C_FIELD(arg0, u16 *, 0x52) - (s16) M2C_FIELD(arg0, u16 *, 0x50);
            temp_a0_4 = temp_v1 * 8;
            temp_a0_9 = 0x300 - temp_a0_4;
            temp_s2 = temp_a0_9 - (temp_v1 << 5);
            temp_s3 = temp_s4 + 0x20;
            if (temp_s2 < 0x40) {
                temp_s2 = 0x40;
            }
            frame.sp48 = (func_80069EF8() & 0xFF) - 0x80;
            frame.sp4C = (func_80069EF8() & 0xFF) - 0x80;
            h48_x = frame.sp48;
            if (h48_x <= 0) {
                tmp48_x = h48_x - temp_s2;
            } else {
                tmp48_x = h48_x + temp_s2;
            }
            h48_x = frame.sp4C;
            frame.sp48 = tmp48_x;
            h2a_x = M2C_FIELD(temp_s7, s16 *, 0x2A);
            if (h48_x <= 0) {
                tmp48_x = h2a_x - temp_s2;
            } else {
                tmp48_x = temp_s2 + h2a_x;
            }
            var_v0 = h48_x + tmp48_x;
            frame.sp4C = var_v0;
            frame.sp50 = 0;
            frame.sp52 = 0;
            frame.sp54 = 0;
            frame.sp58 = 1;
            frame.sp5A = 0;
            func_800DBA90(&frame.sp40);
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 8), s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + (((func_80069EF8() & 0x1FF) - 0xFF) << 9));
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 8), s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + (((func_80069EF8() & 0x1FF) - 0xFF) << 9));
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 8), s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + (((func_80069EF8() & 0x1FF) - 0xFF) << 9));
            temp_a1_3 = M2C_FIELD(temp_s4, void **, 8);
            M2C_FIELD(temp_a1_3, s32 *, 0) = (s32) (M2C_FIELD(temp_a1_3, s32 *, 0) + ((frame.sp60 << 0xC) + (sp6C << 0x15)));
            temp_a1_4 = M2C_FIELD(temp_s4, void **, 8);
            M2C_FIELD(temp_a1_4, s32 *, 4) = (s32) (M2C_FIELD(temp_a1_4, s32 *, 4) + ((frame.sp62 << 0xC) + (sp70 << 0x15)));
            temp_a0_7 = M2C_FIELD(temp_s4, void **, 8);
            M2C_FIELD(temp_a0_7, s32 *, 8) = (s32) (M2C_FIELD(temp_a0_7, s32 *, 8) + (frame.sp64 << 0xC));
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 8), s32 *, 0xC) = (s32) ((s32) M2C_FIELD(arg1, s32 *, 0xC) >> 3);
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 8), s32 *, 0x10) = (s32) ((s32) M2C_FIELD(arg1, s32 *, 0x10) >> 3);
            M2C_FIELD(M2C_FIELD(temp_s4, void **, 8), s32 *, 0x14) = (s32) ((s32) M2C_FIELD(arg1, s32 *, 0x14) >> 3);
            M2C_FIELD(temp_s0_3, s16 *, 0x1E) = 0x800;
            M2C_FIELD(temp_s0_3, s16 *, 0x1C) = 0x800;
            M2C_FIELD(temp_s0_3, s16 *, 0x10) = 0x60;
            M2C_FIELD(temp_s0_3, u8 **, 0) = state1_tex;
            M2C_FIELD(temp_s0_3, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0_3, u16 *, 0x14) | 0xC);
            M2C_FIELD(temp_s0_3, s32 *, 8) = (s32) M2C_FIELD(state1_tex, s32 *, 4);
            M2C_FIELD(temp_s0_3, s8 *, 4) = 0;
            M2C_FIELD(temp_s0_3, s8 *, 5) = 0;
            M2C_FIELD(temp_s0_3, s32 *, 0xC) = 0x808080;
            M2C_FIELD(temp_s3, void **, 0) = arg0;
            M2C_FIELD(temp_s3, s16 *, 0x48) = (s16) (func_80069EF8() & 3);
            M2C_FIELD(temp_s3, s16 *, 0x4C) = 0;
            goto block_49;
        }
block_49:
        var_s1 -= 1;
        if (var_s1 < 0) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (M2C_FIELD(arg1, s32 *, 0xC) - M2C_FIELD(arg0, s32 *, 0x44));
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (M2C_FIELD(arg1, s32 *, 0x10) - M2C_FIELD(arg0, s32 *, 0x48));
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) - M2C_FIELD(arg0, s32 *, 0x4C));
            M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
            M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
            M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
            func_800478B8((void *) work_s5);
            temp_v1_2 = M2C_FIELD(work_s5, u16 *, 0x14);
            if (temp_v1_2 & 0x6000) {
                M2C_FIELD(work_s5, u16 *, 0x14) = (u16) (temp_v1_2 & 0x9FFF);
                page_e = D_800DEC00;
                M2C_FIELD(work_s5, u8 **, 0) = page_e;
                page_ev = M2C_FIELD(page_e, s32 *, 4);
                M2C_FIELD(work_s5, s8 *, 4) = 0;
                M2C_FIELD(work_s5, s8 *, 5) = 0;
                M2C_FIELD(work_s5, s32 *, 8) = page_ev;
            }
            temp_a0_8 = M2C_FIELD(arg0, u16 *, 0x50) - 1;
            M2C_FIELD(arg0, u16 *, 0x50) = temp_a0_8;
            var_v0 = M2C_FIELD(arg1, s16 *, 2);
            if (var_v0 < 0) {
                var_v0 += 0x3F;
            }
            if ((var_v0 >> 6) == (s8) M2C_FIELD(temp_s7, u8 *, 0x72)) {
                var_v0_2 = M2C_FIELD(arg1, s16 *, 6);
                if (var_v0_2 < 0) {
                    var_v0_2 += 0x3F;
                }
                if (((var_v0_2 >> 6) != (s8) M2C_FIELD(temp_s7, u8 *, 0x73)) || ((s16) temp_a0_8 >= 0)) {
                    goto block_59;
                }
                goto block_60;
            }
block_59:
            if ((s16) M2C_FIELD(arg0, u16 *, 0x50) < -0x20) {
block_60:
                if (M2C_FIELD(temp_s7, s32 *, 0x60) == 0) {
                    M2C_FIELD(arg0, s16 *, 0xA) = 3;
                    goto jt_end;
                }
                page_b = (u8 *) &D_800DEB70;
                M2C_FIELD(work_s5, u8 **, 0) = page_b;
                page_w = M2C_FIELD(page_b, s32 *, 4);
                M2C_FIELD(work_s5, s8 *, 4) = 0;
                M2C_FIELD(work_s5, s8 *, 5) = 0;
                M2C_FIELD(work_s5, s32 *, 0xC) = 0xC0C0C0;
                M2C_FIELD(work_s5, s16 *, 0x10) = 0x20;
                M2C_FIELD(work_s5, s32 *, 8) = page_w;
                byte_x = M2C_FIELD(temp_s7, s8 *, 0x72);

                M2C_FIELD(arg1, s16 *, 2) = (s16) ((byte_x << 6) + 0x20);
                byte_y = M2C_FIELD(temp_s7, s8 *, 0x73);
                M2C_FIELD(arg1, s32 *, 0x14) = 0;
                M2C_FIELD(arg1, s32 *, 0x10) = 0;
                M2C_FIELD(arg1, s32 *, 0xC) = 0;
                M2C_FIELD(arg1, s16 *, 6) = (s16) ((byte_y << 6) + 0x20);
                M2C_FIELD(arg0, s16 *, 0xA) += 1;
                goto jt_end;
            }
        } else {
            goto loop_39;
        }
        goto jt_end;
jt_c2:
        func_800478B8((void *) work_s5);
        if (M2C_FIELD(work_s5, u16 *, 0x14) & 0x6000) {
            if (M2C_FIELD(temp_s7, s32 *, 0x60) != 0) {
                func_8009CE1C(M2C_FIELD(temp_s7, s32 *, 0x60), 0xA, M2C_FIELD(arg0, u8 *, 9), 2, (s32) M2C_FIELD(temp_s7, s16 *, 0x2A), temp_s7, 2);
                var_s1_2 = 0x50;
                do {
                    temp_s4 = func_8003FD64(0x312, D_80083498);
                    if (temp_s4 != NULL) {
                        temp_s0_4 = M2C_FIELD(temp_s4, void **, 0xC);
                        M2C_FIELD(temp_s4, M2C_UNK **, 0x10) = &D_80024E98;
                        M2C_FIELD(M2C_FIELD(temp_s4, void **, 8), s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xD));
                        M2C_FIELD(M2C_FIELD(temp_s4, void **, 8), s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xD));
                        M2C_FIELD(M2C_FIELD(temp_s4, void **, 8), s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xC));
                        temp_a0_11 = M2C_FIELD(temp_s4, void **, 8);
                        M2C_FIELD(temp_a0_11, s32 *, 0xC) = (s32) ((s32) (M2C_FIELD(arg1, s32 *, 0) - M2C_FIELD(temp_a0_11, s32 *, 0)) >> 3);
                        temp_a0_12 = M2C_FIELD(temp_s4, void **, 8);
                        M2C_FIELD(temp_a0_12, s32 *, 0x10) = (s32) ((s32) (M2C_FIELD(arg1, s32 *, 4) - M2C_FIELD(temp_a0_12, s32 *, 4)) >> 3);
                        M2C_FIELD(M2C_FIELD(temp_s4, void **, 8), s32 *, 0x14) = (s32) (0 - ((func_80069EF8() & 0x3FF) << 9));
                        M2C_FIELD(temp_s0_4, s16 *, 0x1E) = 0x800;
                        M2C_FIELD(temp_s0_4, s16 *, 0x1C) = 0x800;
                        M2C_FIELD(temp_s0_4, s16 *, 0x10) = 0x20;
                        page_d = D_800DEC28;
                        M2C_FIELD(temp_s0_4, u8 **, 0) = page_d;
                        M2C_FIELD(temp_s0_4, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0_4, u16 *, 0x14) | 0xC);
                        page_dv = M2C_FIELD(page_d, s32 *, 4);
                        M2C_FIELD(temp_s0_4, s8 *, 4) = 0;
                        M2C_FIELD(temp_s0_4, s8 *, 5) = 0;
                        M2C_FIELD(temp_s0_4, s32 *, 0xC) = 0x808080;
                        M2C_FIELD(temp_s0_4, s32 *, 8) = page_dv;
                        M2C_FIELD(temp_s4, void **, 0x20) = arg0;
                        temp_s3 = temp_s4 + 0x20;
                        M2C_FIELD(temp_s3, s16 *, 0x48) = (s16) (func_80069EF8() & 3);
                    }
                    var_s1_2 -= 1;
                } while (var_s1_2 >= 0);
            }
            M2C_FIELD(arg0, s16 *, 0xA) += 1;
            goto jt_end;
        }
        goto jt_end;
jt_c3:
        M2C_FIELD(work_s5, s32 *, 0xC) = (s32) (M2C_FIELD(work_s5, s32 *, 0xC) + 0xFFEFEFF0);
        if ((u8) M2C_FIELD(work_s5, s32 *, 0xC) == 0) {
            M2C_FIELD(arg0, s16 *, 0xA) += 1;
            goto jt_end;
        }
        goto jt_end;
jt_c4:
        temp_v1_3 = M2C_FIELD(arg0, s32 *, 0xC);
        if (temp_v1_3 & 0x8000) {
            M2C_FIELD(arg0, s32 *, 0xC) = temp_v1_3 & 0xFFFF7FFF;
            goto jt_end;
        }
        *D_8008346C = 0;
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        M2C_FIELD(D_800814A0, s32 *, 0) = (s32) (M2C_FIELD(D_800814A0, s32 *, 0) | 0x8000);
jt_end:
        return;
}
