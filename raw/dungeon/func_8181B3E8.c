#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
    register void *arg0 ASM_REG("$20") = in0;
    register void *arg1 ASM_REG("$22") = in1;
    register void *arg2 ASM_REG("$23") = in2;
    register void *base ASM_REG("$21");
    s32 state;

    base = FIELD(arg0, void *, 0);
    path = D_80024004;
    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    {
    void *task;
    void *origin;
    register void **jump_table ASM_REG("$2");
    static void *const keepalive[] = {
        &&state_0, &&state_1, &&state_2, &&state_3, &&state_4,
        &&state_5, &&state_6, &&common, &&state_8
    };

    task = (u8 *)base - 0x20;
    origin = FIELD(task, void *, 8);
    FIELD(arg0, u16, 0x82)++;
    state = FIELD(arg0, s16, 0xA);

    if ((u32)state >= 9U) {
        goto common;
    }
    jump_table = (void **)0x80020000;
    ASM_KEEP(jump_table);
    jump_table = (void **)((u8 *)jump_table + 0x4028);
    ASM_KEEP(jump_table);
    goto *jump_table[state];

state_0:
{
    void *child0;
    register void *target0 ASM_REG("$2");
    register void *graphics0 ASM_REG("$6");
    register u8 *lookup0 ASM_REG("$2");
    register u8 *lookup_entry0 ASM_REG("$3");
    register s32 fallback0 ASM_REG("$3");
    register s32 difference0 ASM_REG("$2");
    register s32 lookup_byte0 ASM_REG("$3");
    register s32 graphics_byte0 ASM_REG("$2");
    register s32 compare_byte0 ASM_REG("$3");
    register s32 direction0 ASM_REG("$3");
    register s32 sum0 ASM_REG("$2");
    register u16 advance_value0 ASM_REG("$2");
    u16 mode0;
    u16 target_height0;
    u16 value0;

    FIELD(arg2, s32, 0xC) = 0x808080;
    FIELD(arg2, s16, 0x1E) = 0x400;
    FIELD(arg2, s16, 0x1C) = 0x400;
    FIELD(arg2, s16, 0x12) = 0x7DCF;
    FIELD(arg2, u16, 0x14) |= 0x100;
    FIELD(arg0, u16, 0x84) = 0;
    func_8003DB94(arg2, D_800DE870, 2);
    mode0 = FIELD(base, u16, 0x2A);
    D_80025914[0] = 1;
    FIELD(arg0, s16, 0x7E) = (mode0 >> 9) & 7;
    FIELD(arg0, s16, 0xA)++;

    child0 = FIELD(task, void *, 0xC);
    if ((func_8003DF74(FIELD(child0, s32, 8), child0, delta, 0) != 0) ||
        (FIELD(FIELD(task, void *, 0xC), u16, 0x14) & 0x8000)) {
        FIELD(arg1, u16, 2) = FIELD(origin, u16, 2);
        FIELD(arg1, u16, 6) = FIELD(origin, u16, 6);
        value0 = FIELD(origin, u16, 0xA);
        FIELD(arg1, u16, 0xA) = value0;

        if (!(FIELD(FIELD(task, void *, 0xC), u16, 0x14) & 0x8000)) {
            FIELD(arg1, u16, 2) += delta[0];
            FIELD(arg1, u16, 6) += delta[1];
            FIELD(arg1, u16, 0xA) += delta[2];
        } else {
            FIELD(arg1, u16, 0xA) = value0 - 0x40;
        }

        if (*FIELD(arg0, u16 *, 4) & 0x80) {
            if (!(FIELD(arg0, u8, 0x7A) & 4)) {
                func_8004491C((u8 *)arg0 - 0x20, D_80045340);
                FIELD(arg2, s16, 0x10) = 0x60;
                FIELD(arg2, u16, 0x14) |= 0xC;
                FIELD(arg0, u8, 0x7A) |= 4;
            }

            fallback0 = 8;
            target0 = FIELD(base, void *, 0x60);
            if (target0 != 0) {
                target_height0 = FIELD(target0, u16, 0x88);
                direction0 = FIELD(arg0, s16, 0x7E);
                FIELD(arg0, u16, 0x78) = target_height0;
                ASM_SCHED_BARRIER();
                lookup0 = D_8006CCD8;
                lookup_entry0 = lookup0 + direction0 * 2;
                graphics0 = FIELD(base, void *, -0x14);
                lookup_byte0 = *lookup_entry0;
                ASM_KEEP_NV(lookup_byte0);
                graphics_byte0 = FIELD(graphics0, u8, 0x24);
                sum0 = graphics_byte0 + lookup_byte0;
                FIELD(arg0, s8, 0xA2) = sum0;
                lookup0 = D_8006CCE8;
                direction0 = FIELD(arg0, s16, 0x7E);
                lookup_entry0 = lookup0 + direction0 * 2;
                graphics_byte0 = FIELD(graphics0, u8, 0x25);
                lookup_byte0 = *lookup_entry0;
                ASM_KEEP_NV(lookup_byte0);
                sum0 = graphics_byte0 + lookup_byte0;
                FIELD(arg0, s8, 0xA3) = sum0;
                difference0 = FIELD(base, s8, 0x72);
                compare_byte0 = FIELD(graphics0, u8, 0x24);
                if (difference0 == compare_byte0) {
                    difference0 = FIELD(base, s8, 0x73);
                    compare_byte0 = FIELD(graphics0, u8, 0x25);
                }
                difference0 -= compare_byte0;
                if (difference0 < 0) {
                    difference0 = -difference0;
                }
                difference0 *= 2;
                difference0 -= 1;
                FIELD(arg0, s8, 0x7B) = difference0;
            } else {
                target_height0 = FIELD(base, u16, 0x88);
                FIELD(arg0, s8, 0x7B) = fallback0;
                FIELD(arg0, u16, 0x78) = target_height0 - 0x50;
            }

            FIELD(arg1, s32, 0xC) = path.entries[FIELD(arg0, s16, 0x7E)].x << 16;
            FIELD(arg1, s32, 0x10) = path.entries[FIELD(arg0, s16, 0x7E)].y << 16;
            FIELD(arg1, s32, 0x14) =
                ((FIELD(arg0, s16, 0x78) << 16) - FIELD(arg1, s32, 8)) /
                FIELD(arg0, s8, 0x7B);
            advance_value0 = FIELD(arg0, u16, 0xA);
            FIELD(arg0, u16, 0x82) = 0;
            FIELD(arg0, u16, 0xA) = advance_value0 + 1;
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
    register void *entity1 ASM_REG("$19");
    register void *sprite1 ASM_REG("$16");
    register void *position1 ASM_REG("$17");
    register s32 i1 ASM_REG("$18");
    register s32 color1 ASM_REG("$18");
    register s32 call_mode1 ASM_REG("$4");
    s32 random_color1;

    if ((func_800A4778(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                       FIELD(arg1, s16, 0xA), FIELD(base, void *, 0x60)) << 16) != 0) {
        FIELD(arg0, s16, 0xA) = 8;
        FIELD(arg0, u16, 0x82) = 0;
        FIELD(arg2, u16, 0x14) |= 0x80;
        goto common;
    }

    i1 = 0;
    ASM_KEEP(i1);
    do {
        register void *a0v ASM_REG("$4");
        register s32 a1v ASM_REG("$5");
        register s32 a2v ASM_REG("$6");
        register s32 a3v ASM_REG("$7");
        i1++;
        random_color1 = func_80069EF8();
        a0v = (u8 *)arg0 - 0x20;
        a2v = 0xF04040;
        ASM_KEEP_NV(a2v);
        a3v = (random_color1 & 0xFF) | 0x80;
        ASM_KEEP_NV(a3v);
        a1v = FIELD(arg0, s16, 0x7E);
        func_80024758(a0v, a1v, a2v, a3v, 0, 0, 0);
    } while (i1 < 4);

    FIELD(arg0, s8, 0x7B)--;
    if (FIELD(arg0, s8, 0x7B) > 0) {
        goto state_2;
    }

    ASM_KEEP(arg0);
    func_80044A50((u8 *)arg0 - 0x20);
    call_mode1 = 4;
    if (FIELD(base, void *, 0x60) != 0) {
        FIELD(arg0, u16, 0x86) = 0;
        FIELD(arg0, s16, 0xA)++;
        target_position1 = FIELD(FIELD(base, void *, 0x60), void *, -0x18);
        FIELD(arg1, u16, 2) = FIELD(target_position1, u16, 2);
        FIELD(arg1, u16, 6) = FIELD(target_position1, u16, 6);
        FIELD(arg1, u16, 0xA) = FIELD(arg0, u16, 0x78);
        FIELD(FIELD(base, void *, 0x60), s32, 0x1C) |= 0x10000000;
        graphics1 = FIELD(FIELD(base, void *, 0x60), void *, -0x14);
        color1 = 0x80;
        ASM_KEEP(color1);
        FIELD(graphics1, s8, 0xE) = color1;
        FIELD(graphics1, s8, 0xC) = color1;
        FIELD(graphics1, s8, 0xD) = color1;
        func_800419EC(call_mode1, 8, graphics1);
        func_800A56E0(0x300);

        entity1 = func_8003FC64(0x212);
        ASM_KEEP(entity1);
        if (entity1 != 0) {
            FIELD(entity1, void *, 0x10) = D_80024B14;
            func_8004491C(entity1, D_80045C34);
            sprite1 = FIELD(entity1, void *, 0xC);
            ASM_KEEP(sprite1);
            FIELD(sprite1, s16, 0x10) = 0;
            FIELD(sprite1, u16, 0x14) |= 0xC;
            position1 = FIELD(entity1, void *, 8);
            ASM_KEEP(position1);
            FIELD(position1, u16, 2) = FIELD(arg1, u16, 2);
            FIELD(position1, u16, 6) = FIELD(arg1, u16, 6);
            FIELD(position1, s32, 8) = FIELD(arg1, s32, 8);
            ASM_KEEP(position1);
            animation1 = D_800258FC;
            sprite1 = FIELD(entity1, void *, 0xC);
            FIELD(sprite1, void *, 8) = animation1;
            FIELD(sprite1, s8, 0xE) = color1;
            FIELD(sprite1, s8, 0xD) = color1;
            FIELD(sprite1, s8, 0xC) = color1;
            FIELD(sprite1, s16, 0x1E) = 1;
            FIELD(sprite1, s16, 0x1C) = 1;
            FIELD(sprite1, u16, 0x14) ^= 0xC;
            FIELD(position1, u16, 0xA) = FIELD(FIELD(base, void *, 0x60), u16, 0x88);
        }
        FIELD(arg1, u16, 0xA) = FIELD(FIELD(base, void *, 0x60), u16, 0x88);
    } else {
        FIELD(arg0, s16, 0xA) = 8;
        FIELD(arg0, u16, 0x82) = 0;
        FIELD(arg2, s8, 0xE) = 0;
        FIELD(arg2, s8, 0xD) = 0;
        FIELD(arg2, s8, 0xC) = 0;
    }
    goto common;
}

state_2:
{
    register s32 random_x2 ASM_REG("$17");
    register s32 random_y2 ASM_REG("$16");

    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);

    random_x2 = func_80069EF8() & 0xF;
    ASM_KEEP(random_x2);
    random_x2 = (s16)(random_x2 - 8);
    random_y2 = func_80069EF8() & 0xF;
    ASM_KEEP(random_y2);
    random_y2 = (s16)(random_y2 - 8);
    func_800240C0(arg0, arg1, arg2, random_x2, random_y2,
                  (s16)((func_80069EF8() & 0xF) - 8));
    random_x2 = func_80069EF8() & 0xF;
    ASM_KEEP(random_x2);
    random_x2 = (s16)(random_x2 - 8);
    random_y2 = func_80069EF8() & 0xF;
    ASM_KEEP(random_y2);
    random_y2 = (s16)(random_y2 - 8);
    func_800240C0(arg0, arg1, arg2, random_x2, random_y2,
                  (s16)((func_80069EF8() & 0xF) - 8));
    random_x2 = func_80069EF8() & 0xF;
    ASM_KEEP(random_x2);
    random_x2 = (s16)(random_x2 - 8);
    random_y2 = func_80069EF8() & 0xF;
    ASM_KEEP(random_y2);
    random_y2 = (s16)(random_y2 - 8);
    func_800240C0(arg0, arg1, arg2, random_x2, random_y2,
                  (s16)((func_80069EF8() & 0xF) - 8));
    random_x2 = func_80069EF8() & 0xF;
    ASM_KEEP(random_x2);
    random_x2 = (s16)(random_x2 - 8);
    random_y2 = func_80069EF8() & 0xF;
    ASM_KEEP(random_y2);
    random_y2 = (s16)(random_y2 - 8);
    func_800240C0(arg0, arg1, arg2, random_x2, random_y2,
                  (s16)((func_80069EF8() & 0xF) - 8));
    random_x2 = func_80069EF8() & 0xF;
    ASM_KEEP(random_x2);
    random_x2 = (s16)(random_x2 - 8);
    random_y2 = func_80069EF8() & 0xF;
    ASM_KEEP(random_y2);
    random_y2 = (s16)(random_y2 - 8);
    func_800240C0(arg0, arg1, arg2, random_x2, random_y2,
                  (s16)((func_80069EF8() & 0xF) - 8));
    random_x2 = func_80069EF8() & 0xF;
    ASM_KEEP(random_x2);
    random_x2 = (s16)(random_x2 - 8);
    random_y2 = func_80069EF8() & 0xF;
    ASM_KEEP(random_y2);
    random_y2 = (s16)(random_y2 - 8);
    func_800240C0(arg0, arg1, arg2, random_x2, random_y2,
                  (s16)((func_80069EF8() & 0xF) - 8));
    goto common;
}

state_3:
{
    register void *graphics3 ASM_REG("$6");
    register s32 value3 ASM_REG("$3");
    register u16 advance_value3 ASM_REG("$2");

    value3 = FIELD(arg0, u16, 0x86);
    ASM_KEEP(value3);
    value3 += 2;
    FIELD(arg0, u16, 0x86) = value3;
    graphics3 = FIELD(FIELD(base, void *, 0x60), void *, -0x14);
    FIELD(graphics3, s8, 0xE) = (s16)value3 * 3 - 0x70;
    FIELD(graphics3, s8, 0xD) = 0x70 - FIELD(arg0, s16, 0x86) * 3;
    FIELD(graphics3, s8, 0xC) = 0x70 - FIELD(arg0, s16, 0x86) * 3;
    if (FIELD(arg0, s16, 0x86) >= 0x24) {
        advance_value3 = FIELD(arg0, u16, 0xA);
        FIELD(arg0, u16, 0x86) = 0;
        FIELD(arg0, u16, 0x82) = 0;
        FIELD(arg0, u16, 0xA) = advance_value3 + 1;
        goto common;
    }
    goto common;
}

state_4:
{
    void *animation4;
    register void *entity4 ASM_REG("$19");
    register void *sprite4 ASM_REG("$16");
    register void *position4 ASM_REG("$17");
    register s32 i4 ASM_REG("$18");
    register s32 random_x4 ASM_REG("$16");
    register s32 entity_kind4 ASM_REG("$4");
    register u16 direction_preload4 ASM_REG("$2");
    register s32 animation_mode4 ASM_REG("$6");
    register u16 advance_value4 ASM_REG("$2");
    s32 direction4;
    s32 random_position4;
    s32 position_value4;
    s32 position_z4;
    u16 value4;

    i4 = 0;
    ASM_KEEP(i4);
    do {
        i4++;
        random_x4 = func_80069EF8() & 0x3F;
        ASM_KEEP(random_x4);
        random_x4 = (s16)(random_x4 - 0x20);
        func_800249A0((u8 *)arg0 - 0x20, random_x4,
                      (s16)((func_80069EF8() & 0x3F) - 0x20),
                      (s16)(-(FIELD(arg0, s16, 0x86) * 2) + 0x10), 0x1E);
    } while (i4 < 2);

    entity_kind4 = 0x212;
    direction4 = FIELD(arg0, u16, 0x86) & 3;
    entity4 = func_8003FC64(entity_kind4);
    ASM_KEEP(entity4);
    ASM_KEEP(direction4);
    if (entity4 != 0) {
        FIELD(entity4, s16, 0x22) = 0x1E;
        FIELD(entity4, void *, 0x10) = D_8002443C;
        func_8004491C(entity4, D_80045340);
        sprite4 = FIELD(entity4, void *, 0xC);
        ASM_KEEP(sprite4);
        FIELD(sprite4, s16, 0x10) = 0;
        FIELD(sprite4, u16, 0x14) |= 0xC;
        position4 = FIELD(entity4, void *, 8);
        ASM_KEEP(position4);
        random_position4 = func_80069EF8() & 0xF;
        position_value4 = FIELD(arg1, u16, 2);
        position_value4 -= 8;
        position_value4 += random_position4;
        FIELD(position4, s16, 2) = position_value4;
        random_position4 = func_80069EF8() & 0xF;
        position_value4 = FIELD(arg1, u16, 6);
        position_value4 -= 8;
        position_value4 += random_position4;
        FIELD(position4, s16, 6) = position_value4;
        if (func_80069EF8() & 1) {
            FIELD(sprite4, u16, 0x14) |= 1;
        }

        switch (direction4) {
        case 0:
            FIELD(position4, s16, 6) = FIELD(arg1, u16, 6) + 8;
            FIELD(sprite4, s16, 6) = 7;
            break;
        case 1:
            FIELD(position4, s16, 2) = FIELD(arg1, u16, 2) - 8;
            FIELD(sprite4, s16, 6) = 7;
            break;
        case 2:
            FIELD(position4, s16, 2) = FIELD(arg1, u16, 2) + 8;
            FIELD(sprite4, s16, 6) = 7;
            break;
        case 3:
            FIELD(position4, s16, 6) = FIELD(arg1, u16, 6) - 8;
            FIELD(sprite4, s16, 6) = -7;
            break;
        }

        animation4 = D_800DE9D0;
        position_z4 = FIELD(arg1, s32, 8);
        ASM_SCHED_BARRIER();
        animation_mode4 = 0;
        ASM_KEEP(animation_mode4);
        FIELD(position4, s32, 8) = position_z4;
        {
        register void *sprite_arg4 ASM_REG("$4");
        s32 scale_state4;

        sprite4 = FIELD(entity4, void *, 0xC);
        ASM_KEEP_NV(sprite4);
        scale_state4 = FIELD(arg0, s16, 0x86);
        ASM_SCHED_BARRIER();
        sprite_arg4 = sprite4;
        ASM_KEEP_NV(sprite_arg4);
        FIELD(sprite_arg4, s16, 0x1C) = scale_state4 * 0xAA;
        ASM_SCHED_BARRIER();
        scale_state4 = FIELD(arg0, s16, 0x86);
        ASM_SCHED_BARRIER();
        FIELD(sprite_arg4, u8, 0xE) = 0x80;
        FIELD(sprite_arg4, u8, 0xD) = 0x80;
        FIELD(sprite_arg4, u8, 0xC) = 0x80;
        FIELD(sprite_arg4, s16, 0x1E) = scale_state4 * 0xCC;
        func_8003DB94(sprite_arg4, animation4, animation_mode4);
        }
    }

    value4 = FIELD(arg0, u16, 0x86) + 2;
    FIELD(arg0, u16, 0x86) = value4;
    if ((s16)value4 >= 0x3D) {
        value4 = 0x28;
        advance_value4 = FIELD(arg0, u16, 0xA);
        FIELD(arg0, u16, 0x86) = value4;
        FIELD(arg0, u16, 0xA) = advance_value4 + 1;
        goto common;
    }
    goto common;
}

state_5:
{
    register void *target5 ASM_REG("$4");
    register void *graphics5 ASM_REG("$6");
    register void *target_reload5 ASM_REG("$2");
    register s32 i5 ASM_REG("$18");
    register s32 random_x5 ASM_REG("$17");
    register s32 random_y5 ASM_REG("$16");
    register s32 mask5 ASM_REG("$3");
    u16 value5;

    i5 = 0;
    ASM_KEEP(i5);
    do {
        i5++;
        random_x5 = func_80069EF8() & 0x3F;
        ASM_KEEP(random_x5);
        random_x5 = (s16)(random_x5 - 0x20);
        random_y5 = func_80069EF8() & 0x3F;
        ASM_KEEP(random_y5);
        random_y5 = (s16)(random_y5 - 0x20);
        func_800249A0((u8 *)arg0 - 0x20, random_x5, random_y5,
                      (s16)(-0x20 - (func_80069EF8() & 0x3F)), 0x1E);
    } while (i5 < 2);

    value5 = FIELD(arg0, u16, 0x86) - 2;
    FIELD(arg0, u16, 0x86) = value5;
    mask5 = 0x10000000;
    if ((s16)value5 <= 0) {
        FIELD(arg0, u16, 0x86) = 0;
        FIELD(arg0, u16, 0x82) = 0;
        FIELD(arg0, s16, 0xA)++;
        target5 = FIELD(base, void *, 0x60);
        FIELD(target5, s32, 0x1C) ^= mask5;
        target_reload5 = FIELD(base, void *, 0x60);
        graphics5 = FIELD(target_reload5, void *, -0x14);
        FIELD(graphics5, u8, 0xC) = 0x80;
        FIELD(graphics5, u8, 0xD) = 0x80;
        FIELD(graphics5, u8, 0xE) = 0x80;
        func_8009CE1C(FIELD(base, void *, 0x60), 0x10, FIELD(arg0, u8, 9), 2,
                      (s16)(FIELD(arg0, u16, 0x7E) << 9), base, 2);
    }
    goto common;
}

state_6:
{
    u16 value6;

    value6 = FIELD(arg0, u16, 0x82) + 1;
    FIELD(arg0, u16, 0x82) = value6;
    if ((s16)value6 >= 0x3D) {
        FIELD(arg0, s16, 0xA) = 8;
        FIELD(arg0, u16, 0x82) = 0x1E;
    }
    goto common;
}

state_8:
{
    u16 value7;
    s32 flag7;

    value7 = FIELD(arg0, u16, 0x82);
    FIELD(arg0, u16, 0x82) = value7 + 1;
    if ((s16)(value7 + 1) >= 0x1F) {
        flag7 = D_80025914[0];
        FIELD(arg0, u16, 0x82) = value7;
        if (flag7 == 0) {
            D_8008346C[0] = 0;
            FIELD(arg0, u16, -2) |= 0x8000;
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
    common_value = FIELD(arg0, u16, 0x84);
    FIELD(arg0, u16, 0x84) = common_value + 1;
    if ((s16)common_value >= 5) {
        func_8003DB94(arg2, D_800DE870, 2);
        FIELD(arg0, u16, 0x84) = 0;
    }
}
}
