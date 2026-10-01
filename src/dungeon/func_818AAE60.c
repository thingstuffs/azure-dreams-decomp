#include "common.h"
#include "shared/object_flags.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_800243B8_arg0.h"
extern int abs(int);


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
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_00;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
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

typedef struct S_80024660_12 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80024660_12;   /* ((S_80024660_3 *)temp_s0)->unk_0C in func_80024660 */


M2C_UNK func_8002403C();
s32 func_800243B8();
s32 func_8003DE58();
s32 func_800A44E0(s32, s32, s16, s32);
M2C_UNK func_800A56E0();
s32 func_800BCB04(s32, s32, s16);

typedef struct {
    s32 pos[3];
    u8 pad18[0xC];
    u16 dist[3];
} Func818AAE60Scratch;

/* Update an effect that travels toward a target or along a clear path and spawns child effects. */
void func_80024660(void *effect, void *motion, void *appearance) {
    Func818AAE60Scratch scratch;
    s16 *target_dist_cursor;
    s16 *path_dist_cursor;
    M2C_UNK *destination;
    s32 state;
    s16 target_frames;
    s16 path_frames;
    s32 target_x_dist;
    s32 target_dist_fixed;
    s32 path_dist_fixed;
    s32 index;
    s32 axis_dist;
    s32 origin_coord;
    void *tile_x;
    u16 source_z;
    void *source_info;
    void *source_record;
    void *source;
    void *target;
    void *source_pos;
    u16 elapsed;

    elapsed = ((Rec_func_800243B8_arg0 *)effect)->unk_10;
    state = ((Rec_func_800243B8_arg0 *)effect)->unk_0A;
    source = ((Rec_func_800243B8_arg0 *)effect)->unk_00;
    ((Rec_func_800243B8_arg0 *)effect)->unk_10 = elapsed + 1;
    switch (state) {
    case 0:
        ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
        ((Rec_func_800243B8_arg0 *)effect)->unk_0A = (s16) ((u16) ((Rec_func_800243B8_arg0 *)effect)->unk_0A + 1);
        ((Rec_func_800243B8_arg0 *)effect)->unk_0E = (u16) (((u16) ((S_80024660_1 *)source)->unk_2A >> 9) & 7);
        ((S_80024660_2 *)appearance)->unk_0C = 0x808080;
    case 1:
        source_record = source - 0x20;
        source_info = ((S_80024660_3 *)source_record)->unk_0C;
        if (func_8003DE58(((S_80024660_4 *)source_info)->unk_08, source_info, &scratch.dist[0], 0) == 0) {
            if (!(((S_80024660_12 *)(((S_80024660_3 *)source_record)->unk_0C))->unk_14 & 0x8000)) {
                goto finish;
            }
        }
        source_pos = ((S_80024660_3 *)source_record)->unk_08;
        ((S_80024660_5 *)motion)->unk_00.at02.v = (u16) ((S_80024660_6 *)source_pos)->unk_02;
        ((S_80024660_5 *)motion)->unk_04.at02.v = (u16) ((S_80024660_6 *)source_pos)->unk_06;
        source_z = ((S_80024660_6 *)source_pos)->unk_0A;
        ((S_80024660_5 *)motion)->unk_08.at02.v = source_z;
        if (!(((S_80024660_12 *)(((S_80024660_3 *)source_record)->unk_0C))->unk_14 & 0x8000)) {
            ((S_80024660_5 *)motion)->unk_00.at02.v = (u16) (((S_80024660_5 *)motion)->unk_00.at02.v + scratch.dist[0]);
            ((S_80024660_5 *)motion)->unk_04.at02.v = (u16) (((S_80024660_5 *)motion)->unk_04.at02.v + scratch.dist[1]);
            ((S_80024660_5 *)motion)->unk_08.at02.v = (u16) (((S_80024660_5 *)motion)->unk_08.at02.v + scratch.dist[2]);
        } else {
            ((S_80024660_5 *)motion)->unk_08.at02.v = source_z - 0x40;
        }
        if (!(*((Rec_func_800243B8_arg0 *)effect)->unk_04 & 0x80)) {
            goto finish;
        }
        target = ((S_80024660_1 *)source)->unk_60;
        index = 1;
        if (target != NULL) {
            destination = ((S_80024660_7_pre *)target)[-1].unk_00;
            target_x_dist = ((S_80024660_8 *)destination)->unk_00.at02.v;
            target_x_dist -= ((S_80024660_5 *)motion)->unk_00.at02u.v;
            if (target_x_dist < 0) {
                target_x_dist = 0 - target_x_dist;
            }
            scratch.dist[0] = (u16) target_x_dist;
            axis_dist = ((S_80024660_8 *)destination)->unk_04.at02.v;
            origin_coord = ((S_80024660_5 *)motion)->unk_04.at02u.v;
            target_dist_cursor = (s16 *)((u8 *)&scratch + 2);
            axis_dist -= origin_coord;
            axis_dist = abs(axis_dist);
            scratch.dist[1] = (u16) axis_dist;
            origin_coord = ((S_80024660_5 *)motion)->unk_08.at02u.v;
            origin_coord += 0x20;
            axis_dist = ((S_80024660_8 *)destination)->unk_08.at02.v - origin_coord;
            axis_dist = abs(axis_dist);
            scratch.dist[2] = (u16) axis_dist;
            ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = target_x_dist;
            do {
                if (target_dist_cursor[12] > ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16) {
                    ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = (s16) (u16) target_dist_cursor[12];
                }
                index += 1;
                target_dist_cursor += 1;
            } while (index < 3);
            target_dist_fixed = (u16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 << 0x10;
            target_frames = (target_dist_fixed >> 0x14) + (target_dist_fixed >> 0x15);
            ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = target_frames;
            if (target_frames == 0) {
                ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = 1;
            }
            ((S_80024660_5 *)motion)->unk_0C = (s32) ((s32) (((S_80024660_8 *)destination)->unk_00.at00.v
                - ((S_80024660_5 *)motion)->unk_00.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
            ((S_80024660_5 *)motion)->unk_10 = (s32) ((s32) (((S_80024660_8 *)destination)->unk_04.at00.v
                - ((S_80024660_5 *)motion)->unk_04.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
            ((S_80024660_5 *)motion)->unk_14 = (s32) ((s32) (((S_80024660_8 *)destination)->unk_08.at00.v
                - ((S_80024660_5 *)motion)->unk_08.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
            func_800A56E0(0x300);
            ((Rec_func_800243B8_arg0 *)effect)->unk_0A += 1;
        } else {
            u16 path_x;
            u16 path_y;
            s16 grid_x;
            s16 grid_y;
            u16 last_x;
            u16 saved_y;
            s32 probe_z;
            s16 *step_y;
            s32 floor_height;
            s32 dest_x;
            s32 dest_y;

            index = 0;
            path_y = ((S_80024660_9 *)((S_80024660_3 *)source_record)->unk_0C)->unk_25;
            path_x = ((S_80024660_9 *)((S_80024660_3 *)source_record)->unk_0C)->unk_24;
            saved_y = path_y;
            last_x = path_x;
            while (index < 8) {
                grid_x = (s16)path_x;
                grid_y = (s16)path_y;
                if ((s16)func_800A44E0((grid_x << 6) & 0xFFC0, (grid_y << 6) & 0xFFC0,
                        ((S_80024660_1 *)source)->unk_88,
                        (s16)(((Rec_func_800243B8_arg0 *)effect)->unk_0E << 9)) != 0) {
                    break;
                }
                source_pos = &dirStepX[(s16)((Rec_func_800243B8_arg0 *)effect)->unk_0E];
                probe_z = (u16)((S_80024660_1 *)source)->unk_88;
                probe_z -= 32;
                probe_z = (u32)probe_z << 16;
                probe_z >>= 16;
                step_y = &dirStepY[(s16)((Rec_func_800243B8_arg0 *)effect)->unk_0E];
                floor_height = func_800BCB04(((grid_x + *(s16 *)source_pos) << 6) + 32 & 0xFFE0,
                    ((grid_y + *step_y) << 6) + 32 & 0xFFE0, probe_z);
                if ((s16)floor_height >= 513 ||
                    (s16)(floor_height - ((S_80024660_1 *)source)->unk_88) < -63) {
                    break;
                }
                index++;
                path_x += dirStepX[(s16)((Rec_func_800243B8_arg0 *)effect)->unk_0E];
                path_y += dirStepY[(s16)((Rec_func_800243B8_arg0 *)effect)->unk_0E];
                saved_y = path_y;
                last_x = path_x;
            }
            destination = (M2C_UNK *)&scratch;
            index = 1;
            path_dist_cursor = (s16 *)((u8 *)&scratch + 2);
            dest_x = ((last_x << 16) >> 10) + ((dirStepX[(s16)((Rec_func_800243B8_arg0 *)effect)->unk_0E] + 1) << 5);
            ((S_80024660_8 *)destination)->unk_00.at02.v = dest_x;
            dest_y = ((saved_y << 16) >> 10) + ((dirStepY[(s16)((Rec_func_800243B8_arg0 *)effect)->unk_0E] + 1) << 5);
            ((S_80024660_8 *)destination)->unk_04.at02.v = dest_y;
            ((S_80024660_8 *)destination)->unk_08.at02.v = ((S_80024660_5 *)motion)->unk_08.at02.v + 32;
            scratch.dist[0] = abs(((S_80024660_8 *)destination)->unk_00.at02.v - ((S_80024660_5 *)motion)->unk_00.at02u.v);
            scratch.dist[1] = abs(((S_80024660_8 *)destination)->unk_04.at02.v - ((S_80024660_5 *)motion)->unk_04.at02u.v);
            scratch.dist[2] = abs(((S_80024660_8 *)destination)->unk_08.at02.v - ((S_80024660_5 *)motion)->unk_08.at02u.v);
            ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = scratch.dist[0];
            do {
                if (path_dist_cursor[12] > ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16) {
                    ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = (s16) (u16) path_dist_cursor[12];
                }
                index += 1;
                path_dist_cursor += 1;
            } while (index < 3);
            path_dist_fixed = (u16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 << 0x10;
            path_frames = (path_dist_fixed >> 0x14) + (path_dist_fixed >> 0x15);
            ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = path_frames;
            if (path_frames == 0) {
                ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16 = 1;
            }
            ((S_80024660_5 *)motion)->unk_0C = (s32) ((s32) (((S_80024660_8 *)destination)->unk_00.at00.v
                - ((S_80024660_5 *)motion)->unk_00.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
            ((S_80024660_5 *)motion)->unk_10 = (s32) ((s32) (((S_80024660_8 *)destination)->unk_04.at00.v
                - ((S_80024660_5 *)motion)->unk_04.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
            ((S_80024660_5 *)motion)->unk_14 = (s32) ((s32) (((S_80024660_8 *)destination)->unk_08.at00.v
                - ((S_80024660_5 *)motion)->unk_08.at00.v) / (s16) ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16);
            ((Rec_func_800243B8_arg0 *)effect)->unk_0A = 5;
        }
        index = 0x1F;
        tile_x = effect + 0x7C;
        do {
            ((S_80024660_10 *)tile_x)->unk_18 = func_800243B8(effect, motion, destination, (s16)index);
            index -= 1;
            tile_x -= 4;
        } while (index >= 0);
        ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
        break;
    case 3:
        if ((s16) ((Rec_func_800243B8_arg0 *)effect)->unk_10 < 0x28) {
            break;
        }
        func_8002403C(((S_80024660_1 *)source)->unk_60, ((Rec_func_800243B8_arg0 *)effect)->unk_09, source);
        ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
        ((Rec_func_800243B8_arg0 *)effect)->unk_0A = (s16) ((u16) ((Rec_func_800243B8_arg0 *)effect)->unk_0A + 1);
        break;
    case 4:
        if (((Rec_func_800243B8_arg0 *)effect)->unk_14 != 0) {
            break;
        }
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)effect + -2)) = (u16) ((*(u16 *)((u8 *)effect + -2)) | 0x8000);
        (*(s32 *)&objectFlagBlock.flags) = (s32) (objectFlagBlock.flags | 0x8000);
        break;
    case 2:
        ((S_80024660_5 *)motion)->unk_00.at00.v = (s32) (((S_80024660_5 *)motion)->unk_00.at00.v
            + ((S_80024660_5 *)motion)->unk_0C);
        ((S_80024660_5 *)motion)->unk_04.at00.v = (s32) (((S_80024660_5 *)motion)->unk_04.at00.v
            + ((S_80024660_5 *)motion)->unk_10);
        ((S_80024660_5 *)motion)->unk_08.at00.v = (s32) (((S_80024660_5 *)motion)->unk_08.at00.v
            + ((S_80024660_5 *)motion)->unk_14);
        if ((s16) ((Rec_func_800243B8_arg0 *)effect)->unk_10 < ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16) {
            break;
        }
        ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
        ((Rec_func_800243B8_arg0 *)effect)->unk_0A = (s16) ((u16) ((Rec_func_800243B8_arg0 *)effect)->unk_0A + 1);
        break;
    case 5:
        ((S_80024660_5 *)motion)->unk_00.at00.v = (s32) (((S_80024660_5 *)motion)->unk_00.at00.v
            + ((S_80024660_5 *)motion)->unk_0C);
        ((S_80024660_5 *)motion)->unk_04.at00.v = (s32) (((S_80024660_5 *)motion)->unk_04.at00.v
            + ((S_80024660_5 *)motion)->unk_10);
        ((S_80024660_5 *)motion)->unk_08.at00.v = (s32) (((S_80024660_5 *)motion)->unk_08.at00.v
            + ((S_80024660_5 *)motion)->unk_14);
        if ((s16) ((Rec_func_800243B8_arg0 *)effect)->unk_10 < ((Rec_func_800243B8_arg0 *)effect)->unk_12.as_s16) {
            break;
        }
        ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
        ((Rec_func_800243B8_arg0 *)effect)->unk_0A = (s16) ((u16) ((Rec_func_800243B8_arg0 *)effect)->unk_0A + 1);
        break;
    case 6:
        if ((s16) ((Rec_func_800243B8_arg0 *)effect)->unk_10 < 0x28) {
            break;
        }
        ((Rec_func_800243B8_arg0 *)effect)->unk_0A = 4;
        ((Rec_func_800243B8_arg0 *)effect)->unk_10 = 0U;
    default:
        break;
    }
finish:
    ((Rec_func_800243B8_arg0 *)effect)->unk_14 = 0;
    return;
}
