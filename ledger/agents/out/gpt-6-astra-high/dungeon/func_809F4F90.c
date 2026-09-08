#include "common.h"

#ifdef NON_MATCHING
#include <stdint.h>
typedef uintptr_t az_uptr;
#else
typedef u32 az_uptr;
#endif

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80172790_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80172790_0;   /* arg3 in func_80172790 */

typedef struct S_80172790_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
} S_80172790_1;   /* arg0 in func_80172790 */

typedef struct S_80172790_2 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
} S_80172790_2;   /* object in func_80172790 */

typedef struct S_80172790_3 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    s16 unk_16;
    volatile u16 unk_18;
    u8 pad_1A[0x2E];
    volatile s16 unk_48;
    u8 pad_4A[0x2];
    volatile s16 unk_4C;
} S_80172790_3;   /* part in func_80172790 */

typedef struct S_80172790_4 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172790_4;   /* arg1 in func_80172790 */

typedef struct S_80172790_5 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
} S_80172790_5;   /* sprite in func_80172790 */

typedef struct S_80172790_6 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172790_6;   /* arg2 in func_80172790 */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 rand(void);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern u8 D_80045340;
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_80083228;
extern s32 D_8008346C;
extern s32 D_80083498;
extern u8 D_800DEC28[];
extern void *D_800E3DE8;
extern u8 D_80171400[];
extern u8 D_801743EC[];
extern u8 D_80175148[];
extern u8 D_80175160[];

/* Updates an actor's staged movement, particle effects, and return to its tile. */
void func_80172790(void *action_in, void *motion_in, void *tile_in, void *actor_in)
{
    s32 particle_x_offset;
    u8 *move_frames;
    s32 move_angle;
    s32 move_direction;
    u8 *idle_frames;
    s32 idle_angle;
    s32 idle_direction;
    register s32 heading_byte ASM_REG("$19");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 direction_offset ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 return_speed ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    s32 state;
    register s32 particles_left ASM_REG("$19");   /* MATCH pin: load-bearing for the whole function shape */
    s32 random_offset;
    s32 fall_speed;
    u16 flags;
    s32 vertical_speed;
    s32 origin_x;
    s32 origin_y;
    s32 x_speed;
    s32 y_speed;
    s32 z_speed;
    u32 color;
    s32 sprite_params;
    u8 *sprite_data;
    s32 x_step;
    s32 y_step;
    s32 particle_y;
    u16 heading_raw;
    void *particle;
    void *particle_motion;
    void *sprite;
    void *action;
    void *motion;
    void *tile;
    void *actor;
    register u8 *x_step_entry ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

    action = action_in;
    motion = motion_in;
    tile = tile_in;
    actor = actor_in;
    x_step_entry = (u8 *)0x80070000;
    ASM_KEEP(action);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(motion);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(tile);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(actor);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(x_step_entry);   /* MATCH pin: retail immediate-load split depends on it */

    heading_raw = ((S_80172790_0 *)actor)->unk_2A.s;
    ASM_KEEP(heading_raw);   /* MATCH pin: load-bearing for the whole function shape */
    x_step_entry -= 0x3328;
    heading_byte = heading_raw >> 8;
    direction_offset = heading_byte & 0xE;
    ASM_KEEP(direction_offset);   /* MATCH pin: load-bearing for the whole function shape */
    x_step_entry = (u8 *)((az_uptr)direction_offset + (az_uptr)x_step_entry);
    x_step = *(s16 *)x_step_entry;
    y_step = *(s16 *)(direction_offset + (u8 *)D_8006CCE8);
    ((S_80172790_1 *)action)->unk_96.s--;

    if ((u32)(((S_80172790_1 *)action)->unk_9B - 1) < 3U) {
        particles_left = 15;
        particle_x_offset = (x_step << 5) - 8;
        do {
            particle = func_8003FD64(0x312, &D_80083498);
            if (particle != NULL) {
                func_8004491C(particle, &D_80045340);
                particle_motion = (u8 *)particle + 0x20;
                ((S_80172790_2 *)particle)->unk_10 = D_801743EC;
                sprite = ((S_80172790_2 *)particle)->unk_0C;
                if (((S_80172790_1 *)action)->unk_9B < 3U) {
                    ((S_80172790_3 *)particle_motion)->unk_0C = ((S_80172790_4 *)motion)->unk_02.s + (rand() & 0xF) - 8;
                    random_offset = rand();
                    fall_speed = -0x500;
                    ASM_KEEP(fall_speed);   /* MATCH pin: retail register colouring depends on it */
                    particle_y = ((S_80172790_4 *)motion)->unk_06.s;
                    random_offset &= 0xF;
                    ((S_80172790_3 *)particle_motion)->unk_16 = fall_speed;
                    particle_y += random_offset;
                    particle_y -= 8;
                } else {
                    ((S_80172790_3 *)particle_motion)->unk_0C = ((S_80172790_4 *)motion)->unk_02.s + (rand() & 0xF) + particle_x_offset;
                    random_offset = rand();
                    fall_speed = -0x200;
                    ASM_KEEP(fall_speed);   /* MATCH pin: retail register colouring depends on it */
                    particle_y = ((S_80172790_4 *)motion)->unk_06.s;
                    random_offset &= 0xF;
                    ((S_80172790_3 *)particle_motion)->unk_16 = fall_speed;
                    particle_y += random_offset;
                    random_offset = (y_step << 5) - 8;
                    particle_y += random_offset;
                }
                ((S_80172790_3 *)particle_motion)->unk_0E = particle_y;
                ((S_80172790_3 *)particle_motion)->unk_10 = ((S_80172790_4 *)motion)->unk_0A + 8;
                ((S_80172790_3 *)particle_motion)->unk_14 = rand();
                heading_raw = ((S_80172790_0 *)actor)->unk_2A.s;
                do {
                    color = 0x00C00000;
                } while (0);
                ASM_KEEP(color);   /* MATCH pin: retail schedule: same instructions, different order without it */
                ((S_80172790_3 *)particle_motion)->unk_4C = 0;
                ((S_80172790_3 *)particle_motion)->unk_48 = 0;
                ((S_80172790_3 *)particle_motion)->unk_18 = heading_raw;
                (*(s16 *)((u8 *)sprite + 0x1E)) = 0x1000;
                (*(s16 *)((u8 *)sprite + 0x1C)) = 0x1000;
                (*(s16 *)((u8 *)sprite + 0x10)) = 0x60;
                sprite_data = D_800DEC28;
                (*(void * *)((u8 *)sprite + 0)) = sprite_data;
                (*(u16 *)((u8 *)sprite + 0x14)) |= 0xC;
                sprite_params = *(s32 *)(sprite_data + 4);
                color |= 0xC0C0;
                ((S_80172790_5 *)sprite)->unk_04 = 0;
                ((S_80172790_5 *)sprite)->unk_05 = 0;
                (*(s32 *)((u8 *)sprite + 0xC)) = color;
                ((S_80172790_5 *)sprite)->unk_08 = sprite_params;
            }
            particles_left--;
        } while (particles_left >= 0);
    }

    state = ((S_80172790_1 *)action)->unk_9B;
    switch (state) {
    case 0:
        flags = ((S_80172790_6 *)tile)->unk_14;
        if (flags & 0x8000) {
            ((S_80172790_1 *)action)->unk_9B = 0xFF;
            ((S_80172790_6 *)tile)->unk_14 |= 0x6000;
            func_8009C12C(actor, tile, ((S_80172790_0 *)actor)->unk_2A.u, 1);
            goto end;
        }
        if (flags & 0xE000) {
            move_frames = D_80175160;
            (*(void * *)((u8 *)tile + 0x2C)) = move_frames;
            move_angle = D_80083228 + ((S_80172790_0 *)actor)->unk_2A.u;
            move_direction = ((move_angle + 0x100) >> 9) & 7;
            func_80047784(tile, move_frames[move_direction], 0);
            ((S_80172790_4 *)motion)->unk_0C = (-x_step) << 0x12;
            ((S_80172790_4 *)motion)->unk_10 = (-y_step) << 0x12;
            ((S_80172790_1 *)action)->unk_98 |= 8;
            ((S_80172790_0 *)actor)->unk_1C &= 0xF7FFFFFF;
            ((S_80172790_0 *)actor)->unk_1C &= 0xFFFBFFFF;
            ((S_80172790_1 *)action)->unk_96.s = 4;
            ((S_80172790_4 *)motion)->unk_14 = 0xFFFC0000;
            goto advance;
        }
        goto end;

    case 1:
        vertical_speed = ((S_80172790_4 *)motion)->unk_14;
        ((S_80172790_4 *)motion)->unk_14 = vertical_speed + (vertical_speed >> 2);
        if (((S_80172790_1 *)action)->unk_96.u <= 0) {
            ((S_80172790_1 *)action)->unk_96.u = 3;
            ((S_80172790_1 *)action)->unk_9B++;
            goto end;
        }
        goto end;

    case 2:
        x_speed = ((S_80172790_4 *)motion)->unk_0C;
        y_speed = ((S_80172790_4 *)motion)->unk_10;
        ((S_80172790_4 *)motion)->unk_0C = x_speed - (x_speed >> 2);
        z_speed = ((S_80172790_4 *)motion)->unk_14;
        ((S_80172790_4 *)motion)->unk_10 = y_speed - (y_speed >> 2);
        ((S_80172790_4 *)motion)->unk_14 = z_speed - (z_speed >> 2);
        if (((S_80172790_1 *)action)->unk_96.u <= 0) {
            ((S_80172790_1 *)action)->unk_96.u = 7;
            ((S_80172790_4 *)motion)->unk_0C = x_step << 0x12;
            ((S_80172790_4 *)motion)->unk_10 = y_step << 0x12;
            ((S_80172790_4 *)motion)->unk_14 = 0x30000;
            func_800A56E0(0x80E);
            goto advance;
        }
        goto end;

advance:
        ((S_80172790_1 *)action)->unk_9B++;
        goto end;

    case 3:
        ((S_80172790_4 *)motion)->unk_0C += x_step << 0x12;
        ((S_80172790_4 *)motion)->unk_10 += y_step << 0x12;
        if (((S_80172790_1 *)action)->unk_96.u < 2) {
            ((S_80172790_4 *)motion)->unk_10 = 0;
            ((S_80172790_4 *)motion)->unk_0C = 0;
        }
        if (((S_80172790_1 *)action)->unk_96.u == 1) {
            func_8009C12C(actor, tile, ((S_80172790_0 *)actor)->unk_2A.u, 1);
            func_800A56E0(0x808);
        }
        if (((S_80172790_1 *)action)->unk_96.u <= 0) {
            ((S_80172790_4 *)motion)->unk_14 = 0xFFF60000;
            ((S_80172790_1 *)action)->unk_96.u = 0x14;
            ((S_80172790_1 *)action)->unk_9B = 0xFF;
        }
        goto end;

    case 0xFF:
        return_speed = ((S_80172790_6 *)tile)->unk_24 << 6;
        origin_x = ((S_80172790_4 *)motion)->unk_02.u - 0x20;
        return_speed -= origin_x;
        return_speed <<= 0xF;
        return_speed >>= 1;
        ((S_80172790_4 *)motion)->unk_0C = return_speed;
        return_speed = ((S_80172790_6 *)tile)->unk_25 << 6;
        origin_y = ((S_80172790_4 *)motion)->unk_06.u - 0x20;
        return_speed -= origin_y;
        return_speed <<= 0xF;
        return_speed >>= 1;
        ((S_80172790_4 *)motion)->unk_10 = return_speed;
        if (((S_80172790_1 *)action)->unk_96.u >= 0xA) {
            ((S_80172790_4 *)motion)->unk_14 += 0x10000;
        } else {
            ((S_80172790_4 *)motion)->unk_14 = -((S_80172790_1 *)action)->unk_92 << 0xD;
        }
        if (((S_80172790_1 *)action)->unk_96.u > 0 && !(((S_80172790_6 *)tile)->unk_14 & 0x8000)) {
            goto end;
        }
        ((S_80172790_4 *)motion)->unk_10 = 0;
        ((S_80172790_4 *)motion)->unk_0C = 0;
        ((S_80172790_0 *)actor)->unk_1C |= 0x40000;
        func_800A2B04(motion, ((S_80172790_6 *)tile)->unk_24, ((S_80172790_6 *)tile)->unk_25);
        func_800AD594(actor, 0x100);
        ((S_80172790_1 *)action)->unk_8C = D_80171400;
        D_8008346C = 0;
        func_800A4ACC(actor);
        ((S_80172790_4 *)motion)->unk_14 = 0;
        ((S_80172790_1 *)action)->unk_98 &= 0xFFF7;
        ((S_80172790_0 *)actor)->unk_1C |= 0x08000000;
        ((S_80172790_1 *)action)->unk_A8 = 7;
        idle_frames = D_80175148;
        (*(void * *)((u8 *)tile + 0x2C)) = idle_frames;
        idle_angle = D_80083228 + ((S_80172790_0 *)actor)->unk_2A.u;
        idle_direction = ((idle_angle + 0x100) >> 9) & 7;
        func_80047784(tile, idle_frames[idle_direction], 2);
        if (((S_80172790_0 *)actor)->unk_6D == 0) {
            ((S_80172790_0 *)actor)->unk_46 &= 0x7FFF;
        } else {
            D_800E3DE8 = (u8 *)actor - 0x20;
        }
        goto end;

    default:
        goto end;
    }
end:
    return;
}
