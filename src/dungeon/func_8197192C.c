#include "common.h"

typedef struct S_8197192C_0_pre {
    u16 unk_00;
} S_8197192C_0_pre;   /* the 0x2 bytes before arg0 in func_8197192C, addressed as arg0[-1] */

typedef struct S_8197192C_0 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 unk_08;
    u8 pad_09[0x1];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x20];
    union { u16 s; s16 u; } unk_2C;   /* accessed as both */
    union { s16 s; u16 u; } unk_2E;   /* accessed as both */
    union { s16 s; u16 u; } unk_30;   /* accessed as both */
    union { s16 s; u16 u; } unk_32;   /* accessed as both */
    u16 unk_34;
    u8 pad_36[0x2];
    u16 unk_38;
    u8 pad_3A[0x12];
    union { u16 s; s16 u; } unk_4C;   /* accessed as both */
    union { u16 s; s16 u; } unk_4E;   /* accessed as both */
    union { u16 s; s16 u; } unk_50;   /* accessed as both */
    u16 unk_52;
    u16 unk_54;
    u16 unk_56;
    union { u16 s; s16 u; } unk_58;   /* accessed as both */
    union { u16 s; s16 u; } unk_5A;   /* accessed as both */
    union { u16 s; s16 u; } unk_5C;   /* accessed as both */
    u16 unk_5E;
    u16 unk_60;
    u16 unk_62;
    union { u16 s; s16 u; } unk_64;   /* accessed as both */
    union { u16 s; s16 u; } unk_66;   /* accessed as both */
    union { u16 s; s16 u; } unk_68;   /* accessed as both */
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
    union { u16 s; s16 u; } unk_70;   /* accessed as both */
    union { u16 s; s16 u; } unk_72;   /* accessed as both */
    union { u16 s; s16 u; } unk_74;   /* accessed as both */
    u16 unk_76;
    u16 unk_78;
    u16 unk_7A;
    union { u16 s; s16 u; } unk_7C;   /* accessed as both */
    union { u16 s; s16 u; } unk_7E;   /* accessed as both */
    union { u16 s; s16 u; } unk_80;   /* accessed as both */
} S_8197192C_0;   /* arg0 in func_8197192C */

typedef struct S_8197192C_1_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_8197192C_1_pre;   /* the 0x18 bytes before obj in func_8197192C, addressed as obj[-1] */

typedef struct S_8197192C_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    union { struct { void * v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_10;   /* overlapping accesses */
    u8 pad_14[0x16];
    u16 unk_2A;
    u8 pad_2C[0x6A];
    s16 unk_96;
    u8 pad_98[0xE];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x4B];
    s32 unk_F4;
} S_8197192C_1;   /* obj in func_8197192C */

typedef struct S_8197192C_2 {
    u16 unk_00;
} S_8197192C_2;   /* D_80082E86 in func_8197192C */

typedef struct S_8197192C_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8197192C_3;   /* gbase in func_8197192C */

typedef struct S_8197192C_4 {
    u16 unk_00;
} S_8197192C_4;   /* D_80025FF4 in func_8197192C */

typedef struct S_8197192C_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8197192C_5;   /* map_base in func_8197192C */

typedef struct S_8197192C_6 {
    void * unk_00;
} S_8197192C_6;   /* &D_800814A8 in func_8197192C */

typedef struct S_8197192C_7 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    u8 pad_2C[0xC];
    u16 unk_38;
    u16 unk_3A;
    u8 pad_3C[0x10];
    u16 unk_4C;
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
    u16 unk_54;
    u16 unk_56;
    u16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
    u16 unk_60;
    u16 unk_62;
} S_8197192C_7;   /* work in func_8197192C */

typedef struct S_8197192C_8 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8197192C_8;   /* part in func_8197192C */

typedef struct S_8197192C_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x40];
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
} S_8197192C_9;   /* dst in func_8197192C */

typedef struct S_8197192C_10 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8197192C_10;   /* gbase3 in func_8197192C */

typedef struct S_8197192C_11 {
    u8 pad_00[0x4C];
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
} S_8197192C_11;   /* dst2 in func_8197192C */

typedef struct S_8197192C_12 {
    u8 pad_00[0x2E94];
    u16 unk_2E94;
} S_8197192C_12;   /* status_page in func_8197192C */

typedef struct S_8197192C_13 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8197192C_13;   /* cleanup_obj in func_8197192C */

typedef struct S_8197192C_14 {
    u16 unk_00;
} S_8197192C_14;   /* ((S_8197192C_0 *)arg0)->unk_04 in func_8197192C */

typedef struct S_8197192C_15 {
    u8 pad_00[0x60];
    void * unk_60;
} S_8197192C_15;   /* ((S_8197192C_6 *)(&D_800814A8))->unk_00 in func_8197192C */



typedef struct {
    u8 bytes[12];
} Data12;

/* These data objects are present in the retail image but are not in the
 * current symbol catalog.  Keep the bindings narrow: they are not local
 * definitions, only names for the linked overlay data. */
__asm__(".set D_80024058, 0x80024058");
__asm__(".set D_80024B98, 0x80024B98");
__asm__(".set D_80024D10, 0x80024D10");
__asm__(".set D_80024544, 0x80024544");
__asm__(".set D_80025FD0, 0x80025FD0");
__asm__(".set D_80025FDC, 0x80025FDC");
__asm__(".set D_800DDC40, 0x800DDC40");

extern void *D_80024058[];
extern void *D_80024B98;
extern void *D_80024D10;
extern void *D_80024544;
extern u8 D_80045340[];
extern Data12 D_80025FD0;
extern Data12 D_80025FDC;
extern u8 D_800DDC40[];

extern void *D_800814A8[3];
extern void *D_800814A8_case0[3] __asm__("D_800814A8");
extern s32 D_800814A0[3];
extern u16 D_80082E86[5];
extern u16 D_80082E94[5];
extern void *D_80082E80[10];
extern u8 D_80083460[];
extern u8 D_80083780[12];
extern s16 D_80025FF4[5];

extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern void *func_8003DF74(void *, void *, void *, s16);
extern s32 func_80069EF8(void);
extern void func_800248A8(void *, s32, s32, s32, s32, s32, s32);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80024DD4(void *, void *, void *, s32, s32, s32);
extern void func_80024F60(void *, void *, void *, s32, s32, s32);
extern void func_80025F9C(void) __attribute__((noreturn));
extern void func_80025DAC(void) __attribute__((noreturn));

void func_8197192C(void *arg0, void *arg1, void *arg2)
{
    static void *const keep_cases[] __attribute__((used)) = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4, &&cleanup, &&done
    };
    u32 state;
    void *base2 = arg0;
    register void *base3 ASM_REG("$19") = arg1;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *base5 ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
    register u32 color0 ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u32 color1;

    (void)keep_cases;
    ASM_KEEP4_NV(base2, base3, base5, base5);   /* MATCH pin: keeps a statement from moving across a call/branch */
#define arg0 base2
#define arg1 base3
    ((S_8197192C_0 *)arg0)->unk_38 = ((S_8197192C_0 *)arg0)->unk_38 + 1;
    state = ((S_8197192C_0 *)arg0)->unk_0A.s;
    if (state >= 5) {
        goto done;
    }
    base5 = arg2;
    ASM_KEEP_NV(base5);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
#define arg2 base5
    goto *D_80024058[state];

case_0:
{
    register void *obj ASM_REG("$3") = D_800814A8_case0[0];   /* MATCH pin: keeps a constant in a register as retail does */
    register u8 *gbase ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    u16 coord_z;
    u16 heading;
    ((S_8197192C_1 *)obj)->unk_F4 = 0;
    ((S_8197192C_1 *)obj)->unk_96 = 20;
    ((S_8197192C_2 *)D_80082E86)->unk_00 = 6;
    gbase = D_80083780;
    ((S_8197192C_0 *)arg0)->unk_0A.u = ((S_8197192C_0 *)arg0)->unk_0A.u + 1;
    ((S_8197192C_0 *)arg0)->unk_7C.s = ((S_8197192C_3 *)gbase)->unk_02;
    ((S_8197192C_0 *)arg0)->unk_7E.s = ((S_8197192C_3 *)gbase)->unk_06;
    coord_z = ((S_8197192C_3 *)gbase)->unk_0A;
    ((S_8197192C_4 *)D_80025FF4)->unk_00 = 1;
    ((S_8197192C_0 *)arg0)->unk_80.s = coord_z;
    ASM_KEEP(coord_z);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if ((((S_8197192C_14 *)(((S_8197192C_0 *)arg0)->unk_04))->unk_00 & 0x80) == 0) {
        goto done;
    }
    obj = D_800814A8[0];
    ((S_8197192C_0 *)arg0)->unk_2C.s = 33;
    ((S_8197192C_1 *)obj)->unk_A6 = ((S_8197192C_1 *)obj)->unk_A6 - 1;
    ((S_8197192C_1 *)obj)->unk_A8 = ((S_8197192C_0 *)arg0)->unk_08;
    obj = D_800814A8[0];
    heading = ((S_8197192C_1 *)obj)->unk_2A;
    ((S_8197192C_0 *)arg0)->unk_0A.u = ((S_8197192C_0 *)arg0)->unk_0A.u + 1;
    ((S_8197192C_0 *)arg0)->unk_38 = 0;
    ((S_8197192C_0 *)arg0)->unk_34 = (heading >> 9) & 7;
    func_80025F9C();
}

case_1:
{
    ((S_8197192C_0 *)arg0)->unk_2C.s = ((S_8197192C_0 *)arg0)->unk_2C.s - 1;
    if ((s16)((S_8197192C_0 *)arg0)->unk_2C.s <= 0) {
        ((S_8197192C_0 *)arg0)->unk_2C.s = 16;
        ((S_8197192C_0 *)arg0)->unk_0A.u = ((S_8197192C_0 *)arg0)->unk_0A.u + 1;
        func_80025F9C();
    }
    if ((s16)((S_8197192C_0 *)arg0)->unk_2C.s == 26) {
        if (func_80053EF0(4) != 2) {
            func_800A56E0(0x300);
        } else {
            func_800A56E0(0x4300);
        }
    }

}

case_2:
{
    s32 i;
    if ((u16)(((S_8197192C_0 *)arg0)->unk_2C.s - 5) < 19) {
        void *map_base = (void *)D_80082E80;
        if (func_8003DF74(
            ((S_8197192C_5 *)map_base)->unk_08, map_base,
            (u8 *)arg0 + 0x2E, 0) != 0) {
            i = 0;
            do {
                func_800248A8((u8 *)((S_8197192C_6 *)(&D_800814A8))->unk_00 - 0x20, 0,
                              0xE04040, (func_80069EF8() & 0x3F) | 0x40,
                              ((S_8197192C_0 *)arg0)->unk_2E.s,
                              ((S_8197192C_0 *)arg0)->unk_30.s,
                              ((S_8197192C_0 *)arg0)->unk_32.s);
                i++;
            } while (i < 2);
        }
    }

    if (((S_8197192C_0 *)arg0)->unk_2C.u == 24) {
        void *map_base = (void *)D_80082E80;
        if (func_8003DF74(((S_8197192C_5 *)map_base)->unk_08, map_base,
                          (u8 *)arg0 + 0x2E, 0) != 0) {
            void *obj;
            register u8 *work ASM_REG("$16");   /* MATCH pin: retail keeps a computation the compiler would drop */
            u8 *part;
            u8 *dst;
            u8 *gbase;

            obj = func_8003FC64(0x212);
            if (obj != 0) {
                work = (u8 *)obj + 0x20;
                ((S_8197192C_7 *)work)->unk_38 = 20;
                ((S_8197192C_7 *)work)->unk_3A = 20;
                ((S_8197192C_1 *)obj)->unk_10.at00.v = (void *)&D_80024D10;
                func_8004491C(obj, D_80045340);
                part = ((S_8197192C_1 *)obj)->unk_0C;
                gbase = D_80083780;
                ((S_8197192C_8 *)part)->unk_10 = 0x60;
                ((S_8197192C_8 *)part)->unk_14 = ((S_8197192C_8 *)part)->unk_14 | 0x0C;
                dst = ((S_8197192C_1 *)obj)->unk_08;
                ((S_8197192C_9 *)dst)->unk_02 = ((S_8197192C_0 *)arg0)->unk_2E.u +
                                      ((S_8197192C_3 *)gbase)->unk_02;
                ((S_8197192C_9 *)dst)->unk_06 = ((S_8197192C_0 *)arg0)->unk_30.u +
                                      ((S_8197192C_3 *)gbase)->unk_06;
                ((S_8197192C_9 *)dst)->unk_0A = ((S_8197192C_0 *)arg0)->unk_32.u +
                                       ((S_8197192C_3 *)gbase)->unk_0A;
                part = ((S_8197192C_1 *)obj)->unk_0C;
                ((S_8197192C_8 *)part)->unk_1E = 0x1000;
                ((S_8197192C_8 *)part)->unk_1C = 0x1000;
                ((S_8197192C_8 *)part)->unk_0E = 0x20;
                ((S_8197192C_8 *)part)->unk_0D = 0x20;
                ((S_8197192C_8 *)part)->unk_0C = 0x20;
                *(Data12 *)((u8 *)obj + 0xA2) = D_80025FD0;
                ((S_8197192C_8 *)part)->unk_08 = (u8 *)obj + 0xA2;
            }
        }
    }
}

case_3:
{
    s32 index;
    s32 index2;
    s32 i;
    u8 *gbase3;
    if (((S_8197192C_0 *)arg0)->unk_2C.u >= 10) {
        goto done;
    }
    if (((S_8197192C_0 *)arg0)->unk_2C.u >= 6) {
        goto done;
    }
    if (((S_8197192C_0 *)arg0)->unk_2C.u == 3) {
        goto done;
    }
    index = (((S_8197192C_0 *)arg0)->unk_2C.u == 4);
    if (((S_8197192C_0 *)arg0)->unk_2C.u == 2) {
        index = 2;
    }
    if (((S_8197192C_0 *)arg0)->unk_2C.u == 1) {
        index = 3;
    }
    {
        void *map_base = (void *)D_80082E80;
    if (func_8003DF74(((S_8197192C_5 *)map_base)->unk_08, map_base,
                      (u8 *)arg0 + 0x2E, 0) == 0) {
        goto after_coords;
    }
    if (((S_8197192C_0 *)arg0)->unk_2C.u == 1) {
        ((S_8197192C_0 *)arg0)->unk_32.s = -12;
    }
    }
    index2 = index << 1;
    {
    register u8 *dst ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    dst = (u8 *)arg0 + ((index2 + index) << 2);
    index2++;
    {
        u32 raw_x;
        s32 origin_x;
        s32 half;
        u32 coord_page;
        raw_x = ((S_8197192C_0 *)arg0)->unk_2E.u;
        origin_x = ((S_8197192C_0 *)arg0)->unk_7C.u;
        raw_x <<= 16;
        half = (s32)raw_x >> 16;
        half += raw_x >> 31;
        ASM_KEEP(half);   /* MATCH pin: keeps a constant in a register as retail does */
        coord_page = 0x80080000;
        ASM_KEEP(coord_page);   /* MATCH pin: load-bearing for the whole function shape */
        gbase3 = (u8 *)(coord_page + 0x3780);
        ASM_KEEP_NV(gbase3);   /* MATCH pin: retail register colouring depends on it */
        half >>= 1;
        ((S_8197192C_9 *)dst)->unk_4C = (s16)(half +
            (((S_8197192C_10 *)gbase3)->unk_02 - origin_x) / 2);
    }
    ((S_8197192C_9 *)dst)->unk_4E = (s16)(((s16)((S_8197192C_0 *)arg0)->unk_30.u) / 2 +
        (((S_8197192C_10 *)gbase3)->unk_06 - ((S_8197192C_0 *)arg0)->unk_7E.u) / 2);
    ((S_8197192C_9 *)dst)->unk_50 = (s16)(((s16)((S_8197192C_0 *)arg0)->unk_32.u) / 2 +
        (((S_8197192C_10 *)gbase3)->unk_0A - ((S_8197192C_0 *)arg0)->unk_80.u) / 2);
    }

    {
    u8 *dst2 = (u8 *)arg0 + (((index2 << 1) + index2) << 1);
    ((S_8197192C_11 *)dst2)->unk_4C = (s16)(((s16)((S_8197192C_0 *)arg0)->unk_2E.u) / 4 +
        (((S_8197192C_10 *)gbase3)->unk_02 - ((S_8197192C_0 *)arg0)->unk_7C.u) / 2);
    ((S_8197192C_11 *)dst2)->unk_4E = (s16)(((s16)((S_8197192C_0 *)arg0)->unk_30.u) / 4 +
        (((S_8197192C_10 *)gbase3)->unk_06 - ((S_8197192C_0 *)arg0)->unk_7E.u) / 2);
    ((S_8197192C_11 *)dst2)->unk_50 = (s16)(((s16)((S_8197192C_0 *)arg0)->unk_32.u) / 4 +
        (((S_8197192C_10 *)gbase3)->unk_0A - ((S_8197192C_0 *)arg0)->unk_80.u) / 2);
    }

after_coords:
    if (((S_8197192C_0 *)arg0)->unk_2C.u == 4) {
        void *obj = func_8003FC64(0x212);
        if (obj != 0) {
            u8 *work = (u8 *)obj + 0x20;
            u8 *part;
            register u8 *dst ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
            u32 color0_saved;
            register u32 color0_copy ASM_REG("$6");   /* MATCH pin: retail delay-slot fill depends on it */
            u32 color1_a3;
            u32 color1_t0;
            register void *cb_obj ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
            void *cb_arg;
            ASM_KEEP(work);   /* MATCH pin: retail schedule: same instructions, different order without it */
            color0 = 0x00E0E0E0;
            color1 = 0x00804020;
            cb_obj = obj;
            cb_arg = (void *)&D_80024544;
            ((S_8197192C_7 *)work)->unk_1C = color0;
            ((S_8197192C_7 *)work)->unk_24 = color1;
            ((S_8197192C_7 *)work)->unk_28 = color1;
            ASM_KEEP(color0);   /* MATCH pin: retail immediate-load split depends on it */
            color0_saved = color0;
            ASM_KEEP(color0_saved);   /* MATCH pin: retail immediate-load split depends on it */
            ((S_8197192C_7 *)work)->unk_20 = color0;
            ASM_KEEP(color0);   /* MATCH pin: retail immediate-load split depends on it */
            color0_copy = color0;
            ASM_KEEP(color0_copy);   /* MATCH pin: retail immediate-load split depends on it */
            ((S_8197192C_7 *)work)->unk_38 = 20;
            ((S_8197192C_7 *)work)->unk_3A = 20;
            ((S_8197192C_7 *)work)->unk_0C = color0_saved;
            ((S_8197192C_7 *)work)->unk_10 = color0_copy;
            color1_a3 = ((S_8197192C_7 *)work)->unk_24;
            color1_t0 = ((S_8197192C_7 *)work)->unk_28;
            ((S_8197192C_7 *)work)->unk_14 = color1_a3;
            ((S_8197192C_7 *)work)->unk_18 = color1_t0;
            ((S_8197192C_1 *)obj)->unk_10.at00.v = (void *)&D_80024B98;
            func_8004491C(cb_obj, cb_arg);
            part = ((S_8197192C_1 *)obj)->unk_0C;
            ((S_8197192C_8 *)part)->unk_10 = 0x20;
            ((S_8197192C_8 *)part)->unk_14 = ((S_8197192C_8 *)part)->unk_14 | 0x0C;
            ((S_8197192C_7 *)work)->unk_4C = ((S_8197192C_0 *)arg0)->unk_58.s;
            ((S_8197192C_7 *)work)->unk_4E = ((S_8197192C_0 *)arg0)->unk_5A.s;
            ((S_8197192C_7 *)work)->unk_50 = ((S_8197192C_0 *)arg0)->unk_5C.s;
            ((S_8197192C_7 *)work)->unk_52 = ((S_8197192C_0 *)arg0)->unk_4C.s;
            ((S_8197192C_7 *)work)->unk_54 = ((S_8197192C_0 *)arg0)->unk_4E.s;
            ((S_8197192C_7 *)work)->unk_56 = ((S_8197192C_0 *)arg0)->unk_50.s;
            ((S_8197192C_7 *)work)->unk_58 = ((S_8197192C_0 *)arg0)->unk_5E;
            ((S_8197192C_7 *)work)->unk_5A = ((S_8197192C_0 *)arg0)->unk_60;
            ((S_8197192C_7 *)work)->unk_5C = ((S_8197192C_0 *)arg0)->unk_62;
            ((S_8197192C_7 *)work)->unk_5E = ((S_8197192C_0 *)arg0)->unk_52;
            ((S_8197192C_7 *)work)->unk_60 = ((S_8197192C_0 *)arg0)->unk_54;
            ((S_8197192C_7 *)work)->unk_62 = ((S_8197192C_0 *)arg0)->unk_56;
            dst = ((S_8197192C_1 *)obj)->unk_08;
            ((S_8197192C_9 *)dst)->unk_02 = ((S_8197192C_0 *)arg0)->unk_7C.s;
            ((S_8197192C_9 *)dst)->unk_06 = ((S_8197192C_0 *)arg0)->unk_7E.s;
            ((S_8197192C_9 *)dst)->unk_0A = ((S_8197192C_0 *)arg0)->unk_80.s;
            part = ((S_8197192C_1 *)obj)->unk_0C;
            ((S_8197192C_8 *)part)->unk_1E = 0x1000;
            ((S_8197192C_8 *)part)->unk_1C = 0x1000;
            ((S_8197192C_8 *)part)->unk_0E = 0x80;
            ((S_8197192C_8 *)part)->unk_0D = 0x80;
            ((S_8197192C_8 *)part)->unk_0C = 0x80;
            *(Data12 *)((u8 *)obj + 0xA2) = D_80025FDC;
            ((S_8197192C_8 *)part)->unk_08 = (u8 *)obj + 0xA2;
        }
    }
    if (((S_8197192C_0 *)arg0)->unk_2C.u == 2) {
        void *obj = func_8003FC64(0x212);
        if (obj != 0) {
            u8 *work = (u8 *)obj + 0x20;
            u8 *part;
            register u8 *dst ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
            u32 color0_saved;
            register u32 color0_copy ASM_REG("$6");   /* MATCH pin: retail delay-slot fill depends on it */
            u32 color1_a3;
            u32 color1_t0;
            register void *cb_obj ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
            void *cb_arg;
            ASM_KEEP(work);   /* MATCH pin: retail schedule: same instructions, different order without it */
            color0 = 0x00E0E0E0;
            color1 = 0x00804020;
            cb_obj = obj;
            cb_arg = (void *)&D_80024544;
            ((S_8197192C_7 *)work)->unk_1C = color0;
            ((S_8197192C_7 *)work)->unk_24 = color1;
            ((S_8197192C_7 *)work)->unk_28 = color1;
            ASM_KEEP(color0);   /* MATCH pin: retail immediate-load split depends on it */
            color0_saved = color0;
            ASM_KEEP(color0_saved);   /* MATCH pin: retail immediate-load split depends on it */
            ((S_8197192C_7 *)work)->unk_20 = color0;
            ASM_KEEP(color0);   /* MATCH pin: retail immediate-load split depends on it */
            color0_copy = color0;
            ASM_KEEP(color0_copy);   /* MATCH pin: retail immediate-load split depends on it */
            ((S_8197192C_7 *)work)->unk_38 = 20;
            ((S_8197192C_7 *)work)->unk_3A = 20;
            ((S_8197192C_7 *)work)->unk_0C = color0_saved;
            ((S_8197192C_7 *)work)->unk_10 = color0_copy;
            color1_a3 = ((S_8197192C_7 *)work)->unk_24;
            color1_t0 = ((S_8197192C_7 *)work)->unk_28;
            ((S_8197192C_7 *)work)->unk_14 = color1_a3;
            ((S_8197192C_7 *)work)->unk_18 = color1_t0;
            ((S_8197192C_1 *)obj)->unk_10.at00.v = (void *)&D_80024B98;
            func_8004491C(cb_obj, cb_arg);
            part = ((S_8197192C_1 *)obj)->unk_0C;
            ((S_8197192C_8 *)part)->unk_10 = 0x20;
            ((S_8197192C_8 *)part)->unk_14 = ((S_8197192C_8 *)part)->unk_14 | 0x0C;
            ((S_8197192C_7 *)work)->unk_4C = ((S_8197192C_0 *)arg0)->unk_64.s;
            ((S_8197192C_7 *)work)->unk_4E = ((S_8197192C_0 *)arg0)->unk_66.s;
            ((S_8197192C_7 *)work)->unk_50 = ((S_8197192C_0 *)arg0)->unk_68.s;
            ((S_8197192C_7 *)work)->unk_52 = ((S_8197192C_0 *)arg0)->unk_58.s;
            ((S_8197192C_7 *)work)->unk_54 = ((S_8197192C_0 *)arg0)->unk_5A.s;
            ((S_8197192C_7 *)work)->unk_56 = ((S_8197192C_0 *)arg0)->unk_5C.s;
            ((S_8197192C_7 *)work)->unk_58 = ((S_8197192C_0 *)arg0)->unk_6A;
            ((S_8197192C_7 *)work)->unk_5A = ((S_8197192C_0 *)arg0)->unk_6C;
            ((S_8197192C_7 *)work)->unk_5C = ((S_8197192C_0 *)arg0)->unk_6E;
            ((S_8197192C_7 *)work)->unk_5E = ((S_8197192C_0 *)arg0)->unk_5E;
            ((S_8197192C_7 *)work)->unk_60 = ((S_8197192C_0 *)arg0)->unk_60;
            ((S_8197192C_7 *)work)->unk_62 = ((S_8197192C_0 *)arg0)->unk_62;
            dst = ((S_8197192C_1 *)obj)->unk_08;
            ((S_8197192C_9 *)dst)->unk_02 = ((S_8197192C_0 *)arg0)->unk_7C.s;
            ((S_8197192C_9 *)dst)->unk_06 = ((S_8197192C_0 *)arg0)->unk_7E.s;
            ((S_8197192C_9 *)dst)->unk_0A = ((S_8197192C_0 *)arg0)->unk_80.s;
            part = ((S_8197192C_1 *)obj)->unk_0C;
            ((S_8197192C_8 *)part)->unk_1E = 0x1000;
            ((S_8197192C_8 *)part)->unk_1C = 0x1000;
            ((S_8197192C_8 *)part)->unk_0E = 0x80;
            ((S_8197192C_8 *)part)->unk_0D = 0x80;
            ((S_8197192C_8 *)part)->unk_0C = 0x80;
            *(Data12 *)((u8 *)obj + 0xA2) = D_80025FDC;
            ((S_8197192C_8 *)part)->unk_08 = (u8 *)obj + 0xA2;
        }
    }
    if (((S_8197192C_0 *)arg0)->unk_2C.u == 1) {
        register void *obj ASM_REG("$17") = func_8003FC64(0x212);   /* MATCH pin: keeps a constant in a register as retail does */
        if (obj != 0) {
            register u8 *work ASM_REG("$16") = (u8 *)obj + 0x20;   /* MATCH pin: retail keeps a computation the compiler would drop */
            u8 *part;
            register u8 *dst ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
            u32 color0_saved;
            register u32 color0_copy ASM_REG("$6");   /* MATCH pin: retail delay-slot fill depends on it */
            u32 color1_a3;
            u32 color1_t0;
            register void *cb_obj ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
            void *cb_arg;
            color0 = 0x00E0E0E0;
            color1 = 0x00804020;
            cb_obj = obj;
            cb_arg = (void *)&D_80024544;
            ((S_8197192C_7 *)work)->unk_1C = color0;
            ((S_8197192C_7 *)work)->unk_24 = color1;
            ((S_8197192C_7 *)work)->unk_28 = color1;
            ASM_KEEP(color0);   /* MATCH pin: retail immediate-load split depends on it */
            color0_saved = color0;
            ASM_KEEP(color0_saved);   /* MATCH pin: retail immediate-load split depends on it */
            ((S_8197192C_7 *)work)->unk_20 = color0;
            ASM_KEEP(color0);   /* MATCH pin: retail immediate-load split depends on it */
            color0_copy = color0;
            ASM_KEEP(color0_copy);   /* MATCH pin: retail immediate-load split depends on it */
            ((S_8197192C_7 *)work)->unk_38 = 20;
            ((S_8197192C_7 *)work)->unk_3A = 20;
            ((S_8197192C_7 *)work)->unk_0C = color0_saved;
            ((S_8197192C_7 *)work)->unk_10 = color0_copy;
            color1_a3 = ((S_8197192C_7 *)work)->unk_24;
            color1_t0 = ((S_8197192C_7 *)work)->unk_28;
            ((S_8197192C_7 *)work)->unk_14 = color1_a3;
            ((S_8197192C_7 *)work)->unk_18 = color1_t0;
            ((S_8197192C_1 *)obj)->unk_10.at00.v = (void *)&D_80024B98;
            func_8004491C(cb_obj, cb_arg);
            part = ((S_8197192C_1 *)obj)->unk_0C;
            ((S_8197192C_8 *)part)->unk_10 = 0x20;
            ((S_8197192C_8 *)part)->unk_14 = ((S_8197192C_8 *)part)->unk_14 | 0x0C;
            ((S_8197192C_7 *)work)->unk_4C = ((S_8197192C_0 *)arg0)->unk_70.s;
            ((S_8197192C_7 *)work)->unk_4E = ((S_8197192C_0 *)arg0)->unk_72.s;
            ((S_8197192C_7 *)work)->unk_50 = ((S_8197192C_0 *)arg0)->unk_74.s;
            ((S_8197192C_7 *)work)->unk_52 = ((S_8197192C_0 *)arg0)->unk_64.s;
            ((S_8197192C_7 *)work)->unk_54 = ((S_8197192C_0 *)arg0)->unk_66.s;
            ((S_8197192C_7 *)work)->unk_56 = ((S_8197192C_0 *)arg0)->unk_68.s;
            ((S_8197192C_7 *)work)->unk_58 = ((S_8197192C_0 *)arg0)->unk_76;
            ((S_8197192C_7 *)work)->unk_5A = ((S_8197192C_0 *)arg0)->unk_78;
            ((S_8197192C_7 *)work)->unk_5C = ((S_8197192C_0 *)arg0)->unk_7A;
            ((S_8197192C_7 *)work)->unk_5E = ((S_8197192C_0 *)arg0)->unk_6A;
            ((S_8197192C_7 *)work)->unk_60 = ((S_8197192C_0 *)arg0)->unk_6C;
            ((S_8197192C_7 *)work)->unk_62 = ((S_8197192C_0 *)arg0)->unk_6E;
            dst = ((S_8197192C_1 *)obj)->unk_08;
            ((S_8197192C_9 *)dst)->unk_02 = ((S_8197192C_0 *)arg0)->unk_7C.s;
            ((S_8197192C_9 *)dst)->unk_06 = ((S_8197192C_0 *)arg0)->unk_7E.s;
            ((S_8197192C_9 *)dst)->unk_0A = ((S_8197192C_0 *)arg0)->unk_80.s;
            part = ((S_8197192C_1 *)obj)->unk_0C;
            ((S_8197192C_8 *)part)->unk_1E = 0x1000;
            ((S_8197192C_8 *)part)->unk_1C = 0x1000;
            ((S_8197192C_8 *)part)->unk_0E = 0x80;
            ((S_8197192C_8 *)part)->unk_0D = 0x80;
            ((S_8197192C_8 *)part)->unk_0C = 0x80;
            *(Data12 *)((u8 *)obj + 0xA2) = D_80025FDC;
            ((S_8197192C_8 *)part)->unk_08 = (u8 *)obj + 0xA2;
            ASM_KEEP(obj);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        }
    }

    if (((S_8197192C_0 *)arg0)->unk_2C.u == 4) {
        i = 0;
        do {
            s32 call_x;
            s32 call_y;
            s32 call_z;
            call_x = (s16)((((S_8197192C_0 *)arg0)->unk_58.s +
                      (((S_8197192C_0 *)arg0)->unk_4C.u - ((S_8197192C_0 *)arg0)->unk_58.u) * i / 6) << 1);
            call_y = (s16)((((S_8197192C_0 *)arg0)->unk_5A.s +
                      (((S_8197192C_0 *)arg0)->unk_4E.u - ((S_8197192C_0 *)arg0)->unk_5A.u) * i / 6) << 1);
            call_z = (s16)((((S_8197192C_0 *)arg0)->unk_5C.s +
                      (((S_8197192C_0 *)arg0)->unk_50.u - ((S_8197192C_0 *)arg0)->unk_5C.u) * i / 6) << 1);
            func_80024DD4(arg0, arg1, arg2,
                call_x, call_y, call_z);
            i++;
        } while (i < 6);
    }
    if (((S_8197192C_0 *)arg0)->unk_2C.u == 2) {
        i = 0;
        do {
            s32 call_x;
            s32 call_y;
            s32 call_z;
            call_x = (s16)((((S_8197192C_0 *)arg0)->unk_64.s +
                      (((S_8197192C_0 *)arg0)->unk_58.u - ((S_8197192C_0 *)arg0)->unk_64.u) * i / 12) << 1);
            call_y = (s16)((((S_8197192C_0 *)arg0)->unk_66.s +
                      (((S_8197192C_0 *)arg0)->unk_5A.u - ((S_8197192C_0 *)arg0)->unk_66.u) * i / 12) << 1);
            call_z = (s16)((((S_8197192C_0 *)arg0)->unk_68.s +
                      (((S_8197192C_0 *)arg0)->unk_5C.u - ((S_8197192C_0 *)arg0)->unk_68.u) * i / 12) << 1);
            func_80024DD4(arg0, arg1, arg2,
                call_x, call_y, call_z);
            i++;
        } while (i < 12);
    }
    if (((S_8197192C_0 *)arg0)->unk_2C.u != 1) {
        goto done;
    }
    i = 0;
    ASM_KEEP_NV(i);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    {
        s32 call_x;
        s32 call_y;
        s32 call_z;
        call_x = (s16)((((S_8197192C_0 *)arg0)->unk_70.s +
                  (((S_8197192C_0 *)arg0)->unk_64.u - ((S_8197192C_0 *)arg0)->unk_70.u) * i / 2) << 1);
        call_y = (s16)((((S_8197192C_0 *)arg0)->unk_72.s +
                  (((S_8197192C_0 *)arg0)->unk_66.u - ((S_8197192C_0 *)arg0)->unk_72.u) * i / 2) << 1);
        {
        void *call_obj = arg0;
        ASM_KEEP_NV(call_obj);
        call_z = (s16)((((S_8197192C_0 *)arg0)->unk_74.s +
                  (((S_8197192C_0 *)arg0)->unk_68.u - ((S_8197192C_0 *)arg0)->unk_74.u) * i / 2) << 1);
        func_80024DD4(call_obj, arg1, arg2,
            call_x, call_y, call_z);
        }
        i++;
        if (i >= 2) {
            goto done;
        }
        func_80025DAC();
    }

}

case_4:
{
    s32 i;
    void *obj;
    u8 *base;
    u8 *lookup;
    u8 count;
    u8 *status_page;
    if (((S_8197192C_0 *)arg0)->unk_2C.u != 16) {
        status_page = (u8 *)0x80080000;
        goto case_4_global_use;
    }
    obj = ((S_8197192C_15 *)(((S_8197192C_6 *)(&D_800814A8))->unk_00))->unk_60;
    if (obj != 0) {
        lookup = D_800DDC40;
        count = lookup[((S_8197192C_1 *)obj)->unk_10.at03.v];
        arg1 = ((S_8197192C_1_pre *)obj)[-1].unk_00;
        i = 0;
        if (count == 0) {
            goto case_4_global;
        }
        base = lookup;
        do {
            func_80024F60(arg0, arg1, arg2, 0, 0, (s16)i);
            i -= 15;
        } while (-*(u8 *)((u32)((S_8197192C_1 *)obj)->unk_10.at03.v + (u32)base) < i);
    }
case_4_global:
    status_page = (u8 *)0x80080000;
case_4_global_use:
    {
        u16 next_state = 4;
        if ((((S_8197192C_12 *)status_page)->unk_2E94 & 0x8000) != 0) {
            goto case_4_set_state;
        }
        ((S_8197192C_0 *)arg0)->unk_2C.s = ((S_8197192C_0 *)arg0)->unk_2C.s - 1;
        if ((s16)((S_8197192C_0 *)arg0)->unk_2C.s >= 0) {
            goto done;
        }
case_4_set_state:
        ((S_8197192C_0 *)arg0)->unk_0A.u = next_state;
        func_80025F9C();
    }
    goto done;
}

cleanup:
{
    void *cleanup_obj;
    u16 cleanup_count;
    if (D_80025FF4[0] == 0) {
        cleanup_obj = D_80083460;
        cleanup_count = ((S_8197192C_13 *)cleanup_obj)->unk_0A;
        ((S_8197192C_13 *)cleanup_obj)->unk_0C = 0;
        D_80082E86[0] = 0;
        ((S_8197192C_13 *)cleanup_obj)->unk_0A = cleanup_count - 1;
        ((S_8197192C_0_pre *)arg0)[-1].unk_00 = ((S_8197192C_0_pre *)arg0)[-1].unk_00 | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        func_80025F9C();
    }
    D_80025FF4[0] = 0;

}

done:
    return;
}

#undef arg0
#undef arg1
#undef arg2
