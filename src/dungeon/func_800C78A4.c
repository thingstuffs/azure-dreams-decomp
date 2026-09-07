#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800CD004_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD004_0_pre;   /* the 0x14 bytes before arg0 in func_800CD004, addressed as arg0[-1] */

typedef struct S_800CD004_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0xF];
    u8 unk_13;
    u8 pad_14[0x74];
    u16 unk_88;
} S_800CD004_0;   /* arg0 in func_800CD004 */

typedef struct S_800CD004_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_800CD004_1;   /* object in func_800CD004 */

typedef struct S_800CD004_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CD004_2;   /* map in func_800CD004 */

typedef struct S_800CD004_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CD004_3;   /* quad in func_800CD004 */

typedef struct S_800CD004_4 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0xA];
    s16 unk_1C;
    s16 unk_1E;
} S_800CD004_4;   /* sprite in func_800CD004 */

typedef struct S_800CD004_5 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CD004_5;   /* tail in func_800CD004 */

typedef struct S_800CD004_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CD004_6;   /* counter in func_800CD004 */



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
    s32 numerator;
    register s32 denominator ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 remainder ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 value ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 divisor;
    s32 first_coord;
    void *object;
    S_800CD004_3 *quad;
    S_800CD004_5 *tail;
    S_800CD004_4 *sprite;
    S_800CD004_2 *map;
    void *texture;
    s32 color;
    s32 variant;
    register s32 table_value ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 table_delta;
    s32 result;
    u8 *counter;

    if (D_800E3D40 == 0) {
        random = func_800A6D30();
        divisor = ((S_800CD004_0 *)arg0)->unk_03;
        if (divisor != 0) {
            numerator = (u16)random;
            denominator = divisor;
            ASM_KEEP(numerator);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            remainder = numerator % denominator;
            value = remainder;
        } else {
            value = 0;
        }
    } else {
        value = 0;
    }

    if (value < 0x30) {
        object = func_8003FC64(2);
        if (object == NULL) {
            goto return_object;
        }
        ((S_800CD004_1 *)object)->unk_10 = &D_800CCDA0;
        func_8004491C(object, &D_80045340);

        map = ((S_800CD004_0_pre *)arg0)[-1].unk_00;
        first_coord = map->unk_24;
        ASM_KEEP(first_coord);   /* MATCH pin: retail schedule: same instructions, different order without it */
        quad = ((S_800CD004_1 *)object)->unk_08;
        ASM_KEEP(quad);   /* MATCH pin: load-bearing for the whole function shape */
        quad->unk_02 = (first_coord << 6) + 0x20;
        quad->unk_06 = (map->unk_25 << 6) + 0x20;
        quad->unk_0A = ((S_800CD004_0 *)arg0)->unk_88 - 0x200;

        sprite = ((S_800CD004_1 *)object)->unk_0C;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        color = 0x808080;
        ASM_KEEP(color);   /* MATCH pin: retail immediate-load split depends on it */
        sprite->unk_0C = color;

        variant = func_80069EF8(color);
        if (variant & 3) {
            texture = D_800DFD0C;
        } else {
            texture = D_800DFD30;
        }
        sprite->unk_08 = texture;
        sprite->unk_10 = 0x20;

        table_value = D_800DDC40[((S_800CD004_0 *)arg0)->unk_13];
        table_delta = ((S_800CD004_0 *)arg0)->unk_88 - table_value;
        tail = (u8 *)object + 0x20;
        ASM_KEEP(tail);   /* MATCH pin: keeps a statement from moving across a call/branch */
        tail->unk_0A = table_delta;
        ((S_800CD004_1 *)object)->unk_20 = arg0;
        tail->unk_06 = 0xC;

        counter = D_80083460;
        ((S_800CD004_6 *)counter)->unk_0A = ((S_800CD004_6 *)counter)->unk_0A + 1;
        func_800A56E0(0x50D);
        goto return_object;
    }

    if (((S_800CD004_0 *)arg0)->unk_13 == 0) {
        /* PASSTHRU (audit `need` = $a3): retail forwards this row's incoming
           $a3 straight through the call, so the site must NOT be spelled with
           empty parentheses.  The forwarded value lives in $a3 already; the
           pins name it (and the o32 positions before it) without emitting a
           byte.  decomp_issues.md sections 20-22. */
        s32 fa0;
        register s32 fa1 ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
        register s32 fa2 ASM_REG("$6");   /* MATCH pin: retail delay-slot contents depend on it */
        register s32 fa3 ASM_REG("$7");   /* MATCH pin: retail delay-slot contents depend on it */

        ASM_SET(fa0);   /* MATCH pin: retail delay-slot contents depend on it */
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
