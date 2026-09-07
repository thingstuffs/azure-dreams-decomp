#include "common.h"

typedef s32 M2C_UNK;
typedef struct ObjA0 ObjA0;
typedef struct Motion Motion;
typedef struct TilePos TilePos;
typedef struct ObjA3 ObjA3;

typedef struct S_800AB1C0_0 {
    u8 pad_00[0x90];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x2];
    s16 unk_96;
} S_800AB1C0_0;   /* arg0 in func_800AB1C0 */

typedef struct S_800AB1C0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800AB1C0_1;   /* arg2 in func_800AB1C0 */

typedef struct S_800AB1C0_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800AB1C0_2;   /* arg1 in func_800AB1C0 */

typedef struct S_800AB1C0_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x26];
    u16 unk_46;
    u8 pad_48[0x40];
    u16 unk_88;
} S_800AB1C0_3;   /* arg3 in func_800AB1C0 */

typedef struct {
    u16 pad00;
    u16 flags;
    u8 pad04[4];
    s16 count;
} DungeonState;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

void func_800A2B04(Motion *, s32, s32);
u16 func_800BCB04(s32, s32, s32);
extern DungeonState D_80083460;

/* Update motion toward the target tile and finalize movement when the countdown expires. */
s32 func_800AB1C0(ObjA0 *move_state, Motion *motion, TilePos *target_tile, ObjA3 *actor) {
    s16 frames_left;
    s16 next_frames;
    u16 new_height;
    s32 tile_x;
    s32 scaled_x;
    s32 adjusted_x;
    s32 adjusted_y;

    if (D_80083460.flags & 0x80) {
        ((S_800AB1C0_0 *)move_state)->unk_96 = 0;
    }
    frames_left = ((S_800AB1C0_0 *)move_state)->unk_96;
    if (frames_left != 0) {
        tile_x = ((S_800AB1C0_1 *)target_tile)->unk_24;
        ASM_KEEP(tile_x);   /* MATCH pin: retail schedule: same instructions, different order without it */
        adjusted_x = ((S_800AB1C0_2 *)motion)->unk_02;
        adjusted_x -= 0x20;
        scaled_x = tile_x << 6;
        ((S_800AB1C0_2 *)motion)->unk_0C =
            (s32)(((s32)((scaled_x - adjusted_x) << 0x10)) /
                  frames_left);
        adjusted_y = ((S_800AB1C0_2 *)motion)->unk_06;
        adjusted_y -= 0x20;
        ((S_800AB1C0_2 *)motion)->unk_10 =
            (s32)(((s32)(((((S_800AB1C0_1 *)target_tile)->unk_25 << 6) - adjusted_y)
                          << 0x10)) /
                  (s16)((S_800AB1C0_0 *)move_state)->unk_96);
    }
    next_frames = (u16)((S_800AB1C0_0 *)move_state)->unk_96 - 1;
    ((S_800AB1C0_0 *)move_state)->unk_96 = next_frames;
    if ((next_frames << 0x10) <= 0) {
        ((S_800AB1C0_2 *)motion)->unk_14 = 0;
        ((S_800AB1C0_2 *)motion)->unk_10 = 0;
        ((S_800AB1C0_2 *)motion)->unk_0C = 0;
        func_800A2B04(motion, ((S_800AB1C0_1 *)target_tile)->unk_24,
                      ((S_800AB1C0_1 *)target_tile)->unk_25);
        if (D_80083460.count != 0) {
            D_80083460.count = (s16)((u16)D_80083460.count - 1);
        }
        if (((S_800AB1C0_3 *)actor)->unk_1C & 0x2000) {
            ((S_800AB1C0_3 *)actor)->unk_46 =
                (u16)(((S_800AB1C0_3 *)actor)->unk_46 & 0x7FFF);
        }
        if (D_80083460.flags & 0x80) {
            ((S_800AB1C0_3 *)actor)->unk_1C =
                (s32)(((S_800AB1C0_3 *)actor)->unk_1C & 0xBFFFFFFF);
            new_height = func_800BCB04(
                (((S_800AB1C0_1 *)target_tile)->unk_24 << 6) | 0x20,
                (((S_800AB1C0_1 *)target_tile)->unk_25 << 6) | 0x20,
                (s16)(((S_800AB1C0_3 *)actor)->unk_88 - 0x20));
            ((S_800AB1C0_0 *)move_state)->unk_90.at02.v =
                (u16)(((S_800AB1C0_0 *)move_state)->unk_90.at02.v +
                      (((S_800AB1C0_3 *)actor)->unk_88 - new_height));
            ((S_800AB1C0_3 *)actor)->unk_88 = new_height;
            if (!(((S_800AB1C0_3 *)actor)->unk_1C & 0x40000)) {
                ((S_800AB1C0_0 *)move_state)->unk_90.at00.v = 0;
            }
        }
        return 1;
    }
    return 0;
}
