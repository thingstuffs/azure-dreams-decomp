#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
    register void *base2 ASM_REG("$18") = arg0;
    register void *base3 ASM_REG("$19") = arg1;
    register void *base5 ASM_REG("$21");
    register u32 color0 ASM_REG("$2");
    register u32 color1 ASM_REG("$3");

    (void)keep_cases;
    ASM_KEEP4_NV(base2, base3, base5, base5);
#define arg0 base2
#define arg1 base3
    FIELD(arg0, u16, 0x38) = FIELD(arg0, u16, 0x38) + 1;
    state = FIELD(arg0, s16, 0x0A);
    if (state >= 5) {
        goto done;
    }
    base5 = arg2;
    ASM_KEEP_NV(base5);
#define arg2 base5
    goto *D_80024058[state];

case_0:
{
    register void *obj ASM_REG("$3") = D_800814A8_case0[0];
    register u8 *gbase ASM_REG("$3");
    register u16 coord_z ASM_REG("$3");
    u16 heading;
    FIELD(obj, s32, 0xF4) = 0;
    FIELD(obj, s16, 0x96) = 20;
    FIELD(D_80082E86, u16, 0) = 6;
    gbase = D_80083780;
    FIELD(arg0, u16, 0x0A) = FIELD(arg0, u16, 0x0A) + 1;
    FIELD(arg0, u16, 0x7C) = FIELD(gbase, u16, 2);
    FIELD(arg0, u16, 0x7E) = FIELD(gbase, u16, 6);
    coord_z = FIELD(gbase, u16, 0x0A);
    FIELD(D_80025FF4, u16, 0) = 1;
    FIELD(arg0, u16, 0x80) = coord_z;
    ASM_KEEP(coord_z);
    if ((FIELD(FIELD(arg0, void *, 4), u16, 0) & 0x80) == 0) {
        goto done;
    }
    obj = D_800814A8[0];
    FIELD(arg0, u16, 0x2C) = 33;
    FIELD(obj, u16, 0xA6) = FIELD(obj, u16, 0xA6) - 1;
    FIELD(obj, u8, 0xA8) = FIELD(arg0, u8, 8);
    obj = D_800814A8[0];
    heading = FIELD(obj, u16, 0x2A);
    FIELD(arg0, u16, 0x0A) = FIELD(arg0, u16, 0x0A) + 1;
    FIELD(arg0, u16, 0x38) = 0;
    FIELD(arg0, u16, 0x34) = (heading >> 9) & 7;
    func_80025F9C();
}

case_1:
{
    FIELD(arg0, u16, 0x2C) = FIELD(arg0, u16, 0x2C) - 1;
    if ((s16)FIELD(arg0, u16, 0x2C) <= 0) {
        FIELD(arg0, u16, 0x2C) = 16;
        FIELD(arg0, u16, 0x0A) = FIELD(arg0, u16, 0x0A) + 1;
        func_80025F9C();
    }
    if ((s16)FIELD(arg0, u16, 0x2C) == 26) {
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
    if ((u16)(FIELD(arg0, u16, 0x2C) - 5) < 19) {
        register void *map_base ASM_REG("$5") = (void *)D_80082E80;
        ASM_KEEP(map_base);
        if (func_8003DF74(
            FIELD(map_base, void *, 8), map_base,
            (u8 *)arg0 + 0x2E, 0) != 0) {
            i = 0;
            do {
                func_800248A8((u8 *)FIELD(&D_800814A8, void *, 0) - 0x20, 0,
                              0xE04040, (func_80069EF8() & 0x3F) | 0x40,
                              FIELD(arg0, s16, 0x2E),
                              FIELD(arg0, s16, 0x30),
                              FIELD(arg0, s16, 0x32));
                i++;
            } while (i < 2);
        }
    }

    if (FIELD(arg0, s16, 0x2C) == 24) {
        register void *map_base ASM_REG("$5") = (void *)D_80082E80;
        ASM_KEEP(map_base);
        if (func_8003DF74(FIELD(map_base, void *, 8), map_base,
                          (u8 *)arg0 + 0x2E, 0) != 0) {
            register void *obj ASM_REG("$17");
            register u8 *work ASM_REG("$16");
            u8 *part;
            u8 *dst;
            u8 *gbase;

            obj = func_8003FC64(0x212);
            ASM_KEEP(obj);
            if (obj != 0) {
                work = (u8 *)obj + 0x20;
                ASM_KEEP(work);
                FIELD(work, u16, 0x38) = 20;
                FIELD(work, u16, 0x3A) = 20;
                FIELD(obj, void *, 0x10) = (void *)&D_80024D10;
                func_8004491C(obj, D_80045340);
                part = FIELD(obj, u8 *, 0x0C);
                gbase = D_80083780;
                FIELD(part, u16, 0x10) = 0x60;
                FIELD(part, u16, 0x14) = FIELD(part, u16, 0x14) | 0x0C;
                dst = FIELD(obj, u8 *, 8);
                FIELD(dst, u16, 2) = FIELD(arg0, u16, 0x2E) +
                                      FIELD(gbase, u16, 2);
                FIELD(dst, u16, 6) = FIELD(arg0, u16, 0x30) +
                                      FIELD(gbase, u16, 6);
                FIELD(dst, u16, 0x0A) = FIELD(arg0, u16, 0x32) +
                                       FIELD(gbase, u16, 0x0A);
                part = FIELD(obj, u8 *, 0x0C);
                FIELD(part, u16, 0x1E) = 0x1000;
                FIELD(part, u16, 0x1C) = 0x1000;
                FIELD(part, u8, 0x0E) = 0x20;
                FIELD(part, u8, 0x0D) = 0x20;
                FIELD(part, u8, 0x0C) = 0x20;
                *(Data12 *)((u8 *)obj + 0xA2) = D_80025FD0;
                FIELD(part, void *, 8) = (u8 *)obj + 0xA2;
                ASM_KEEP(obj);
            }
        }
    }
}

case_3:
{
    s32 index;
    register s32 index2 ASM_REG("$6");
    s32 i;
    register u8 *gbase3 ASM_REG("$7");
    if (FIELD(arg0, s16, 0x2C) >= 10) {
        goto done;
    }
    if (FIELD(arg0, s16, 0x2C) >= 6) {
        goto done;
    }
    if (FIELD(arg0, s16, 0x2C) == 3) {
        goto done;
    }
    index = (FIELD(arg0, s16, 0x2C) == 4);
    if (FIELD(arg0, s16, 0x2C) == 2) {
        index = 2;
    }
    if (FIELD(arg0, s16, 0x2C) == 1) {
        index = 3;
    }
    {
        register void *map_base ASM_REG("$5") = (void *)D_80082E80;
        ASM_KEEP(map_base);
    if (func_8003DF74(FIELD(map_base, void *, 8), map_base,
                      (u8 *)arg0 + 0x2E, 0) == 0) {
        goto after_coords;
    }
    if (FIELD(arg0, s16, 0x2C) == 1) {
        FIELD(arg0, s16, 0x32) = -12;
    }
    }
    index2 = index << 1;
    {
    register u8 *dst ASM_REG("$5");
    dst = (u8 *)arg0 + ((index2 + index) << 2);
    index2++;
    ASM_KEEP(index2);
    {
        register u32 raw_x ASM_REG("$2");
        register s32 origin_x ASM_REG("$3");
        register s32 half ASM_REG("$4");
        register u32 coord_page ASM_REG("$2");
        raw_x = FIELD(arg0, u16, 0x2E);
        origin_x = FIELD(arg0, s16, 0x7C);
        raw_x <<= 16;
        half = (s32)raw_x >> 16;
        half += raw_x >> 31;
        ASM_KEEP(half);
        coord_page = 0x80080000;
        ASM_KEEP(coord_page);
        gbase3 = (u8 *)(coord_page + 0x3780);
        ASM_KEEP_NV(gbase3);
        half >>= 1;
        FIELD(dst, s16, 0x4C) = (s16)(half +
            (FIELD(gbase3, s16, 2) - origin_x) / 2);
    }
    FIELD(dst, s16, 0x4E) = (s16)(((s16)FIELD(arg0, u16, 0x30)) / 2 +
        (FIELD(gbase3, s16, 6) - FIELD(arg0, s16, 0x7E)) / 2);
    FIELD(dst, s16, 0x50) = (s16)(((s16)FIELD(arg0, u16, 0x32)) / 2 +
        (FIELD(gbase3, s16, 0x0A) - FIELD(arg0, s16, 0x80)) / 2);
    }

    {
    u8 *dst2 = (u8 *)arg0 + (((index2 << 1) + index2) << 1);
    FIELD(dst2, s16, 0x4C) = (s16)(((s16)FIELD(arg0, u16, 0x2E)) / 4 +
        (FIELD(gbase3, s16, 2) - FIELD(arg0, s16, 0x7C)) / 2);
    FIELD(dst2, s16, 0x4E) = (s16)(((s16)FIELD(arg0, u16, 0x30)) / 4 +
        (FIELD(gbase3, s16, 6) - FIELD(arg0, s16, 0x7E)) / 2);
    FIELD(dst2, s16, 0x50) = (s16)(((s16)FIELD(arg0, u16, 0x32)) / 4 +
        (FIELD(gbase3, s16, 0x0A) - FIELD(arg0, s16, 0x80)) / 2);
    }

after_coords:
    if (FIELD(arg0, s16, 0x2C) == 4) {
        register void *obj ASM_REG("$17") = func_8003FC64(0x212);
        ASM_KEEP(obj);
        if (obj != 0) {
            register u8 *work ASM_REG("$16") = (u8 *)obj + 0x20;
            u8 *part;
            register u8 *dst ASM_REG("$5");
            u32 color0_saved;
            register u32 color0_copy ASM_REG("$6");
            register u32 color1_a3 ASM_REG("$7");
            register u32 color1_t0 ASM_REG("$8");
            register void *cb_obj ASM_REG("$4");
            register void *cb_arg ASM_REG("$5");
            ASM_KEEP(work);
            color0 = 0x00E0E0E0;
            color1 = 0x00804020;
            cb_obj = obj;
            cb_arg = (void *)&D_80024544;
            FIELD(work, u32, 0x1C) = color0;
            FIELD(work, u32, 0x24) = color1;
            FIELD(work, u32, 0x28) = color1;
            ASM_KEEP(color0);
            color0_saved = color0;
            ASM_KEEP(color0_saved);
            FIELD(work, u32, 0x20) = color0;
            ASM_KEEP(color0);
            color0_copy = color0;
            ASM_KEEP(color0_copy);
            FIELD(work, u16, 0x38) = 20;
            FIELD(work, u16, 0x3A) = 20;
            FIELD(work, u32, 0x0C) = color0_saved;
            FIELD(work, u32, 0x10) = color0_copy;
            color1_a3 = FIELD(work, u32, 0x24);
            color1_t0 = FIELD(work, u32, 0x28);
            FIELD(work, u32, 0x14) = color1_a3;
            FIELD(work, u32, 0x18) = color1_t0;
            FIELD(obj, void *, 0x10) = (void *)&D_80024B98;
            func_8004491C(cb_obj, cb_arg);
            part = FIELD(obj, u8 *, 0x0C);
            FIELD(part, u16, 0x10) = 0x20;
            FIELD(part, u16, 0x14) = FIELD(part, u16, 0x14) | 0x0C;
            FIELD(work, u16, 0x4C) = FIELD(arg0, u16, 0x58);
            FIELD(work, u16, 0x4E) = FIELD(arg0, u16, 0x5A);
            FIELD(work, u16, 0x50) = FIELD(arg0, u16, 0x5C);
            FIELD(work, u16, 0x52) = FIELD(arg0, u16, 0x4C);
            FIELD(work, u16, 0x54) = FIELD(arg0, u16, 0x4E);
            FIELD(work, u16, 0x56) = FIELD(arg0, u16, 0x50);
            FIELD(work, u16, 0x58) = FIELD(arg0, u16, 0x5E);
            FIELD(work, u16, 0x5A) = FIELD(arg0, u16, 0x60);
            FIELD(work, u16, 0x5C) = FIELD(arg0, u16, 0x62);
            FIELD(work, u16, 0x5E) = FIELD(arg0, u16, 0x52);
            FIELD(work, u16, 0x60) = FIELD(arg0, u16, 0x54);
            FIELD(work, u16, 0x62) = FIELD(arg0, u16, 0x56);
            dst = FIELD(obj, u8 *, 8);
            FIELD(dst, u16, 2) = FIELD(arg0, u16, 0x7C);
            FIELD(dst, u16, 6) = FIELD(arg0, u16, 0x7E);
            FIELD(dst, u16, 0x0A) = FIELD(arg0, u16, 0x80);
            part = FIELD(obj, u8 *, 0x0C);
            FIELD(part, u16, 0x1E) = 0x1000;
            FIELD(part, u16, 0x1C) = 0x1000;
            FIELD(part, u8, 0x0E) = 0x80;
            FIELD(part, u8, 0x0D) = 0x80;
            FIELD(part, u8, 0x0C) = 0x80;
            *(Data12 *)((u8 *)obj + 0xA2) = D_80025FDC;
            FIELD(part, void *, 8) = (u8 *)obj + 0xA2;
            ASM_KEEP(obj);
        }
    }
    if (FIELD(arg0, s16, 0x2C) == 2) {
        register void *obj ASM_REG("$17") = func_8003FC64(0x212);
        ASM_KEEP(obj);
        if (obj != 0) {
            register u8 *work ASM_REG("$16") = (u8 *)obj + 0x20;
            u8 *part;
            register u8 *dst ASM_REG("$5");
            u32 color0_saved;
            register u32 color0_copy ASM_REG("$6");
            register u32 color1_a3 ASM_REG("$7");
            register u32 color1_t0 ASM_REG("$8");
            register void *cb_obj ASM_REG("$4");
            register void *cb_arg ASM_REG("$5");
            ASM_KEEP(work);
            color0 = 0x00E0E0E0;
            color1 = 0x00804020;
            cb_obj = obj;
            cb_arg = (void *)&D_80024544;
            FIELD(work, u32, 0x1C) = color0;
            FIELD(work, u32, 0x24) = color1;
            FIELD(work, u32, 0x28) = color1;
            ASM_KEEP(color0);
            color0_saved = color0;
            ASM_KEEP(color0_saved);
            FIELD(work, u32, 0x20) = color0;
            ASM_KEEP(color0);
            color0_copy = color0;
            ASM_KEEP(color0_copy);
            FIELD(work, u16, 0x38) = 20;
            FIELD(work, u16, 0x3A) = 20;
            FIELD(work, u32, 0x0C) = color0_saved;
            FIELD(work, u32, 0x10) = color0_copy;
            color1_a3 = FIELD(work, u32, 0x24);
            color1_t0 = FIELD(work, u32, 0x28);
            FIELD(work, u32, 0x14) = color1_a3;
            FIELD(work, u32, 0x18) = color1_t0;
            FIELD(obj, void *, 0x10) = (void *)&D_80024B98;
            func_8004491C(cb_obj, cb_arg);
            part = FIELD(obj, u8 *, 0x0C);
            FIELD(part, u16, 0x10) = 0x20;
            FIELD(part, u16, 0x14) = FIELD(part, u16, 0x14) | 0x0C;
            FIELD(work, u16, 0x4C) = FIELD(arg0, u16, 0x64);
            FIELD(work, u16, 0x4E) = FIELD(arg0, u16, 0x66);
            FIELD(work, u16, 0x50) = FIELD(arg0, u16, 0x68);
            FIELD(work, u16, 0x52) = FIELD(arg0, u16, 0x58);
            FIELD(work, u16, 0x54) = FIELD(arg0, u16, 0x5A);
            FIELD(work, u16, 0x56) = FIELD(arg0, u16, 0x5C);
            FIELD(work, u16, 0x58) = FIELD(arg0, u16, 0x6A);
            FIELD(work, u16, 0x5A) = FIELD(arg0, u16, 0x6C);
            FIELD(work, u16, 0x5C) = FIELD(arg0, u16, 0x6E);
            FIELD(work, u16, 0x5E) = FIELD(arg0, u16, 0x5E);
            FIELD(work, u16, 0x60) = FIELD(arg0, u16, 0x60);
            FIELD(work, u16, 0x62) = FIELD(arg0, u16, 0x62);
            dst = FIELD(obj, u8 *, 8);
            FIELD(dst, u16, 2) = FIELD(arg0, u16, 0x7C);
            FIELD(dst, u16, 6) = FIELD(arg0, u16, 0x7E);
            FIELD(dst, u16, 0x0A) = FIELD(arg0, u16, 0x80);
            part = FIELD(obj, u8 *, 0x0C);
            FIELD(part, u16, 0x1E) = 0x1000;
            FIELD(part, u16, 0x1C) = 0x1000;
            FIELD(part, u8, 0x0E) = 0x80;
            FIELD(part, u8, 0x0D) = 0x80;
            FIELD(part, u8, 0x0C) = 0x80;
            *(Data12 *)((u8 *)obj + 0xA2) = D_80025FDC;
            FIELD(part, void *, 8) = (u8 *)obj + 0xA2;
            ASM_KEEP(obj);
        }
    }
    if (FIELD(arg0, s16, 0x2C) == 1) {
        register void *obj ASM_REG("$17") = func_8003FC64(0x212);
        ASM_KEEP(obj);
        if (obj != 0) {
            register u8 *work ASM_REG("$16") = (u8 *)obj + 0x20;
            u8 *part;
            register u8 *dst ASM_REG("$5");
            u32 color0_saved;
            register u32 color0_copy ASM_REG("$6");
            register u32 color1_a3 ASM_REG("$7");
            register u32 color1_t0 ASM_REG("$8");
            register void *cb_obj ASM_REG("$4");
            register void *cb_arg ASM_REG("$5");
            ASM_KEEP(work);
            color0 = 0x00E0E0E0;
            color1 = 0x00804020;
            cb_obj = obj;
            cb_arg = (void *)&D_80024544;
            FIELD(work, u32, 0x1C) = color0;
            FIELD(work, u32, 0x24) = color1;
            FIELD(work, u32, 0x28) = color1;
            ASM_KEEP(color0);
            color0_saved = color0;
            ASM_KEEP(color0_saved);
            FIELD(work, u32, 0x20) = color0;
            ASM_KEEP(color0);
            color0_copy = color0;
            ASM_KEEP(color0_copy);
            FIELD(work, u16, 0x38) = 20;
            FIELD(work, u16, 0x3A) = 20;
            FIELD(work, u32, 0x0C) = color0_saved;
            FIELD(work, u32, 0x10) = color0_copy;
            color1_a3 = FIELD(work, u32, 0x24);
            color1_t0 = FIELD(work, u32, 0x28);
            FIELD(work, u32, 0x14) = color1_a3;
            FIELD(work, u32, 0x18) = color1_t0;
            FIELD(obj, void *, 0x10) = (void *)&D_80024B98;
            func_8004491C(cb_obj, cb_arg);
            part = FIELD(obj, u8 *, 0x0C);
            FIELD(part, u16, 0x10) = 0x20;
            FIELD(part, u16, 0x14) = FIELD(part, u16, 0x14) | 0x0C;
            FIELD(work, u16, 0x4C) = FIELD(arg0, u16, 0x70);
            FIELD(work, u16, 0x4E) = FIELD(arg0, u16, 0x72);
            FIELD(work, u16, 0x50) = FIELD(arg0, u16, 0x74);
            FIELD(work, u16, 0x52) = FIELD(arg0, u16, 0x64);
            FIELD(work, u16, 0x54) = FIELD(arg0, u16, 0x66);
            FIELD(work, u16, 0x56) = FIELD(arg0, u16, 0x68);
            FIELD(work, u16, 0x58) = FIELD(arg0, u16, 0x76);
            FIELD(work, u16, 0x5A) = FIELD(arg0, u16, 0x78);
            FIELD(work, u16, 0x5C) = FIELD(arg0, u16, 0x7A);
            FIELD(work, u16, 0x5E) = FIELD(arg0, u16, 0x6A);
            FIELD(work, u16, 0x60) = FIELD(arg0, u16, 0x6C);
            FIELD(work, u16, 0x62) = FIELD(arg0, u16, 0x6E);
            dst = FIELD(obj, u8 *, 8);
            FIELD(dst, u16, 2) = FIELD(arg0, u16, 0x7C);
            FIELD(dst, u16, 6) = FIELD(arg0, u16, 0x7E);
            FIELD(dst, u16, 0x0A) = FIELD(arg0, u16, 0x80);
            part = FIELD(obj, u8 *, 0x0C);
            FIELD(part, u16, 0x1E) = 0x1000;
            FIELD(part, u16, 0x1C) = 0x1000;
            FIELD(part, u8, 0x0E) = 0x80;
            FIELD(part, u8, 0x0D) = 0x80;
            FIELD(part, u8, 0x0C) = 0x80;
            *(Data12 *)((u8 *)obj + 0xA2) = D_80025FDC;
            FIELD(part, void *, 8) = (u8 *)obj + 0xA2;
            ASM_KEEP(obj);
        }
    }

    if (FIELD(arg0, s16, 0x2C) == 4) {
        i = 0;
        do {
            s32 call_x;
            s32 call_y;
            s32 call_z;
            call_x = (s16)((FIELD(arg0, u16, 0x58) +
                      (FIELD(arg0, s16, 0x4C) - FIELD(arg0, s16, 0x58)) * i / 6) << 1);
            call_y = (s16)((FIELD(arg0, u16, 0x5A) +
                      (FIELD(arg0, s16, 0x4E) - FIELD(arg0, s16, 0x5A)) * i / 6) << 1);
            call_z = (s16)((FIELD(arg0, u16, 0x5C) +
                      (FIELD(arg0, s16, 0x50) - FIELD(arg0, s16, 0x5C)) * i / 6) << 1);
            func_80024DD4(arg0, arg1, arg2,
                call_x, call_y, call_z);
            i++;
        } while (i < 6);
    }
    if (FIELD(arg0, s16, 0x2C) == 2) {
        i = 0;
        do {
            s32 call_x;
            s32 call_y;
            s32 call_z;
            call_x = (s16)((FIELD(arg0, u16, 0x64) +
                      (FIELD(arg0, s16, 0x58) - FIELD(arg0, s16, 0x64)) * i / 12) << 1);
            call_y = (s16)((FIELD(arg0, u16, 0x66) +
                      (FIELD(arg0, s16, 0x5A) - FIELD(arg0, s16, 0x66)) * i / 12) << 1);
            call_z = (s16)((FIELD(arg0, u16, 0x68) +
                      (FIELD(arg0, s16, 0x5C) - FIELD(arg0, s16, 0x68)) * i / 12) << 1);
            func_80024DD4(arg0, arg1, arg2,
                call_x, call_y, call_z);
            i++;
        } while (i < 12);
    }
    if (FIELD(arg0, s16, 0x2C) != 1) {
        goto done;
    }
    i = 0;
    ASM_KEEP_NV(i);
    {
        s32 call_x;
        s32 call_y;
        s32 call_z;
        call_x = (s16)((FIELD(arg0, u16, 0x70) +
                  (FIELD(arg0, s16, 0x64) - FIELD(arg0, s16, 0x70)) * i / 2) << 1);
        call_y = (s16)((FIELD(arg0, u16, 0x72) +
                  (FIELD(arg0, s16, 0x66) - FIELD(arg0, s16, 0x72)) * i / 2) << 1);
        {
        register void *call_obj ASM_REG("$4") = arg0;
        ASM_KEEP_NV(call_obj);
        call_z = (s16)((FIELD(arg0, u16, 0x74) +
                  (FIELD(arg0, s16, 0x68) - FIELD(arg0, s16, 0x74)) * i / 2) << 1);
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
    register u8 *status_page ASM_REG("$2");
    if (FIELD(arg0, s16, 0x2C) != 16) {
        status_page = (u8 *)0x80080000;
        goto case_4_global_use;
    }
    obj = FIELD(FIELD(&D_800814A8, void *, 0), void *, 0x60);
    if (obj != 0) {
        lookup = D_800DDC40;
        count = lookup[FIELD(obj, u8, 0x13)];
        arg1 = FIELD(obj, void *, -0x18);
        i = 0;
        if (count == 0) {
            goto case_4_global;
        }
        base = lookup;
        do {
            func_80024F60(arg0, arg1, arg2, 0, 0, (s16)i);
            i -= 15;
        } while (-*(u8 *)((u32)FIELD(obj, u8, 0x13) + (u32)base) < i);
    }
case_4_global:
    ASM_SCHED_BARRIER();
    status_page = (u8 *)0x80080000;
case_4_global_use:
    {
        u16 next_state = 4;
        if ((FIELD(status_page, u16, 0x2E94) & 0x8000) != 0) {
            goto case_4_set_state;
        }
        FIELD(arg0, u16, 0x2C) = FIELD(arg0, u16, 0x2C) - 1;
        if ((s16)FIELD(arg0, u16, 0x2C) >= 0) {
            goto done;
        }
case_4_set_state:
        FIELD(arg0, u16, 0x0A) = next_state;
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
        cleanup_count = FIELD(cleanup_obj, u16, 0x0A);
        FIELD(cleanup_obj, s32, 0x0C) = 0;
        D_80082E86[0] = 0;
        FIELD(cleanup_obj, u16, 0x0A) = cleanup_count - 1;
        FIELD(arg0, u16, -2) = FIELD(arg0, u16, -2) | 0x8000;
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
