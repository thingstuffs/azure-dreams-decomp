#include "common.h"


typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} LocalVector;

typedef struct {
    u32 words[8];
} __attribute__((packed)) LocalTable;


extern void func_80047784(void *, u8, s32);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_8009A028(void *);
extern void func_8009A3D0(u8, u8, s32);
extern s32 func_800A2FE0(void *);
extern s32 func_800A32A4(void *);
extern s32 func_800A45D8(u16, u16, s16);
extern void func_800A56E0(s32);
extern void func_800ACF88(void *);
extern s16 func_800BCB04(u16, u16, s16);
extern s32 func_8017165C(s32);

extern s32 D_800814A0;
extern u8 D_80083160[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800E2368[];
extern s32 D_800E296C;
extern LocalTable D_8017088C;
extern void *const D_801708B0[];
extern void *const D_801708C8[];


typedef struct S_8017450C_0 {
    u8 pad_00[0x90];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
    u8 pad_A4[0xA];
    s16 unk_AE;
    u8 pad_B0[0x6];
    u16 unk_B6;
} S_8017450C_0;   /* arg0 in func_8017450C */

typedef struct S_8017450C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x4];
    union { u16 u; s16 s; } unk_1A;   /* accessed as both */
    s16 unk_1C;
    u8 pad_1E[0x4];
    u16 unk_22;
    u8 unk_24;
    u8 unk_25;
} S_8017450C_1;   /* monster in func_8017450C */

typedef struct S_8017450C_2 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_8017450C_2;   /* globals in func_8017450C */

typedef struct S_8017450C_3 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_8017450C_3;   /* actor in func_8017450C */

typedef struct S_8017450C_4 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8017450C_4;   /* motion in func_8017450C */

typedef struct S_8017450C_5 {
    u8 pad_00[0x10];
    u32 unk_10;
} S_8017450C_5;   /* cleanup_base in func_8017450C */

/* Update the monster's staged motion, choose a nearby destination, and clean up its actor. */
void func_8017450C(void *state, void *motion, void *monster, void *actor_ptr)
{
    LocalVector direction;
    LocalTable direction_table;
    s16 facing_angle;
    s32 trig_value;
    s32 scaled_speed;
    s32 attempt;
    s32 random_x;
    s32 random_y;
    s32 x_offset;
    s32 y_offset;
    s32 x;
    s32 y;
    s32 direction_index;
    u32 actor;
    u8 *view_state;
    u8 tile_x;
    u8 tile_y;

    direction_table = D_8017088C;
    actor = (u32)actor_ptr;

    {
        static void *const state_labels[] = {
            &&state_0, &&state_1, &&state_2, &&state_3, &&state_4
        };
        u32 state_index = ((S_8017450C_0 *)state)->unk_9B;

        if (state_index >= 5) {
            return;
        }
        (void)state_labels;
        goto *D_801708B0[state_index];
    }

state_0:
    if (((S_8017450C_1 *)monster)->unk_14 & 0x8000) {
        goto cleanup;
    }

    facing_angle = 0;
    view_state = D_80083160;
    do {
        if (((((S_8017450C_2 *)view_state)->unk_C8 + facing_angle + 0x100) >> 9 & 7) == 2) {
            ((S_8017450C_3 *)actor)->unk_2A = facing_angle;
        }
        facing_angle += 0x200;
    } while (facing_angle < 0x1000);

    {
        u8 *animation_table = D_800E2368;
        (*(u8 * *)((u8 *)monster + (0x2C))) = animation_table;
        direction_index = (D_80083228 + ((S_8017450C_3 *)actor)->unk_2A + 0x100) >> 9 & 7;
        func_80047784(monster, animation_table[direction_index], 0);
        ((S_8017450C_0 *)state)->unk_98 |= 8;
        ((S_8017450C_3 *)actor)->unk_1C &= 0xFFFBFFFF;
        ((S_8017450C_0 *)state)->unk_90.at02.v += ((S_8017450C_3 *)actor)->unk_88;
        ((S_8017450C_3 *)actor)->unk_88 = 0;
    }
    {
        register u16 state_or_height ASM_REG("$2") = ((S_8017450C_0 *)state)->unk_9B;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 height_offset = ((S_8017450C_0 *)state)->unk_90.at02.v;
        s32 *sound_flags = &D_800E296C;
        s32 sound_bits;

        ((S_8017450C_0 *)state)->unk_A0 = 0;
        ((S_8017450C_0 *)state)->unk_9B = state_or_height + 1;
        state_or_height = ((S_8017450C_4 *)motion)->unk_0A;
        sound_bits = *sound_flags;
        state_or_height += height_offset;
        sound_bits |= 0x40;
        ((S_8017450C_0 *)state)->unk_B6 = state_or_height;
        *sound_flags = sound_bits;
        func_800A56E0(0x807);
    }

state_1:
    ((S_8017450C_0 *)state)->unk_96.s = 0;
    ((S_8017450C_0 *)state)->unk_9B++;
    ((S_8017450C_1 *)monster)->unk_22 = 0xFFEC;
    ((S_8017450C_1 *)monster)->unk_1C = 0x800;

state_2:
    {
        static void *const angle_labels[] = {
            &&angle_default,
            &&angle_12, &&angle_12,
            &&angle_3_8, &&angle_3_8, &&angle_3_8,
            &&angle_3_8, &&angle_3_8, &&angle_3_8,
            &&angle_9_10, &&angle_9_10,
            &&angle_11_14, &&angle_11_14, &&angle_11_14, &&angle_11_14,
            &&angle_15_17, &&angle_15_17, &&angle_15_17,
            &&angle_18_21, &&angle_18_21, &&angle_18_21, &&angle_18_21
        };
        u32 frame_index = (u32)(s16)((S_8017450C_0 *)state)->unk_96.s;

        if (frame_index >= 0x16) {
            goto angle_default;
        }
        (void)angle_labels;
        goto *D_801708C8[frame_index];
    }

angle_12:
    ((S_8017450C_0 *)state)->unk_AE = 0x30;
    ((S_8017450C_1 *)monster)->unk_1A.u += 0x100;
    goto angle_store;

angle_3_8:
    ((S_8017450C_0 *)state)->unk_AE = 0x28;
    ((S_8017450C_1 *)monster)->unk_1A.u += 0x200;
    goto angle_store;

angle_9_10:
    ((S_8017450C_0 *)state)->unk_AE = 0x30;
    ((S_8017450C_1 *)monster)->unk_1A.u += 0x100;
    goto angle_store;

angle_11_14:
    ((S_8017450C_0 *)state)->unk_AE = 0x70;
    ((S_8017450C_1 *)monster)->unk_1A.u += 0x100;
    goto angle_store;

angle_15_17:
    ((S_8017450C_0 *)state)->unk_AE = 0x60;
    ((S_8017450C_1 *)monster)->unk_1A.u += 0x200;
    goto angle_store;

angle_18_21:
    ((S_8017450C_0 *)state)->unk_AE = 0x50;
    ((S_8017450C_1 *)monster)->unk_1A.u += 0x80;
    goto angle_store;

angle_default:
    ((S_8017450C_1 *)monster)->unk_1A.u += 0x20;

angle_store:
    if (((S_8017450C_1 *)monster)->unk_1A.u >= 0x1000) {
        ((S_8017450C_1 *)monster)->unk_1A.u -= 0x1000;
    }

    {
        register s32 angle ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 angle_delta;

        angle = ((S_8017450C_1 *)monster)->unk_1A.u;
        angle_delta = angle - 0x400;
        angle = angle_delta;
        if ((s16)angle_delta < 0) {
            angle = angle_delta + 0x1000;
        }
        angle = (s16)angle;

        trig_value = func_80064584(angle);
        scaled_speed = ((S_8017450C_0 *)state)->unk_AE * trig_value;
        {
            s32 original_angle = angle;

            angle = scaled_speed << 4;
            trig_value = func_800644B8(original_angle);
        }

        scaled_speed = ((S_8017450C_0 *)state)->unk_AE * trig_value;
        {
            u8 *direction_entry = (u8 *)&direction_table;
            direction.x = (*(u16 *)((u8 *)direction_entry + (((((S_8017450C_3 *)actor)->unk_2A - 0x400) >> 7) & 0x1C)));
            direction_entry +=
                ((((S_8017450C_3 *)actor)->unk_2A - 0x400) >> 7) & 0x1C;
            direction.y = (*(u16 *)((u8 *)direction_entry + (2)));

            ((S_8017450C_0 *)state)->unk_90.at00.v += scaled_speed << 4;
            ((S_8017450C_4 *)motion)->unk_0C = (direction.x * angle) >> 4;
            ((S_8017450C_4 *)motion)->unk_10 = (direction.y * angle) >> 4;
        }
    }

    if ((s16)(((S_8017450C_0 *)state)->unk_96.u++) < 0x2D) {
        return;
    }

    ((S_8017450C_0 *)state)->unk_96.s = 0;
    ((S_8017450C_0 *)state)->unk_9B++;
    ((S_8017450C_1 *)monster)->unk_1A.s = 0x800;
    ((S_8017450C_4 *)motion)->unk_10 = 0;
    ((S_8017450C_4 *)motion)->unk_0C = 0;
    ((S_8017450C_4 *)motion)->unk_02.s = (((S_8017450C_1 *)monster)->unk_24 << 6) + 0x20;
    ((S_8017450C_4 *)motion)->unk_06.s = (((S_8017450C_1 *)monster)->unk_25 << 6) + 0x20;
    ((S_8017450C_4 *)motion)->unk_0A = ((S_8017450C_0 *)state)->unk_B6;
    ((S_8017450C_4 *)motion)->unk_14 = 0x280000;
    ((S_8017450C_0 *)state)->unk_A0 = 0;
    ((S_8017450C_0 *)state)->unk_90.at02.v = ((S_8017450C_0 *)state)->unk_B6 - 0x12C;
    ((S_8017450C_1 *)monster)->unk_1C = 0x600;

    attempt = 0;
    do {
        random_x = func_8017165C(7) - 3;
        random_y = func_8017165C(6) - 2;
        x_offset = random_x << 6;
        x = ((S_8017450C_4 *)motion)->unk_02.s + x_offset;
        if (x >= 0x1020) {
            goto next_try;
        }
        if (x <= 0) {
            goto next_try;
        }

        y_offset = random_y << 6;
        y = ((S_8017450C_4 *)motion)->unk_06.s + y_offset;
        if (y >= 0x1020) {
            goto next_try;
        }
        if (y <= 0) {
            goto next_try;
        }

        actor = (u16)x;
        y = (u16)y;
        if ((func_800A45D8(actor, y, -0x200) << 16) != 0) {
            goto next_try;
        }
        if (func_800BCB04(actor, y, -0x200) < 0x200) {
            attempt++;
            continue;
        }

        random_x = 0xB;
        attempt = random_x;
        ((S_8017450C_4 *)motion)->unk_02.u += x_offset;
        ((S_8017450C_4 *)motion)->unk_06.u += y_offset;

next_try:
        attempt++;
    } while (attempt < 0xA);

    if (random_x == 0xB) {
        return;
    }

    ((S_8017450C_0 *)state)->unk_9B = 4;
    ((S_8017450C_4 *)motion)->unk_14 = 0;
    ((S_8017450C_1 *)monster)->unk_14 |= 0x80;
    return;

state_3:
    if ((s16)(((S_8017450C_0 *)state)->unk_96.u++) < 0x1E) {
        return;
    }
    ((S_8017450C_0 *)state)->unk_96.s = 0;
    ((S_8017450C_0 *)state)->unk_9B++;
    return;

state_4:
    if ((s16)(((S_8017450C_0 *)state)->unk_96.u++) < 0xA) {
        return;
    }
    if (((S_8017450C_3 *)actor)->unk_14 & 0x4000) {
        if (!(((S_8017450C_3 *)actor)->unk_14 & 0x20000000)) {
            func_800ACF88((void *)actor);
        }
    }

cleanup:
{
    u8 *cleanup_base = (u8 *)&D_80083460;
    u32 tracked_actor;
    s32 tile_flags;

    tracked_actor = ((S_8017450C_5 *)cleanup_base)->unk_10;
    if (tracked_actor == actor - 0x20) {
        ((S_8017450C_5 *)cleanup_base)->unk_10 = tracked_actor & 0x7FFFFFFF;
    }
    func_800A2FE0((void *)actor);
    func_800A32A4((void *)actor);
    tile_x = ((S_8017450C_1 *)monster)->unk_24;
    tile_y = ((S_8017450C_1 *)monster)->unk_25;
    if (((S_8017450C_3 *)actor)->unk_1C & 0x2000) {
        tile_flags = 0x300;
    } else {
        tile_flags = 0x3000;
    }
    func_8009A3D0(tile_x, tile_y, tile_flags);
    func_8009A028((void *)actor);
    (*(u16 *)((u8 *)actor + (-2))) |= 0x8000;
    D_800814A0 |= 0x8000;
}
}
