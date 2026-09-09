#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800247B8();      /* extern */
M2C_UNK func_80024AEC();      /* extern */
M2C_UNK func_80024D34();      /* extern */
M2C_UNK func_80047784();         /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800A4778();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800D4AB0();      /* extern */
extern u8 D_80025B38[9];
extern s16 D_80025B60;
extern s32 D_800814A0;
extern u8 D_800DDC40[];


typedef struct S_80024E5C_0_pre {
    u16 unk_00;
} S_80024E5C_0_pre;   /* the 0x2 bytes before arg0 in func_80024E5C, addressed as arg0[-1] */

typedef struct S_80024E5C_0 {
    u8 pad_00[0x56];
    u16 unk_56;
    union { u16 u; s16 s; } unk_58;   /* accessed as both */
    union { u16 u; s16 s; } unk_5A;   /* accessed as both */
    u16 unk_5C;
    u8 pad_5E[0x2];
    s16 unk_60;
    s16 unk_62;
    u8 pad_64[0xE];
    u16 unk_72;
    u8 pad_74[0x14];
    void * unk_88;
    void * unk_8C;
    u8 pad_90[0x8];
    s32 unk_98;
    s32 unk_9C;
    s32 unk_A0;
} S_80024E5C_0;   /* arg0 in func_80024E5C */

typedef struct S_80024E5C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    union { s8 s; u8 u; } unk_0C;   /* accessed as both */
    union { s8 s; u8 u; } unk_0D;   /* accessed as both */
    union { s8 s; u8 u; } unk_0E;   /* accessed as both */
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80024E5C_1;   /* arg2 in func_80024E5C */

typedef struct S_80024E5C_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024E5C_2;   /* arg1 in func_80024E5C */

typedef struct S_80024E5C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_80024E5C_3;   /* temp_a1 in func_80024E5C */

typedef struct S_80024E5C_4_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_80024E5C_4_pre;   /* the 0x18 bytes before ((S_80024E5C_0 *)arg0)->unk_88 in func_80024E5C, addressed as ((S_80024E5C_0 *)arg0)->unk_88[-1] */

typedef struct S_80024E5C_4 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_80024E5C_4;   /* ((S_80024E5C_0 *)arg0)->unk_88 in func_80024E5C */

typedef struct S_80024E5C_5 {
    u8 pad_00[0x86];
    s16 unk_86;
} S_80024E5C_5;   /* ((S_80024E5C_0 *)arg0)->unk_8C in func_80024E5C */

/* Update the effect's color cycle, movement, bursts, and destruction. */
void func_80024E5C(void *effect, void *motion, void *sprite) {
    register s32 delta_or_divisor ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s16 reduced_scale;
    u8 *height_table;
    register s32 travel_distance ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s16 travel_frames;
    s16 next_burst;
    s16 next_pair;
    s16 next_triple;
    s16 next_quad;
    s16 next_trail;
    s16 impact_state;
    s16 trail_index;
    s16 burst_index;
    s16 pair_index;
    s16 triple_index;
    s16 quad_index;
    s32 velocity_y;
    s32 target_y;
    s32 velocity_z;
    s32 target_z;
    s32 current_x;
    s32 end_frame;
    s32 target_x_or_z_step;
    s32 distance_x;
    s32 completion_state;
    s32 near_target;
    u16 next_color;
    u16 start_frame;
    u16 frames_left;
    u16 impact_frame;
    u16 scale;
    u16 burst_frame;
    u16 color_cycle;
    u16 initial_state;
    u16 clamped_scale;
    u8 effect_id;
    void *target_position;

    initial_state = ((S_80024E5C_0 *)effect)->unk_58.u;
    D_80025B60 = 1;
    if (initial_state < 3U) {
        ((S_80024E5C_1 *)sprite)->unk_0E.s = 0x3C;
        ((S_80024E5C_1 *)sprite)->unk_0D.s = 0x3C;
        ((S_80024E5C_1 *)sprite)->unk_0C.s = 0x3C;
        color_cycle = ((S_80024E5C_0 *)effect)->unk_72;
        next_color = color_cycle + 1;
        ((S_80024E5C_0 *)effect)->unk_72 = next_color;
        if (!(next_color & 7)) {
            ((S_80024E5C_0 *)effect)->unk_72 = (u16) (color_cycle + 2);
        }
        if (((S_80024E5C_0 *)effect)->unk_72 & 1) {
            ((S_80024E5C_1 *)sprite)->unk_0C.u = 0x80;
        }
        if (((S_80024E5C_0 *)effect)->unk_72 & 2) {
            ((S_80024E5C_1 *)sprite)->unk_0D.u = 0x80;
        }
        if (((S_80024E5C_0 *)effect)->unk_72 & 4) {
            ((S_80024E5C_1 *)sprite)->unk_0E.u = 0x80;
        }
    }
    if (((S_80024E5C_0 *)effect)->unk_58.s == 0) {
        start_frame = ((S_80024E5C_0 *)effect)->unk_5A.u;
        ((S_80024E5C_0 *)effect)->unk_5A.u = (u16) (start_frame + 1);
        if ((s16) start_frame >= 6) {
            effect_id = D_80025B38[0];
            ((S_80024E5C_1 *)sprite)->unk_2C = D_80025B38;
            func_80047784(sprite, effect_id, 0);
            ((S_80024E5C_0 *)effect)->unk_5A.u = 0U;
            ((S_80024E5C_0 *)effect)->unk_58.u = (u16) (((S_80024E5C_0 *)effect)->unk_58.u + 1);
            ((S_80024E5C_2 *)motion)->unk_08.at02.v = (u16) (((S_80024E5C_2 *)motion)->unk_08.at02.v - 0x5A);
        }
    }
    completion_state = ((S_80024E5C_0 *)effect)->unk_58.s;
    if (completion_state == 1) {
        if ((func_800A4778(((S_80024E5C_2 *)motion)->unk_00.at02.v, ((S_80024E5C_2 *)motion)->unk_04.at02.v, (s16) ((S_80024E5C_2 *)motion)->unk_08.at02.v, ((S_80024E5C_0 *)effect)->unk_88) << 0x10) == 0) {
            if (((S_80024E5C_0 *)effect)->unk_60 != 0) {
                target_position = ((S_80024E5C_4_pre *)(((S_80024E5C_0 *)effect)->unk_88))[-1].unk_00;
                ((S_80024E5C_1 *)sprite)->unk_06 = 8;
                if (((S_80024E5C_0 *)effect)->unk_5A.s == 0) {
                    delta_or_divisor = ((S_80024E5C_3 *)target_position)->unk_00.at02.v;
                    delta_or_divisor -= ((S_80024E5C_2 *)motion)->unk_00.at02u.v;
                    distance_x = delta_or_divisor;
                    if (delta_or_divisor < 0) {
                        distance_x = 0 - distance_x;
                    }
                    if (distance_x < 0) {
                        distance_x += 0x3F;
                    }
                    delta_or_divisor = ((S_80024E5C_3 *)target_position)->unk_04.at02.v;
                    delta_or_divisor -= ((S_80024E5C_2 *)motion)->unk_04.at02u.v;
                    travel_distance = delta_or_divisor;
                    if (delta_or_divisor < 0) {
                        travel_distance = 0 - travel_distance;
                    }
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    if (travel_distance < 0) {
                        travel_distance += 0x3F;
                    }
                    travel_distance = (distance_x >> 6) + (travel_distance >> 6);
                    ((S_80024E5C_0 *)effect)->unk_5A.u = (u16) (((s32) (travel_distance << 0x10) >> 0xF) + 0xB);
                }
                height_table = D_800DDC40;
                travel_frames = (s16) ((S_80024E5C_0 *)effect)->unk_5A.u;
                target_z = ((S_80024E5C_3 *)target_position)->unk_08 - (((u8) *(((S_80024E5C_4 *)(((S_80024E5C_0 *)effect)->unk_88))->unk_13 + height_table) >> 1) << 0x10);
                near_target = travel_frames < 0xE;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                target_x_or_z_step = ((S_80024E5C_3 *)target_position)->unk_00.at00.v;
                target_y = ((S_80024E5C_3 *)target_position)->unk_04.at00.v;
                if (near_target == 0) {
                    current_x = ((S_80024E5C_2 *)motion)->unk_00.at00.v;
                    ((S_80024E5C_2 *)motion)->unk_0C = (s32) ((target_x_or_z_step - current_x) / (s32) (travel_frames - 0xB));
                    ((S_80024E5C_2 *)motion)->unk_10 = (s32) ((s32) (target_y - ((S_80024E5C_2 *)motion)->unk_04.at00.v) / (s32) ((s16) ((S_80024E5C_0 *)effect)->unk_5A.u - 0xB));
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    target_x_or_z_step = ((S_80024E5C_2 *)motion)->unk_08.at00.v;
                    delta_or_divisor = ((S_80024E5C_0 *)effect)->unk_5A.s;
                    target_x_or_z_step = target_z - target_x_or_z_step;
                    delta_or_divisor -= 0xB;
                    goto divide_z;
                }
                if (travel_frames >= 0xB) {
                    current_x = ((S_80024E5C_2 *)motion)->unk_00.at00.v;
                    ((S_80024E5C_2 *)motion)->unk_0C = (s32) ((target_x_or_z_step - current_x) / (s32) (travel_frames - 9));
                    ((S_80024E5C_2 *)motion)->unk_10 = (s32) ((s32) (target_y - ((S_80024E5C_2 *)motion)->unk_04.at00.v) / (s32) ((s16) ((S_80024E5C_0 *)effect)->unk_5A.u - 9));
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    target_x_or_z_step = ((S_80024E5C_2 *)motion)->unk_08.at00.v;
                    delta_or_divisor = ((S_80024E5C_0 *)effect)->unk_5A.s;
                    target_x_or_z_step = target_z - target_x_or_z_step;
                    delta_or_divisor -= 9;
                    goto divide_z;
                }
                if (travel_frames >= 5) {
                    current_x = ((S_80024E5C_2 *)motion)->unk_00.at00.v;
                    ((S_80024E5C_2 *)motion)->unk_0C = (s32) ((target_x_or_z_step - current_x) / (s32) (travel_frames - 4));
                    ((S_80024E5C_2 *)motion)->unk_10 = (s32) ((s32) (target_y - ((S_80024E5C_2 *)motion)->unk_04.at00.v) / (s32) ((s16) ((S_80024E5C_0 *)effect)->unk_5A.u - 4));
                    target_x_or_z_step = target_z - ((S_80024E5C_2 *)motion)->unk_08.at00.v;
                    delta_or_divisor = ((S_80024E5C_0 *)effect)->unk_5A.s - 4;
divide_z:
                    target_x_or_z_step /= delta_or_divisor;
                    ((S_80024E5C_2 *)motion)->unk_14 = target_x_or_z_step;
                    goto integrate;
                }
                ((S_80024E5C_2 *)motion)->unk_0C = (s32) ((s32) (target_x_or_z_step - ((S_80024E5C_2 *)motion)->unk_00.at00.v) / travel_frames);
                ((S_80024E5C_2 *)motion)->unk_10 = (s32) ((s32) (target_y - ((S_80024E5C_2 *)motion)->unk_04.at00.v) / (s16) ((S_80024E5C_0 *)effect)->unk_5A.u);
                ((S_80024E5C_2 *)motion)->unk_14 = (s32) ((s32) (target_z - ((S_80024E5C_2 *)motion)->unk_08.at00.v) / (s16) ((S_80024E5C_0 *)effect)->unk_5A.u);
integrate:
                velocity_y = ((S_80024E5C_2 *)motion)->unk_10;
                velocity_z = ((S_80024E5C_2 *)motion)->unk_14;
                ((S_80024E5C_2 *)motion)->unk_00.at00.v = (s32) (((S_80024E5C_2 *)motion)->unk_00.at00.v + ((S_80024E5C_2 *)motion)->unk_0C);
                ((S_80024E5C_2 *)motion)->unk_04.at00.v = (s32) (((S_80024E5C_2 *)motion)->unk_04.at00.v + velocity_y);
                ((S_80024E5C_2 *)motion)->unk_08.at00.v = (s32) (((S_80024E5C_2 *)motion)->unk_08.at00.v + velocity_z);
                frames_left = ((S_80024E5C_0 *)effect)->unk_5A.u - 1;
                ((S_80024E5C_0 *)effect)->unk_5A.u = frames_left;
                if ((frames_left << 0x10) == 0) {
                    ((S_80024E5C_0 *)effect)->unk_58.u = 2U;
                    ((S_80024E5C_0 *)effect)->unk_62 = 6;
                    ((S_80024E5C_0 *)effect)->unk_5A.u = 0U;
                    ((S_80024E5C_2 *)motion)->unk_14 = 0;
                    ((S_80024E5C_2 *)motion)->unk_10 = 0;
                    ((S_80024E5C_2 *)motion)->unk_0C = 0;
                    ((S_80024E5C_0 *)effect)->unk_56 = 0x1E;
                    goto emit_trail;
                }
                goto emit_trail;
            }
            ((S_80024E5C_0 *)effect)->unk_5A.u = 0xAU;
            ((S_80024E5C_0 *)effect)->unk_5C = (u16) (((S_80024E5C_0 *)effect)->unk_5C - 1);
            ((S_80024E5C_2 *)motion)->unk_00.at00.v = (s32) (((S_80024E5C_2 *)motion)->unk_00.at00.v + ((S_80024E5C_0 *)effect)->unk_98);
            ((S_80024E5C_2 *)motion)->unk_04.at00.v = (s32) (((S_80024E5C_2 *)motion)->unk_04.at00.v + ((S_80024E5C_0 *)effect)->unk_9C);
            ((S_80024E5C_2 *)motion)->unk_08.at00.v = (s32) (((S_80024E5C_2 *)motion)->unk_08.at00.v + ((S_80024E5C_0 *)effect)->unk_A0);
            if ((s16) ((S_80024E5C_0 *)effect)->unk_5C > 0) {
emit_trail:
                if ((s16) ((S_80024E5C_0 *)effect)->unk_5A.u >= 5) {
                    trail_index = 0;
                    do {
                        func_80024D34(effect, motion, sprite);
                        next_trail = trail_index + 1;
                        trail_index = next_trail;
                    } while (next_trail < 4);
                }
                goto update_impact;
            }
            goto destroy;
        }
        goto destroy;
    }
update_impact:
    impact_state = (s16) ((S_80024E5C_0 *)effect)->unk_58.u;
    if (impact_state == 2) {
        impact_frame = ((S_80024E5C_0 *)effect)->unk_5A.u + 1;
        ((S_80024E5C_0 *)effect)->unk_5A.u = impact_frame;
        if ((s16) impact_frame == impact_state) {
            func_80024AEC(effect, motion, sprite);
            func_800A56E0(0x300);
        }
        if ((s16) ((S_80024E5C_0 *)effect)->unk_5A.u >= 0xA) {
            scale = ((S_80024E5C_1 *)sprite)->unk_1C;
            if (scale != 0) {
                reduced_scale = scale - 0xC8;
                clamped_scale = reduced_scale;
                if (reduced_scale < 0) {
                    clamped_scale = 0;
                }
                ((S_80024E5C_1 *)sprite)->unk_1C = clamped_scale;
                ((S_80024E5C_1 *)sprite)->unk_1E = clamped_scale;
            }
        }
        if ((s16) ((S_80024E5C_0 *)effect)->unk_5A.u >= 0x1E) {
            ((S_80024E5C_0 *)effect)->unk_56 = (u16) (((S_80024E5C_0 *)effect)->unk_56 + 3);
            func_800247B8(effect, motion, sprite);
            if ((s16) ((S_80024E5C_0 *)effect)->unk_5A.u >= 0x28) {
                func_800247B8(effect, motion, sprite);
            }
            if ((s16) ((S_80024E5C_0 *)effect)->unk_5A.u >= 0x2D) {
                func_800247B8(effect, motion, sprite);
            }
        }
        if ((s16) ((S_80024E5C_0 *)effect)->unk_5A.u >= 0x32) {
            ((S_80024E5C_0 *)effect)->unk_58.u = 3U;
            ((S_80024E5C_0 *)effect)->unk_5A.u = 0U;
            ((S_80024E5C_1 *)sprite)->unk_14 = (u16) (((S_80024E5C_1 *)sprite)->unk_14 | 0x80);
        }
    }
    if ((s16) ((S_80024E5C_0 *)effect)->unk_58.u == 3) {
        burst_frame = ((S_80024E5C_0 *)effect)->unk_5A.u + 1;
        ((S_80024E5C_0 *)effect)->unk_5A.u = burst_frame;
        if ((s16) burst_frame < 0x12) {
            burst_index = 0;
            ((S_80024E5C_0 *)effect)->unk_56 = (u16) (((S_80024E5C_0 *)effect)->unk_56 - 3);
            do {
                func_800247B8(effect, motion, sprite);
                next_burst = burst_index + 1;
                burst_index = next_burst;
            } while (next_burst < 5);
        }
        if ((s16) ((S_80024E5C_0 *)effect)->unk_5A.u == 0x10) {
            pair_index = 0;
            do {
                func_800247B8(effect, motion, sprite);
                next_pair = pair_index + 1;
                pair_index = next_pair;
            } while (next_pair < 2);
        }
        triple_index = 0;
        if ((s16) ((S_80024E5C_0 *)effect)->unk_5A.u == 0x11) {
            do {
                func_800247B8(effect, motion, sprite);
                next_triple = triple_index + 1;
                triple_index = next_triple;
            } while (next_triple < 3);
        }
        quad_index = 0;
        if ((s16) ((S_80024E5C_0 *)effect)->unk_5A.u == 0x12) {
            do {
                func_800247B8(effect, motion, sprite);
                next_quad = quad_index + 1;
                quad_index = next_quad;
            } while (next_quad < 4);
        }
        end_frame = (s16) ((S_80024E5C_0 *)effect)->unk_5A.u;
        completion_state = 1;
        if (end_frame == 1) {
            func_800D4AB0(effect, motion, sprite);
            end_frame = ((S_80024E5C_0 *)effect)->unk_5A.s;
        }
        if (end_frame >= 0x1B) {
            goto destroy;
        }
    }
    goto normal_return;
destroy:
    ((S_80024E5C_5 *)(((S_80024E5C_0 *)effect)->unk_8C))->unk_86 = completion_state;
    (*(u16 *)((u8 *)effect + (-2))) = (u16) (((S_80024E5C_0_pre *)effect)[-1].unk_00 | 0x8000);
    D_800814A0 |= 0x8000;
    return;
normal_return:
    func_800478B8(sprite);
}
