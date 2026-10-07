/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
extern int abs(int);

typedef struct S_8080C650_0_pre {
    u16 unk_00;
} S_8080C650_0_pre;   /* the 0x2 bytes before in0 in func_8080C650, addressed as in0[-1] */

typedef struct S_8080C650_0 {
    u8 pad_00[0x15];
    s8 unk_15;
    u8 pad_16[0x52];
    union { s16 s; u16 u; } unk_68;   /* accessed as both */
    u8 pad_6A[0x2];
    u16 unk_6C;
    u8 pad_6E[0x3A];
    s32 unk_A8;
    void * unk_AC;
} S_8080C650_0;   /* in0 in func_8080C650 */

typedef struct S_8080C650_1 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xA];
    u16 unk_2A;
    s16 unk_2C;
    u16 unk_2E;
    u8 pad_30[0x4];
    s16 unk_34;
    s16 unk_36;
} S_8080C650_1;   /* sequence in func_8080C650 */

typedef struct S_8080C650_2 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8080C650_2;   /* motion in func_8080C650 */

typedef struct S_8080C650_3 {
    u8 pad_00[0xC];
    union { s32 s32; u8 u8; } unk_0C;   /* accessed as both */
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_8080C650_3;   /* primitive in func_8080C650 */

typedef struct S_8080C650_4 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
    void * unk_24;
} S_8080C650_4;   /* floor_height_or_spawned_object in func_8080C650 */


s32 func_80034A1C();                /* extern */
void *func_800374FC();            /* extern */
M2C_UNK func_8003BC18();           /* extern */
M2C_UNK func_8003EA54();                      /* extern */
M2C_UNK func_80050BD8();                     /* extern */
M2C_UNK func_80050BFC();                     /* extern */
M2C_UNK func_80058F88();                     /* extern */
s32 func_8006A3A4();                             /* extern */
s32 func_8006A470();                             /* extern */
M2C_UNK func_8023FB18();                      /* extern */
M2C_UNK func_80245C10();             /* extern */
s16 func_8025E01C();                          /* extern */
extern s16 D_800133A0[5];
extern s16 D_800133A0_store[5] __asm__("D_800133A0");
extern u8 D_8003C558[3];
extern s32 D_80084D5C;
extern M2C_UNK D_8012F130[5];
extern u8 D_801328C8[3];
extern s32 D_801328E8[3];
extern s32 D_80132AE8[3];
extern s32 D_80132AEC[3];
extern s32 D_80132AF0[3];
extern s16 D_80132AF2[5];
extern u8 D_802430A8[12];
extern u8 D_80243200[12];
extern u8 D_802434B0[12];
extern u8 D_802892EC[12];
extern u8 D_80289334[12];
extern u8 D_8028937C[12];
extern u8 D_802893C4[12];
extern u8 D_8028940C[12];
extern u8 D_802894AC[12];
extern u8 D_80289454[12];
extern u8 D_8028950C[12];
extern u8 D_8028954C[12];
extern s32 D_8029070C[3];
extern u8 D_80529080[12];
extern s16 D_80530658[];
void func_8080C650(void *in0, void *motion, void *in2) {
    s16 *count_cursor;
    s16 raw_s1;
    s32 slot_count;
    s16 phase;
    s32 count_sum_or_color;
    s32 x_before_acceleration;
    s32 x_before_clamp;
    s32 velocity_component;
    s32 x_limit_flags_or_phase;
    s32 current_y;
    s32 current_x;
    s32 delta;
    s32 loop_index;
    s32 animation_descriptor;
    s32 clamped_x;
    s32 tmpx;
    s32 state4_v0;
    s32 state4_a1;
    s32 high_v0;
    register s32 abs_v1;
    s32 state6_v0;
    s32 state6_v1;
    s32 orbit_ticks;
    u16 approach_ticks;
    u16 high_phase_ticks;
    u16 return_ticks;
    u16 phase_before_increment;
    u16 sequence_flags;
    u16 primitive_flags;
    void *floor_height_or_spawned_object;
    void *sequence;
    void *spawned_primitive;
    void *primitive = in2;
    s32 *global_s7;
    s32 *global_s5;

    animation_descriptor = 0;
    sequence = NULL;
    raw_s1 = func_8025E01C(motion);
    global_s7 = D_8012F130;
    global_s5 = D_801328E8;
    floor_height_or_spawned_object = (void *)raw_s1;
    if (((S_8080C650_0 *)in0)->unk_68.s < 0xFF) {
        sequence = ((S_8080C650_0 *)in0)->unk_AC;
        if (((S_8080C650_1 *)sequence)->unk_36 == 0xFF) {
            ((S_8080C650_0 *)in0)->unk_68.s = 0xFF;
        }
        func_80245C10(motion);
    } else {
        func_80245C10(motion);
    }
    if (((S_8080C650_2 *)motion)->unk_08.at02.v >= ((s32)floor_height_or_spawned_object)) {
        ((S_8080C650_2 *)motion)->unk_08.at02.v = (s32)floor_height_or_spawned_object;
        func_8003EA54(primitive);
    } else {
        func_8003EA54(primitive);
    }
    phase = ((S_8080C650_0 *)in0)->unk_68.s;
    switch (phase) {
    case 0:
        ((S_8080C650_2 *)motion)->unk_00 = 0x03A00000;
        ((S_8080C650_2 *)motion)->unk_04 = 0x01E00000;
        ((S_8080C650_2 *)motion)->unk_08.at02.v = func_8025E01C(motion);
        ((S_8080C650_0 *)in0)->unk_6C = 0x40U;
        ((S_8080C650_0 *)in0)->unk_15 = 0;
        ((S_8080C650_0 *)in0)->unk_68.s = 1;
    case 1:
        if (((S_8080C650_3 *)primitive)->unk_14 & 0x6000) {
            ((S_8080C650_2 *)motion)->unk_10 = 0x80000;
            animation_descriptor = (s32)D_802892EC;
        }
        if (((S_8080C650_0 *)in0)->unk_A8 & 1) {
            orbit_ticks = ((S_8080C650_0 *)in0)->unk_6C - 1;
            ((S_8080C650_0 *)in0)->unk_6C = orbit_ticks;
            if ((s16) orbit_ticks >= 0) {
                ((S_8080C650_2 *)motion)->unk_00 = (s32) ((func_8006A3A4((s16) orbit_ticks << 7) << 7) + 0x03A00000);
            }
        }
        if (((S_8080C650_2 *)motion)->unk_04 > 0x0477FFFF) {
            ((S_8080C650_3 *)primitive)->unk_14 = (u16) (((S_8080C650_3 *)primitive)->unk_14 | 1);
            ((S_8080C650_2 *)motion)->unk_0C = 0x80000;
            animation_descriptor = (s32)D_80289334;
            ((S_8080C650_0 *)in0)->unk_68.s = 2;
        }
        if (animation_descriptor != 0) {
            func_80034A1C(primitive, animation_descriptor, 0);
        }
        return;
    case 2:
        if (((S_8080C650_3 *)primitive)->unk_14 & 0x6000) {
            animation_descriptor = (s32)D_802893C4;
        }
        if (((S_8080C650_2 *)motion)->unk_04 > 0x048FFFFF) {
            tmpx = 3;
            animation_descriptor = (s32)D_8028937C;
            ((S_8080C650_2 *)motion)->unk_10 = 0;
            ((S_8080C650_0 *)in0)->unk_68.s = tmpx;
        }
        break;
    case 3:
        if (((S_8080C650_3 *)primitive)->unk_14 & 0x6000) {
            animation_descriptor = (s32)D_802893C4;
        }
        if (((S_8080C650_2 *)motion)->unk_00 > 0x03DFFFFF) {
            ((S_8080C650_2 *)motion)->unk_14 = -0x100000;
            animation_descriptor = (s32)D_80289454;
            ((S_8080C650_0 *)in0)->unk_68.s = 4;
        }
        break;
    case 4:
        x_before_acceleration = ((S_8080C650_2 *)motion)->unk_00;
        state4_a1 = 0x48000;
        state4_v0 = ((S_8080C650_2 *)motion)->unk_14 + state4_a1;
        ((S_8080C650_2 *)motion)->unk_14 = state4_v0;
        if (x_before_acceleration > 0x041FFFFF) {
            ((S_8080C650_2 *)motion)->unk_14 = 0;
            ((S_8080C650_2 *)motion)->unk_0C = 0;
            ((S_8080C650_0 *)in0)->unk_15 = 1;
            ((S_8080C650_0 *)in0)->unk_68.s = 5;
        }
        break;
    case 5:
        if (global_s5[0] == (s32)D_802430A8) {
            ((S_8080C650_0 *)in0)->unk_6C = 7U;
            global_s5[0] = (s32)D_80243200;
            ((S_8080C650_0 *)in0)->unk_15 = 0;
            ((S_8080C650_0 *)in0)->unk_68.s = 6;
        }
        break;
    case 6:
        ((S_8080C650_2 *)motion)->unk_0C = (s32) ((s32) (D_80132AE8[0] - ((S_8080C650_2 *)motion)->unk_00) >> 1);
        ((S_8080C650_2 *)motion)->unk_10 = (s32) ((s32) (D_80132AEC[0] - ((S_8080C650_2 *)motion)->unk_04) >> 1);
        state6_v0 = D_80132AF0[0] + D_8029070C[0];
        state6_v1 = ((S_8080C650_2 *)motion)->unk_08.at00.v + 0x80000;
        state6_v0 -= state6_v1;
        ((S_8080C650_2 *)motion)->unk_14 = state6_v0 >> 1;
        func_80245C10(motion);
        global_s5[0] = (s32)D_80243200;
        approach_ticks = ((S_8080C650_0 *)in0)->unk_6C - 1;
        ((S_8080C650_0 *)in0)->unk_6C = approach_ticks;
        if ((approach_ticks << 0x10) <= 0) {
            global_s5[0] = (s32)D_80243200;
            ((S_8080C650_2 *)motion)->unk_14 = 0;
            ((S_8080C650_2 *)motion)->unk_10 = 0;
            ((S_8080C650_2 *)motion)->unk_0C = 0;
            ((S_8080C650_0 *)in0)->unk_68.s = 7;
        }
        break;
    case 7:
    case 8:
    case 9:
        ((S_8080C650_2 *)motion)->unk_00 = (s32) D_80132AE8[0];
        ((S_8080C650_2 *)motion)->unk_04 = (s32) D_80132AEC[0];
        ((S_8080C650_2 *)motion)->unk_08.at00.v = (s32) (D_80132AF0[0] + D_8029070C[0] + 0xFFF80000);
        global_s7 += 4;
        if (*global_s7 & 0x20) {
            if (D_80132AF2[0] == 0) {
                if (((S_8080C650_0 *)in0)->unk_68.s == 9) {
                    tmpx = 0x100000;
                    animation_descriptor = (s32)D_8028950C;
                    ((S_8080C650_1 *)sequence)->unk_00 = tmpx;
                } else {
                    global_s5[0] = (s32)D_802434B0;
                    ((S_8080C650_2 *)motion)->unk_14 = 0x100000;
                }
            } else {
                global_s5[0] = (s32)D_80243200;
            }
            if (((S_8080C650_0 *)in0)->unk_68.s == 9) {
                func_80058F88(0x700);
            }
            ((S_8080C650_1 *)sequence)->unk_2A = (u16)(((S_8080C650_1 *)sequence)->unk_2A & ~4);
            phase_before_increment = ((S_8080C650_0 *)in0)->unk_68.u;
            ((S_8080C650_0 *)in0)->unk_68.s = (s16) (phase_before_increment + 1);
        }
        break;
    case 10:
        velocity_component = (s32) (((s32) ((S_8080C650_1 *)sequence)->unk_00
            >> 0xC) * func_8006A3A4(((S_8080C650_1 *)sequence)->unk_2C));
        ((S_8080C650_2 *)motion)->unk_0C = velocity_component;
        velocity_component = ((s32) (0 - ((S_8080C650_1 *)sequence)->unk_00)
            >> 0xC) * func_8006A470(((S_8080C650_1 *)sequence)->unk_2C);
        ((S_8080C650_2 *)motion)->unk_10 = velocity_component;
        if (velocity_component > -0x40000) {
            ((S_8080C650_2 *)motion)->unk_10 = -0x40000;
        }
        ((S_8080C650_1 *)sequence)->unk_2C = (s16) ((u16) ((S_8080C650_1 *)sequence)->unk_2C
            - ((s32) (((S_8080C650_1 *)sequence)->unk_2E << 0x10) >> 0x14));
        if (((S_8080C650_2 *)motion)->unk_08.at00.v > 0) {
            sequence_flags = ((S_8080C650_1 *)sequence)->unk_2A;
            if (!(sequence_flags & 4)) {
                ((S_8080C650_1 *)sequence)->unk_2A = (u16) (sequence_flags | 4);
                func_80058F88(0x701);
            }
            x_before_clamp = ((S_8080C650_2 *)motion)->unk_00;
            ((S_8080C650_2 *)motion)->unk_08.at00.v = 0x200000;
            if (x_before_clamp <= 0x041FFFFF) {
                if (x_before_clamp > 0x03BFFFFF) {
                    clamped_x = 0x03B80000;
                    ((S_8080C650_2 *)motion)->unk_00 = clamped_x;
                } else if (x_before_clamp <= 0x03800000) {
                    ((S_8080C650_2 *)motion)->unk_00 = 0x03880000;
                }
            } else if (x_before_clamp > 0x04BFFFFF) {
                clamped_x = 0x04B80000;
                ((S_8080C650_2 *)motion)->unk_00 = clamped_x;
            } else if (x_before_clamp <= 0x04800000) {
                clamped_x = 0x04880000;
                ((S_8080C650_2 *)motion)->unk_00 = clamped_x;
            }
            ((S_8080C650_1 *)sequence)->unk_2C = (s16) ((s32) (0 - ((S_8080C650_1 *)sequence)->unk_2C) >> 1);
        }
        if (((S_8080C650_2 *)motion)->unk_04 <= 0x01E00000) {
            func_80058F88(0x1700);
            func_80058F88(0x1701);
            if (D_80530658[((S_8080C650_1 *)sequence)->unk_34] == 8) {
                loop_index = 1;
                global_s5 = (s32 *)0x1000;
                ((S_8080C650_0 *)in0)->unk_A8 = (s32) (((S_8080C650_0 *)in0)->unk_A8 | 1);
                {
                    do {
                        floor_height_or_spawned_object = func_800374FC(0x136, D_801328C8);
                        if (floor_height_or_spawned_object != NULL) {
                            spawned_primitive = ((S_8080C650_4 *)floor_height_or_spawned_object)->unk_0C;
                            func_8003BC18(floor_height_or_spawned_object, D_8003C558);
                            ((S_8080C650_1 *)spawned_primitive)->unk_0C = 0x808080;
                            ((S_8080C650_1 *)spawned_primitive)->unk_1E = (s16)(s32)global_s5;
                            ((S_8080C650_1 *)spawned_primitive)->unk_1C = (s16)(s32)global_s5;
                            ((S_8080C650_4 *)floor_height_or_spawned_object)->unk_22 = 0x78;
                            ((S_8080C650_4 *)floor_height_or_spawned_object)->unk_24 = motion;
                            ((S_8080C650_4 *)floor_height_or_spawned_object)->unk_10 = (s32)D_80529080;
                            func_80034A1C(spawned_primitive, D_8028954C, (s16)(loop_index * 4));
                        }
                    } while (--loop_index >= 0);
                }
            } else {
                ((S_8080C650_0 *)in0)->unk_A8 = (s32) (((S_8080C650_0 *)in0)->unk_A8 & ~1);
            }
            animation_descriptor = (s32)D_802894AC;
            ((S_8080C650_2 *)motion)->unk_14 = 0;
            ((S_8080C650_2 *)motion)->unk_10 = 0;
            ((S_8080C650_2 *)motion)->unk_0C = 0;
            ((S_8080C650_0 *)in0)->unk_6C = 0x14U;
            ((S_8080C650_0 *)in0)->unk_68.s = 0xB;
        }
        break;
    case 11:
        primitive_flags = ((S_8080C650_3 *)primitive)->unk_14;
        if ((primitive_flags & 0x6000) && ((s16) ((S_8080C650_0 *)in0)->unk_6C > 0)) {
            animation_descriptor = (s32)D_802892EC;
            ((S_8080C650_3 *)primitive)->unk_14 = (u16) (primitive_flags | 0x800);
        }
        current_x = ((S_8080C650_2 *)motion)->unk_00;
        x_limit_flags_or_phase = 0x03A00000;
        if (current_x > x_limit_flags_or_phase) {
            x_limit_flags_or_phase = ((S_8080C650_3 *)primitive)->unk_14 & 0xFFFE;
        } else {
            x_limit_flags_or_phase = ((S_8080C650_3 *)primitive)->unk_14 | 1;
        }
        ((S_8080C650_3 *)primitive)->unk_14 = (u16)x_limit_flags_or_phase;
        current_y = ((S_8080C650_2 *)motion)->unk_04;
        ((S_8080C650_2 *)motion)->unk_04 = (s32) (((s32) (0x01E00000 - current_y) >> 1) + current_y);
        return_ticks = ((S_8080C650_0 *)in0)->unk_6C - 1;
        ((S_8080C650_0 *)in0)->unk_6C = return_ticks;
        if ((return_ticks << 0x10) == 0) {
            ((S_8080C650_3 *)primitive)->unk_14 = (u16) (((S_8080C650_3 *)primitive)->unk_14 & 0xF7FF);
            current_x = ((S_8080C650_2 *)motion)->unk_00;
            if (current_x > 0x03A80000) {
                ((S_8080C650_2 *)motion)->unk_0C = -0x80000;
            } else if (current_x <= 0x0397FFFF) {
                ((S_8080C650_2 *)motion)->unk_0C = 0x80000;
            } else {
                animation_descriptor = (s32)D_8028937C;
                ((S_8080C650_2 *)motion)->unk_0C = 0;
                ((S_8080C650_2 *)motion)->unk_00 = 0x03A00000;
            }
        }
        if ((u32) (((S_8080C650_2 *)motion)->unk_00 + 0xFC440000) <= 0xC80000U) {
            ((S_8080C650_2 *)motion)->unk_08.at00.v = 0;
        } else {
            ((S_8080C650_2 *)motion)->unk_08.at00.v = 0x200000;
        }
        abs_v1 = 0xFC600000;
        delta = ((S_8080C650_2 *)motion)->unk_00 + abs_v1;
        if ((abs(delta)) <= 0x80000) {
            if (((s32) (s16) ((S_8080C650_0 *)in0)->unk_6C) < 0) {
                ((S_8080C650_1 *)sequence)->unk_2A = (u16) (((S_8080C650_1 *)sequence)->unk_2A | 2);
                ((S_8080C650_2 *)motion)->unk_14 = 0;
                ((S_8080C650_2 *)motion)->unk_10 = 0;
                ((S_8080C650_2 *)motion)->unk_0C = 0;
                ((S_8080C650_0 *)in0)->unk_68.s = 0;
                break;
            }
        }
        break;
    case 0xFF:
        count_sum_or_color = 0;
        loop_index = 7;
        count_cursor = &D_80530658[7];
        do {
            slot_count = *count_cursor;
            count_cursor -= 1;
            loop_index -= 1;
            count_sum_or_color += slot_count;
        } while (loop_index >= 0);
        if ((D_800133A0[0] < count_sum_or_color) || (count_sum_or_color == 0x40)) {
            D_800133A0_store[0] = count_sum_or_color;
            func_80050BFC(0x5DA);
        } else {
            func_80050BD8(0x5DA);
        }
        animation_descriptor = (s32)D_802892EC;
        ((S_8080C650_2 *)motion)->unk_10 = 0x80000;
        ((S_8080C650_0 *)in0)->unk_6C = 0x1EU;
        ((S_8080C650_0 *)in0)->unk_68.s = (s16) ((u16) ((S_8080C650_0 *)in0)->unk_68.s + 1);
    case 0x100:
    case 0x102:
        high_phase_ticks = ((S_8080C650_0 *)in0)->unk_6C - 1;
        ((S_8080C650_0 *)in0)->unk_6C = high_phase_ticks;
        if ((high_phase_ticks << 0x10) <= 0) {
            ((S_8080C650_2 *)motion)->unk_10 = 0;
            ((S_8080C650_2 *)motion)->unk_14 = -0x100000;
            phase_before_increment = ((S_8080C650_0 *)in0)->unk_68.u;
            ((S_8080C650_0 *)in0)->unk_68.s = (s16) (phase_before_increment + 1);
        }
        break;
    case 0x101:
    case 0x103:
        high_v0 = ((S_8080C650_2 *)motion)->unk_14 + 0x20000;
        ((S_8080C650_2 *)motion)->unk_14 = high_v0;
        if (((S_8080C650_2 *)motion)->unk_08.at00.v > 0x1FFFFF) {
            ((S_8080C650_2 *)motion)->unk_08.at00.v = 0x200000;
            ((S_8080C650_2 *)motion)->unk_14 = 0;
            phase_before_increment = ((S_8080C650_0 *)in0)->unk_68.u;
            ((S_8080C650_0 *)in0)->unk_68.s = (s16) (phase_before_increment + 1);
        }
        break;
    case 0x104:
        animation_descriptor = (s32)D_80289334;
        raw_s1 = phase + 1;
        ((S_8080C650_0 *)in0)->unk_68.s = raw_s1;
        break;
    case 0x105:
        animation_descriptor = (s32)D_8028937C;
        raw_s1 = phase + 1;
        ((S_8080C650_0 *)in0)->unk_68.s = raw_s1;
        break;
    case 0x106:
        animation_descriptor = (s32)D_802893C4;
        raw_s1 = phase + 1;
        ((S_8080C650_0 *)in0)->unk_68.s = raw_s1;
        break;
    case 0x107:
        count_sum_or_color = 0xC0C0C0;
        ((S_8080C650_2 *)motion)->unk_10 = -0x80000;
        primitive_flags = ((S_8080C650_3 *)primitive)->unk_14;
        ((S_8080C650_3 *)primitive)->unk_10 = 0x60;
        ((S_8080C650_3 *)primitive)->unk_0C.s32 = count_sum_or_color;
        primitive_flags |= 0xC;
        ((S_8080C650_3 *)primitive)->unk_14 = primitive_flags;
        x_limit_flags_or_phase = (u16) ((S_8080C650_0 *)in0)->unk_68.u;
        animation_descriptor = (s32)D_8028940C;
        x_limit_flags_or_phase += 1;
        ((S_8080C650_0 *)in0)->unk_68.s = (s16) x_limit_flags_or_phase;
        break;
    case 0x108:
        ((S_8080C650_3 *)primitive)->unk_0C.s32 = (s32) (((S_8080C650_3 *)primitive)->unk_0C.s32 + 0xFFF7F7F8);
        if (((S_8080C650_3 *)primitive)->unk_0C.u8 < 0x11U) {
            phase_before_increment = ((S_8080C650_0 *)in0)->unk_68.u;
            ((S_8080C650_0 *)in0)->unk_68.s = (s16) (phase_before_increment + 1);
        }
        break;
    case 0x109:
        func_8023FB18(in0);
        (*(u16 *)((u8 *)in0 + -2)) = (u16) (((S_8080C650_0_pre *)in0)[-1].unk_00 | 0x8000);
        D_80084D5C |= 0x8000;
        return;
    }
    if (animation_descriptor != 0) {
        func_80034A1C(primitive, animation_descriptor, 0);
    }
}
