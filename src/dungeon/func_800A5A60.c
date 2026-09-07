#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

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

s32 func_800AB1C0(ObjA0 *arg0, Motion *arg1, TilePos *arg2, ObjA3 *arg3) {
    s16 temp_a1;
    s16 temp_v0;
    u16 temp_v0_2;
    s32 tile_x;
    s32 scaled_x;
    s32 adjusted_x;
    s32 adjusted_y;

    if (D_80083460.flags & 0x80) {
        ((S_800AB1C0_0 *)arg0)->unk_96 = 0;
    }
    temp_a1 = ((S_800AB1C0_0 *)arg0)->unk_96;
    if (temp_a1 != 0) {
        tile_x = ((Rec_D_80082E80 *)arg2)->unk_24;
        ASM_KEEP(tile_x);   /* MATCH pin: retail schedule: same instructions, different order without it */
        adjusted_x = ((S_800AB1C0_2 *)arg1)->unk_02;
        adjusted_x -= 0x20;
        scaled_x = tile_x << 6;
        ((S_800AB1C0_2 *)arg1)->unk_0C =
            (s32)(((s32)((scaled_x - adjusted_x) << 0x10)) /
                  temp_a1);
        adjusted_y = ((S_800AB1C0_2 *)arg1)->unk_06;
        adjusted_y -= 0x20;
        ((S_800AB1C0_2 *)arg1)->unk_10 =
            (s32)(((s32)(((((Rec_D_80082E80 *)arg2)->unk_25 << 6) - adjusted_y)
                          << 0x10)) /
                  (s16)((S_800AB1C0_0 *)arg0)->unk_96);
    }
    temp_v0 = (u16)((S_800AB1C0_0 *)arg0)->unk_96 - 1;
    ((S_800AB1C0_0 *)arg0)->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_800AB1C0_2 *)arg1)->unk_14 = 0;
        ((S_800AB1C0_2 *)arg1)->unk_10 = 0;
        ((S_800AB1C0_2 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24,
                      ((Rec_D_80082E80 *)arg2)->unk_25);
        if (D_80083460.count != 0) {
            D_80083460.count = (s16)((u16)D_80083460.count - 1);
        }
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x2000) {
            ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v =
                (u16)(((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x7FFF);
        }
        if (D_80083460.flags & 0x80) {
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 =
                (s32)(((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0xBFFFFFFF);
            temp_v0_2 = func_800BCB04(
                (((Rec_D_80082E80 *)arg2)->unk_24 << 6) | 0x20,
                (((Rec_D_80082E80 *)arg2)->unk_25 << 6) | 0x20,
                (s16)(((Rec_D_800E3D7C *)arg3)->unk_88.as_u16 - 0x20));
            ((S_800AB1C0_0 *)arg0)->unk_90.at02.v =
                (u16)(((S_800AB1C0_0 *)arg0)->unk_90.at02.v +
                      (((Rec_D_800E3D7C *)arg3)->unk_88.as_u16 - temp_v0_2));
            ((Rec_D_800E3D7C *)arg3)->unk_88.as_u16 = temp_v0_2;
            if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x40000)) {
                ((S_800AB1C0_0 *)arg0)->unk_90.at00.v = 0;
            }
        }
        return 1;
    }
    return 0;
}
