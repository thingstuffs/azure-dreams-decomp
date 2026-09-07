#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(s32);
extern void func_800A56E0(s32);
extern void func_800A6508(s32, s32, s32, s32);
extern s32 func_800A6D30(void);

extern u8 D_80045340;
extern u8 D_80083460[];
extern u8 D_800CCDA0;
extern u8 D_800DDC40[];
extern u8 D_800DFD0C[];
extern u8 D_800DFD30[];
extern u8 D_800E3D40;

s32 func_800CD004(void *arg0)
{
    s32 random;
    register s32 numerator ASM_REG("$4");
    register s32 denominator ASM_REG("$2");
    register s32 remainder ASM_REG("$3");
    register s32 value ASM_REG("$2");
    register s32 divisor ASM_REG("$3");
    register s32 first_coord ASM_REG("$2");
    void *object;
    register void *quad ASM_REG("$3");
    register void *tail ASM_REG("$4");
    void *sprite;
    register void *map ASM_REG("$4");
    void *texture;
    register s32 color ASM_REG("$4");
    s32 variant;
    register s32 table_value ASM_REG("$3");
    s32 table_delta;
    s32 result;
    u8 *counter;

    if (D_800E3D40 == 0) {
        random = func_800A6D30();
        divisor = FIELD(arg0, u8, 3);
        if (divisor != 0) {
            numerator = (u16)random;
            denominator = divisor;
            ASM_KEEP(numerator);
            ASM_KEEP(divisor);
            ASM_KEEP(denominator);
            remainder = numerator % denominator;
            ASM_KEEP(remainder);
            value = remainder;
        } else {
            value = 0;
        }
    } else {
        value = 0;
    }
    ASM_KEEP(value);

    if (value < 0x30) {
        object = func_8003FC64(2);
        if (object == NULL) {
            goto return_object;
        }
        FIELD(object, void *, 0x10) = &D_800CCDA0;
        func_8004491C(object, &D_80045340);

        map = FIELD(arg0, void *, -0x14);
        ASM_KEEP(map);
        first_coord = FIELD(map, u8, 0x24);
        ASM_KEEP(first_coord);
        quad = FIELD(object, void *, 8);
        ASM_KEEP(quad);
        FIELD(quad, s16, 2) = (first_coord << 6) + 0x20;
        FIELD(quad, s16, 6) = (FIELD(map, u8, 0x25) << 6) + 0x20;
        FIELD(quad, s16, 0xA) = FIELD(arg0, u16, 0x88) - 0x200;

        sprite = FIELD(object, void *, 0xC);
        FIELD(sprite, s16, 0x1E) = 0x1000;
        FIELD(sprite, s16, 0x1C) = 0x1000;
        color = 0x808080;
        ASM_KEEP(color);
        FIELD(sprite, s32, 0xC) = color;

        variant = func_80069EF8(color);
        if (variant & 3) {
            texture = D_800DFD0C;
        } else {
            texture = D_800DFD30;
        }
        FIELD(sprite, void *, 8) = texture;
        FIELD(sprite, s16, 0x10) = 0x20;

        table_value = D_800DDC40[FIELD(arg0, u8, 0x13)];
        ASM_KEEP(table_value);
        table_delta = FIELD(arg0, u16, 0x88) - table_value;
        tail = (u8 *)object + 0x20;
        ASM_KEEP(tail);
        FIELD(tail, s16, 0xA) = table_delta;
        FIELD(object, void *, 0x20) = arg0;
        FIELD(tail, s16, 6) = 0xC;

        counter = D_80083460;
        FIELD(counter, u16, 0xA) = FIELD(counter, u16, 0xA) + 1;
        func_800A56E0(0x50D);
        goto return_object;
    }

    if (FIELD(arg0, u8, 0x13) == 0) {
        /* PASSTHRU (audit `need` = $a3): retail forwards this row's incoming
           $a3 straight through the call, so the site must NOT be spelled with
           empty parentheses.  The forwarded value lives in $a3 already; the
           pins name it (and the o32 positions before it) without emitting a
           byte.  decomp_issues.md sections 20-22. */
        register s32 fa0 ASM_REG("$4");
        register s32 fa1 ASM_REG("$5");
        register s32 fa2 ASM_REG("$6");
        register s32 fa3 ASM_REG("$7");

        ASM_SET(fa0);
        func_800A6508(fa0, fa1, fa2, fa3);
    }
    result = 1;
    goto done;

return_object:
    return object != NULL;
done:
    return result;
}

/* MECHANISM: The natural long-lived arg/object/sprite locals encode retail's
   s2/s1/s0 roles and 0x20 frame. Split RNG-return and merged-value names keep
   the remainder CFG in v0; texture and byte-table paths preserve its joins. */
