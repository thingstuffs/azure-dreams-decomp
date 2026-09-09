#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8182C800_0_pre {
    u16 unk_00;
} S_8182C800_0_pre;   /* the 0x2 bytes before arg0 in BODY_NAME, addressed as arg0[-1] */


typedef struct S_8182C800_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8182C800_1_pre;   /* the 0x14 bytes before temp_s7 in BODY_NAME, addressed as temp_s7[-1] */

typedef struct S_8182C800_1 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    s32 unk_60;
    u8 pad_64[0xE];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_8182C800_1;   /* temp_s7 in BODY_NAME */

typedef struct S_8182C800_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_8182C800_2;   /* sp68 in BODY_NAME */

typedef struct S_8182C800_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8182C800_3;   /* temp_a1_2 in BODY_NAME */

typedef struct S_8182C800_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8182C800_4;   /* temp_fp in BODY_NAME */

typedef struct S_8182C800_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8182C800_5;   /* arg1 in BODY_NAME */

typedef struct S_8182C800_6 {
    u8 * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8182C800_6;   /* work_s5 in BODY_NAME */

typedef struct S_8182C800_7 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_7;   /* page_a in BODY_NAME */

typedef struct S_8182C800_8 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_8182C800_8;   /* temp_s4 in BODY_NAME */

typedef struct S_8182C800_9 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8182C800_9;   /* temp_s0_2 in BODY_NAME */

typedef struct S_8182C800_10 {
    s32 unk_00;
} S_8182C800_10;   /* temp_a1_3 in BODY_NAME */

typedef struct S_8182C800_11 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_11;   /* temp_a1_4 in BODY_NAME */

typedef struct S_8182C800_12 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8182C800_12;   /* temp_a0_7 in BODY_NAME */

typedef struct S_8182C800_13 {
    u8 * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8182C800_13;   /* temp_s0_3 in BODY_NAME */

typedef struct S_8182C800_14 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_14;   /* state1_tex in BODY_NAME */

typedef struct S_8182C800_15 {
    void * unk_00;
    u8 pad_04[0x44];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_8182C800_15;   /* temp_s3 in BODY_NAME */

typedef struct S_8182C800_16 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_16;   /* page_e in BODY_NAME */

typedef struct S_8182C800_17 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_17;   /* page_b in BODY_NAME */

typedef struct S_8182C800_18 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_8182C800_18;   /* temp_a0_11 in BODY_NAME */

typedef struct S_8182C800_19 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_8182C800_19;   /* temp_a0_12 in BODY_NAME */

typedef struct S_8182C800_20 {
    u8 * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8182C800_20;   /* temp_s0_4 in BODY_NAME */

typedef struct S_8182C800_21 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8182C800_21;   /* page_d in BODY_NAME */

typedef struct S_8182C800_22 {
    s32 unk_00;
} S_8182C800_22;   /* D_800814A0 in BODY_NAME */

typedef struct S_8182C800_23 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_8182C800_23;   /* ((S_8182C800_2 *)sp68)->unk_08 in BODY_NAME */

typedef struct S_8182C800_24 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8182C800_24;   /* ((S_8182C800_8 *)temp_s4)->unk_08 in BODY_NAME */


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
    S_8182C800_2 *sp68;
    s32 sp6C;
    s32 sp70;
    s32 byte_x;
    register s32 shift_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 shift_y;
    s32 h2a_x;
    register s32 sub_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 sub_y;
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
    M2C_UNK temp_lo;
    register s32 temp_s1_2 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 temp_s2;
    s32 temp_v0;
    s32 quotient_y;
    s32 temp_scale;
    s32 temp_v1;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s3;
    register s32 var_s3_2 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 var_s3_3;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    register s32 move_count ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 work_s5;
    s32 move_y;
    u8 *state1_tex;
    u16 temp_a0_8;
    s32 ysum;
    s32 temp_s0;
    register u16 temp_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 temp_v1_2;
    S_8182C800_18 *temp_a0_11;
    S_8182C800_19 *temp_a0_12;
    S_8182C800_12 *temp_a0_7;
    S_8182C800_3 *temp_a1_2;
    S_8182C800_10 *temp_a1_3;
    S_8182C800_11 *temp_a1_4;
    S_8182C800_4 *temp_fp;
    register S_8182C800_9 *temp_s0_2 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register S_8182C800_13 *temp_s0_3 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_8182C800_20 *temp_s0_4;
    S_8182C800_15 *temp_s3;
    void *temp_s4;
    void *temp_s7;
    s16 *direction_x_table;

    work_s5 = (s32) arg2;

    direction_x_table = D_8006CCD8;
    temp_s7 = ((Rec_D_800E3D7C *)arg0)->unk_00.at00_pv.v;
    temp_a1 = ((Rec_D_800E3D7C *)arg0)->unk_08.at02_s16.v;
    temp_fp = ((S_8182C800_1_pre *)temp_s7)[-1].unk_00;

    temp_s2 = (u16) ((S_8182C800_1 *)temp_s7)->unk_2A.s >> 8;
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
        if (*((Rec_D_800E3D7C *)arg0)->unk_04.at00_pu16.v & 0x80) {
            temp_a1_2 = sp68->unk_0C;
            if (func_8003DE58(temp_a1_2->unk_08, temp_a1_2, &frame.sp38, 0) == 0) {
                frame.sp3A = 0;
                frame.sp38 = 0;
                var_v1 = 0;
                if (temp_fp->unk_14 & 0x8000) {
                    var_v1 = -0x30;
                }
                frame.sp3C = var_v1;
            }
            ((S_8182C800_5 *)arg1)->unk_00.at00.v = (s32) (((S_8182C800_23 *)(sp68->unk_08))->unk_00 + (frame.sp38 << 0x10));
            ((S_8182C800_5 *)arg1)->unk_04.at00.v = (s32) (((S_8182C800_23 *)(sp68->unk_08))->unk_04 + (frame.sp3A << 0x10));
            ((S_8182C800_5 *)arg1)->unk_08 = (s32) (((S_8182C800_23 *)(sp68->unk_08))->unk_08.at00.v + (frame.sp3C << 0x10));
            temp_s4 = arg0 - 0x20;
            func_8004491C(temp_s4, D_80045340);
            ((S_8182C800_6 *)work_s5)->unk_1E = 0x1000;
            ((S_8182C800_6 *)work_s5)->unk_1C = 0x1000;
            page_a = &D_800DEBD8;
            ((S_8182C800_6 *)work_s5)->unk_00 = page_a;
            page_v = ((S_8182C800_7 *)page_a)->unk_04;
            page_c = 0x808080;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            ((S_8182C800_6 *)work_s5)->unk_0C = page_c;
            ((S_8182C800_6 *)work_s5)->unk_04 = 0;
            ((S_8182C800_6 *)work_s5)->unk_05 = 0;
            ((S_8182C800_6 *)work_s5)->unk_10 = 0x20;
            ((S_8182C800_6 *)work_s5)->unk_08 = page_v;
            ((S_8182C800_6 *)work_s5)->unk_14 = (u16) (((S_8182C800_6 *)work_s5)->unk_14 | 0xC);
            temp_v0 = func_800A05A4(temp_s7, temp_fp->unk_24, temp_fp->unk_25, ((S_8182C800_1 *)temp_s7)->unk_2A.u, (s16) func_800A3820(5, page_v));
            ((S_8182C800_1 *)temp_s7)->unk_60 = temp_v0;
            if (temp_v0 == 0) {
                move_count = 0;
                move_y = 0;
                work_s5 = 0;
                while (move_count < func_800A3820(5)) {
                    shift_x = (temp_fp->unk_24 + work_s5) << 6;
                    ASM_KEEP_NV(shift_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    temp_s1 = shift_x + 0x20;
                    shift_y = (temp_fp->unk_25 + move_y) << 6;
                    ysum = shift_y + 0x20;
                    temp_s0 = (u16) ysum;
                    if ((func_800A4688(temp_s1, temp_s0, func_800BCB04(temp_s1, temp_s0, -0x400), ((S_8182C800_1 *)temp_s7)->unk_2A.u, ((S_8182C800_1 *)temp_s7)->unk_60) << 0x10) != 0) {
                        break;
                    }
                    move_y += sp70;
                    ASM_KEEP(ysum);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                    move_count += 1;
                    work_s5 += sp6C;
                }
                ((S_8182C800_1 *)temp_s7)->unk_72.s = (u8) (temp_fp->unk_24 + (sp6C * move_count));
                ((S_8182C800_1 *)temp_s7)->unk_73.s = (u8) (temp_fp->unk_25 + (sp70 * move_count));
            } else {
                temp_s4 = temp_v0 - 0x20;
                temp_s0_2 = ((S_8182C800_8 *)temp_s4)->unk_0C;
                if ((temp_s0_2->unk_14 & 0x8000) && (((S_8182C800_6 *)work_s5)->unk_14 & 0x8000)) {
                    func_8009CE1C(((S_8182C800_1 *)temp_s7)->unk_60, 8, ((Rec_D_800E3D7C *)arg0)->unk_08.at01_u8.v, 2, (s32) ((S_8182C800_1 *)temp_s7)->unk_2A.u, temp_s7, 2);
                    ((Rec_D_800E3D7C *)arg0)->unk_08.at02_s16.v = 4;
                    goto jt_end;
                }
                ((S_8182C800_1 *)temp_s7)->unk_72.s = (u8) temp_s0_2->unk_24;
                ((S_8182C800_1 *)temp_s7)->unk_73.s = (u8) temp_s0_2->unk_25;
            }
            byte_x = ((S_8182C800_1 *)temp_s7)->unk_72.u;

            frame.sp22 = (byte_x << 6) + 0x20;
            byte_x = ((S_8182C800_1 *)temp_s7)->unk_73.u;

            frame.sp26 = (byte_x << 6) + 0x20;
            if (((S_8182C800_1 *)temp_s7)->unk_60 == 0) {
                temp_v0_2 = func_800BCB04((u16) frame.sp22, (u16) frame.sp26, (s16) (((S_8182C800_23 *)(sp68->unk_08))->unk_08.at02.v - 0x30));
                frame.u28.half.sp2A = temp_v0_2;
                if (temp_v0_2 >= 0x200) {
                    frame.u28.half.sp2A = ((S_8182C800_23 *)(sp68->unk_08))->unk_08.at02.v;
                }
                frame.u28.half.sp2A -= 0x30;
            } else {
                frame.u28.half.sp2A = ((S_8182C800_24 *)(((S_8182C800_8 *)temp_s4)->unk_08))->unk_08.at02.v - 0x28;
            }
            a1v = frame.sp22;
            sub_x = ((S_8182C800_5 *)arg1)->unk_00.at02.v;
            a0v = frame.sp26;
            sub_y = ((S_8182C800_5 *)arg1)->unk_04.at02.v;
            temp_s1_2 = a1v - sub_x;
            temp_s2 = a0v - sub_y;
            ASM_SET(a1v);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            var_s3_2 = temp_s1_2;
            if (temp_s1_2 < 0) {
                var_s3_2 = 0 - var_s3_2;
            }
            var_v1_2 = __builtin_abs(temp_s2);
            if (var_s3_2 < var_v1_2) {
                var_s3_2 = var_v1_2;
            }
            var_v1_3 = 0;
            temp_a0_3 = var_s3_2 << 0x10;
            ((Rec_D_800E3D7C *)arg0)->unk_50.at00_u16.v = 0U;
            if (temp_a0_3 > 0) {
                do {
                    ap = arg0;
                    arg0 = ap;
                    var_v1_3 += 0xD6666;
                    ((Rec_D_800E3D7C *)arg0)->unk_50.at00_u16.v = (u16) (((Rec_D_800E3D7C *)arg0)->unk_50.at00_u16.v + 1);
                } while (var_v1_3 < temp_a0_3);
            }
            ASM_USE_NV(var_s3_2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            var_s3_2 = 0;
            temp_v0_3 = (s16) ((Rec_D_800E3D7C *)arg0)->unk_50.at00_u16.v;
            var_v1_4 = 1;
            if (temp_v0_3 > 0) {
                bound_x = temp_v0_3;
                ASM_KEEP_NV(var_s3_2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                ASM_KEEP_NV(var_v1_4);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                var_s3_3 = var_s3_2 + var_v1_4;
                do {
                    var_v1_4 += 1;
                    var_s3_3 += var_v1_4;
                } while (bound_x >= var_v1_4);
                var_s3_2 = var_s3_3 - var_v1_4;
            }
            temp_scale = (s16) ((Rec_D_800E3D7C *)arg0)->unk_50.at00_u16.v * 0x66666;
            prod3 = sp6C * temp_scale;
            temp_lo = (s32) ((temp_s1_2 << 0x10) - prod3) / var_s3_2;
            ((Rec_D_800E3D7C *)arg0)->unk_44.at00_s32.v = temp_lo;
            temp_scale = (s16) ((Rec_D_800E3D7C *)arg0)->unk_50.at00_u16.v * 0x66666;
            quotient_y = (s32) ((s32) ((temp_s2 << 0x10) - (sp70 * temp_scale)) / var_s3_2);
            ((Rec_D_800E3D7C *)arg0)->unk_48.at00_s32.v = quotient_y;
            ((Rec_D_800E3D7C *)arg0)->unk_4C.as_s32 = (s32) ((s32) ((s32) frame.u28.sp28 - ((S_8182C800_5 *)arg1)->unk_08) / var_s3_2);
            ((S_8182C800_5 *)arg1)->unk_0C = (s32) ((sp6C * 0x66666) + ((s16) ((Rec_D_800E3D7C *)arg0)->unk_50.at00_u16.v * ((Rec_D_800E3D7C *)arg0)->unk_44.at00_s32.v));
            ((S_8182C800_5 *)arg1)->unk_10 = (s32) ((sp70 * 0x66666) + ((s16) ((Rec_D_800E3D7C *)arg0)->unk_50.at00_u16.v * ((Rec_D_800E3D7C *)arg0)->unk_48.at00_s32.v));
            ((S_8182C800_5 *)arg1)->unk_14 = (s32) ((s16) ((Rec_D_800E3D7C *)arg0)->unk_50.at00_u16.v * ((Rec_D_800E3D7C *)arg0)->unk_4C.as_s32);
            ((Rec_D_800E3D7C *)arg0)->unk_50.at02_u16.v = (u16) ((Rec_D_800E3D7C *)arg0)->unk_50.at00_u16.v;
            func_800A56E0(0x300, temp_lo);
            ((Rec_D_800E3D7C *)arg0)->unk_08.at02_s16.v += 1;
            goto jt_end;
        }
        goto jt_end;
jt_c1:
        var_s1 = 0x14;
        state1_tex = D_800DEC28;
loop_39:
        temp_s4 = func_8003FD64(0x312, D_80083498);
        if (temp_s4 != NULL) {
            temp_s0_3 = ((S_8182C800_8 *)temp_s4)->unk_0C;
            ((S_8182C800_8 *)temp_s4)->unk_10 = &D_80024D44;
            frame.sp60 = 0 - (func_80069EF8() & 0x1FF);
            frame.sp64 = 0;
            frame.sp62 = 0;
            frame.sp40 = &frame.sp60;
            frame.sp44 = &frame.sp60;
            temp_v1 = (s16) ((Rec_D_800E3D7C *)arg0)->unk_50.at02_u16.v - (s16) ((Rec_D_800E3D7C *)arg0)->unk_50.at00_u16.v;
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
            h2a_x = ((S_8182C800_1 *)temp_s7)->unk_2A.u;
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
            ((S_8182C800_24 *)(((S_8182C800_8 *)temp_s4)->unk_08))->unk_00 = (s32) (((S_8182C800_5 *)arg1)->unk_00.at00.v + (((func_80069EF8() & 0x1FF) - 0xFF) << 9));
            ((S_8182C800_24 *)(((S_8182C800_8 *)temp_s4)->unk_08))->unk_04 = (s32) (((S_8182C800_5 *)arg1)->unk_04.at00.v + (((func_80069EF8() & 0x1FF) - 0xFF) << 9));
            ((S_8182C800_24 *)(((S_8182C800_8 *)temp_s4)->unk_08))->unk_08.at00.v = (s32) (((S_8182C800_5 *)arg1)->unk_08 + (((func_80069EF8() & 0x1FF) - 0xFF) << 9));
            temp_a1_3 = ((S_8182C800_8 *)temp_s4)->unk_08;
            temp_a1_3->unk_00 = (s32) (temp_a1_3->unk_00 + ((frame.sp60 << 0xC) + (sp6C << 0x15)));
            temp_a1_4 = ((S_8182C800_8 *)temp_s4)->unk_08;
            temp_a1_4->unk_04 = (s32) (temp_a1_4->unk_04 + ((frame.sp62 << 0xC) + (sp70 << 0x15)));
            temp_a0_7 = ((S_8182C800_8 *)temp_s4)->unk_08;
            temp_a0_7->unk_08 = (s32) (temp_a0_7->unk_08 + (frame.sp64 << 0xC));
            ((S_8182C800_24 *)(((S_8182C800_8 *)temp_s4)->unk_08))->unk_0C = (s32) ((s32) ((S_8182C800_5 *)arg1)->unk_0C >> 3);
            ((S_8182C800_24 *)(((S_8182C800_8 *)temp_s4)->unk_08))->unk_10 = (s32) ((s32) ((S_8182C800_5 *)arg1)->unk_10 >> 3);
            ((S_8182C800_24 *)(((S_8182C800_8 *)temp_s4)->unk_08))->unk_14 = (s32) ((s32) ((S_8182C800_5 *)arg1)->unk_14 >> 3);
            temp_s0_3->unk_1E = 0x800;
            temp_s0_3->unk_1C = 0x800;
            temp_s0_3->unk_10 = 0x60;
            temp_s0_3->unk_00 = state1_tex;
            temp_s0_3->unk_14 = (u16) (temp_s0_3->unk_14 | 0xC);
            temp_s0_3->unk_08 = (s32) ((S_8182C800_14 *)state1_tex)->unk_04;
            temp_s0_3->unk_04 = 0;
            temp_s0_3->unk_05 = 0;
            temp_s0_3->unk_0C = 0x808080;
            temp_s3->unk_00 = arg0;
            temp_s3->unk_48 = (s16) (func_80069EF8() & 3);
            temp_s3->unk_4C = 0;
            goto block_49;
        }
block_49:
        var_s1 -= 1;
        if (var_s1 < 0) {
            ((S_8182C800_5 *)arg1)->unk_0C = (s32) (((S_8182C800_5 *)arg1)->unk_0C - ((Rec_D_800E3D7C *)arg0)->unk_44.at00_s32.v);
            ((S_8182C800_5 *)arg1)->unk_10 = (s32) (((S_8182C800_5 *)arg1)->unk_10 - ((Rec_D_800E3D7C *)arg0)->unk_48.at00_s32.v);
            ((S_8182C800_5 *)arg1)->unk_14 = (s32) (((S_8182C800_5 *)arg1)->unk_14 - ((Rec_D_800E3D7C *)arg0)->unk_4C.as_s32);
            ((S_8182C800_5 *)arg1)->unk_00.at00.v = (s32) (((S_8182C800_5 *)arg1)->unk_00.at00.v + ((S_8182C800_5 *)arg1)->unk_0C);
            ((S_8182C800_5 *)arg1)->unk_04.at00.v = (s32) (((S_8182C800_5 *)arg1)->unk_04.at00.v + ((S_8182C800_5 *)arg1)->unk_10);
            ((S_8182C800_5 *)arg1)->unk_08 = (s32) (((S_8182C800_5 *)arg1)->unk_08 + ((S_8182C800_5 *)arg1)->unk_14);
            func_800478B8((void *) work_s5);
            temp_v1_2 = ((S_8182C800_6 *)work_s5)->unk_14;
            if (temp_v1_2 & 0x6000) {
                ((S_8182C800_6 *)work_s5)->unk_14 = (u16) (temp_v1_2 & 0x9FFF);
                page_e = D_800DEC00;
                ((S_8182C800_6 *)work_s5)->unk_00 = page_e;
                page_ev = ((S_8182C800_16 *)page_e)->unk_04;
                ((S_8182C800_6 *)work_s5)->unk_04 = 0;
                ((S_8182C800_6 *)work_s5)->unk_05 = 0;
                ((S_8182C800_6 *)work_s5)->unk_08 = page_ev;
            }
            temp_a0_8 = ((Rec_D_800E3D7C *)arg0)->unk_50.at00_u16.v - 1;
            ((Rec_D_800E3D7C *)arg0)->unk_50.at00_u16.v = temp_a0_8;
            var_v0 = ((S_8182C800_5 *)arg1)->unk_00.at02.v;
            if (var_v0 < 0) {
                var_v0 += 0x3F;
            }
            if ((var_v0 >> 6) == (s8) ((S_8182C800_1 *)temp_s7)->unk_72.s) {
                var_v0_2 = ((S_8182C800_5 *)arg1)->unk_04.at02.v;
                if (var_v0_2 < 0) {
                    var_v0_2 += 0x3F;
                }
                if (((var_v0_2 >> 6) != (s8) ((S_8182C800_1 *)temp_s7)->unk_73.s) || ((s16) temp_a0_8 >= 0)) {
                    goto block_59;
                }
                goto block_60;
            }
block_59:
            if ((s16) ((Rec_D_800E3D7C *)arg0)->unk_50.at00_u16.v < -0x20) {
block_60:
                if (((S_8182C800_1 *)temp_s7)->unk_60 == 0) {
                    ((Rec_D_800E3D7C *)arg0)->unk_08.at02_s16.v = 3;
                    goto jt_end;
                }
                page_b = (u8 *) &D_800DEB70;
                ((S_8182C800_6 *)work_s5)->unk_00 = page_b;
                page_w = ((S_8182C800_17 *)page_b)->unk_04;
                ((S_8182C800_6 *)work_s5)->unk_04 = 0;
                ((S_8182C800_6 *)work_s5)->unk_05 = 0;
                ((S_8182C800_6 *)work_s5)->unk_0C = 0xC0C0C0;
                ((S_8182C800_6 *)work_s5)->unk_10 = 0x20;
                ((S_8182C800_6 *)work_s5)->unk_08 = page_w;
                byte_x = ((S_8182C800_1 *)temp_s7)->unk_72.u;

                ((S_8182C800_5 *)arg1)->unk_00.at02.v = (s16) ((byte_x << 6) + 0x20);
                byte_y = ((S_8182C800_1 *)temp_s7)->unk_73.u;
                ((S_8182C800_5 *)arg1)->unk_14 = 0;
                ((S_8182C800_5 *)arg1)->unk_10 = 0;
                ((S_8182C800_5 *)arg1)->unk_0C = 0;
                ((S_8182C800_5 *)arg1)->unk_04.at02.v = (s16) ((byte_y << 6) + 0x20);
                ((Rec_D_800E3D7C *)arg0)->unk_08.at02_s16.v += 1;
                goto jt_end;
            }
        } else {
            goto loop_39;
        }
        goto jt_end;
jt_c2:
        func_800478B8((void *) work_s5);
        if (((S_8182C800_6 *)work_s5)->unk_14 & 0x6000) {
            if (((S_8182C800_1 *)temp_s7)->unk_60 != 0) {
                func_8009CE1C(((S_8182C800_1 *)temp_s7)->unk_60, 0xA, ((Rec_D_800E3D7C *)arg0)->unk_08.at01_u8.v, 2, (s32) ((S_8182C800_1 *)temp_s7)->unk_2A.u, temp_s7, 2);
                var_s1_2 = 0x50;
                do {
                    temp_s4 = func_8003FD64(0x312, D_80083498);
                    if (temp_s4 != NULL) {
                        temp_s0_4 = ((S_8182C800_8 *)temp_s4)->unk_0C;
                        ((S_8182C800_8 *)temp_s4)->unk_10 = &D_80024E98;
                        ((S_8182C800_24 *)(((S_8182C800_8 *)temp_s4)->unk_08))->unk_00 = (s32) (((S_8182C800_5 *)arg1)->unk_00.at00.v + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xD));
                        ((S_8182C800_24 *)(((S_8182C800_8 *)temp_s4)->unk_08))->unk_04 = (s32) (((S_8182C800_5 *)arg1)->unk_04.at00.v + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xD));
                        ((S_8182C800_24 *)(((S_8182C800_8 *)temp_s4)->unk_08))->unk_08.at00.v = (s32) (((S_8182C800_5 *)arg1)->unk_08 + (((func_80069EF8() & 0x3FF) - 0x1FF) << 0xC));
                        temp_a0_11 = ((S_8182C800_8 *)temp_s4)->unk_08;
                        temp_a0_11->unk_0C = (s32) ((s32) (((S_8182C800_5 *)arg1)->unk_00.at00.v - temp_a0_11->unk_00) >> 3);
                        temp_a0_12 = ((S_8182C800_8 *)temp_s4)->unk_08;
                        temp_a0_12->unk_10 = (s32) ((s32) (((S_8182C800_5 *)arg1)->unk_04.at00.v - temp_a0_12->unk_04) >> 3);
                        ((S_8182C800_24 *)(((S_8182C800_8 *)temp_s4)->unk_08))->unk_14 = (s32) (0 - ((func_80069EF8() & 0x3FF) << 9));
                        temp_s0_4->unk_1E = 0x800;
                        temp_s0_4->unk_1C = 0x800;
                        temp_s0_4->unk_10 = 0x20;
                        page_d = D_800DEC28;
                        temp_s0_4->unk_00 = page_d;
                        temp_s0_4->unk_14 = (u16) (temp_s0_4->unk_14 | 0xC);
                        page_dv = ((S_8182C800_21 *)page_d)->unk_04;
                        temp_s0_4->unk_04 = 0;
                        temp_s0_4->unk_05 = 0;
                        temp_s0_4->unk_0C = 0x808080;
                        temp_s0_4->unk_08 = page_dv;
                        ((S_8182C800_8 *)temp_s4)->unk_20 = arg0;
                        temp_s3 = temp_s4 + 0x20;
                        temp_s3->unk_48 = (s16) (func_80069EF8() & 3);
                    }
                    var_s1_2 -= 1;
                } while (var_s1_2 >= 0);
            }
            ((Rec_D_800E3D7C *)arg0)->unk_08.at02_s16.v += 1;
            goto jt_end;
        }
        goto jt_end;
jt_c3:
        ((S_8182C800_6 *)work_s5)->unk_0C = (s32) (((S_8182C800_6 *)work_s5)->unk_0C + 0xFFEFEFF0);
        if ((u8) ((S_8182C800_6 *)work_s5)->unk_0C == 0) {
            ((Rec_D_800E3D7C *)arg0)->unk_08.at02_s16.v += 1;
            goto jt_end;
        }
        goto jt_end;
jt_c4:
        temp_v1_3 = ((Rec_D_800E3D7C *)arg0)->unk_0C.as_s32;
        if (temp_v1_3 & 0x8000) {
            ((Rec_D_800E3D7C *)arg0)->unk_0C.as_s32 = temp_v1_3 & 0xFFFF7FFF;
            goto jt_end;
        }
        *D_8008346C = 0;
        ((S_8182C800_0_pre *)arg0)[-1].unk_00 = (u16) (((S_8182C800_0_pre *)arg0)[-1].unk_00 | 0x8000);
        ((S_8182C800_22 *)D_800814A0)->unk_00 = (s32) (((S_8182C800_22 *)D_800814A0)->unk_00 | 0x8000);
jt_end:
        return;
}
