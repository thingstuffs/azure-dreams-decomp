#include "common.h"
#include "m2c_compat.h"

s32 func_80052374();                             /* extern */
M2C_UNK func_80058F88();        /* extern */
s32 func_8006A3A4();                             /* extern */
s32 func_8006A470();                             /* extern */
M2C_UNK func_802441A4();                       /* extern */
M2C_UNK func_80244588();                  /* extern */
M2C_UNK func_802445FC();                     /* extern */
M2C_UNK func_80244660();                     /* extern */
M2C_UNK func_8025E01C();                     /* extern */
M2C_UNK func_80526BFC();              /* extern */
M2C_UNK func_80526D34();                      /* extern */
M2C_UNK func_80526E4C(); /* extern */
M2C_UNK func_80528998();                      /* extern */
extern s32 D_80084D5C;
extern u8 D_80095AA0[8];
extern u8 D_801328E8[0x14];
extern u8 D_80132AE8[0x18];
extern u16 D_80530658[];
extern u16 D_805306C8[];
M2C_UNK func_802483B8();                      /* extern */
M2C_UNK func_80529134();                      /* extern */
M2C_UNK func_80290318();                      /* extern */
M2C_UNK func_80528950();                      /* extern */
M2C_UNK func_80528910();                      /* extern */
M2C_UNK func_80526B18();                      /* extern */
M2C_UNK func_80243A38();                      
typedef struct S_80527D5C_0_pre {
    u16 unk_00;
} S_80527D5C_0_pre;   /* the 0x2 bytes before arg0 in func_80527D5C, addressed as arg0[-1] */

typedef struct S_80527D5C_0 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x20];
    u16 unk_28;
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    union { u16 u; s16 s; } unk_2C;   /* accessed as both */
    union { u16 u; s16 s; } unk_2E;   /* accessed as both */
    u16 unk_30;
    u16 unk_32;
    s16 unk_34;
    union { s16 s; u16 u; } unk_36;   /* accessed as both */
} S_80527D5C_0;   /* arg0 in func_80527D5C */

typedef struct S_80527D5C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x7C];
    s16 unk_88;
} S_80527D5C_1;   /* temp_a0 in func_80527D5C */

typedef struct S_80527D5C_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80527D5C_2;   /* &D_80132AE8 in func_80527D5C */

typedef struct S_80527D5C_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
} S_80527D5C_3;   /* &D_801328E8 in func_80527D5C */

typedef struct S_80527D5C_4 {
    u8 pad_00[0x68];
    s16 unk_68;
} S_80527D5C_4;   /* temp_s4 in func_80527D5C */

typedef struct S_80527D5C_5 {
    u16 unk_00;
    u16 unk_02;
    s16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x2];
    s32 unk_10;
    s32 unk_14;
} S_80527D5C_5;   /* second in func_80527D5C */

typedef struct S_80527D5C_6 {
    s16 unk_00;
    u8 pad_02[0x2];
    s32 unk_04;
    s32 unk_08;
    void * unk_0C;
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    u16 unk_1C;
} S_80527D5C_6;   /* first in func_80527D5C */

typedef struct S_80527D5C_7 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80527D5C_7;   /* state8_item_addr in func_80527D5C */

typedef struct S_80527D5C_8 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x1C];
    u16 unk_28;
} S_80527D5C_8;   /* temp_a1 in func_80527D5C */

typedef struct S_80527D5C_9 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_80527D5C_9;   /* (void *) var_a0 in func_80527D5C */

typedef struct S_80527D5C_10 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_80527D5C_10;   /* temp_s2 in func_80527D5C */

typedef struct S_80527D5C_11 {
    u16 unk_00;
} S_80527D5C_11;   /* temp_v1_2 in func_80527D5C */

/* extern */

/* Advances the animation and item collection sequence and clamps its position. */
void func_80527D5C(void *sequence) {
    u8 record_params[0x30];
    u8 line_params[0x28];
    M2C_UNK coord_or_sound;
    s16 next_round;
    s16 state;
    s32 speed_magnitude;
    s32 angle_magnitude;
    u16 center_y;
    s32 angle;
    s32 orbit_offset;
    s32 cosine;
    s32 count_addr;
    s32 height_or_index;
    s32 coord_delta;
    void *owner;
    u16 item_flags;
    u16 start_ticks;
    u16 move_ticks;
    u16 finish_ticks;
    u16 round_ticks;
    u16 round_flags;
    u16 start_x;
    u16 start_y;
    u16 finish_flags;
    void *item;
    void *position;
    u16 *position_x;
    void *render_or_counts;
    void *phase_data;
    s32 direction_flags;
    s32 saved_flags;
    s32 record_color;
    s32 round_index;
    s32 record_addr;
    s32 round_count_addr;
    u16 next_state;
    s32 eased_y;
    s32 item_slot;

    owner = ((S_80527D5C_0 *)sequence)->unk_04;
    state = ((S_80527D5C_0 *)sequence)->unk_36.s;
    position = ((S_80527D5C_1 *)owner)->unk_08;
    render_or_counts = D_801328E8;
    phase_data = (u8 *) owner + 0x20;
    if (state == 6) {
        goto block_state6;
    }
    if (state < 7) {
        if (state == 2) {
            goto block_state2;
        }
        if (state < 3) {
            if (state == 0) {
                goto block_state0;
            }
            if (state == 1) {
                goto block_state1;
            }
            goto clamp_position;
        }
        if (state == 4) {
            goto block_state4;
        }
        if (state >= 5) {
            goto block_state5;
        }
        goto block_state3;
    }
    if (state == 9) {
        goto block_state9;
    }
    if (state < 0xA) {
        if (state == 7) {
            goto block_state7;
        }
        if (state == 8) {
            goto block_state8;
        }
        goto clamp_position;
    }
    if (state == 0xFF) {
        goto block_state255;
    }
    if (state < 0x100) {
        if (state == 0xA) {
            goto block_state10;
        }
        goto clamp_position;
    }
    if (state != 0x100) {
        goto clamp_position;
    }
    goto block_state256;

block_state0:
    start_x = ((S_80527D5C_2 *)(&D_80132AE8))->unk_00.at02.v;
    ((S_80527D5C_0 *)sequence)->unk_30 = start_x;
    start_y = ((S_80527D5C_2 *)(&D_80132AE8))->unk_04.at02.v;
    ((S_80527D5C_0 *)sequence)->unk_28 = 4U;
    ((S_80527D5C_0 *)sequence)->unk_36.s = 1;
    ((S_80527D5C_0 *)sequence)->unk_32 = start_y;
    ((S_80527D5C_2 *)(&D_80132AE8))->unk_14 = 0xFFE00000;
    ((S_80527D5C_2 *)(&D_80132AE8))->unk_10 = -0x200000;
    ((S_80527D5C_2 *)(&D_80132AE8))->unk_0C = -0x200000;
    (*(s32 *)((u8 *)render_or_counts + (0))) = (s32) &func_802483B8;
    ((S_80527D5C_3 *)(&D_801328E8))->unk_04 = (s32) &func_80529134;

block_state1:
    (*(u16 *)((u8 *)render_or_counts + (0x10))) = (u16) (((*(u16 *)((u8 *)render_or_counts + (0x10))) + 0x200) & 0xFFF);
    start_ticks = ((S_80527D5C_0 *)sequence)->unk_28 - 1;
    ((S_80527D5C_0 *)sequence)->unk_28 = start_ticks;
    if ((start_ticks << 0x10) <= 0) {
        ((S_80527D5C_0 *)sequence)->unk_28 = 0x10U;
        ((S_80527D5C_0 *)sequence)->unk_36.s = 2;
        ((S_80527D5C_2 *)(&D_80132AE8))->unk_0C = (s32) ((0x420 - (s16) ((S_80527D5C_0 *)sequence)->unk_30) << 0x10) / (s16) ((S_80527D5C_0 *)sequence)->unk_28;
        ((S_80527D5C_2 *)(&D_80132AE8))->unk_10 = (s32) ((0x460 - (s16) ((S_80527D5C_0 *)sequence)->unk_32) << 0x10) / (s16) ((S_80527D5C_0 *)sequence)->unk_28;
        ((S_80527D5C_2 *)(&D_80132AE8))->unk_14 = 0xFFF40000;
        goto clamp_position;
    }
    goto clamp_position;

block_state2:
    position_x = (u16 *)((s8 *)&D_80132AE8 + 2);
    ((S_80527D5C_3 *)(&D_801328E8))->unk_10.s = ((u16) ((S_80527D5C_3 *)(&D_801328E8))->unk_10.s + 0x200) & 0xFFF;
    if ((s16) *position_x < 0x420) {
        *position_x = 0x420;
    }
    move_ticks = ((S_80527D5C_0 *)sequence)->unk_28 - 1;
    ((S_80527D5C_0 *)sequence)->unk_28 = move_ticks;
    if ((move_ticks << 0x10) <= 0) {
        ((S_80527D5C_2 *)(&D_80132AE8))->unk_10 = 0;
        ((S_80527D5C_2 *)(&D_80132AE8))->unk_0C = 0;
        ((S_80527D5C_0 *)sequence)->unk_36.s = 3;
        goto clamp_position;
    }
    goto clamp_position;

block_state3:
    {
        s32 *position_y = (s32 *)((s8 *)&D_80132AE8 + 4);
        s32 current_y = *position_y;

        if (current_y <= 0x44FFFFF) {
            eased_y = ((0x4500000 - current_y) >> 1) + current_y;
            *position_y = eased_y;
        }
        current_y = *position_y;
        if (current_y > 0x4700000) {
            eased_y = ((0x4700000 - current_y) >> 1) + current_y;
            *position_y = eased_y;
        }
        position = position_y - 1;
        (*(u16 *)((u8 *)render_or_counts + (0x10))) =
            (u16) (((*(u16 *)((u8 *)render_or_counts + (0x10))) + 0x200) & 0xFFF);
        height_or_index = (s16) func_8025E01C(position);
        if (((S_80527D5C_2 *)(&D_80132AE8))->unk_0A < height_or_index) {
            goto clamp_position;
        }
        if ((*(s16 *)((u8 *)render_or_counts + (0x10))) != 0x800) {
            goto clamp_position;
        }
        ((S_80527D5C_0 *)sequence)->unk_36.s = 4;
        func_80526D34(sequence);
        func_80244660(render_or_counts, position, D_80095AA0);
        goto clamp_position;
    }

block_state4:
    if (((S_80527D5C_1 *)owner)->unk_88 == 7) {
        ((S_80527D5C_0 *)sequence)->unk_36.s = 5;
        goto clamp_position;
    }
    goto clamp_position;

block_state5:
    angle = ((S_80527D5C_3 *)(&D_801328E8))->unk_10.s;
    if (angle >= 0x801) {
        ((S_80527D5C_3 *)(&D_801328E8))->unk_10.u =
            ((S_80527D5C_3 *)(&D_801328E8))->unk_10.u - 0x200;
    } else if (angle < 0x800) {
        ((S_80527D5C_3 *)(&D_801328E8))->unk_10.u =
            ((S_80527D5C_3 *)(&D_801328E8))->unk_10.u + 0x200;
    }
    if ((func_80052374(angle) == 0) && (((S_80527D5C_4 *)phase_data)->unk_68 == 8)) {
        (*(u16 *)((u8 *)render_or_counts + (0x10))) = 0x800U;
        func_80244588();
        func_802445FC((s32) &func_80290318);
        ((S_80527D5C_0 *)sequence)->unk_30 = (u16) ((S_80527D5C_2 *)(&D_80132AE8))->unk_00.at02.v;
        center_y = (u16) ((S_80527D5C_2 *)(&D_80132AE8))->unk_04.at02.v;
        ((S_80527D5C_0 *)sequence)->unk_2C.u = 0U;
        ((S_80527D5C_0 *)sequence)->unk_2A.u = (u16) (((S_80527D5C_0 *)sequence)->unk_2A.u & 0x7FFF);
        ((S_80527D5C_0 *)sequence)->unk_36.s = 6;
        ((S_80527D5C_0 *)sequence)->unk_32 = center_y;
        goto clamp_position;
    }
    goto clamp_position;

block_state6:
    if ((s16) ((S_80527D5C_0 *)sequence)->unk_2A.u & 0x8000) {
        ((S_80527D5C_0 *)sequence)->unk_2C.u -= 0x20;
    } else {
        ((S_80527D5C_0 *)sequence)->unk_2C.u += 0x20;
    }
    angle_magnitude = ((S_80527D5C_0 *)sequence)->unk_2C.s;
    if (angle_magnitude < 0) {
        angle_magnitude = 0 - angle_magnitude;
    }
    if (angle_magnitude >= 0x200) {
        direction_flags = ((S_80527D5C_0 *)sequence)->unk_2A.s;
        saved_flags = direction_flags;
        direction_flags &= 0x8000;
        if (direction_flags) {
            direction_flags = saved_flags & 0x7FFF;
        } else {
            direction_flags = saved_flags | 0x8000;
        }
        ((S_80527D5C_0 *)sequence)->unk_2A.u = direction_flags;
    }
    ((S_80527D5C_5 *)line_params)->unk_0C = 0;
    ((S_80527D5C_5 *)line_params)->unk_04 = 0;
    ((S_80527D5C_5 *)line_params)->unk_00 = ((S_80527D5C_0 *)sequence)->unk_30;
    ((S_80527D5C_5 *)line_params)->unk_02 = ((S_80527D5C_0 *)sequence)->unk_32;
    orbit_offset = func_8006A3A4((s16) ((S_80527D5C_0 *)sequence)->unk_2C.u) / 24;
    ((S_80527D5C_5 *)line_params)->unk_08 = ((S_80527D5C_0 *)sequence)->unk_30 + orbit_offset;
    cosine = func_8006A470((s16) ((S_80527D5C_0 *)sequence)->unk_2C.u);
    orbit_offset = cosine / 24;
    ((S_80527D5C_5 *)line_params)->unk_14 = 0x202020;
    ((S_80527D5C_5 *)line_params)->unk_10 = 0x202020;
    ((S_80527D5C_5 *)line_params)->unk_0A = ((S_80527D5C_0 *)sequence)->unk_32 - orbit_offset;
    if (((S_80527D5C_4 *)phase_data)->unk_68 == 9) {
        func_80244588();
        func_802445FC((s32) &func_80290318);
        func_80526E4C((s32) &func_80528950, line_params, line_params + 0x10, sequence);
        ((S_80527D5C_0 *)sequence)->unk_28 = 0x200U;
        ((S_80527D5C_0 *)sequence)->unk_2E.u = 0U;
        ((S_80527D5C_0 *)sequence)->unk_36.s = 7;
        ((S_80527D5C_0 *)sequence)->unk_2A.u &= 0x7FFF;
        goto clamp_position;
    }
    func_80526E4C((s32) &func_80528910, line_params, line_params + 0x10, sequence);
    goto clamp_position;

block_state7:
    if ((s16) ((S_80527D5C_0 *)sequence)->unk_2A.u & 0x8000) {
        ((S_80527D5C_0 *)sequence)->unk_2E.u -= 4;
    } else {
        ((S_80527D5C_0 *)sequence)->unk_2E.u += 4;
    }
    speed_magnitude = ((S_80527D5C_0 *)sequence)->unk_2E.s;
    if (speed_magnitude < 0) {
        speed_magnitude = 0 - speed_magnitude;
    }
    if (speed_magnitude >= 0x100) {
        direction_flags = ((S_80527D5C_0 *)sequence)->unk_2A.s;
        saved_flags = direction_flags;
        direction_flags &= 0x8000;
        if (direction_flags) {
            direction_flags = saved_flags & 0x7FFF;
        } else {
            direction_flags = saved_flags | 0x8000;
        }
        ((S_80527D5C_0 *)sequence)->unk_2A.u = direction_flags;
    }
    ((S_80527D5C_0 *)sequence)->unk_28 = (u16) ((((S_80527D5C_0 *)sequence)->unk_28 + ((S_80527D5C_0 *)sequence)->unk_2E.u + 0x1000) & 0xFFF);
    func_80528998(sequence);
    if (((S_80527D5C_4 *)phase_data)->unk_68 == 0xA) {
        func_802441A4();
        record_color = 0x808080;
        (*(s32 *)((u8 *)render_or_counts + (0))) = (s32) &func_80243A38;
        round_index = ((S_80527D5C_0 *)sequence)->unk_34;
        ((S_80527D5C_6 *)record_params)->unk_16 = 0xB6;
        ((S_80527D5C_6 *)record_params)->unk_18 = 3;
        ((S_80527D5C_6 *)record_params)->unk_10 = record_color;
        ((S_80527D5C_6 *)record_params)->unk_1A = 0x7C80;
        ((S_80527D5C_6 *)record_params)->unk_14 = (round_index * 0x10) + 0x64;
        ((S_80527D5C_6 *)record_params)->unk_1C &= 0xFFFE;
        record_addr = ((S_80527D5C_0 *)sequence)->unk_34 * 2;
        record_addr += (s32) D_805306C8;
        ((S_80527D5C_6 *)record_params)->unk_04 = record_addr;
        round_count_addr = ((S_80527D5C_0 *)sequence)->unk_34 * 2;
        ((S_80527D5C_6 *)record_params)->unk_00 = 0;
        ((S_80527D5C_6 *)record_params)->unk_0C = sequence;
        round_count_addr += (s32) D_80530658;
        ((S_80527D5C_6 *)record_params)->unk_08 = round_count_addr;
        func_80526BFC((s32) &func_80526B18, record_params);
        ((S_80527D5C_0 *)sequence)->unk_36.s = 8;
        goto clamp_position;
    }
    goto clamp_position;

block_state8:
    render_or_counts = D_80530658;
    for (height_or_index = 7; height_or_index >= 0; height_or_index--) {
        item_slot = (height_or_index << 2) + (s32) sequence;
        item = ((S_80527D5C_7 *)item_slot)->unk_08;
        item_flags = ((S_80527D5C_8 *)item)->unk_28;
        {
            coord_or_sound = (s32) ((S_80527D5C_8 *)item)->unk_08;
            if (!(item_flags & 3)) {
                s32 distance_x;
                s32 delta_x;

                delta_x = ((S_80527D5C_9 *)((void *) coord_or_sound))->unk_02;
                coord_delta = ((S_80527D5C_10 *)position)->unk_02;
                delta_x -= coord_delta;
                coord_delta = ((S_80527D5C_9 *)((void *) coord_or_sound))->unk_06;
                coord_or_sound = ((S_80527D5C_10 *)position)->unk_06;
                distance_x = __builtin_abs(delta_x);
                coord_delta -= coord_or_sound;
                if (coord_delta < 0) {
                    coord_delta = -coord_delta;
                }
                if ((distance_x + coord_delta) < 0x20) {
                    ((S_80527D5C_8 *)item)->unk_28 = (u16) (item_flags | 1);
                    count_addr = ((S_80527D5C_0 *)sequence)->unk_34 * 2;
                    count_addr += (s32) render_or_counts;
                    ((S_80527D5C_11 *)count_addr)->unk_00 = (u16) (((S_80527D5C_11 *)count_addr)->unk_00 + 1);
                    coord_or_sound = 0x703;
                    if ((*(s16 *)((u8 *)render_or_counts + ((((S_80527D5C_0 *)sequence)->unk_34 * 2)))) < 7) {
                        coord_or_sound = 0x702;
                    }
                    func_80058F88(coord_or_sound, item, item_flags);
                }
            }
        }
    }
    if (((S_80527D5C_4 *)phase_data)->unk_68 == 0xB) {
        ((S_80527D5C_0 *)sequence)->unk_28 = 0x1EU;
        ((S_80527D5C_0 *)sequence)->unk_36.s = 9;
        goto clamp_position;
    }
    goto clamp_position;

block_state9:
    round_ticks = ((S_80527D5C_0 *)sequence)->unk_28 - 1;
    ((S_80527D5C_0 *)sequence)->unk_28 = round_ticks;
    if ((round_ticks << 0x10) <= 0) {
        ((S_80527D5C_0 *)sequence)->unk_36.s = 0xA;
        goto clamp_position;
    }
    goto clamp_position;

block_state10:
    round_flags = ((S_80527D5C_0 *)sequence)->unk_2A.u;
    if (round_flags & 2) {
        ((S_80527D5C_0 *)sequence)->unk_2A.u = (u16) (round_flags & 0xFFFD);
        func_802441A4();
        next_round = (u16) ((S_80527D5C_0 *)sequence)->unk_34 + 1;
        ((S_80527D5C_0 *)sequence)->unk_34 = next_round;
        if (next_round == 8) {
            ((S_80527D5C_0 *)sequence)->unk_28 = 0x1EU;
            ((S_80527D5C_0 *)sequence)->unk_36.s = 0xFF;
            goto clamp_position;
        }
        func_80526D34(sequence);
        ((S_80527D5C_0 *)sequence)->unk_36.s = 4;
        goto clamp_position;
    }
    goto clamp_position;

block_state255:
    finish_ticks = ((S_80527D5C_0 *)sequence)->unk_28 - 1;
    ((S_80527D5C_0 *)sequence)->unk_28 = finish_ticks;
    if ((finish_ticks << 0x10) <= 0) {
        next_state = ((S_80527D5C_0 *)sequence)->unk_36.u;
        finish_flags = ((S_80527D5C_0 *)sequence)->unk_2A.u;
        next_state++;
        finish_flags |= 1;
        ((S_80527D5C_0 *)sequence)->unk_2A.u = finish_flags;
        ((S_80527D5C_0 *)sequence)->unk_36.u = next_state;
        goto clamp_position;
    }
    goto clamp_position;

block_state256:
    (*(u16 *)((u8 *)sequence + (-2))) = (u16) (((S_80527D5C_0_pre *)sequence)[-1].unk_00 | 0x8000);
    D_80084D5C |= 0x8000;
    goto clamp_position;

clamp_position:
    if (((S_80527D5C_0 *)sequence)->unk_36.s >= 4) {
        if (((S_80527D5C_2 *)(&D_80132AE8))->unk_00.at00.v <= 0x03CFFFFF) {
            ((S_80527D5C_2 *)(&D_80132AE8))->unk_00.at00.v = 0x03D00000;
        }
        if ((*(s32 *)((u8 *)(&D_80132AE8) + (4))) <= 0x044FFFFF) {
            ((S_80527D5C_2 *)(&D_80132AE8))->unk_04.at00.v = 0x04500000;
        }
        if (((S_80527D5C_2 *)(&D_80132AE8))->unk_00.at00.v > 0x04700000) {
            ((S_80527D5C_2 *)(&D_80132AE8))->unk_00.at00.v = 0x04700000;
        }
        if ((*(s32 *)((u8 *)(&D_80132AE8) + (4))) > 0x04700000) {
            ((S_80527D5C_2 *)(&D_80132AE8))->unk_04.at00.v = 0x04700000;
        }
    }
    return;
}
