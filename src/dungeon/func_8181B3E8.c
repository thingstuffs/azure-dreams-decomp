#include "common.h"

typedef struct S_80024BE8_0_pre {
    u16 unk_00;
} S_80024BE8_0_pre;   /* the 0x2 bytes before arg0 in func_80024BE8, addressed as arg0[-1] */

typedef struct S_80024BE8_0 {
    void * unk_00;
    u16 * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x6C];
    union { u16 u; s16 s; } unk_78;   /* accessed as both */
    u8 unk_7A;
    s8 unk_7B;
    u8 pad_7C[0x2];
    union { s16 s; u16 u; } unk_7E;   /* accessed as both */
    u8 pad_80[0x2];
    u16 unk_82;
    u16 unk_84;
    union { u16 u; s16 s; } unk_86;   /* accessed as both */
    u8 pad_88[0x1A];
    s8 unk_A2;
    s8 unk_A3;
} S_80024BE8_0;   /* arg0 in func_80024BE8 */

typedef struct S_80024BE8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80024BE8_1;   /* task in func_80024BE8 */

typedef struct S_80024BE8_2 {
    u8 pad_00[0xC];
    union { struct { s32 v; } at00; struct { s8 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80024BE8_2;   /* arg2 in func_80024BE8 */

typedef struct S_80024BE8_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80024BE8_3_pre;   /* the 0x14 bytes before base in func_80024BE8, addressed as base[-1] */

typedef struct S_80024BE8_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} S_80024BE8_3;   /* base in func_80024BE8 */

typedef struct S_80024BE8_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80024BE8_4;   /* child0 in func_80024BE8 */

typedef struct S_80024BE8_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024BE8_5;   /* arg1 in func_80024BE8 */

typedef struct S_80024BE8_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024BE8_6;   /* origin in func_80024BE8 */

typedef struct S_80024BE8_7 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_80024BE8_7;   /* target0 in func_80024BE8 */

typedef struct S_80024BE8_8 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80024BE8_8;   /* graphics0 in func_80024BE8 */

typedef struct S_80024BE8_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_80024BE8_9;   /* target_position1 in func_80024BE8 */

typedef struct S_80024BE8_10 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_80024BE8_10;   /* graphics1 in func_80024BE8 */

typedef struct S_80024BE8_11 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80024BE8_11;   /* entity1 in func_80024BE8 */

typedef struct S_80024BE8_12 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80024BE8_12;   /* sprite1 in func_80024BE8 */

typedef struct S_80024BE8_13 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80024BE8_13;   /* position1 in func_80024BE8 */

typedef struct S_80024BE8_14 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_80024BE8_14;   /* graphics3 in func_80024BE8 */

typedef struct S_80024BE8_15 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
} S_80024BE8_15;   /* entity4 in func_80024BE8 */

typedef struct S_80024BE8_16 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x8];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_80024BE8_16;   /* sprite4 in func_80024BE8 */

typedef struct S_80024BE8_17 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    s32 unk_08;
} S_80024BE8_17;   /* position4 in func_80024BE8 */

typedef struct S_80024BE8_18 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_80024BE8_18;   /* sprite_arg4 in func_80024BE8 */

typedef struct S_80024BE8_19 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80024BE8_19;   /* target5 in func_80024BE8 */

typedef struct S_80024BE8_20_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80024BE8_20_pre;   /* the 0x14 bytes before target_reload5 in func_80024BE8, addressed as target_reload5[-1] */

typedef struct S_80024BE8_21 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80024BE8_21;   /* graphics5 in func_80024BE8 */

typedef struct S_80024BE8_22 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80024BE8_22;   /* ((S_80024BE8_1 *)task)->unk_0C in func_80024BE8 */

typedef struct S_80024BE8_23_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_80024BE8_23_pre;   /* the 0x18 bytes before ((S_80024BE8_3 *)base)->unk_60 in func_80024BE8, addressed as ((S_80024BE8_3 *)base)->unk_60[-1] */

typedef struct S_80024BE8_23 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} S_80024BE8_23;   /* ((S_80024BE8_3 *)base)->unk_60 in func_80024BE8 */



typedef struct Pair16 {
    s16 x;
    u16 y;
} Pair16;

typedef struct PathBlock {
    Pair16 entries[8];
} PathBlock;

extern void func_800240C0(void *, void *, void *, s16, s32, s32);
extern void func_80024758(void *, s16, s32, s32, s32, s32, s32);
extern void func_800249A0(void *, s16, s16, s16, s32);
extern void func_8003DB94(void *, void *, s32);
extern s32 func_8003DF74(s32, void *, s16 *, s32);
extern void *func_8003FC64(s32);
extern void func_800419EC(s32, s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80044A50(void *);
extern void func_800478B8(void *);
extern s32 func_80069EF8(void);
extern void func_8009CE1C(void *, s32, u8, s32, s32, void *, s32);
extern s32 func_800A4778(u16, u16, s16, void *);
extern void func_800A56E0(s32);

extern PathBlock D_80024004;
extern u8 D_8002443C[];
extern u8 D_80024B14[];
extern u8 D_800258FC[];
extern s16 D_80025914[8];
extern u8 D_80045340[];
extern u8 D_80045C34[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s32 D_800814A0[3];
extern s32 D_8008346C[3];
extern u8 D_800DE870[];
extern u8 D_800DE9D0[];

void func_80024BE8(void *in0, void *in1, void *in2) {
    s16 delta[3];
    PathBlock path;
    void *arg0 = in0;
    void *arg1 = in1;
    void *arg2 = in2;
    register void *base ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 state;

    base = ((S_80024BE8_0 *)arg0)->unk_00;
    path = D_80024004;
    ASM_KEEP(arg1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    {
    S_80024BE8_1 *task;
    S_80024BE8_6 *origin;
    void **jump_table;
    static void *const keepalive[] = {
        &&state_0, &&state_1, &&state_2, &&state_3, &&state_4,
        &&state_5, &&state_6, &&common, &&state_8
    };

    task = (u8 *)base - 0x20;
    origin = task->unk_08;
    ((S_80024BE8_0 *)arg0)->unk_82++;
    state = ((S_80024BE8_0 *)arg0)->unk_0A.s;

    if ((u32)state >= 9U) {
        goto common;
    }
    jump_table = (void **)0x80020000;
    ASM_KEEP(jump_table);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    jump_table = (void **)((u8 *)jump_table + 0x4028);
    ASM_KEEP(jump_table);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    goto *jump_table[state];

state_0:
{
    S_80024BE8_4 *child0;
    void *target0;
    register void *graphics0 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 *lookup0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *lookup_entry0;
    register s32 fallback0 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 difference0;
    s32 lookup_byte0;
    s32 graphics_byte0;
    s32 compare_byte0;
    register s32 direction0 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 sum0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 advance_value0;
    u16 mode0;
    u16 target_height0;
    u16 value0;

    ((S_80024BE8_2 *)arg2)->unk_0C.at00.v = 0x808080;
    ((S_80024BE8_2 *)arg2)->unk_1E = 0x400;
    ((S_80024BE8_2 *)arg2)->unk_1C = 0x400;
    ((S_80024BE8_2 *)arg2)->unk_12 = 0x7DCF;
    ((S_80024BE8_2 *)arg2)->unk_14 |= 0x100;
    ((S_80024BE8_0 *)arg0)->unk_84 = 0;
    func_8003DB94(arg2, D_800DE870, 2);
    mode0 = ((S_80024BE8_3 *)base)->unk_2A;
    D_80025914[0] = 1;
    ((S_80024BE8_0 *)arg0)->unk_7E.s = (mode0 >> 9) & 7;
    ((S_80024BE8_0 *)arg0)->unk_0A.s++;

    child0 = task->unk_0C;
    if ((func_8003DF74(child0->unk_08, child0, delta, 0) != 0) ||
        (((S_80024BE8_22 *)(task->unk_0C))->unk_14 & 0x8000)) {
        ((S_80024BE8_5 *)arg1)->unk_00.at02.v = origin->unk_02;
        ((S_80024BE8_5 *)arg1)->unk_04.at02.v = origin->unk_06;
        value0 = origin->unk_0A;
        ((S_80024BE8_5 *)arg1)->unk_08.at02.v = value0;

        if (!(((S_80024BE8_22 *)(task->unk_0C))->unk_14 & 0x8000)) {
            ((S_80024BE8_5 *)arg1)->unk_00.at02.v += delta[0];
            ((S_80024BE8_5 *)arg1)->unk_04.at02.v += delta[1];
            ((S_80024BE8_5 *)arg1)->unk_08.at02.v += delta[2];
        } else {
            ((S_80024BE8_5 *)arg1)->unk_08.at02.v = value0 - 0x40;
        }

        if (*((S_80024BE8_0 *)arg0)->unk_04 & 0x80) {
            if (!(((S_80024BE8_0 *)arg0)->unk_7A & 4)) {
                func_8004491C((u8 *)arg0 - 0x20, D_80045340);
                ((S_80024BE8_2 *)arg2)->unk_10 = 0x60;
                ((S_80024BE8_2 *)arg2)->unk_14 |= 0xC;
                ((S_80024BE8_0 *)arg0)->unk_7A |= 4;
            }

            fallback0 = 8;
            target0 = ((S_80024BE8_3 *)base)->unk_60;
            if (target0 != 0) {
                target_height0 = ((S_80024BE8_7 *)target0)->unk_88;
                direction0 = ((S_80024BE8_0 *)arg0)->unk_7E.s;
                ((S_80024BE8_0 *)arg0)->unk_78.u = target_height0;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                lookup0 = D_8006CCD8;
                lookup_entry0 = lookup0 + direction0 * 2;
                graphics0 = ((S_80024BE8_3_pre *)base)[-1].unk_00;
                lookup_byte0 = *lookup_entry0;
                graphics_byte0 = ((S_80024BE8_8 *)graphics0)->unk_24;
                sum0 = graphics_byte0 + lookup_byte0;
                ((S_80024BE8_0 *)arg0)->unk_A2 = sum0;
                lookup0 = D_8006CCE8;
                direction0 = ((S_80024BE8_0 *)arg0)->unk_7E.s;
                lookup_entry0 = lookup0 + direction0 * 2;
                graphics_byte0 = ((S_80024BE8_8 *)graphics0)->unk_25;
                lookup_byte0 = *lookup_entry0;
                sum0 = graphics_byte0 + lookup_byte0;
                ((S_80024BE8_0 *)arg0)->unk_A3 = sum0;
                difference0 = ((S_80024BE8_3 *)base)->unk_72;
                compare_byte0 = ((S_80024BE8_8 *)graphics0)->unk_24;
                if (difference0 == compare_byte0) {
                    difference0 = ((S_80024BE8_3 *)base)->unk_73;
                    compare_byte0 = ((S_80024BE8_8 *)graphics0)->unk_25;
                }
                difference0 -= compare_byte0;
                if (difference0 < 0) {
                    difference0 = -difference0;
                }
                difference0 *= 2;
                difference0 -= 1;
                ((S_80024BE8_0 *)arg0)->unk_7B = difference0;
            } else {
                target_height0 = ((S_80024BE8_3 *)base)->unk_88;
                ((S_80024BE8_0 *)arg0)->unk_7B = fallback0;
                ((S_80024BE8_0 *)arg0)->unk_78.u = target_height0 - 0x50;
            }

            ((S_80024BE8_5 *)arg1)->unk_0C = path.entries[((S_80024BE8_0 *)arg0)->unk_7E.s].x << 16;
            ((S_80024BE8_5 *)arg1)->unk_10 = path.entries[((S_80024BE8_0 *)arg0)->unk_7E.s].y << 16;
            ((S_80024BE8_5 *)arg1)->unk_14 =
                ((((S_80024BE8_0 *)arg0)->unk_78.s << 16) - ((S_80024BE8_5 *)arg1)->unk_08.at00.v) /
                ((S_80024BE8_0 *)arg0)->unk_7B;
            advance_value0 = ((S_80024BE8_0 *)arg0)->unk_0A.u;
            ((S_80024BE8_0 *)arg0)->unk_82 = 0;
            ((S_80024BE8_0 *)arg0)->unk_0A.u = advance_value0 + 1;
            goto common;
        }
    }
    goto common;
}
}

state_1:
{
    void *graphics1;
    void *target_position1;
    void *animation1;
    void *entity1;
    register void *sprite1 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register void *position1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 i1 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 color1;
    register s32 call_mode1 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 random_color1;

    if ((func_800A4778(((S_80024BE8_5 *)arg1)->unk_00.at02.v, ((S_80024BE8_5 *)arg1)->unk_04.at02.v,
                       ((S_80024BE8_5 *)arg1)->unk_08.at02u.v, ((S_80024BE8_3 *)base)->unk_60) << 16) != 0) {
        ((S_80024BE8_0 *)arg0)->unk_0A.s = 8;
        ((S_80024BE8_0 *)arg0)->unk_82 = 0;
        ((S_80024BE8_2 *)arg2)->unk_14 |= 0x80;
        goto common;
    }

    i1 = 0;
    do {
        register void *a0v ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        s32 a1v;
        register s32 a2v ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 a3v ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        i1++;
        random_color1 = func_80069EF8();
        a0v = (u8 *)arg0 - 0x20;
        a2v = 0xF04040;
        ASM_KEEP_NV(a2v);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        a3v = (random_color1 & 0xFF) | 0x80;
        ASM_KEEP_NV(a3v);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        a1v = ((S_80024BE8_0 *)arg0)->unk_7E.s;
        func_80024758(a0v, a1v, a2v, a3v, 0, 0, 0);
    } while (i1 < 4);

    ((S_80024BE8_0 *)arg0)->unk_7B--;
    if (((S_80024BE8_0 *)arg0)->unk_7B > 0) {
        goto state_2;
    }

    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    func_80044A50((u8 *)arg0 - 0x20);
    call_mode1 = 4;
    if (((S_80024BE8_3 *)base)->unk_60 != 0) {
        ((S_80024BE8_0 *)arg0)->unk_86.u = 0;
        ((S_80024BE8_0 *)arg0)->unk_0A.s++;
        target_position1 = ((S_80024BE8_23_pre *)(((S_80024BE8_3 *)base)->unk_60))[-1].unk_00;
        ((S_80024BE8_5 *)arg1)->unk_00.at02.v = ((S_80024BE8_9 *)target_position1)->unk_02;
        ((S_80024BE8_5 *)arg1)->unk_04.at02.v = ((S_80024BE8_9 *)target_position1)->unk_06;
        ((S_80024BE8_5 *)arg1)->unk_08.at02.v = ((S_80024BE8_0 *)arg0)->unk_78.u;
        ((S_80024BE8_23 *)(((S_80024BE8_3 *)base)->unk_60))->unk_1C |= 0x10000000;
        graphics1 = ((S_80024BE8_23_pre *)(((S_80024BE8_3 *)base)->unk_60))[-1].unk_04;
        color1 = 0x80;
        ASM_KEEP(color1);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ((S_80024BE8_10 *)graphics1)->unk_0E = color1;
        ((S_80024BE8_10 *)graphics1)->unk_0C = color1;
        ((S_80024BE8_10 *)graphics1)->unk_0D = color1;
        func_800419EC(call_mode1, 8, graphics1);
        func_800A56E0(0x300);

        entity1 = func_8003FC64(0x212);
        if (entity1 != 0) {
            ((S_80024BE8_11 *)entity1)->unk_10 = D_80024B14;
            func_8004491C(entity1, D_80045C34);
            sprite1 = ((S_80024BE8_11 *)entity1)->unk_0C;
            ((S_80024BE8_12 *)sprite1)->unk_10 = 0;
            ((S_80024BE8_12 *)sprite1)->unk_14 |= 0xC;
            position1 = ((S_80024BE8_11 *)entity1)->unk_08;
            ((S_80024BE8_13 *)position1)->unk_02 = ((S_80024BE8_5 *)arg1)->unk_00.at02.v;
            ((S_80024BE8_13 *)position1)->unk_06 = ((S_80024BE8_5 *)arg1)->unk_04.at02.v;
            ((S_80024BE8_13 *)position1)->unk_08.at00.v = ((S_80024BE8_5 *)arg1)->unk_08.at00.v;
            animation1 = D_800258FC;
            sprite1 = ((S_80024BE8_11 *)entity1)->unk_0C;
            ((S_80024BE8_12 *)sprite1)->unk_08 = animation1;
            ((S_80024BE8_12 *)sprite1)->unk_0E = color1;
            ((S_80024BE8_12 *)sprite1)->unk_0D = color1;
            ((S_80024BE8_12 *)sprite1)->unk_0C = color1;
            ((S_80024BE8_12 *)sprite1)->unk_1E = 1;
            ((S_80024BE8_12 *)sprite1)->unk_1C = 1;
            ((S_80024BE8_12 *)sprite1)->unk_14 ^= 0xC;
            ((S_80024BE8_13 *)position1)->unk_08.at02.v = ((S_80024BE8_23 *)(((S_80024BE8_3 *)base)->unk_60))->unk_88;
        }
        ((S_80024BE8_5 *)arg1)->unk_08.at02.v = ((S_80024BE8_23 *)(((S_80024BE8_3 *)base)->unk_60))->unk_88;
    } else {
        ((S_80024BE8_0 *)arg0)->unk_0A.s = 8;
        ((S_80024BE8_0 *)arg0)->unk_82 = 0;
        ((S_80024BE8_2 *)arg2)->unk_0C.at02.v = 0;
        ((S_80024BE8_2 *)arg2)->unk_0C.at01.v = 0;
        ((S_80024BE8_2 *)arg2)->unk_0C.at00u.v = 0;
    }
    goto common;
}

state_2:
{
    register s32 random_x2 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 random_y2 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    ((S_80024BE8_5 *)arg1)->unk_00.at00.v += ((S_80024BE8_5 *)arg1)->unk_0C;
    ((S_80024BE8_5 *)arg1)->unk_04.at00.v += ((S_80024BE8_5 *)arg1)->unk_10;
    ((S_80024BE8_5 *)arg1)->unk_08.at00.v += ((S_80024BE8_5 *)arg1)->unk_14;

    random_x2 = func_80069EF8() & 0xF;
    ASM_KEEP(random_x2);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    random_x2 = (s16)(random_x2 - 8);
    random_y2 = func_80069EF8() & 0xF;
    ASM_KEEP(random_y2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    random_y2 = (s16)(random_y2 - 8);
    func_800240C0(arg0, arg1, arg2, random_x2, random_y2,
                  (s16)((func_80069EF8() & 0xF) - 8));
    random_x2 = func_80069EF8() & 0xF;
    random_x2 = (s16)(random_x2 - 8);
    random_y2 = func_80069EF8() & 0xF;
    random_y2 = (s16)(random_y2 - 8);
    func_800240C0(arg0, arg1, arg2, random_x2, random_y2,
                  (s16)((func_80069EF8() & 0xF) - 8));
    random_x2 = func_80069EF8() & 0xF;
    random_x2 = (s16)(random_x2 - 8);
    random_y2 = func_80069EF8() & 0xF;
    random_y2 = (s16)(random_y2 - 8);
    func_800240C0(arg0, arg1, arg2, random_x2, random_y2,
                  (s16)((func_80069EF8() & 0xF) - 8));
    random_x2 = func_80069EF8() & 0xF;
    random_x2 = (s16)(random_x2 - 8);
    random_y2 = func_80069EF8() & 0xF;
    random_y2 = (s16)(random_y2 - 8);
    func_800240C0(arg0, arg1, arg2, random_x2, random_y2,
                  (s16)((func_80069EF8() & 0xF) - 8));
    random_x2 = func_80069EF8() & 0xF;
    random_x2 = (s16)(random_x2 - 8);
    random_y2 = func_80069EF8() & 0xF;
    random_y2 = (s16)(random_y2 - 8);
    func_800240C0(arg0, arg1, arg2, random_x2, random_y2,
                  (s16)((func_80069EF8() & 0xF) - 8));
    random_x2 = func_80069EF8() & 0xF;
    random_x2 = (s16)(random_x2 - 8);
    random_y2 = func_80069EF8() & 0xF;
    random_y2 = (s16)(random_y2 - 8);
    func_800240C0(arg0, arg1, arg2, random_x2, random_y2,
                  (s16)((func_80069EF8() & 0xF) - 8));
    goto common;
}

state_3:
{
    register void *graphics3 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 value3;
    u16 advance_value3;

    value3 = ((S_80024BE8_0 *)arg0)->unk_86.u;
    value3 += 2;
    ((S_80024BE8_0 *)arg0)->unk_86.u = value3;
    graphics3 = ((S_80024BE8_23_pre *)(((S_80024BE8_3 *)base)->unk_60))[-1].unk_04;
    ((S_80024BE8_14 *)graphics3)->unk_0E = (s16)value3 * 3 - 0x70;
    ((S_80024BE8_14 *)graphics3)->unk_0D = 0x70 - ((S_80024BE8_0 *)arg0)->unk_86.s * 3;
    ((S_80024BE8_14 *)graphics3)->unk_0C = 0x70 - ((S_80024BE8_0 *)arg0)->unk_86.s * 3;
    if (((S_80024BE8_0 *)arg0)->unk_86.s >= 0x24) {
        advance_value3 = ((S_80024BE8_0 *)arg0)->unk_0A.u;
        ((S_80024BE8_0 *)arg0)->unk_86.u = 0;
        ((S_80024BE8_0 *)arg0)->unk_82 = 0;
        ((S_80024BE8_0 *)arg0)->unk_0A.u = advance_value3 + 1;
        goto common;
    }
    goto common;
}

state_4:
{
    void *animation4;
    register void *entity4 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *sprite4;
    void *position4;
    register s32 i4 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 random_x4 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 entity_kind4;
    u16 direction_preload4;
    s32 animation_mode4;
    u16 advance_value4;
    s32 direction4;
    s32 random_position4;
    s32 position_value4;
    s32 position_z4;
    u16 value4;

    i4 = 0;
    do {
        i4++;
        random_x4 = func_80069EF8() & 0x3F;
        ASM_KEEP(random_x4);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        random_x4 = (s16)(random_x4 - 0x20);
        func_800249A0((u8 *)arg0 - 0x20, random_x4,
                      (s16)((func_80069EF8() & 0x3F) - 0x20),
                      (s16)(-(((S_80024BE8_0 *)arg0)->unk_86.s * 2) + 0x10), 0x1E);
    } while (i4 < 2);

    entity_kind4 = 0x212;
    direction4 = ((S_80024BE8_0 *)arg0)->unk_86.u & 3;
    entity4 = func_8003FC64(entity_kind4);
    if (entity4 != 0) {
        ((S_80024BE8_15 *)entity4)->unk_22 = 0x1E;
        ((S_80024BE8_15 *)entity4)->unk_10 = D_8002443C;
        func_8004491C(entity4, D_80045340);
        sprite4 = ((S_80024BE8_15 *)entity4)->unk_0C;
        ((S_80024BE8_16 *)sprite4)->unk_10 = 0;
        ((S_80024BE8_16 *)sprite4)->unk_14 |= 0xC;
        position4 = ((S_80024BE8_15 *)entity4)->unk_08;
        random_position4 = func_80069EF8() & 0xF;
        position_value4 = ((S_80024BE8_5 *)arg1)->unk_00.at02.v;
        position_value4 -= 8;
        position_value4 += random_position4;
        ((S_80024BE8_17 *)position4)->unk_02 = position_value4;
        random_position4 = func_80069EF8() & 0xF;
        position_value4 = ((S_80024BE8_5 *)arg1)->unk_04.at02.v;
        position_value4 -= 8;
        position_value4 += random_position4;
        ((S_80024BE8_17 *)position4)->unk_06 = position_value4;
        if (func_80069EF8() & 1) {
            ((S_80024BE8_16 *)sprite4)->unk_14 |= 1;
        }

        switch (direction4) {
        case 0:
            ((S_80024BE8_17 *)position4)->unk_06 = ((S_80024BE8_5 *)arg1)->unk_04.at02.v + 8;
            ((S_80024BE8_16 *)sprite4)->unk_06 = 7;
            break;
        case 1:
            ((S_80024BE8_17 *)position4)->unk_02 = ((S_80024BE8_5 *)arg1)->unk_00.at02.v - 8;
            ((S_80024BE8_16 *)sprite4)->unk_06 = 7;
            break;
        case 2:
            ((S_80024BE8_17 *)position4)->unk_02 = ((S_80024BE8_5 *)arg1)->unk_00.at02.v + 8;
            ((S_80024BE8_16 *)sprite4)->unk_06 = 7;
            break;
        case 3:
            ((S_80024BE8_17 *)position4)->unk_06 = ((S_80024BE8_5 *)arg1)->unk_04.at02.v - 8;
            ((S_80024BE8_16 *)sprite4)->unk_06 = -7;
            break;
        }

        animation4 = D_800DE9D0;
        position_z4 = ((S_80024BE8_5 *)arg1)->unk_08.at00.v;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        animation_mode4 = 0;
        ASM_KEEP(animation_mode4);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ((S_80024BE8_17 *)position4)->unk_08 = position_z4;
        {
        void *sprite_arg4;
        s32 scale_state4;

        sprite4 = ((S_80024BE8_15 *)entity4)->unk_0C;
        scale_state4 = ((S_80024BE8_0 *)arg0)->unk_86.s;
        sprite_arg4 = sprite4;
        ((S_80024BE8_18 *)sprite_arg4)->unk_1C = scale_state4 * 0xAA;
        scale_state4 = ((S_80024BE8_0 *)arg0)->unk_86.s;
        ((S_80024BE8_18 *)sprite_arg4)->unk_0E = 0x80;
        ((S_80024BE8_18 *)sprite_arg4)->unk_0D = 0x80;
        ((S_80024BE8_18 *)sprite_arg4)->unk_0C = 0x80;
        ((S_80024BE8_18 *)sprite_arg4)->unk_1E = scale_state4 * 0xCC;
        func_8003DB94(sprite_arg4, animation4, animation_mode4);
        }
    }

    value4 = ((S_80024BE8_0 *)arg0)->unk_86.u + 2;
    ((S_80024BE8_0 *)arg0)->unk_86.u = value4;
    if ((s16)value4 >= 0x3D) {
        value4 = 0x28;
        advance_value4 = ((S_80024BE8_0 *)arg0)->unk_0A.u;
        ((S_80024BE8_0 *)arg0)->unk_86.u = value4;
        ((S_80024BE8_0 *)arg0)->unk_0A.u = advance_value4 + 1;
        goto common;
    }
    goto common;
}

state_5:
{
    void *target5;
    register void *graphics5 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *target_reload5;
    s32 i5;
    register s32 random_x5 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 random_y5 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 mask5;
    u16 value5;

    i5 = 0;
    do {
        i5++;
        random_x5 = func_80069EF8() & 0x3F;
        ASM_KEEP(random_x5);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        random_x5 = (s16)(random_x5 - 0x20);
        random_y5 = func_80069EF8() & 0x3F;
        ASM_KEEP(random_y5);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        random_y5 = (s16)(random_y5 - 0x20);
        func_800249A0((u8 *)arg0 - 0x20, random_x5, random_y5,
                      (s16)(-0x20 - (func_80069EF8() & 0x3F)), 0x1E);
    } while (i5 < 2);

    value5 = ((S_80024BE8_0 *)arg0)->unk_86.u - 2;
    ((S_80024BE8_0 *)arg0)->unk_86.u = value5;
    mask5 = 0x10000000;
    if ((s16)value5 <= 0) {
        ((S_80024BE8_0 *)arg0)->unk_86.u = 0;
        ((S_80024BE8_0 *)arg0)->unk_82 = 0;
        ((S_80024BE8_0 *)arg0)->unk_0A.s++;
        target5 = ((S_80024BE8_3 *)base)->unk_60;
        ((S_80024BE8_19 *)target5)->unk_1C ^= mask5;
        target_reload5 = ((S_80024BE8_3 *)base)->unk_60;
        graphics5 = ((S_80024BE8_20_pre *)target_reload5)[-1].unk_00;
        ((S_80024BE8_21 *)graphics5)->unk_0C = 0x80;
        ((S_80024BE8_21 *)graphics5)->unk_0D = 0x80;
        ((S_80024BE8_21 *)graphics5)->unk_0E = 0x80;
        func_8009CE1C(((S_80024BE8_3 *)base)->unk_60, 0x10, ((S_80024BE8_0 *)arg0)->unk_09, 2,
                      (s16)(((S_80024BE8_0 *)arg0)->unk_7E.u << 9), base, 2);
    }
    goto common;
}

state_6:
{
    u16 value6;

    value6 = ((S_80024BE8_0 *)arg0)->unk_82 + 1;
    ((S_80024BE8_0 *)arg0)->unk_82 = value6;
    if ((s16)value6 >= 0x3D) {
        ((S_80024BE8_0 *)arg0)->unk_0A.s = 8;
        ((S_80024BE8_0 *)arg0)->unk_82 = 0x1E;
    }
    goto common;
}

state_8:
{
    u16 value7;
    s32 flag7;

    value7 = ((S_80024BE8_0 *)arg0)->unk_82;
    ((S_80024BE8_0 *)arg0)->unk_82 = value7 + 1;
    if ((s16)(value7 + 1) >= 0x1F) {
        flag7 = D_80025914[0];
        ((S_80024BE8_0 *)arg0)->unk_82 = value7;
        if (flag7 == 0) {
            D_8008346C[0] = 0;
            ((S_80024BE8_0_pre *)arg0)[-1].unk_00 |= 0x8000;
            D_800814A0[0] |= 0x8000;
        } else {
            D_80025914[0] = 0;
        }
    }
    goto common;
}

common:
{
    u16 common_value;

    func_800478B8(arg2);
    common_value = ((S_80024BE8_0 *)arg0)->unk_84;
    ((S_80024BE8_0 *)arg0)->unk_84 = common_value + 1;
    if ((s16)common_value >= 5) {
        func_8003DB94(arg2, D_800DE870, 2);
        ((S_80024BE8_0 *)arg0)->unk_84 = 0;
    }
}
}
