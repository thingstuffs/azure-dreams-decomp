#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"

typedef struct S_800CA444_0 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    s8 unk_26;
} S_800CA444_0;   /* arg2 in func_800CA444 */

typedef struct S_800CA444_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    u16 unk_88;
} S_800CA444_1;   /* arg3 in func_800CA444 */

typedef struct S_800CA444_2 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    s8 unk_9C;
} S_800CA444_2;   /* arg0 in func_800CA444 */

typedef struct S_800CA444_3 {
    s16 unk_00;
} S_800CA444_3;   /* ((s32) (var_s1 << 0x10) >> 0xF) + (u32) temp_s4 in func_800CA444 */

typedef struct S_800CA444_4 {
    u8 pad_00[0x58];
    s32 unk_58;
} S_800CA444_4;   /* *D_800814A8 in func_800CA444 */

typedef struct S_800CA444_5 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_800CA444_5;   /* (arg3 + (((S_800CA444_1 *)arg3)->unk_71 & 0x7F)) in func_800CA444 */


typedef struct {
    u8 pad_00[0xC];
    u16 flags;
    u8 pad_0E[6];
} DungeonTableEntry;

extern s16 D_8006CD00[];
s32 func_800A0E6C();
s32 func_800A19E4();
void func_800A9A0C();
s32 func_8009A180();
s16 func_800BCB04();
s32 func_800CA1E0();

/* Find a movement direction, record the tile, and update the actor's position and height. */
void func_800CA444(void *motion, s32 unused, S_800CA444_0 *tile, void *actor) {
    s16 next_heading;
    s16 height;
    s16 scan_result;
    s32 heading;
    s32 heading_offset;
    s16 *heading_offsets;
    TileObject *map_state;
    s32 direction_index;
    s8 tile_type;

    if (dungeonStatus.flags & 0x4000) {
        func_800A9A0C(actor);
        return;
    }
    if (!(dungeonStatus.flags & 0x2000)) {
        return;
    }
    func_800A19E4(tile, actor, 3, 6, motion + 0x9C);
    tile_type = tile->unk_26;
    if (tile_type >= 0 && (D_800E2970[tile_type].flags & 2)) {
        func_800A0E6C(tile, ((S_800CA444_2 *)motion)->unk_9C, actor, motion + 0x98);
    } else if (!(((S_800CA444_1 *)actor)->unk_46 & 0x8000)) {
        func_800A0E6C(tile, ((S_800CA444_2 *)motion)->unk_9C, actor, motion + 0x98);
    }
    scan_result = 0;
    heading_offsets = D_8006CD00;
    map_state = &D_80082E80;
    for (; scan_result < 8; scan_result++) {
        heading = ((S_800CA444_1 *)actor)->unk_2A;
        if (((S_800CA444_2 *)motion)->unk_98 & 2) {
            heading_offset = heading_offsets[scan_result];
            next_heading = heading - heading_offset;
        } else {
            heading_offset = heading_offsets[scan_result];
            next_heading = heading + heading_offset;
        }
        if ((func_800CA1E0(next_heading, tile, actor, 0x20) << 0x10) > 0) {
            ((S_800CA444_1 *)actor)->unk_2A = next_heading;
            ((S_800CA444_5 *)((actor + (((S_800CA444_1 *)actor)->unk_71 & 0x7F))))->unk_74 = tile->unk_24.at00.v;
            ((S_800CA444_5 *)((actor + (((S_800CA444_1 *)actor)->unk_71 & 0x7F))))->unk_7C = tile->unk_24.at01.v;
            ((S_800CA444_1 *)actor)->unk_71++;
            direction_index = (((u16) ((S_800CA444_1 *)actor)->unk_2A) >> 9) & 7;
            tile->unk_24.at00.v += dirStepX[direction_index];
            tile->unk_24.at01.v += dirStepY[direction_index];
            break;
        }
        if (scan_result == 0 && *(u16 *)(&map_state->tileX) != tile->unk_24.at00u.v) {
            if ((func_8009A180(actor, ((S_800CA444_4 *)(((int)D_800814A8)))->unk_58 + 0x20) << 0x10) != 0) {
                return;
            }
        }
    }

    if (scan_result >= 8) {
        ((S_800CA444_1 *)actor)->unk_71 = (u8) (((S_800CA444_1 *)actor)->unk_71 & 0x7F);
        ((S_800CA444_1 *)actor)->unk_46 = (u16) (((S_800CA444_1 *)actor)->unk_46 & 0x7FFF);
        func_800A9A0C(actor);
        return;
    }
    ((S_800CA444_1 *)actor)->unk_46 = (u16) (((S_800CA444_1 *)actor)->unk_46 & 0x7FFF);
    ((S_800CA444_2 *)motion)->unk_9C = (s8) (u8) tile->unk_26;
    ((S_800CA444_1 *)actor)->unk_6D.u = (u8) (((S_800CA444_1 *)actor)->unk_6D.u - 1);
    dungeonStatus.unk_08 = (u16) (((u16)dungeonStatus.unk_08) + 1);
    if (((S_800CA444_1 *)actor)->unk_6D.s == 0) {
        ((S_800CA444_1 *)actor)->unk_71 = (u8) (((S_800CA444_1 *)actor)->unk_71 & 0x7F);
        return;
    }
    scan_result = func_800BCB04((tile->unk_24.at00.v << 6) | 0x20, (tile->unk_24.at01.v << 6) | 0x20,
        (s16) (((S_800CA444_1 *)actor)->unk_88 - 0x20));
    height = scan_result;
    if (height < 0x200) {
        ((S_800CA444_1 *)actor)->unk_88 = (u16) scan_result;
    }
}
