#include "common.h"
#include "m2c_compat.h"

extern void *D_8016A868[];
s32 func_800A45D8();
s32 func_800A7234();
M2C_UNK func_800A7A7C();
s16 func_800BCB04();
extern s32 D_800814A0;
extern u8 D_80174708;


typedef struct S_8016E528_0_pre {
    u16 unk_00;
} S_8016E528_0_pre;   /* the 0x2 bytes before arg0 in func_8016E528, addressed as arg0[-1] */

typedef struct S_8016E528_0 {
    u8 pad_00[0x12];
    s16 unk_12;
    s16 unk_14;
    u8 pad_16[0x2];
    s16 unk_18;
    u16 unk_1A;
    u8 pad_1C[0x28];
    u8 unk_44;
    u8 unk_45;
    u8 unk_46;
    u8 unk_47;
    s8 unk_48;
    s8 unk_49;
    u8 pad_4A[0x2];
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_8016E528_0;   /* arg0 in func_8016E528 */

typedef struct S_8016E528_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8016E528_1;   /* arg2 in func_8016E528 */

typedef struct S_8016E528_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; volatile u16 v; } at02u; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_8016E528_2;   /* arg1 in func_8016E528 */

typedef struct S_8016E528_3 {
    s16 unk_00;
    s16 unk_02;
} S_8016E528_3;   /* temp_a1 in func_8016E528 */

typedef struct S_8016E528_4 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_8016E528_4;   /* ((((S_8016E528_0 *)arg0)->unk_18 * 4) + table_base) in func_8016E528 */

/* Updates object motion, landing interpolation, and removal. */
void func_8016E528(void *motion, void *position, void *object) {
    static void *const distance_labels[] = { &&distance_zero, &&distance_one, &&distance_two, &&distance_three, &&distance_four };
    u8 item_data[4];
    s32 fall_height;
    s16 move_height;
    s32 world_x;
    s32 world_y;
    s32 y_distance;
    s32 settle_ticks;
    s32 x_distance;
    s32 next_tile;
    s32 tile_y;
    s32 target_y;
    u16 delay_ticks;
    s16 ticks_left;
    u16 scale;
    u16 probe_height;
    u32 tile_distance;
    void *direction_step;
    u8 *direction_table;

    if (((S_8016E528_0 *)motion)->unk_12 != 3) {
        goto check_settling;
    }
    delay_ticks = ((S_8016E528_0 *)motion)->unk_1A;
    ((S_8016E528_0 *)motion)->unk_1A = (u16) (delay_ticks + 1);
    if ((s16) delay_ticks < 0x38) {
        goto repeat_settling;
    }
    ((S_8016E528_0 *)motion)->unk_12 = 0;
    ((S_8016E528_1 *)object)->unk_14 = (u16) (((S_8016E528_1 *)object)->unk_14 & 0xFF7F);
    ((S_8016E528_0 *)motion)->unk_1A = 0U;
    ((S_8016E528_0 *)motion)->unk_60 = 0x14900;
repeat_settling:
check_settling:
    if (((S_8016E528_0 *)motion)->unk_12 != 1) {
        goto check_falling;
    }
    if (((S_8016E528_0 *)motion)->unk_14 != 0) {
        goto update_settling;
    }
    ((S_8016E528_0 *)motion)->unk_14 = (s16) ((u16) ((S_8016E528_0 *)motion)->unk_14 + 1);
    tile_y = ((S_8016E528_0 *)motion)->unk_49;
    x_distance = ((S_8016E528_2 *)position)->unk_0E - ((S_8016E528_0 *)motion)->unk_48;
    target_y = ((S_8016E528_2 *)position)->unk_12;
    if (x_distance >= 0) {
        goto measure_y_distance;
    }
    x_distance = 0 - x_distance;
measure_y_distance:
    y_distance = target_y - tile_y;
    if (y_distance >= 0) {
        goto select_settle_time;
    }
    y_distance = 0 - y_distance;
select_settle_time:
    tile_distance = x_distance + y_distance;
    if (tile_distance >= 5U) {
        goto max_settle_time;
    }
    (void)distance_labels; goto *D_8016A868[(u32)(tile_distance)];
distance_zero:
    settle_ticks = 4;
    goto set_countdown;
distance_one:
    settle_ticks = 8;
    goto set_countdown;
distance_two:
    settle_ticks = 0xC;
    goto set_countdown;
distance_three:
    settle_ticks = 0xE;
    goto set_countdown;
distance_four:
max_settle_time:
    settle_ticks = 0x10;
set_countdown:
    ((S_8016E528_0 *)motion)->unk_1A = settle_ticks;
update_settling:
    ticks_left = ((S_8016E528_0 *)motion)->unk_1A - 1;
    ((S_8016E528_0 *)motion)->unk_1A = ticks_left;
    if ((s16) ticks_left == 0) {
        goto check_settled;
    }
    {
        s32 interp_target;
        s32 interp_current;
        interp_target = ((S_8016E528_2 *)position)->unk_0E << 6;
        interp_current = ((S_8016E528_2 *)position)->unk_00.at02.v - 0x20;
        ((S_8016E528_2 *)position)->unk_00.at02.v = (s16) ((u16) ((S_8016E528_2 *)position)->unk_00.at02.v + (interp_target - interp_current) / (s16) ticks_left);
    }
    {
        s32 interp_target;
        s32 interp_current;
        interp_target = ((S_8016E528_2 *)position)->unk_12 << 6;
        interp_current = ((S_8016E528_2 *)position)->unk_04.at02.v - 0x20;
        ((S_8016E528_2 *)position)->unk_04.at02.v = (s16) ((u16) ((S_8016E528_2 *)position)->unk_04.at02.v + (interp_target - interp_current) / (s16) ((S_8016E528_0 *)motion)->unk_1A);
    }
    ((S_8016E528_2 *)position)->unk_08.at02.v = (s16) ((u16) ((S_8016E528_2 *)position)->unk_08.at02.v + ((s32) (((S_8016E528_2 *)position)->unk_16 - ((S_8016E528_2 *)position)->unk_08.at02.v) / (s16) ((S_8016E528_0 *)motion)->unk_1A));
check_settled:
    if ((s16) ((S_8016E528_0 *)motion)->unk_1A > 0) {
        goto check_settle_repeat;
    }
    item_data[0] = ((S_8016E528_0 *)motion)->unk_44;
    item_data[1] = ((S_8016E528_0 *)motion)->unk_45;
    item_data[2] = ((S_8016E528_0 *)motion)->unk_46;
    item_data[3] = ((S_8016E528_0 *)motion)->unk_47;
    func_800A7A7C(((S_8016E528_2 *)position)->unk_0E, ((S_8016E528_2 *)position)->unk_12, ((S_8016E528_2 *)position)->unk_16, ((S_8016E528_1 *)object)->unk_08, item_data);
    goto mark_removed;
check_settle_repeat:
    if (((S_8016E528_1 *)object)->unk_14 & 0x8000) {
        goto repeat_settling;
    }
repeat_falling:
check_falling:
    if (((S_8016E528_0 *)motion)->unk_12 != 2) {
        goto update_motion;
    }
    ((S_8016E528_2 *)position)->unk_08.at00.v = (s32) (((S_8016E528_2 *)position)->unk_08.at00.v + ((S_8016E528_0 *)motion)->unk_54);
    ((S_8016E528_0 *)motion)->unk_54 = (s32) (((S_8016E528_0 *)motion)->unk_54 + ((S_8016E528_0 *)motion)->unk_60);
    scale = ((S_8016E528_1 *)object)->unk_1E - 0xC8;
    ((S_8016E528_1 *)object)->unk_1E = scale;
    ((S_8016E528_1 *)object)->unk_1C = scale;
    probe_height = ((S_8016E528_2 *)position)->unk_08.at02u.v;
    fall_height = ((S_8016E528_2 *)position)->unk_08.at02.v;
    if ((func_800BCB04((((S_8016E528_0 *)motion)->unk_48 << 6) & 0xFFC0, (((S_8016E528_0 *)motion)->unk_49 << 6) & 0xFFC0, (s16) (probe_height - 0x20)) - 7) >= fall_height) {
        goto check_fall_repeat;
    }
    ((S_8016E528_2 *)position)->unk_08.at02.v = func_800BCB04((((S_8016E528_0 *)motion)->unk_48 << 6) & 0xFFC0, (((S_8016E528_0 *)motion)->unk_49 << 6) & 0xFFC0, (s16) ((u16) ((S_8016E528_2 *)position)->unk_08.at02.v - 0x20));
    ((S_8016E528_2 *)position)->unk_08.at00u.v = 0;
mark_removed:
    (*(u16 *)((u8 *)motion + (-2))) = (u16) (((S_8016E528_0_pre *)motion)[-1].unk_00 | 0x8000);
    D_800814A0 |= 0x8000;
    return;
check_fall_repeat:
    if (((S_8016E528_1 *)object)->unk_14 & 0x8000) {
        goto repeat_falling;
    }
update_motion:
    if (((S_8016E528_0 *)motion)->unk_12 != 0) {
        goto done;
    }
    ((S_8016E528_2 *)position)->unk_00.at00.v = (s32) (((S_8016E528_2 *)position)->unk_00.at00.v + ((S_8016E528_0 *)motion)->unk_4C);
    ((S_8016E528_0 *)motion)->unk_4C = (s32) (((S_8016E528_0 *)motion)->unk_4C + ((S_8016E528_0 *)motion)->unk_58);
    ((S_8016E528_2 *)position)->unk_04.at00.v = (s32) (((S_8016E528_2 *)position)->unk_04.at00.v + ((S_8016E528_0 *)motion)->unk_50);
    direction_table = &D_80174708;
    ((S_8016E528_0 *)motion)->unk_50 = (s32) (((S_8016E528_0 *)motion)->unk_50 + ((S_8016E528_0 *)motion)->unk_5C);
    direction_step = (((S_8016E528_0 *)motion)->unk_18 * 4) + direction_table;
    next_tile = ((S_8016E528_0 *)motion)->unk_48 + ((S_8016E528_3 *)direction_step)->unk_00;
    world_x = ((S_8016E528_2 *)position)->unk_00.at02.v;
    if (world_x >= 0) {
        goto check_tile_x;
    }
    world_x += 0x3F;
check_tile_x:
    if (next_tile != (world_x >> 6)) {
        goto update_height;
    }
    next_tile = ((S_8016E528_0 *)motion)->unk_49 + ((S_8016E528_3 *)direction_step)->unk_02;
    world_y = ((S_8016E528_2 *)position)->unk_04.at02.v;
    if (world_y >= 0) {
        goto check_tile_y;
    }
    world_y += 0x3F;
check_tile_y:
    if (next_tile != (world_y >> 6)) {
        goto update_height;
    }
    if ((func_800A45D8((u16) ((S_8016E528_2 *)position)->unk_00.at02.v, (u16) ((S_8016E528_2 *)position)->unk_04.at02.v, ((S_8016E528_2 *)position)->unk_08.at02.v) << 0x10) != 0) {
        goto stop_at_obstacle;
    }
    if (func_800BCB04((u16) ((S_8016E528_2 *)position)->unk_00.at02.v, (u16) ((S_8016E528_2 *)position)->unk_04.at02.v, ((S_8016E528_2 *)position)->unk_08.at02.v) < 0x200) {
        goto advance_tile;
    }
stop_at_obstacle:
    ((S_8016E528_2 *)position)->unk_00.at00.v = (s32) (((S_8016E528_2 *)position)->unk_00.at00.v - ((S_8016E528_0 *)motion)->unk_4C);
    ((S_8016E528_0 *)motion)->unk_4C = 0;
    ((S_8016E528_0 *)motion)->unk_58 = 0;
    ((S_8016E528_2 *)position)->unk_04.at00.v = (s32) (((S_8016E528_2 *)position)->unk_04.at00.v - ((S_8016E528_0 *)motion)->unk_50);
    ((S_8016E528_0 *)motion)->unk_50 = 0;
    ((S_8016E528_0 *)motion)->unk_5C = 0;
    goto clear_motion;
advance_tile:
    ((S_8016E528_0 *)motion)->unk_48 = (s8) ((u8) ((S_8016E528_0 *)motion)->unk_48 + *((((S_8016E528_0 *)motion)->unk_18 * 4) + direction_table));
    ((S_8016E528_0 *)motion)->unk_49 = (s8) ((u8) ((S_8016E528_0 *)motion)->unk_49 + ((S_8016E528_4 *)(((((S_8016E528_0 *)motion)->unk_18 * 4) + direction_table)))->unk_02);
clear_motion:
    ((S_8016E528_1 *)object)->unk_06 = 0;
update_height:
    ((S_8016E528_2 *)position)->unk_08.at00.v = (s32) (((S_8016E528_2 *)position)->unk_08.at00.v + ((S_8016E528_0 *)motion)->unk_54);
    ((S_8016E528_0 *)motion)->unk_54 = (s32) (((S_8016E528_0 *)motion)->unk_54 + ((S_8016E528_0 *)motion)->unk_60);
    move_height = ((S_8016E528_2 *)position)->unk_08.at02.v;
    if ((func_800BCB04(((((S_8016E528_0 *)motion)->unk_48 << 6) + 0x20) & 0xFFE0, ((((S_8016E528_0 *)motion)->unk_49 << 6) + 0x20) & 0xFFE0, move_height) - 0x10) >= move_height) {
        goto check_motion_repeat;
    }
    ((S_8016E528_2 *)position)->unk_08.at02.v = func_800BCB04(((((S_8016E528_0 *)motion)->unk_48 << 6) + 0x20) & 0xFFE0, ((((S_8016E528_0 *)motion)->unk_49 << 6) + 0x20) & 0xFFE0, ((S_8016E528_2 *)position)->unk_08.at02.v);
    ((S_8016E528_2 *)position)->unk_08.at00u.v = 0;
    ((S_8016E528_0 *)motion)->unk_5C = 0;
    ((S_8016E528_0 *)motion)->unk_50 = 0;
    ((S_8016E528_0 *)motion)->unk_58 = 0;
    ((S_8016E528_0 *)motion)->unk_4C = 0;
    ((S_8016E528_0 *)motion)->unk_12 = (s16) ((u16) ((S_8016E528_0 *)motion)->unk_12 + 1);
    if ((func_800A7234(((S_8016E528_0 *)motion)->unk_48, ((S_8016E528_0 *)motion)->unk_49, (s16) ((u16) ((S_8016E528_2 *)position)->unk_08.at02.v - 0x20), position + 0xE, position + 0x12, position + 0x16) << 0x10) != 0) {
        goto check_motion_repeat;
    }
    ((S_8016E528_0 *)motion)->unk_12 = 2;
    ((S_8016E528_0 *)motion)->unk_54 = 0xFFF80000;
check_motion_repeat:
    if (((S_8016E528_1 *)object)->unk_14 & 0x8000) {
        goto update_motion;
    }
done:
    return;
}
