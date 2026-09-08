#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800243B8_arg0.h"


typedef struct S_80024660_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x24];
    s16 unk_88;
} S_80024660_1;   /* temp_s7 in func_80024660 */

typedef struct S_80024660_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80024660_2;   /* arg2 in func_80024660 */

typedef struct S_80024660_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80024660_3;   /* temp_s0 in func_80024660 */

typedef struct S_80024660_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80024660_4;   /* temp_a1 in func_80024660 */

typedef struct S_80024660_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024660_5;   /* arg1 in func_80024660 */

typedef struct S_80024660_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024660_6;   /* temp_v1_2 in func_80024660 */

typedef struct S_80024660_7_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0x14];
} S_80024660_7_pre;   /* the 0x18 bytes before temp_v0 in func_80024660, addressed as temp_v0[-1] */

typedef struct S_80024660_8 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80024660_8;   /* var_s3 in func_80024660 */

typedef struct S_80024660_9 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80024660_9;   /* temp_v1_5 in func_80024660 */

typedef struct S_80024660_10 {
    u8 pad_00[0x18];
    s32 unk_18;
} S_80024660_10;   /* var_s0 in func_80024660 */

typedef struct S_80024660_11 {
    s32 unk_00;
} S_80024660_11;   /* &D_800814A0 in func_80024660 */

typedef struct S_80024660_12 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80024660_12;   /* ((S_80024660_3 *)temp_s0)->unk_0C in func_80024660 */


extern void *D_80024020[];
M2C_UNK func_8002403C();
s32 func_800243B8();
s32 func_8003DE58();
s32 func_800A44E0();
M2C_UNK func_800A56E0();
s16 func_800BCB04();
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u16 D_8006CCD8_2[] __asm__("D_8006CCD8");
extern u16 D_8006CCE8_2[] __asm__("D_8006CCE8");
extern s16 D_8006CCD8_3[] __asm__("D_8006CCD8");
extern s16 D_8006CCE8_3[] __asm__("D_8006CCE8");
extern M2C_UNK D_800814A0;
extern s32 D_8008346C;

typedef struct {
    s32 pos[3];
    u8 pad18[0xC];
    u16 dist[3];
    u8 pad2E[2];
    u16 saved_y;
} Func818AAE60Scratch;

/* Update an effect that travels toward a target or along a clear path and spawns child effects. */
void func_80024660(void *effect, void *motion, void *appearance) {
    static void *const state_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6 };
    Func818AAE60Scratch scratch;
    s16 *target_dist_cursor;
    s16 *path_dist_cursor;
    M2C_UNK *destination;
    s16 floor_z;
    s32 state;
    s16 target_frames;
    s16 path_frames;
    s32 target_x_dist;
    s32 path_y_dist;
    s32 path_x_dist;
    register s32 path_z_dist ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 target_dist_fixed;
    s32 direction;
    s32 path_dist_fixed;
    s32 origin_x;
    s32 index;
    s32 axis_dist;
    s32 origin_coord;
    s32 tile_x;
    s32 tile_y;
    u16 source_z;
    u16 z_or_state;
    void *source_info;
    void *source_record;
    void *source;
    void *target;
    void *source_pos;
    void *tile_info;
    register void *child_slot ASM_REG("$16");   /* MATCH pin: keeps a constant in a register as retail does */
    u16 elapsed;

    elapsed = ((Rec_func_800243B8_arg0 *)effect)->unk_10;
    state = ((Rec_func_800243B8_arg0 *)effect)->unk_0A;
    source = ((Rec_func_800243B8_arg0 *)effect)->unk_00;
    ((Rec_func_800243B8_arg0 *)effect)->unk_10 = elapsed + 1;
    if ((u32) state >= 7U) {
        goto finish;
    }
    (void)state_labels;
    goto *D_80024020[(u32)(state)];
jt_c0:
    ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
    ((Rec_func_800243B8_arg0 *)effect)->unk_0A = (s16) ((u16) ((Rec_func_800243B8_arg0 *)effect)->unk_0A + 1);
    ((Rec_func_800243B8_arg0 *)effect)->unk_0E = (u16) (((u16) ((S_80024660_1 *)source)->unk_2A >> 9) & 7);
    ((S_80024660_2 *)appearance)->unk_0C = 0x808080;
jt_c1:
    source_record = source - 0x20;
    source_info = ((S_80024660_3 *)source_record)->unk_0C;
    if (func_8003DE58(((S_80024660_4 *)source_info)->unk_08, source_info, &scratch.dist[0], 0) != 0) {
        goto copy_source_pos;
    }
    if (!(((S_80024660_12 *)(((S_80024660_3 *)source_record)->unk_0C))->unk_14 & 0x8000)) {
        goto finish;
    }
copy_source_pos:
    source_pos = ((S_80024660_3 *)source_record)->unk_08;
    ((S_80024660_5 *)motion)->unk_00.at02.v = (u16) ((S_80024660_6 *)source_pos)->unk_02;
    ((S_80024660_5 *)motion)->unk_04.at02.v = (u16) ((S_80024660_6 *)source_pos)->unk_06;
    source_z = ((S_80024660_6 *)source_pos)->unk_0A;
    ((S_80024660_5 *)motion)->unk_08.at02.v = source_z;
    if (((S_80024660_12 *)(((S_80024660_3 *)source_record)->unk_0C))->unk_14 & 0x8000) {
        goto lower_source_z;
    }
    ((S_80024660_5 *)motion)->unk_00.at02.v = (u16) (((S_80024660_5 *)motion)->unk_00.at02.v + scratch.dist[0]);
    ((S_80024660_5 *)motion)->unk_04.at02.v = (u16) (((S_80024660_5 *)motion)->unk_04.at02.v + scratch.dist[1]);
    z_or_state = ((S_80024660_5 *)motion)->unk_08.at02.v;
    ASM_KEEP(z_or_state);   /* MATCH pin: load-bearing for the whole function shape */
    {
        register u16 z_offset ASM_REG("$3");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        z_offset = scratch.dist[2];
        z_or_state = z_or_state + z_offset;
    }
    goto set_start_z;
lower_source_z:
    z_or_state = source_z - 0x40;
set_start_z:
    ((S_80024660_5 *)motion)->unk_08.at02.v = z_or_state;
    if (!(*((Rec_func_800243B8_arg0 *)effect)->unk_04 & 0x80)) {
        goto finish;
    }
    target = ((S_80024660_1 *)source)->unk_60;
    index = 1;
    if (target != NULL) {
        destination = ((S_80024660_7_pre *)target)[-1].unk_00;
        target_x_dist = ((S_80024660_8 *)destination)->unk_00.at02.v;
        target_x_dist -= ((S_80024660_5 *)motion)->unk_00.at02u.v;
        if (target_x_dist >= 0) {
            goto target_x_ready;
        }
        target_x_dist = 0 - target_x_dist;
target_x_ready:
        scratch.dist[0] = (u16) target_x_dist;
        axis_dist = ((S_80024660_8 *)destination)->unk_04.at02.v;
        origin_coord = ((S_80024660_5 *)motion)->unk_04.at02u.v;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        target_dist_cursor = (s16 *)((u8 *)&scratch + 2);
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        axis_dist -= origin_coord;
        if (axis_dist >= 0) {
            goto target_y_ready;
        }
        axis_dist = 0 - axis_dist;
target_y_ready:
        scratch.dist[1] = (u16) axis_dist;
        origin_coord = ((S_80024660_5 *)motion)->unk_08.at02u.v;
        origin_coord += 0x20;
        axis_dist = ((S_80024660_8 *)destination)->unk_08.at02.v - origin_coord;
        if (axis_dist >= 0) {
            goto target_z_ready;
        }
        axis_dist = 0 - axis_dist;
target_z_ready:
        scratch.dist[2] = (u16) axis_dist;
        ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = target_x_dist;
scan_target_dist:
        if (target_dist_cursor[12] <= ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16) {
            goto next_target_axis;
        }
        ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = (s16) (u16) target_dist_cursor[12];
next_target_axis:
        index += 1;
        target_dist_cursor += 1;
        if (index < 3) {
            goto scan_target_dist;
        }
        target_dist_fixed = (u16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 << 0x10;
        target_frames = (target_dist_fixed >> 0x14) + (target_dist_fixed >> 0x15);
        ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = target_frames;
        if (target_frames != 0) {
            goto set_target_velocity;
        }
        ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = 1;
set_target_velocity:
        ((S_80024660_5 *)motion)->unk_0C = (s32) ((s32) (((S_80024660_8 *)destination)->unk_00.at00.v - ((S_80024660_5 *)motion)->unk_00.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
        ((S_80024660_5 *)motion)->unk_10 = (s32) ((s32) (((S_80024660_8 *)destination)->unk_04.at00.v - ((S_80024660_5 *)motion)->unk_04.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
        ((S_80024660_5 *)motion)->unk_14 = (s32) ((s32) (((S_80024660_8 *)destination)->unk_08.at00.v - ((S_80024660_5 *)motion)->unk_08.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
        func_800A56E0(0x300, target_dist_cursor);
        z_or_state = (u16) ((Rec_func_800243B8_arg0 *)effect)->unk_0A + 1;
        goto spawn_children;
    } else {
        register s32 probe_y_dest_x ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 probe_x_dest_y ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
        register u16 saved_tile_y ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */
        register u16 *step_table ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */
        u16 *x_step_ptr;
        register s32 probe_z ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
        register u32 table_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        s32 last_tile_x;
        register s32 path_tile_x ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 path_tile_y ASM_REG("$22");   /* MATCH pin: load-bearing for the whole function shape */
        index = 0;
        tile_info = ((S_80024660_3 *)source_record)->unk_0C;
        ASM_KEEP(tile_info);   /* MATCH pin: load-bearing for the whole function shape */
        table_page = 0x80070000;
        ASM_USE(table_page);   /* MATCH pin: load-bearing for the whole function shape */
        path_tile_x = ((S_80024660_9 *)tile_info)->unk_24;
        path_tile_y = ((S_80024660_9 *)tile_info)->unk_25;
        last_tile_x = path_tile_x;
        scratch.saved_y = (u16) path_tile_y;
        do {
            tile_x = (s16)path_tile_x;
            tile_y = (s16)path_tile_y;
            if ((func_800A44E0((tile_x << 6) & 0xFFC0, (tile_y << 6) & 0xFFC0, ((S_80024660_1 *)source)->unk_88, (s16) (((Rec_func_800243B8_arg0 *)effect)->unk_0E << 9)) << 0x10) != 0) {
                break;
            }
            direction = (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_0E;
            step_table = D_8006CCD8;
            x_step_ptr = &step_table[direction];
            probe_z = (u16) ((S_80024660_1 *)source)->unk_88;
            ASM_KEEP_DEP_NV(probe_z, x_step_ptr);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            probe_z = (s16) (probe_z - 32);
            ASM_KEEP(probe_z);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            step_table = D_8006CCE8;
            probe_x_dest_y = *x_step_ptr;
            probe_y_dest_x = step_table[direction];
            probe_x_dest_y = (((tile_x + (s16)probe_x_dest_y) << 6) + 32) & 0xFFE0;
            probe_y_dest_x = (((tile_y + (s16)probe_y_dest_x) << 6) + 32) & 0xFFE0;
            floor_z = func_800BCB04(probe_x_dest_y, probe_y_dest_x, probe_z);
            if (floor_z >= 513) {
                break;
            }
            if ((s16) (floor_z - (u16) ((S_80024660_1 *)source)->unk_88) < -63) {
                break;
            }
            {
                register s32 next_x ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
                register s32 next_y ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
                register s32 step_index ASM_REG("$3");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                u16 *x_step;
                u16 *y_step;
                step_table = D_8006CCD8_2;
                step_index = (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_0E;
                index += 1;
                x_step = (u16 *) (((unsigned long) step_index << 1) + (unsigned long) step_table);
                step_table = D_8006CCE8_2;
                y_step = step_index + step_table;
                next_x = *x_step;
                next_y = *y_step;
                next_x = path_tile_x + next_x;
                path_tile_x = next_x;
                ASM_KEEP(path_tile_x);   /* MATCH pin: retail register colouring depends on it */
                next_y = path_tile_y + next_y;
                path_tile_y = next_y;
                scratch.saved_y = (u16) next_y;
                last_tile_x = next_x;
            }
        } while (index < 8);
set_path_destination:
        destination = (M2C_UNK *)&scratch;
        index = 1;
        ASM_KEEP(index);   /* MATCH pin: load-bearing for the whole function shape */
        {
            s16 *edge_steps;
            probe_y_dest_x = last_tile_x << 16;
            edge_steps = D_8006CCD8_3;
            ASM_KEEP(edge_steps);   /* MATCH pin: retail register colouring depends on it */
            probe_y_dest_x >>= 10;
            path_dist_cursor = (s16 *)((u8 *)&scratch + 2);
            probe_y_dest_x += ((edge_steps[(s16) ((Rec_func_800243B8_arg0 *)effect)->unk_0E] + 1) << 5);
            edge_steps = D_8006CCE8_3;
            ((S_80024660_8 *)destination)->unk_00.at02.v = probe_y_dest_x;
            probe_y_dest_x = (s16) probe_y_dest_x;
            saved_tile_y = scratch.saved_y;
            ASM_KEEP(saved_tile_y);   /* MATCH pin: load-bearing for the whole function shape */
            probe_x_dest_y = ((s32) (saved_tile_y << 0x10));
            probe_x_dest_y = (probe_x_dest_y >> 0xA) + ((edge_steps[(s16) ((Rec_func_800243B8_arg0 *)effect)->unk_0E] + 1) << 5);
            ((S_80024660_8 *)destination)->unk_04.at02.v = probe_x_dest_y;
            z_or_state = ((S_80024660_5 *)motion)->unk_08.at02.v + 32;
            probe_x_dest_y <<= 16;
            ((S_80024660_8 *)destination)->unk_08.at02.v = z_or_state;
            origin_x = ((S_80024660_5 *)motion)->unk_00.at02u.v;
            probe_x_dest_y >>= 16;
            path_x_dist = probe_y_dest_x - origin_x;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            if (path_x_dist >= 0) {
                goto path_x_ready;
            }
            path_x_dist = 0 - path_x_dist;
path_x_ready:
            scratch.dist[0] = path_x_dist;
            path_z_dist = z_or_state << 16;
            path_y_dist = probe_x_dest_y - ((S_80024660_5 *)motion)->unk_04.at02u.v;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            if (path_y_dist >= 0) {
                goto path_y_ready;
            }
            path_y_dist = 0 - path_y_dist;
path_y_ready:
            scratch.dist[1] = path_y_dist;
            path_z_dist >>= 16;
            path_z_dist -= ((S_80024660_5 *)motion)->unk_08.at02u.v;
            if (path_z_dist >= 0) {
                goto path_z_ready;
            }
            path_z_dist = 0 - path_z_dist;
path_z_ready:
            scratch.dist[2] = path_z_dist;
            ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = path_x_dist;
        }
scan_path_dist:
        if (path_dist_cursor[12] <= ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16) {
            goto next_path_axis;
        }
        ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = (s16) (u16) path_dist_cursor[12];
next_path_axis:
        index += 1;
        path_dist_cursor += 1;
        if (index < 3) {
            goto scan_path_dist;
        }
        path_dist_fixed = (u16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 << 0x10;
        path_frames = (path_dist_fixed >> 0x14) + (path_dist_fixed >> 0x15);
        ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = path_frames;
        if (path_frames != 0) {
            goto set_path_velocity;
        }
        ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = 1;
set_path_velocity:
        ((S_80024660_5 *)motion)->unk_0C = (s32) ((s32) (((S_80024660_8 *)destination)->unk_00.at00.v - ((S_80024660_5 *)motion)->unk_00.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
        ((S_80024660_5 *)motion)->unk_10 = (s32) ((s32) (((S_80024660_8 *)destination)->unk_04.at00.v - ((S_80024660_5 *)motion)->unk_04.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
        ((S_80024660_5 *)motion)->unk_14 = (s32) ((s32) (((S_80024660_8 *)destination)->unk_08.at00.v - ((S_80024660_5 *)motion)->unk_08.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        z_or_state = 5;
    }
spawn_children:
    ((Rec_func_800243B8_arg0 *)effect)->unk_0A = z_or_state;
    index = 0x1F;
    child_slot = effect + 0x7C;
spawn_next_child:
    ((S_80024660_10 *)child_slot)->unk_18 = func_800243B8(effect, motion, destination, (s16)index);
    index -= 1;
    child_slot -= 4;
    if (index >= 0) {
        goto spawn_next_child;
    }
    ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
    goto finish;
jt_c3:
    if ((s16) ((Rec_func_800243B8_arg0 *)effect)->unk_10 < 0x28) {
        goto finish;
    }
    func_8002403C(((S_80024660_1 *)source)->unk_60, ((Rec_func_800243B8_arg0 *)effect)->unk_09, source);
    goto advance_state;
jt_c4:
    if (((Rec_func_800243B8_arg0 *)effect)->unk_14 != 0) {
        goto finish;
    }
    D_8008346C = 0;
    (*(u16 *)((u8 *)effect + -2)) = (u16) ((*(u16 *)((u8 *)effect + -2)) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((S_80024660_11 *)(&D_800814A0))->unk_00 | 0x8000);
    goto finish;
jt_c2:
jt_c5:
    ((S_80024660_5 *)motion)->unk_00.at00.v = (s32) (((S_80024660_5 *)motion)->unk_00.at00.v + ((S_80024660_5 *)motion)->unk_0C);
    ((S_80024660_5 *)motion)->unk_04.at00.v = (s32) (((S_80024660_5 *)motion)->unk_04.at00.v + ((S_80024660_5 *)motion)->unk_10);
    ((S_80024660_5 *)motion)->unk_08.at00.v = (s32) (((S_80024660_5 *)motion)->unk_08.at00.v + ((S_80024660_5 *)motion)->unk_14);
    if ((s16) ((Rec_func_800243B8_arg0 *)effect)->unk_10 < ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16) {
        goto finish;
    }
advance_state:
    ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
    ((Rec_func_800243B8_arg0 *)effect)->unk_0A = (s16) ((u16) ((Rec_func_800243B8_arg0 *)effect)->unk_0A + 1);
    goto finish;
jt_c6:
    if ((s16) ((Rec_func_800243B8_arg0 *)effect)->unk_10 < 0x28) {
        goto finish;
    }
    ((Rec_func_800243B8_arg0 *)effect)->unk_0A = 4;
    ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
finish:
    ((Rec_func_800243B8_arg0 *)effect)->unk_14 = 0;
    return;
}
