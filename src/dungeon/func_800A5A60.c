#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

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


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

void func_800A2B04(Motion *, s32, s32);
u16 func_800BCB04(s32, s32, s32);

/* Update motion toward the target tile and finalize movement when the countdown expires. */
s32 func_800AB1C0(ObjA0 *move_state, Motion *motion, TilePos *target_tile, EntityRec *actor) {
    s16 frames_left;
    s16 next_frames;
    u16 new_height;
    s32 tile_x;
    s32 scaled_x;
    s32 adjusted_x;
    s32 adjusted_y;

    if (dungeonStatus.flags & 0x80) {
        ((S_800AB1C0_0 *)move_state)->unk_96 = 0;
    }
    frames_left = ((S_800AB1C0_0 *)move_state)->unk_96;
    if (frames_left != 0) {
        tile_x = ((Rec_D_80082E80 *)target_tile)->unk_24;
        scaled_x = tile_x << 6;
        adjusted_x = ((S_800AB1C0_2 *)motion)->unk_02 - 0x20 + scaled_x;
        adjusted_x -= scaled_x;
        ((S_800AB1C0_2 *)motion)->unk_0C =
            (s32)(((s32)((scaled_x - adjusted_x) << 0x10)) /
                  frames_left);
        adjusted_y = ((S_800AB1C0_2 *)motion)->unk_06;
        adjusted_y -= 0x20;
        ((S_800AB1C0_2 *)motion)->unk_10 =
            (s32)(((s32)(((((Rec_D_80082E80 *)target_tile)->unk_25 << 6) - adjusted_y)
                          << 0x10)) /
                  (s16)((S_800AB1C0_0 *)move_state)->unk_96);
    }
    next_frames = (u16)((S_800AB1C0_0 *)move_state)->unk_96 - 1;
    ((S_800AB1C0_0 *)move_state)->unk_96 = next_frames;
    if ((next_frames << 0x10) <= 0) {
        ((S_800AB1C0_2 *)motion)->unk_14 = 0;
        ((S_800AB1C0_2 *)motion)->unk_10 = 0;
        ((S_800AB1C0_2 *)motion)->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)target_tile)->unk_24,
                      ((Rec_D_80082E80 *)target_tile)->unk_25);
        if (dungeonStatus.unk_08 != 0) {
            dungeonStatus.unk_08 = (s16)((u16)dungeonStatus.unk_08 - 1);
        }
        if (actor->flags1C & 0x2000) {
            actor->unk_46 =
                (u16)(actor->unk_46 & 0x7FFF);
        }
        if (dungeonStatus.flags & 0x80) {
            actor->flags1C =
                (s32)(actor->flags1C & 0xBFFFFFFF);
            new_height = func_800BCB04(
                (((Rec_D_80082E80 *)target_tile)->unk_24 << 6) | 0x20,
                (((Rec_D_80082E80 *)target_tile)->unk_25 << 6) | 0x20,
                (s16)(((u16)actor->unk_88) - 0x20));
            ((S_800AB1C0_0 *)move_state)->unk_90.at02.v =
                (u16)(((S_800AB1C0_0 *)move_state)->unk_90.at02.v +
                      (((u16)actor->unk_88) - new_height));
            actor->unk_88 = new_height;
            if (!(actor->flags1C & 0x40000)) {
                ((S_800AB1C0_0 *)move_state)->unk_90.at00.v = 0;
            }
        }
        return 1;
    }
    return 0;
}
