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
extern u8 D_80024028;

/* Updates a projectile effect through travel, impact, particles, and cleanup. */
void func_80024BE8(void *effect_data, void *motion_data, void *sprite_data) {
    s16 offset[3];
    PathBlock velocity_table;
    void *effect = effect_data;
    void *motion = motion_data;
    void *sprite = sprite_data;
    register void *source ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs source+offset); the source shape that makes it unnecessary has not been found */
    s32 state;

    source = ((S_80024BE8_0 *)effect)->unk_00;
    velocity_table = D_80024004;
    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(sprite);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    {
        S_80024BE8_1 *task;
        S_80024BE8_6 *origin;
        void **jump_table;
        static void *const state_labels[] = {
            &&state_0, &&state_1, &&state_2, &&state_3, &&state_4,
            &&state_5, &&state_6, &&common, &&state_8
        };

        task = (u8 *)source - 0x20;
        origin = task->unk_08;
        ((S_80024BE8_0 *)effect)->unk_82++;
        state = ((S_80024BE8_0 *)effect)->unk_0A.s;

        if ((u32)state >= 9U) {
            goto common;
        }
        jump_table = (void **)&D_80024028;
           /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        goto *jump_table[state];

state_0:
        {
            S_80024BE8_4 *source_sprite;
            void *target;
            register void *source_graphics ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register u8 *direction_table ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs source+offset); the source shape that makes it unnecessary has not been found */
            u8 *direction_entry;
            register s32 default_steps ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            s32 tile_distance;
            s32 tile_offset;
            s32 tile_coord;
            s32 source_coord;
            register s32 direction ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            register s32 target_coord ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs source+offset); the source shape that makes it unnecessary has not been found */
            u16 prev_state;
            u16 source_flags;
            u16 target_height;
            u16 origin_height;

            ((S_80024BE8_2 *)sprite)->unk_0C.at00.v = 0x808080;
            ((S_80024BE8_2 *)sprite)->unk_1E = 0x400;
            ((S_80024BE8_2 *)sprite)->unk_1C = 0x400;
            ((S_80024BE8_2 *)sprite)->unk_12 = 0x7DCF;
            ((S_80024BE8_2 *)sprite)->unk_14 |= 0x100;
            ((S_80024BE8_0 *)effect)->unk_84 = 0;
            func_8003DB94(sprite, D_800DE870, 2);
            source_flags = ((S_80024BE8_3 *)source)->unk_2A;
            D_80025914[0] = 1;
            ((S_80024BE8_0 *)effect)->unk_7E.s = (source_flags >> 9) & 7;
            ((S_80024BE8_0 *)effect)->unk_0A.s++;

            source_sprite = task->unk_0C;
            if ((func_8003DF74(source_sprite->unk_08, source_sprite, offset, 0) != 0) ||
                (((S_80024BE8_22 *)(task->unk_0C))->unk_14 & 0x8000)) {
                ((S_80024BE8_5 *)motion)->unk_00.at02.v = origin->unk_02;
                ((S_80024BE8_5 *)motion)->unk_04.at02.v = origin->unk_06;
                origin_height = origin->unk_0A;
                ((S_80024BE8_5 *)motion)->unk_08.at02.v = origin_height;

                if (!(((S_80024BE8_22 *)(task->unk_0C))->unk_14 & 0x8000)) {
                    ((S_80024BE8_5 *)motion)->unk_00.at02.v += offset[0];
                    ((S_80024BE8_5 *)motion)->unk_04.at02.v += offset[1];
                    ((S_80024BE8_5 *)motion)->unk_08.at02.v += offset[2];
                } else {
                    ((S_80024BE8_5 *)motion)->unk_08.at02.v = origin_height - 0x40;
                }

                if (*((S_80024BE8_0 *)effect)->unk_04 & 0x80) {
                    if (!(((S_80024BE8_0 *)effect)->unk_7A & 4)) {
                        func_8004491C((u8 *)effect - 0x20, D_80045340);
                        ((S_80024BE8_2 *)sprite)->unk_10 = 0x60;
                        ((S_80024BE8_2 *)sprite)->unk_14 |= 0xC;
                        ((S_80024BE8_0 *)effect)->unk_7A |= 4;
                    }

                    default_steps = 8;
                    target = ((S_80024BE8_3 *)source)->unk_60;
                    if (target != 0) {
                        target_height = ((S_80024BE8_7 *)target)->unk_88;
                        direction = ((S_80024BE8_0 *)effect)->unk_7E.s;
                        ((S_80024BE8_0 *)effect)->unk_78.u = target_height;
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                        direction_table = D_8006CCD8;
                        direction_entry = direction_table + direction * 2;
                        source_graphics = ((S_80024BE8_3_pre *)source)[-1].unk_00;
                        tile_offset = *direction_entry;
                        tile_coord = ((S_80024BE8_8 *)source_graphics)->unk_24;
                        target_coord = tile_coord + tile_offset;
                        ((S_80024BE8_0 *)effect)->unk_A2 = target_coord;
                        direction_table = D_8006CCE8;
                        direction = ((S_80024BE8_0 *)effect)->unk_7E.s;
                        direction_entry = direction_table + direction * 2;
                        tile_coord = ((S_80024BE8_8 *)source_graphics)->unk_25;
                        tile_offset = *direction_entry;
                        target_coord = tile_coord + tile_offset;
                        ((S_80024BE8_0 *)effect)->unk_A3 = target_coord;
                        tile_distance = ((S_80024BE8_3 *)source)->unk_72;
                        source_coord = ((S_80024BE8_8 *)source_graphics)->unk_24;
                        if (tile_distance == source_coord) {
                            tile_distance = ((S_80024BE8_3 *)source)->unk_73;
                            source_coord = ((S_80024BE8_8 *)source_graphics)->unk_25;
                        }
                        tile_distance -= source_coord;
                        if (tile_distance < 0) {
                            tile_distance = -tile_distance;
                        }
                        tile_distance *= 2;
                        tile_distance -= 1;
                        ((S_80024BE8_0 *)effect)->unk_7B = tile_distance;
                    } else {
                        target_height = ((S_80024BE8_3 *)source)->unk_88;
                        ((S_80024BE8_0 *)effect)->unk_7B = default_steps;
                        ((S_80024BE8_0 *)effect)->unk_78.u = target_height - 0x50;
                    }

                    ((S_80024BE8_5 *)motion)->unk_0C = velocity_table.entries[((S_80024BE8_0 *)effect)->unk_7E.s].x << 16;
                    ((S_80024BE8_5 *)motion)->unk_10 = velocity_table.entries[((S_80024BE8_0 *)effect)->unk_7E.s].y << 16;
                    ((S_80024BE8_5 *)motion)->unk_14 =
                        ((((S_80024BE8_0 *)effect)->unk_78.s << 16) - ((S_80024BE8_5 *)motion)->unk_08.at00.v) /
                        ((S_80024BE8_0 *)effect)->unk_7B;
                    prev_state = ((S_80024BE8_0 *)effect)->unk_0A.u;
                    ((S_80024BE8_0 *)effect)->unk_82 = 0;
                    ((S_80024BE8_0 *)effect)->unk_0A.u = prev_state + 1;
                    goto common;
                }
            }
            goto common;
        }
    }

state_1:
    {
        void *target_graphics;
        void *target_position;
        void *animation;
        void *impact;
        register void *impact_sprite ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        register void *impact_position ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        register s32 particle_count ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 color;
        register s32 color_mode ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        s32 random_intensity;

        if ((func_800A4778(((S_80024BE8_5 *)motion)->unk_00.at02.v, ((S_80024BE8_5 *)motion)->unk_04.at02.v,
            ((S_80024BE8_5 *)motion)->unk_08.at02u.v, ((S_80024BE8_3 *)source)->unk_60) << 16) != 0) {
            ((S_80024BE8_0 *)effect)->unk_0A.s = 8;
            ((S_80024BE8_0 *)effect)->unk_82 = 0;
            ((S_80024BE8_2 *)sprite)->unk_14 |= 0x80;
            goto common;
        }

        particle_count = 0;
        do {
            register void *effect_task ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            s32 direction;
            register s32 particle_color ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register s32 intensity ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            particle_count++;
            random_intensity = func_80069EF8();
            effect_task = (u8 *)effect - 0x20;
            particle_color = 0xF04040;
            ASM_KEEP_NV(particle_color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            intensity = (random_intensity & 0xFF) | 0x80;
            ASM_KEEP_NV(intensity);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            direction = ((S_80024BE8_0 *)effect)->unk_7E.s;
            func_80024758(effect_task, direction, particle_color, intensity, 0, 0, 0);
        } while (particle_count < 4);

        ((S_80024BE8_0 *)effect)->unk_7B--;
        if (((S_80024BE8_0 *)effect)->unk_7B > 0) {
            goto state_2;
        }

        ASM_KEEP(effect);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        func_80044A50((u8 *)effect - 0x20);
        color_mode = 4;
        if (((S_80024BE8_3 *)source)->unk_60 != 0) {
            ((S_80024BE8_0 *)effect)->unk_86.u = 0;
            ((S_80024BE8_0 *)effect)->unk_0A.s++;
            target_position = ((S_80024BE8_23_pre *)(((S_80024BE8_3 *)source)->unk_60))[-1].unk_00;
            ((S_80024BE8_5 *)motion)->unk_00.at02.v = ((S_80024BE8_9 *)target_position)->unk_02;
            ((S_80024BE8_5 *)motion)->unk_04.at02.v = ((S_80024BE8_9 *)target_position)->unk_06;
            ((S_80024BE8_5 *)motion)->unk_08.at02.v = ((S_80024BE8_0 *)effect)->unk_78.u;
            ((S_80024BE8_23 *)(((S_80024BE8_3 *)source)->unk_60))->unk_1C |= 0x10000000;
            target_graphics = ((S_80024BE8_23_pre *)(((S_80024BE8_3 *)source)->unk_60))[-1].unk_04;
            color = 0x80;
            ASM_KEEP(color);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs source+offset); the source shape that makes it unnecessary has not been found */
            ((S_80024BE8_10 *)target_graphics)->unk_0E = color;
            ((S_80024BE8_10 *)target_graphics)->unk_0C = color;
            ((S_80024BE8_10 *)target_graphics)->unk_0D = color;
            func_800419EC(color_mode, 8, target_graphics);
            func_800A56E0(0x300);

            impact = func_8003FC64(0x212);
            if (impact != 0) {
                ((S_80024BE8_11 *)impact)->unk_10 = D_80024B14;
                func_8004491C(impact, D_80045C34);
                impact_sprite = ((S_80024BE8_11 *)impact)->unk_0C;
                ((S_80024BE8_12 *)impact_sprite)->unk_10 = 0;
                ((S_80024BE8_12 *)impact_sprite)->unk_14 |= 0xC;
                impact_position = ((S_80024BE8_11 *)impact)->unk_08;
                ((S_80024BE8_13 *)impact_position)->unk_02 = ((S_80024BE8_5 *)motion)->unk_00.at02.v;
                ((S_80024BE8_13 *)impact_position)->unk_06 = ((S_80024BE8_5 *)motion)->unk_04.at02.v;
                ((S_80024BE8_13 *)impact_position)->unk_08.at00.v = ((S_80024BE8_5 *)motion)->unk_08.at00.v;
                animation = D_800258FC;
                impact_sprite = ((S_80024BE8_11 *)impact)->unk_0C;
                ((S_80024BE8_12 *)impact_sprite)->unk_08 = animation;
                ((S_80024BE8_12 *)impact_sprite)->unk_0E = color;
                ((S_80024BE8_12 *)impact_sprite)->unk_0D = color;
                ((S_80024BE8_12 *)impact_sprite)->unk_0C = color;
                ((S_80024BE8_12 *)impact_sprite)->unk_1E = 1;
                ((S_80024BE8_12 *)impact_sprite)->unk_1C = 1;
                ((S_80024BE8_12 *)impact_sprite)->unk_14 ^= 0xC;
                ((S_80024BE8_13 *)impact_position)->unk_08.at02.v = ((S_80024BE8_23 *)(((S_80024BE8_3 *)source)->unk_60))->unk_88;
            }
            ((S_80024BE8_5 *)motion)->unk_08.at02.v = ((S_80024BE8_23 *)(((S_80024BE8_3 *)source)->unk_60))->unk_88;
        } else {
            ((S_80024BE8_0 *)effect)->unk_0A.s = 8;
            ((S_80024BE8_0 *)effect)->unk_82 = 0;
            ((S_80024BE8_2 *)sprite)->unk_0C.at02.v = 0;
            ((S_80024BE8_2 *)sprite)->unk_0C.at01.v = 0;
            ((S_80024BE8_2 *)sprite)->unk_0C.at00u.v = 0;
        }
        goto common;
    }

state_2:
    {
        register s32 offset_x ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        register s32 offset_y ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

        ((S_80024BE8_5 *)motion)->unk_00.at00.v += ((S_80024BE8_5 *)motion)->unk_0C;
        ((S_80024BE8_5 *)motion)->unk_04.at00.v += ((S_80024BE8_5 *)motion)->unk_10;
        ((S_80024BE8_5 *)motion)->unk_08.at00.v += ((S_80024BE8_5 *)motion)->unk_14;

        offset_x = func_80069EF8() & 0xF;
        ASM_KEEP(offset_x);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        offset_x = (s16)(offset_x - 8);
        offset_y = func_80069EF8() & 0xF;
        ASM_KEEP(offset_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        offset_y = (s16)(offset_y - 8);
        func_800240C0(effect, motion, sprite, offset_x, offset_y,
            (s16)((func_80069EF8() & 0xF) - 8));
        offset_x = func_80069EF8() & 0xF;
        offset_x = (s16)(offset_x - 8);
        offset_y = func_80069EF8() & 0xF;
        offset_y = (s16)(offset_y - 8);
        func_800240C0(effect, motion, sprite, offset_x, offset_y,
            (s16)((func_80069EF8() & 0xF) - 8));
        offset_x = func_80069EF8() & 0xF;
        offset_x = (s16)(offset_x - 8);
        offset_y = func_80069EF8() & 0xF;
        offset_y = (s16)(offset_y - 8);
        func_800240C0(effect, motion, sprite, offset_x, offset_y,
            (s16)((func_80069EF8() & 0xF) - 8));
        offset_x = func_80069EF8() & 0xF;
        offset_x = (s16)(offset_x - 8);
        offset_y = func_80069EF8() & 0xF;
        offset_y = (s16)(offset_y - 8);
        func_800240C0(effect, motion, sprite, offset_x, offset_y,
            (s16)((func_80069EF8() & 0xF) - 8));
        offset_x = func_80069EF8() & 0xF;
        offset_x = (s16)(offset_x - 8);
        offset_y = func_80069EF8() & 0xF;
        offset_y = (s16)(offset_y - 8);
        func_800240C0(effect, motion, sprite, offset_x, offset_y,
            (s16)((func_80069EF8() & 0xF) - 8));
        offset_x = func_80069EF8() & 0xF;
        offset_x = (s16)(offset_x - 8);
        offset_y = func_80069EF8() & 0xF;
        offset_y = (s16)(offset_y - 8);
        func_800240C0(effect, motion, sprite, offset_x, offset_y,
            (s16)((func_80069EF8() & 0xF) - 8));
        goto common;
    }

state_3:
    {
        register void *target_graphics ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 color_step;
        u16 prev_state;

        color_step = ((S_80024BE8_0 *)effect)->unk_86.u;
        color_step += 2;
        ((S_80024BE8_0 *)effect)->unk_86.u = color_step;
        target_graphics = ((S_80024BE8_23_pre *)(((S_80024BE8_3 *)source)->unk_60))[-1].unk_04;
        ((S_80024BE8_14 *)target_graphics)->unk_0E = (s16)color_step * 3 - 0x70;
        ((S_80024BE8_14 *)target_graphics)->unk_0D = 0x70 - ((S_80024BE8_0 *)effect)->unk_86.s * 3;
        ((S_80024BE8_14 *)target_graphics)->unk_0C = 0x70 - ((S_80024BE8_0 *)effect)->unk_86.s * 3;
        if (((S_80024BE8_0 *)effect)->unk_86.s >= 0x24) {
            prev_state = ((S_80024BE8_0 *)effect)->unk_0A.u;
            ((S_80024BE8_0 *)effect)->unk_86.u = 0;
            ((S_80024BE8_0 *)effect)->unk_82 = 0;
            ((S_80024BE8_0 *)effect)->unk_0A.u = prev_state + 1;
            goto common;
        }
        goto common;
    }

state_4:
    {
        void *animation;
        register void *particle ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs source+offset); the source shape that makes it unnecessary has not been found */
        void *particle_sprite;
        void *particle_position;
        register s32 particle_count ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 offset_x ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        s32 particle_kind;
        u16 direction_preload;
        s32 animation_mode;
        u16 prev_state;
        s32 side;
        s32 jitter;
        s32 coord;
        s32 height;
        u16 scale_step;

        particle_count = 0;
        do {
            particle_count++;
            offset_x = func_80069EF8() & 0x3F;
            ASM_KEEP(offset_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            offset_x = (s16)(offset_x - 0x20);
            func_800249A0((u8 *)effect - 0x20, offset_x,
                (s16)((func_80069EF8() & 0x3F) - 0x20),
                (s16)(-(((S_80024BE8_0 *)effect)->unk_86.s * 2) + 0x10), 0x1E);
        } while (particle_count < 2);

        particle_kind = 0x212;
        side = ((S_80024BE8_0 *)effect)->unk_86.u & 3;
        particle = func_8003FC64(particle_kind);
        if (particle != 0) {
            ((S_80024BE8_15 *)particle)->unk_22 = 0x1E;
            ((S_80024BE8_15 *)particle)->unk_10 = D_8002443C;
            func_8004491C(particle, D_80045340);
            particle_sprite = ((S_80024BE8_15 *)particle)->unk_0C;
            ((S_80024BE8_16 *)particle_sprite)->unk_10 = 0;
            ((S_80024BE8_16 *)particle_sprite)->unk_14 |= 0xC;
            particle_position = ((S_80024BE8_15 *)particle)->unk_08;
            jitter = func_80069EF8() & 0xF;
            coord = ((S_80024BE8_5 *)motion)->unk_00.at02.v;
            coord -= 8;
            coord += jitter;
            ((S_80024BE8_17 *)particle_position)->unk_02 = coord;
            jitter = func_80069EF8() & 0xF;
            coord = ((S_80024BE8_5 *)motion)->unk_04.at02.v;
            coord -= 8;
            coord += jitter;
            ((S_80024BE8_17 *)particle_position)->unk_06 = coord;
            if (func_80069EF8() & 1) {
                ((S_80024BE8_16 *)particle_sprite)->unk_14 |= 1;
            }

            switch (side) {
            case 0:
                ((S_80024BE8_17 *)particle_position)->unk_06 = ((S_80024BE8_5 *)motion)->unk_04.at02.v + 8;
                ((S_80024BE8_16 *)particle_sprite)->unk_06 = 7;
                break;
            case 1:
                ((S_80024BE8_17 *)particle_position)->unk_02 = ((S_80024BE8_5 *)motion)->unk_00.at02.v - 8;
                ((S_80024BE8_16 *)particle_sprite)->unk_06 = 7;
                break;
            case 2:
                ((S_80024BE8_17 *)particle_position)->unk_02 = ((S_80024BE8_5 *)motion)->unk_00.at02.v + 8;
                ((S_80024BE8_16 *)particle_sprite)->unk_06 = 7;
                break;
            case 3:
                ((S_80024BE8_17 *)particle_position)->unk_06 = ((S_80024BE8_5 *)motion)->unk_04.at02.v - 8;
                ((S_80024BE8_16 *)particle_sprite)->unk_06 = -7;
                break;
            }

            animation = D_800DE9D0;
            height = ((S_80024BE8_5 *)motion)->unk_08.at00.v;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            animation_mode = 0;
            ASM_KEEP(animation_mode);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            ((S_80024BE8_17 *)particle_position)->unk_08 = height;
            {
                void *scaled_sprite;
                s32 scale;

                particle_sprite = ((S_80024BE8_15 *)particle)->unk_0C;
                scale = ((S_80024BE8_0 *)effect)->unk_86.s;
                scaled_sprite = particle_sprite;
                ((S_80024BE8_18 *)scaled_sprite)->unk_1C = scale * 0xAA;
                scale = ((S_80024BE8_0 *)effect)->unk_86.s;
                ((S_80024BE8_18 *)scaled_sprite)->unk_0E = 0x80;
                ((S_80024BE8_18 *)scaled_sprite)->unk_0D = 0x80;
                ((S_80024BE8_18 *)scaled_sprite)->unk_0C = 0x80;
                ((S_80024BE8_18 *)scaled_sprite)->unk_1E = scale * 0xCC;
                func_8003DB94(scaled_sprite, animation, animation_mode);
            }
        }

        scale_step = ((S_80024BE8_0 *)effect)->unk_86.u + 2;
        ((S_80024BE8_0 *)effect)->unk_86.u = scale_step;
        if ((s16)scale_step >= 0x3D) {
            scale_step = 0x28;
            prev_state = ((S_80024BE8_0 *)effect)->unk_0A.u;
            ((S_80024BE8_0 *)effect)->unk_86.u = scale_step;
            ((S_80024BE8_0 *)effect)->unk_0A.u = prev_state + 1;
            goto common;
        }
        goto common;
    }

state_5:
    {
        void *target;
        register void *target_graphics ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        void *current_target;
        s32 particle_count;
        register s32 offset_x ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        register s32 offset_y ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        s32 target_flag;
        u16 scale_step;

        particle_count = 0;
        do {
            particle_count++;
            offset_x = func_80069EF8() & 0x3F;
            ASM_KEEP(offset_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            offset_x = (s16)(offset_x - 0x20);
            offset_y = func_80069EF8() & 0x3F;
            ASM_KEEP(offset_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            offset_y = (s16)(offset_y - 0x20);
            func_800249A0((u8 *)effect - 0x20, offset_x, offset_y,
                (s16)(-0x20 - (func_80069EF8() & 0x3F)), 0x1E);
        } while (particle_count < 2);

        scale_step = ((S_80024BE8_0 *)effect)->unk_86.u - 2;
        ((S_80024BE8_0 *)effect)->unk_86.u = scale_step;
        target_flag = 0x10000000;
        if ((s16)scale_step <= 0) {
            ((S_80024BE8_0 *)effect)->unk_86.u = 0;
            ((S_80024BE8_0 *)effect)->unk_82 = 0;
            ((S_80024BE8_0 *)effect)->unk_0A.s++;
            target = ((S_80024BE8_3 *)source)->unk_60;
            ((S_80024BE8_19 *)target)->unk_1C ^= target_flag;
            current_target = ((S_80024BE8_3 *)source)->unk_60;
            target_graphics = ((S_80024BE8_20_pre *)current_target)[-1].unk_00;
            ((S_80024BE8_21 *)target_graphics)->unk_0C = 0x80;
            ((S_80024BE8_21 *)target_graphics)->unk_0D = 0x80;
            ((S_80024BE8_21 *)target_graphics)->unk_0E = 0x80;
            func_8009CE1C(((S_80024BE8_3 *)source)->unk_60, 0x10, ((S_80024BE8_0 *)effect)->unk_09, 2,
                (s16)(((S_80024BE8_0 *)effect)->unk_7E.u << 9), source, 2);
        }
        goto common;
    }

state_6:
    {
        u16 elapsed;

        elapsed = ((S_80024BE8_0 *)effect)->unk_82 + 1;
        ((S_80024BE8_0 *)effect)->unk_82 = elapsed;
        if ((s16)elapsed >= 0x3D) {
            ((S_80024BE8_0 *)effect)->unk_0A.s = 8;
            ((S_80024BE8_0 *)effect)->unk_82 = 0x1E;
        }
        goto common;
    }

state_8:
    {
        u16 elapsed;
        s32 active;

        elapsed = ((S_80024BE8_0 *)effect)->unk_82;
        ((S_80024BE8_0 *)effect)->unk_82 = elapsed + 1;
        if ((s16)(elapsed + 1) >= 0x1F) {
            active = D_80025914[0];
            ((S_80024BE8_0 *)effect)->unk_82 = elapsed;
            if (active == 0) {
                D_8008346C[0] = 0;
                ((S_80024BE8_0_pre *)effect)[-1].unk_00 |= 0x8000;
                D_800814A0[0] |= 0x8000;
            } else {
                D_80025914[0] = 0;
            }
        }
        goto common;
    }

common:
    {
        u16 animation_tick;

        func_800478B8(sprite);
        animation_tick = ((S_80024BE8_0 *)effect)->unk_84;
        ((S_80024BE8_0 *)effect)->unk_84 = animation_tick + 1;
        if ((s16)animation_tick >= 5) {
            func_8003DB94(sprite, D_800DE870, 2);
            ((S_80024BE8_0 *)effect)->unk_84 = 0;
        }
    }
}
