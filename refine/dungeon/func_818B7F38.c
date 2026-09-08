#include "common.h"
#include "m2c_compat.h"

typedef struct S_80025738_0 {
    void * unk_00;
    u16 * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    s16 unk_12;
    s16 unk_14;
    u8 pad_16[0x2];
    void * unk_18;
} S_80025738_0;   /* arg0 in func_80025738 */

typedef struct S_80025738_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x24];
    s16 unk_88;
} S_80025738_1;   /* temp_s7 in func_80025738 */

typedef struct S_80025738_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80025738_2;   /* arg2 in func_80025738 */

typedef struct S_80025738_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80025738_3;   /* temp_s2 in func_80025738 */

typedef struct S_80025738_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80025738_4;   /* temp_a1 in func_80025738 */

typedef struct S_80025738_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80025738_5;   /* arg1 in func_80025738 */

typedef struct S_80025738_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80025738_6;   /* temp_v1_2 in func_80025738 */

typedef struct S_80025738_7 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80025738_7;   /* temp_a3 in func_80025738 */

typedef struct S_80025738_8 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_80025738_8;   /* temp_v0 in func_80025738 */

typedef struct S_80025738_9 {
    u8 pad_00[0x18];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
} S_80025738_9;   /* var_a1 in func_80025738 */

typedef struct S_80025738_10 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80025738_10;   /* temp_v1_4 in func_80025738 */

typedef struct S_80025738_11 {
    u8 pad_00[0x18];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
} S_80025738_11;   /* var_a2 in func_80025738 */

typedef struct S_80025738_12 {
    s32 unk_00;
} S_80025738_12;   /* &D_800814A0 in func_80025738 */

typedef struct S_80025738_13 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80025738_13;   /* ((S_80025738_3 *)temp_s2)->unk_0C in func_80025738 */

typedef struct S_80025738_14_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_80025738_14_pre;   /* the 0x18 bytes before ((S_80025738_1 *)temp_s7)->unk_60 in func_80025738, addressed as ((S_80025738_1 *)temp_s7)->unk_60[-1] */

typedef struct S_80025738_14 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_80025738_14;   /* ((S_80025738_1 *)temp_s7)->unk_60 in func_80025738 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80024008[];
M2C_UNK func_80024024();          /* extern */
M2C_UNK func_800253D0();              /* extern */
M2C_UNK func_80025614(); /* extern */
s32 func_8003DE58();     /* extern */
s32 func_800A44E0();              /* extern */
M2C_UNK func_800A56E0();                /* extern */
s16 func_800BCB04();                   /* extern */
extern u16 D_8006CCD8[8];
extern u16 D_8006CCE8[8];
extern M2C_UNK D_800814A0;
extern s32 D_8008346C;

#ifdef NON_MATCHING
#define LOAD_TABLE_X_BASE(v) ((v) = (s32)D_8006CCD8)
#define LOAD_TABLE_Y_BASE(v) ((v) = (s32)D_8006CCE8)
#else
#define LOAD_TABLE_X_BASE(v) do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3328; } while (0)
#define LOAD_TABLE_Y_BASE(v) do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3318; } while (0)
#endif

typedef struct LocalFrame {
    s32 out_x;
    s32 out_y;
    s32 out_z;
    u8 pad_C[12];
    u16 delta[3];
    u16 pad_1E;
    u16 raw_y;
} LocalFrame;

/* Advance movement toward a target or a reachable tile, then finish the timed action. */
void func_80025738(void *state, void *motion_in, void *render) {
    static void *const state_labels[] = { &&phase_init, &&phase_aim, &&phase_move_target, &&phase_wait_short, &&phase_wait_long, &&phase_finish, &&phase_move_path };
    register void *motion ASM_REG("$21") = motion_in;
    LocalFrame frame;
    u16 *target_delta_cursor;
    u16 *path_delta_cursor;
    register s32 probe_x ASM_REG("$4");
    s16 end_y;
    s16 end_x;
    register u16 base_z ASM_REG("$2");
    register u16 delta_z ASM_REG("$3");
    s16 floor_z;
    s16 end_z;
    s32 phase;
    s32 target_dx;
    s32 path_dy;
    s32 path_dx;
    s16 next_phase;
    s32 path_dz;
    register s32 velocity_y ASM_REG("$4");
    s32 velocity_z;
    s32 target_ticks;
    s32 probe_dir_offset;
    s32 path_ticks;
    s32 step_dir_offset;
    s32 world_y;
    s32 world_x;
    s32 direction;
    s32 end_x_signed;
    register s32 end_y_signed ASM_REG("$4");
    s32 offset_x;
    s32 offset_y;
    register s32 table_base ASM_REG("$8");
    s16 *table_x_entry;
    s16 *table_y_entry;
    u16 *update_x_entry;
    register u16 *update_y_entry ASM_REG("$3");
    register s32 probe_y ASM_REG("$5");
    register s32 probe_z ASM_REG("$6");
    s32 end_z_signed;
    register s32 current_x ASM_REG("$3");
    register s32 current_y ASM_REG("$3");
    s32 current_z;
    s32 position_xy;
    s32 step_x_or_z;
    s16 *x_offsets;
    s16 *y_offsets;
    register s32 index ASM_REG("$16");
    register s32 target_dy ASM_REG("$2");
    s32 target_dz;
    u16 source_z;
    u16 adjusted_z;
    s32 next_tile_y;
    register s32 last_tile_x;
    u32 table_page;
    register s32 tile_x ASM_REG("$20");
    register s32 tile_y ASM_REG("$22");
    register s32 tile_x_signed ASM_REG("$18");
    register s32 tile_y_signed ASM_REG("$19");
    register s32 tile_shifted ASM_REG("$2");
    void *source_data;
    register void *destination ASM_REG("$7");
    void *source_header;
    void *owner;
    void *target;
    void *source_position;
    void *tile_data;

    phase = (s32) ((S_80025738_0 *)state)->unk_0A;
    owner = ((S_80025738_0 *)state)->unk_00;
    ((S_80025738_0 *)state)->unk_10 = (u16) (((S_80025738_0 *)state)->unk_10 + 1);
    if ((u32) phase >= 7U) {
        goto clear_update_flag;
    }
    (void)state_labels; goto *D_80024008[(u32)(phase)];
phase_init:
    ((S_80025738_0 *)state)->unk_10 = 0U;
    ((S_80025738_0 *)state)->unk_0A = (s16) ((u16) ((S_80025738_0 *)state)->unk_0A + 1);
    ((S_80025738_0 *)state)->unk_0E = (u16) (((u16) ((S_80025738_1 *)owner)->unk_2A >> 9) & 7);
    ((S_80025738_2 *)render)->unk_0C = 0x808080;
phase_aim:
    source_header = owner - 0x20;
    source_data = ((S_80025738_3 *)source_header)->unk_0C;
    if (func_8003DE58(((S_80025738_4 *)source_data)->unk_08, source_data, frame.delta, 0) != 0) {
        goto copy_source_position;
    }
    if (!(((S_80025738_13 *)(((S_80025738_3 *)source_header)->unk_0C))->unk_14 & 0x8000)) {
        goto clear_update_flag;
    }
copy_source_position:
    source_position = ((S_80025738_3 *)source_header)->unk_08;
    ((S_80025738_5 *)motion)->unk_00.at02.v = (u16) ((S_80025738_6 *)source_position)->unk_02;
    ((S_80025738_5 *)motion)->unk_04.at02.v = (u16) ((S_80025738_6 *)source_position)->unk_06;
    source_z = ((S_80025738_6 *)source_position)->unk_0A;
    ((S_80025738_5 *)motion)->unk_08.at02.v = source_z;
    if (((S_80025738_13 *)(((S_80025738_3 *)source_header)->unk_0C))->unk_14 & 0x8000) {
        goto lower_source_z;
    }
    ((S_80025738_5 *)motion)->unk_00.at02.v = (u16) (((S_80025738_5 *)motion)->unk_00.at02.v + frame.delta[0]);
    ((S_80025738_5 *)motion)->unk_04.at02.v = (u16) (((S_80025738_5 *)motion)->unk_04.at02.v + frame.delta[1]);
    ASM_MEM_BARRIER();
    base_z = ((S_80025738_5 *)motion)->unk_08.at02.v;
    delta_z = frame.delta[2];
    adjusted_z = base_z + delta_z;
    goto store_source_z;
lower_source_z:
    adjusted_z = source_z - 0x40;
store_source_z:
    ((S_80025738_5 *)motion)->unk_08.at02.v = adjusted_z;
    if (!(*((S_80025738_0 *)state)->unk_04 & 0x80)) {
        goto clear_update_flag;
    }
    target = ((S_80025738_1 *)owner)->unk_60;
    index = 1;
    if (target == NULL) {
        goto scan_path;
    }
    ((S_80025738_0 *)state)->unk_18 = target;
    destination = ((S_80025738_14_pre *)(((S_80025738_1 *)owner)->unk_60))[-1].unk_00;
    target_dx = ((S_80025738_7 *)destination)->unk_00.at02.v;
    target_dx -= ((S_80025738_5 *)motion)->unk_00.at02u.v;
    if (target_dx >= 0) {
        goto store_target_dx;
    }
    target_dx = 0 - target_dx;
store_target_dx:
    frame.delta[0] = (u16) target_dx;
    target_dy = ((S_80025738_7 *)destination)->unk_04.at02.v;
    target_dy -= ((S_80025738_5 *)motion)->unk_04.at02u.v;
    if (target_dy >= 0) {
        goto store_target_dy;
    }
    target_dy = 0 - target_dy;
store_target_dy:
    frame.delta[1] = (u16) target_dy;
    target = ((S_80025738_1 *)owner)->unk_60;
    current_z = ((S_80025738_5 *)motion)->unk_08.at02u.v;
    target_dz = ((S_80025738_8 *)target)->unk_88;
    ASM_SCHED_BARRIER();
    target_delta_cursor = (u16 *)((u8 *)&frame.out_x + 2);
    ASM_KEEP(target_delta_cursor);
    target_dz -= current_z;
    if (target_dz >= 0) {
        goto store_target_dz;
    }
    target_dz = 0 - target_dz;
store_target_dz:
    frame.delta[2] = (u16) target_dz;
    ((S_80025738_0 *)state)->unk_12 = target_dx;
max_target_delta:
    if (((S_80025738_9 *)target_delta_cursor)->unk_18.s > ((S_80025738_0 *)state)->unk_12) {
        ((S_80025738_0 *)state)->unk_12 = ((S_80025738_9 *)target_delta_cursor)->unk_18.u;
    }
next_target_axis:
    index += 1;
    target_delta_cursor += 1;
    if (index < 3) {
        goto max_target_delta;
    }
    target_ticks = (s32) ((u16) ((S_80025738_0 *)state)->unk_12 << 0x10) >> 0x14;
    ((S_80025738_0 *)state)->unk_12 = (s16) target_ticks;
    if (target_ticks != 0) {
        goto set_target_velocity;
    }
    ((S_80025738_0 *)state)->unk_12 = 1;
set_target_velocity:
    ((S_80025738_5 *)motion)->unk_0C = (s32) ((s32) (((S_80025738_7 *)destination)->unk_00.at00.v - ((S_80025738_5 *)motion)->unk_00.at00.v) / (s16) ((S_80025738_0 *)state)->unk_12);
    ((S_80025738_5 *)motion)->unk_10 = (s32) ((s32) (((S_80025738_7 *)destination)->unk_04.at00.v - ((S_80025738_5 *)motion)->unk_04.at00.v) / (s16) ((S_80025738_0 *)state)->unk_12);
    ((S_80025738_5 *)motion)->unk_14 = (s32) ((s32) ((((S_80025738_14 *)(((S_80025738_1 *)owner)->unk_60))->unk_88 << 0x10) - ((S_80025738_5 *)motion)->unk_08.at00.v) / (s16) ((S_80025738_0 *)state)->unk_12);
    func_800253D0(state, motion);
    next_phase = (u16) ((S_80025738_0 *)state)->unk_0A + 1;
    goto set_phase;
scan_path:
    index = 0;
    tile_data = ((S_80025738_3 *)source_header)->unk_0C;
    ASM_SCHED_BARRIER();
    table_page = 0x80070000;
    ASM_KEEP(table_page);
    tile_x = ((S_80025738_10 *)tile_data)->unk_24;
    ASM_SCHED_BARRIER();
    tile_y = ((S_80025738_10 *)tile_data)->unk_25;
    last_tile_x = tile_x;
    frame.raw_y = (u16) tile_y;
probe_tile:
    tile_shifted = tile_x << 0x10;
    tile_x_signed = tile_shifted >> 0x10;
    probe_x = (tile_x_signed << 6) & 0xFFC0;
    tile_shifted = tile_y << 0x10;
    tile_y_signed = tile_shifted >> 0x10;
    if ((func_800A44E0(probe_x, (tile_y_signed << 6) & 0xFFC0, ((S_80025738_1 *)owner)->unk_88, (s16) (((S_80025738_0 *)state)->unk_0E << 9)) << 0x10) != 0) {
        goto use_path_endpoint;
    }
    LOAD_TABLE_X_BASE(table_base);
    ASM_KEEP(table_base);
    probe_dir_offset = (s16) ((S_80025738_0 *)state)->unk_0E;
    probe_z = (u16) ((S_80025738_1 *)owner)->unk_88;
    probe_dir_offset *= 2;
    table_x_entry = (s16 *)((s32)probe_dir_offset + table_base);
    ASM_KEEP(table_x_entry);
    probe_z -= 0x20;
    probe_z = (s16) probe_z;
    LOAD_TABLE_Y_BASE(table_base);
    table_y_entry = (s16 *)((s32)probe_dir_offset + table_base);
    ASM_USE(last_tile_x);
    probe_x = tile_x_signed + *table_x_entry;
    probe_x = ((probe_x << 6) + 0x20) & 0xFFE0;
    probe_y = tile_y_signed + *table_y_entry;
    probe_y = ((probe_y << 6) + 0x20) & 0xFFE0;
    floor_z = func_800BCB04(probe_x, probe_y, probe_z);
    destination = &frame.out_x;
    if (floor_z >= 0x201) {
        goto build_path_endpoint;
    }
    if ((s16) (floor_z - (u16) ((S_80025738_1 *)owner)->unk_88) < -0x3F) {
        goto build_path_endpoint;
    }
    LOAD_TABLE_X_BASE(table_base);
    ASM_KEEP(table_base);
    index += 1;
    step_dir_offset = (s16) ((S_80025738_0 *)state)->unk_0E;
    step_dir_offset *= 2;
    update_x_entry = (u16 *)((s32)step_dir_offset + table_base);
    LOAD_TABLE_Y_BASE(table_base);
    update_y_entry = (u16 *)((s32)step_dir_offset + table_base);
    ASM_KEEP(update_y_entry);
    probe_x = tile_x + *update_x_entry;
    tile_x = probe_x;
    next_tile_y = tile_y + *update_y_entry;
    tile_y = next_tile_y;
    frame.raw_y = (u16) next_tile_y;
    ASM_KEEP4_NV(probe_x, next_tile_y, tile_x, tile_y);
    last_tile_x = probe_x;
    if (index < 8) {
        goto probe_tile;
    }
use_path_endpoint:
    ASM_SCHED_BARRIER();
    destination = &frame.out_x;
build_path_endpoint:
    index = 1;
    ASM_KEEP(index);
    world_x = last_tile_x << 0x10;
    x_offsets = (s16 *)D_8006CCD8;
    ASM_KEEP(x_offsets);
    world_x >>= 0xA;
    direction = (s16) ((S_80025738_0 *)state)->unk_0E;
    ASM_KEEP(direction);
    path_delta_cursor = (u16 *)((u8 *)&frame.out_x + 2);
    ASM_KEEP(path_delta_cursor);
    offset_x = x_offsets[direction];
    y_offsets = (s16 *)D_8006CCE8;
    end_x = world_x + ((offset_x + 1) << 5);
    ((S_80025738_7 *)destination)->unk_00.at02.v = end_x;
    end_x_signed = end_x;
    table_base = frame.raw_y;
    direction = (s16) ((S_80025738_0 *)state)->unk_0E;
    world_y = table_base << 0x10;
    ASM_KEEP(direction);
    offset_y = y_offsets[direction];
    world_y >>= 0xA;
    end_y = world_y + ((offset_y + 1) << 5);
    ((S_80025738_7 *)destination)->unk_04.at02.v = end_y;
    end_y_signed = (s32) ((u16) end_y << 0x10);
    end_z = ((S_80025738_5 *)motion)->unk_08.at02.v + 0x20;
    ((S_80025738_7 *)destination)->unk_08.at02.v = end_z;
    current_x = ((S_80025738_5 *)motion)->unk_00.at02u.v;
    ASM_SCHED_BARRIER();
    end_y_signed >>= 0x10;
    ASM_SCHED_BARRIER();
    path_dx = end_x_signed;
    path_dx -= current_x;
    if (path_dx >= 0) {
        goto store_path_dx;
    }
    path_dx = 0 - path_dx;
store_path_dx:
    frame.delta[0] = path_dx;
    current_y = ((S_80025738_5 *)motion)->unk_04.at02u.v;
    ASM_SCHED_BARRIER();
    end_z_signed = (s32) ((u16) end_z << 0x10);
    ASM_SCHED_BARRIER();
    path_dy = end_y_signed;
    path_dy -= current_y;
    if (path_dy >= 0) {
        goto store_path_dy;
    }
    path_dy = 0 - path_dy;
store_path_dy:
    frame.delta[1] = path_dy;
    current_z = ((S_80025738_5 *)motion)->unk_08.at02u.v;
    end_z_signed >>= 0x10;
    path_dz = end_z_signed;
    path_dz -= current_z;
    if (path_dz >= 0) {
        goto store_path_dz;
    }
    path_dz = 0 - path_dz;
store_path_dz:
    frame.delta[2] = path_dz;
    ((S_80025738_0 *)state)->unk_12 = path_dx;
max_path_delta:
    if (((S_80025738_11 *)path_delta_cursor)->unk_18.s > ((S_80025738_0 *)state)->unk_12) {
        ((S_80025738_0 *)state)->unk_12 = ((S_80025738_11 *)path_delta_cursor)->unk_18.u;
    }
next_path_axis:
    index += 1;
    path_delta_cursor += 1;
    if (index < 3) {
        goto max_path_delta;
    }
    path_ticks = (s32) ((u16) ((S_80025738_0 *)state)->unk_12 << 0x10) >> 0x14;
    ((S_80025738_0 *)state)->unk_12 = (s16) path_ticks;
    if (path_ticks != 0) {
        goto set_path_velocity;
    }
    ((S_80025738_0 *)state)->unk_12 = 1;
set_path_velocity:
    ((S_80025738_5 *)motion)->unk_0C = (s32) ((s32) (((S_80025738_7 *)destination)->unk_00.at00.v - ((S_80025738_5 *)motion)->unk_00.at00.v) / (s16) ((S_80025738_0 *)state)->unk_12);
    ((S_80025738_5 *)motion)->unk_10 = (s32) ((s32) (((S_80025738_7 *)destination)->unk_04.at00.v - ((S_80025738_5 *)motion)->unk_04.at00.v) / (s16) ((S_80025738_0 *)state)->unk_12);
    ((S_80025738_5 *)motion)->unk_14 = (s32) ((s32) (((S_80025738_7 *)destination)->unk_08.at00.v - ((S_80025738_5 *)motion)->unk_08.at00.v) / (s16) ((S_80025738_0 *)state)->unk_12);
    func_80025614(state, motion);
    next_phase = 6;
    goto set_phase;
phase_move_target:
    position_xy = ((S_80025738_5 *)motion)->unk_00.at00.v;
    step_x_or_z = ((S_80025738_5 *)motion)->unk_0C;
    velocity_y = ((S_80025738_5 *)motion)->unk_10;
    velocity_z = ((S_80025738_5 *)motion)->unk_14;
    position_xy += step_x_or_z;
    ((S_80025738_5 *)motion)->unk_00.at00.v = position_xy;
    position_xy = ((S_80025738_5 *)motion)->unk_04.at00.v;
    step_x_or_z = ((S_80025738_5 *)motion)->unk_08.at00.v;
    position_xy += velocity_y;
    step_x_or_z += velocity_z;
    ((S_80025738_5 *)motion)->unk_04.at00.v = position_xy;
    ((S_80025738_5 *)motion)->unk_08.at00.v = step_x_or_z;
    if ((s16) ((S_80025738_0 *)state)->unk_10 < ((S_80025738_0 *)state)->unk_12) {
        goto clear_update_flag;
    }
    func_800A56E0(0x300, velocity_z);
    goto advance_phase;
phase_wait_short:
    if ((s16) ((S_80025738_0 *)state)->unk_10 >= 0x10) {
        goto advance_phase;
    }
    ((S_80025738_0 *)state)->unk_14 = 0;
    return;
phase_wait_long:
    if ((s16) ((S_80025738_0 *)state)->unk_10 < 0x30) {
        goto clear_update_flag;
    }
    func_80024024(((S_80025738_1 *)owner)->unk_60, ((S_80025738_0 *)state)->unk_09, owner);
advance_phase:
    ((S_80025738_0 *)state)->unk_10 = 0U;
    ((S_80025738_0 *)state)->unk_0A = (s16) ((u16) ((S_80025738_0 *)state)->unk_0A + 1);
    goto clear_update_flag;
phase_finish:
    if (((S_80025738_0 *)state)->unk_14 != 0) {
        goto clear_update_flag;
    }
    D_8008346C = 0;
    (*(u16 *)((u8 *)state + -2)) = (u16) ((*(u16 *)((u8 *)state + -2)) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((S_80025738_12 *)(&D_800814A0))->unk_00 | 0x8000);
    goto clear_update_flag;
phase_move_path:
    ((S_80025738_5 *)motion)->unk_00.at00.v = (s32) (((S_80025738_5 *)motion)->unk_00.at00.v + ((S_80025738_5 *)motion)->unk_0C);
    ((S_80025738_5 *)motion)->unk_04.at00.v = (s32) (((S_80025738_5 *)motion)->unk_04.at00.v + ((S_80025738_5 *)motion)->unk_10);
    ((S_80025738_5 *)motion)->unk_08.at00.v = (s32) (((S_80025738_5 *)motion)->unk_08.at00.v + ((S_80025738_5 *)motion)->unk_14);
    if ((s16) ((S_80025738_0 *)state)->unk_10 < ((S_80025738_0 *)state)->unk_12) {
        goto clear_update_flag;
    }
    next_phase = 5;
set_phase:
    ((S_80025738_0 *)state)->unk_0A = next_phase;
    ((S_80025738_0 *)state)->unk_10 = 0U;
clear_update_flag:
    ((S_80025738_0 *)state)->unk_14 = 0;
    return;
}
