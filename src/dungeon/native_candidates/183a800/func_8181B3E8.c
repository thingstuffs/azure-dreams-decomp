#include "modules/dungeon_ovl_183a800.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"

   /* the 0x2 bytes before arg0 in func_80024BE8, addressed as arg0[-1] */

   /* arg0 in func_80024BE8 */

   /* task in func_80024BE8 */

   /* arg2 in func_80024BE8 */

   /* the 0x14 bytes before base in func_80024BE8, addressed as base[-1] */

   /* base in func_80024BE8 */

   /* child0 in func_80024BE8 */

   /* arg1 in func_80024BE8 */

   /* origin in func_80024BE8 */

   /* target0 in func_80024BE8 */

   /* graphics0 in func_80024BE8 */

   /* target_position1 in func_80024BE8 */

   /* graphics1 in func_80024BE8 */

   /* entity1 in func_80024BE8 */

   /* sprite1 in func_80024BE8 */

   /* position1 in func_80024BE8 */

   /* graphics3 in func_80024BE8 */

   /* entity4 in func_80024BE8 */

   /* sprite4 in func_80024BE8 */

   /* position4 in func_80024BE8 */

   /* sprite_arg4 in func_80024BE8 */

   /* target5 in func_80024BE8 */

   /* the 0x14 bytes before target_reload5 in func_80024BE8, addressed as target_reload5[-1] */

   /* graphics5 in func_80024BE8 */

   /* ((S_80024BE8_1 *)task)->unk_0C in func_80024BE8 */

   /* the 0x18 bytes before ((S_80024BE8_3 *)base)->unk_60 in func_80024BE8, addressed as ((S_80024BE8_3 *)base)->unk_60[-1] */

   /* ((S_80024BE8_3 *)base)->unk_60 in func_80024BE8 */






extern s32 func_8003DF74(s32, void *, s16 *, s32);
extern void func_800419EC(s32, s32, void *);
extern void func_80044A50(void *);
extern s32 func_80069EF8(void);
extern void func_8009CE1C(void *, s32, u8, s32, s32, void *, s32);
extern s32 func_800A4778(u16, u16, s16, void *);

extern u8 D_800258FC[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s32 D_800814A0[3];
extern u8 D_800DE870[];
extern u8 D_800DE9D0[];

/* Updates a projectile effect through travel, impact, particles, and cleanup. */
void func_80024BE8(void *effect, void *motion, void *sprite) {
    s16 offset[3];
    PathBlock velocity_table;
    void *source;
    s32 state;
    void *target_graphics;
    void *impact;
    s32 impact_position;
    s32 impact_sprite;
    s32 particle_count_m;
    S_80024BE8_1 *task;
    S_80024BE8_6 *origin;
    S_80024BE8_4 *source_sprite;
    void *target;
    u8 *direction_table;
    s32 default_steps;
    s32 tile_distance;
    s32 source_coord;
    s32 direction;
    u16 prev_state;
    u16 source_flags;
    u16 target_height;
    u16 origin_height;

    source = ((S_80024BE8_0 *)effect)->unk_00;
    velocity_table = D_80024004;
    task = (u8 *)source - 0x20;
    origin = task->unk_08;
    ((S_80024BE8_0 *)effect)->unk_82++;
    state = ((S_80024BE8_0 *)effect)->unk_0A.s;

    switch (state) {
    case 0:
        ((S_80024BE8_2 *)sprite)->unk_0C.at00.v = 0x808080;
        ((S_80024BE8_2 *)sprite)->unk_1E = 0x400;
        ((S_80024BE8_2 *)sprite)->unk_1C = 0x400;
        ((S_80024BE8_2 *)sprite)->unk_12 = 0x7DCF;
        ((S_80024BE8_2 *)sprite)->unk_14 |= 0x100;
        ((S_80024BE8_0 *)effect)->unk_84 = 0;
        func_8003DB94(sprite, D_800DE870, 2);
        source_flags = ((S_80024BE8_3 *)source)->unk_2A;
        D_80025914 = 1;
        ((S_80024BE8_0 *)effect)->unk_7E.s = (source_flags >> 9) & 7;
        ((S_80024BE8_0 *)effect)->unk_0A.s++;

    case 1:
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
                    func_8004491C((u8 *)effect - 0x20, (s32)func_80045340);
                    ((S_80024BE8_2 *)sprite)->unk_10 = 0x60;
                    ((S_80024BE8_2 *)sprite)->unk_14 |= 0xC;
                    ((S_80024BE8_0 *)effect)->unk_7A |= 4;
                }

                default_steps = 8;
                target = ((S_80024BE8_3 *)source)->unk_60;
                if (target != 0) {
                    target_height = ((S_80024BE8_7 *)target)->unk_88;
                    direction = ((S_80024BE8_0 *)effect)->unk_7E.s;
                    direction_table = target_height;
                    ((S_80024BE8_0 *)effect)->unk_78.u = direction_table;
                    direction_table = D_8006CCD8;
                    direction <<= 1;
                    direction += (s32)direction_table;
                    target_graphics = ((S_80024BE8_3_pre *)source)[-1].unk_00;
                    direction = *(u8 *)direction;
                    direction_table = (u8 *)(u32)((S_80024BE8_8 *)target_graphics)->unk_24;
                    direction_table = (u8 *)((s32)direction_table + direction);
                    ((S_80024BE8_0 *)effect)->unk_A2 = (s32)direction_table;
                    direction = ((S_80024BE8_0 *)effect)->unk_7E.s;
                    direction_table = D_8006CCE8;
                    direction <<= 1;
                    direction += (s32)direction_table;
                    direction_table = (u8 *)(u32)((S_80024BE8_8 *)target_graphics)->unk_25;
                    direction = *(u8 *)direction;
                    direction_table = (u8 *)((s32)direction_table + direction);
                    ((S_80024BE8_0 *)effect)->unk_A3 = (s32)direction_table;
                    tile_distance = ((S_80024BE8_3 *)source)->unk_72;
                    source_coord = ((S_80024BE8_8 *)target_graphics)->unk_24;
                    if (tile_distance == source_coord) {
                        tile_distance = ((S_80024BE8_3 *)source)->unk_73;
                        source_coord = ((S_80024BE8_8 *)target_graphics)->unk_25;
                    }
                    tile_distance -= source_coord;
                    if (tile_distance < 0) {
                        tile_distance = -tile_distance;
                    }
                    tile_distance *= 2;
                    tile_distance -= 1;
                    ((S_80024BE8_0 *)effect)->unk_7B = tile_distance;
                } else {
                    u16 target_height;
                    target_height = ((S_80024BE8_3 *)source)->unk_88;
                    ((S_80024BE8_0 *)effect)->unk_7B = default_steps;
                    ((S_80024BE8_0 *)effect)->unk_78.u = target_height - 0x50;
                }

                ((S_80024BE8_5 *)motion)->unk_0C = velocity_table.entries[((S_80024BE8_0 *)effect)->unk_7E.s].x
                << 16;
                ((S_80024BE8_5 *)motion)->unk_10 = velocity_table.entries[((S_80024BE8_0 *)effect)->unk_7E.s].y
                << 16;
                ((S_80024BE8_5 *)motion)->unk_14 =
                    ((((S_80024BE8_0 *)effect)->unk_78.s << 16) - ((S_80024BE8_5 *)motion)->unk_08.at00.v) /
                    ((S_80024BE8_0 *)effect)->unk_7B;
                prev_state = ((S_80024BE8_0 *)effect)->unk_0A.u;
                ((S_80024BE8_0 *)effect)->unk_82 = 0;
                ((S_80024BE8_0 *)effect)->unk_0A.u = prev_state + 1;
                break;
            }
        }
        break;

    case 2:
    {
        void *target_position;
        void *animation;
        s32 color_mode;
        s32 random_intensity;

        if ((func_800A4778(((S_80024BE8_5 *)motion)->unk_00.at02.v, ((S_80024BE8_5 *)motion)->unk_04.at02.v,
            ((S_80024BE8_5 *)motion)->unk_08.at02u.v, ((S_80024BE8_3 *)source)->unk_60) << 16) != 0) {
            ((S_80024BE8_0 *)effect)->unk_0A.s = 8;
            ((S_80024BE8_0 *)effect)->unk_82 = 0;
            ((S_80024BE8_2 *)sprite)->unk_14 |= 0x80;
            break;
        }

        particle_count_m = 0;
        do {
            s32 direction;
            s32 particle_color;
            s32 intensity;
            random_intensity = func_80069EF8();
            particle_color = 0xF04040;
            intensity = (random_intensity & 0xFF) | 0x80;
            direction = ((S_80024BE8_0 *)effect)->unk_7E.s;
            func_80024758((u8 *)effect - 0x20, direction, particle_color, intensity, 0, 0, 0);
            particle_count_m++;
        } while (particle_count_m < 4);

        ((S_80024BE8_0 *)effect)->unk_7B--;
        if (((S_80024BE8_0 *)effect)->unk_7B <= 0) {
            func_80044A50((u8 *)effect - 0x20);
            color_mode = 4;
            if (((S_80024BE8_3 *)source)->unk_60 != 0) {
                ((S_80024BE8_0 *)effect)->unk_86.u = 0;
                ((S_80024BE8_0 *)effect)->unk_0A.s++;
                target_position = ((S_80024BE8_23_pre *)(((S_80024BE8_3 *)source)->unk_60))[-1].unk_00;
                ((S_80024BE8_5 *)motion)->unk_00.at02.v = ((S_80024BE8_9 *)target_position)->unk_02;
                ((S_80024BE8_5 *)motion)->unk_04.at02.v = ((S_80024BE8_9 *)target_position)->unk_06;
                ((S_80024BE8_5 *)motion)->unk_08.at02.v = ((S_80024BE8_0 *)effect)->unk_78.u;
                source_sprite = (S_80024BE8_4 *)((S_80024BE8_3 *)source)->unk_60;
                ((S_80024BE8_23 *)source_sprite)->unk_1C |= 0x10000000;
                target_graphics = ((S_80024BE8_23_pre *)(((S_80024BE8_3 *)source)->unk_60))[-1].unk_04;
                random_intensity = 0x80;
                ((S_80024BE8_10 *)target_graphics)->unk_0C = random_intensity;
                ((S_80024BE8_10 *)target_graphics)->unk_0D = random_intensity;
                ((S_80024BE8_10 *)target_graphics)->unk_0E = random_intensity;
                func_800419EC(color_mode, 8, target_graphics);
                func_800A56E0(0x300);

                impact = func_8003FC64(0x212);
                if (impact != 0) {
                    ((S_80024BE8_11 *)impact)->unk_10 = func_80024B14;
                    func_8004491C(impact, (s32)func_80045C34);
                    impact_sprite = (s32)(((S_80024BE8_11 *)impact)->unk_0C);
                    ((S_80024BE8_12 *)(void *)impact_sprite)->unk_10 = 0;
                    ((S_80024BE8_12 *)(void *)impact_sprite)->unk_14 |= 0xC;
                    impact_position = (s32)(((S_80024BE8_11 *)impact)->unk_08);
                    ((S_80024BE8_13 *)(void *)impact_position)->unk_02 = ((S_80024BE8_5 *)motion)->unk_00.at02.v;
                    ((S_80024BE8_13 *)(void *)impact_position)->unk_06 = ((S_80024BE8_5 *)motion)->unk_04.at02.v;
                    ((S_80024BE8_13 *)(void *)impact_position)->unk_08.at00.v = ((S_80024BE8_5 *)motion)->unk_08.at00.v;
                    animation = D_800258FC;
                    impact_sprite = (s32)(((S_80024BE8_11 *)impact)->unk_0C);
                    ((S_80024BE8_12 *)(void *)impact_sprite)->unk_08 = animation;
                    ((S_80024BE8_12 *)(void *)impact_sprite)->unk_0E = random_intensity;
                    ((S_80024BE8_12 *)(void *)impact_sprite)->unk_0D = random_intensity;
                    ((S_80024BE8_12 *)(void *)impact_sprite)->unk_0C = random_intensity;
                    ((S_80024BE8_12 *)(void *)impact_sprite)->unk_1E = 1;
                    ((S_80024BE8_12 *)(void *)impact_sprite)->unk_1C = 1;
                    ((S_80024BE8_12 *)(void *)impact_sprite)->unk_14 ^= 0xC;
                    ((S_80024BE8_13 *)(void *)impact_position)->unk_08.at02.v =
                        ((S_80024BE8_23 *)(((S_80024BE8_3 *)source)->unk_60))->unk_88;
                }
                ((S_80024BE8_5 *)motion)->unk_08.at02.v = ((S_80024BE8_23 *)(((S_80024BE8_3 *)source)->unk_60))->unk_88;
            } else {
                ((S_80024BE8_0 *)effect)->unk_0A.s = 8;
                ((S_80024BE8_0 *)effect)->unk_82 = 0;
                ((S_80024BE8_2 *)sprite)->unk_0C.at02.v = 0;
                ((S_80024BE8_2 *)sprite)->unk_0C.at01.v = 0;
                ((S_80024BE8_2 *)sprite)->unk_0C.at00u.v = 0;
            }
            break;
        }
        {
            ((S_80024BE8_5 *)motion)->unk_00.at00.v += ((S_80024BE8_5 *)motion)->unk_0C;
            ((S_80024BE8_5 *)motion)->unk_04.at00.v += ((S_80024BE8_5 *)motion)->unk_10;
            ((S_80024BE8_5 *)motion)->unk_08.at00.v += ((S_80024BE8_5 *)motion)->unk_14;

            random_intensity = func_80069EF8();
            impact_position = random_intensity & 0xF;
            impact_position -= 8;
            impact_position <<= 16;
            impact_position >>= 16;
            impact_sprite = func_80069EF8() & 0xF;
            impact_sprite -= 8;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            func_800240C0(effect, motion, sprite, impact_position, impact_sprite,
                (s16)((func_80069EF8() & 0xF) - 8));
            impact_position = func_80069EF8() & 0xF;
            impact_position -= 8;
            impact_position <<= 16;
            impact_position >>= 16;
            impact_sprite = func_80069EF8() & 0xF;
            impact_sprite -= 8;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            func_800240C0(effect, motion, sprite, impact_position, impact_sprite,
                (s16)((func_80069EF8() & 0xF) - 8));
            impact_position = func_80069EF8() & 0xF;
            impact_position -= 8;
            impact_position <<= 16;
            impact_position >>= 16;
            impact_sprite = func_80069EF8() & 0xF;
            impact_sprite -= 8;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            func_800240C0(effect, motion, sprite, impact_position, impact_sprite,
                (s16)((func_80069EF8() & 0xF) - 8));
            impact_position = func_80069EF8() & 0xF;
            impact_position -= 8;
            impact_position <<= 16;
            impact_position >>= 16;
            impact_sprite = func_80069EF8() & 0xF;
            impact_sprite -= 8;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            func_800240C0(effect, motion, sprite, impact_position, impact_sprite,
                (s16)((func_80069EF8() & 0xF) - 8));
            impact_position = func_80069EF8() & 0xF;
            impact_position -= 8;
            impact_position <<= 16;
            impact_position >>= 16;
            impact_sprite = func_80069EF8() & 0xF;
            impact_sprite -= 8;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            func_800240C0(effect, motion, sprite, impact_position, impact_sprite,
                (s16)((func_80069EF8() & 0xF) - 8));
            impact_position = func_80069EF8() & 0xF;
            impact_position -= 8;
            impact_position <<= 16;
            impact_position >>= 16;
            impact_sprite = func_80069EF8() & 0xF;
            impact_sprite -= 8;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            func_800240C0(effect, motion, sprite, impact_position, impact_sprite,
                (s16)((func_80069EF8() & 0xF) - 8));
            break;
        }
    }

    case 3:
    {
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
            break;
        }
        break;
    }

    case 4:
    {
        void *animation;
        void *particle_sprite;
        void *particle_position;
        s32 particle_kind;
        u16 direction_preload;
        s32 animation_mode;
        u16 prev_state;
        s32 side;
        s32 jitter;
        s32 coord;
        s32 height;
        u16 scale_step;

        particle_count_m = 0;
        do {
            particle_count_m++;
            impact_sprite = func_80069EF8() & 0x3F;
            impact_sprite -= 0x20;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            func_800249A0((u8 *)effect - 0x20, impact_sprite,
                (s16)((func_80069EF8() & 0x3F) - 0x20),
                (s16)(-(((S_80024BE8_0 *)effect)->unk_86.s * 2) + 0x10), 0x1E);
        } while (particle_count_m < 2);

        particle_kind = 0x212;
        side = ((S_80024BE8_0 *)effect)->unk_86.u & 3;
        impact = func_8003FC64(particle_kind);
        if (impact != 0) {
            ((S_80024BE8_15 *)impact)->unk_22 = 0x1E;
            ((S_80024BE8_15 *)impact)->unk_10 = func_8002443C;
            func_8004491C(impact, (s32)func_80045340);
            particle_sprite = ((S_80024BE8_15 *)impact)->unk_0C;
            ((S_80024BE8_16 *)particle_sprite)->unk_10 = 0;
            ((S_80024BE8_16 *)particle_sprite)->unk_14 |= 0xC;
            particle_position = ((S_80024BE8_15 *)impact)->unk_08;
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
            height = (*(s32 *)((u8 *)motion + 8));
            animation_mode = 0;
            ((S_80024BE8_17 *)particle_position)->unk_08 = height;
            {
                void *scaled_sprite;
                s32 scale;

                particle_sprite = ((S_80024BE8_15 *)impact)->unk_0C;
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
            break;
        }
        break;
    }

    case 5:
    {
        void *target;
        void *current_target;
        s32 target_flag;
        u16 scale_step;

        particle_count_m = 0;
        do {
            particle_count_m++;
            impact_position = func_80069EF8() & 0x3F;
            impact_position -= 0x20;
            impact_position <<= 16;
            impact_position >>= 16;
            impact_sprite = func_80069EF8() & 0x3F;
            impact_sprite -= 0x20;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            func_800249A0((u8 *)effect - 0x20, impact_position, impact_sprite,
                (s16)(-0x20 - (func_80069EF8() & 0x3F)), 0x1E);
        } while (particle_count_m < 2);

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
        break;
    }

    case 6:
    {
        u16 elapsed;

        elapsed = ((S_80024BE8_0 *)effect)->unk_82 + 1;
        ((S_80024BE8_0 *)effect)->unk_82 = elapsed;
        if ((s16)elapsed >= 0x3D) {
            ((S_80024BE8_0 *)effect)->unk_0A.s = 8;
            ((S_80024BE8_0 *)effect)->unk_82 = 0x1E;
        }
        break;
    }

    case 8:
    {
        u16 elapsed;
        s32 active;

        elapsed = ((S_80024BE8_0 *)effect)->unk_82;
        ((S_80024BE8_0 *)effect)->unk_82 = elapsed + 1;
        if ((s16)(elapsed + 1) >= 0x1F) {
            active = D_80025914;
            ((S_80024BE8_0 *)effect)->unk_82 = elapsed;
            if (active == 0) {
                dungeonStatus.unk_0C = 0;
                ((S_80024BE8_0_pre *)effect)[-1].unk_00 |= 0x8000;
                D_800814A0[0] |= 0x8000;
            } else {
                D_80025914 = 0;
            }
        }
        break;
    }
    }

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
