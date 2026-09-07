#include "common.h"

typedef s32 M2C_UNK;
typedef struct ObjA0 ObjA0;
typedef struct Motion Motion;
typedef struct TilePos TilePos;
typedef struct ObjA3 ObjA3;
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
        M2C_FIELD(arg0, s16 *, 0x96) = 0;
    }
    temp_a1 = M2C_FIELD(arg0, s16 *, 0x96);
    if (temp_a1 != 0) {
        tile_x = M2C_FIELD(arg2, u8 *, 0x24);
        ASM_KEEP(tile_x);
        adjusted_x = M2C_FIELD(arg1, s16 *, 2);
        adjusted_x -= 0x20;
        scaled_x = tile_x << 6;
        M2C_FIELD(arg1, s32 *, 0xC) =
            (s32)(((s32)((scaled_x - adjusted_x) << 0x10)) /
                  temp_a1);
        adjusted_y = M2C_FIELD(arg1, s16 *, 6);
        adjusted_y -= 0x20;
        M2C_FIELD(arg1, s32 *, 0x10) =
            (s32)(((s32)(((M2C_FIELD(arg2, u8 *, 0x25) << 6) - adjusted_y)
                          << 0x10)) /
                  (s16)M2C_FIELD(arg0, s16 *, 0x96));
    }
    temp_v0 = (u16)M2C_FIELD(arg0, s16 *, 0x96) - 1;
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24),
                      M2C_FIELD(arg2, u8 *, 0x25));
        if (D_80083460.count != 0) {
            D_80083460.count = (s16)((u16)D_80083460.count - 1);
        }
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
            M2C_FIELD(arg3, u16 *, 0x46) =
                (u16)(M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
        }
        if (D_80083460.flags & 0x80) {
            M2C_FIELD(arg3, s32 *, 0x1C) =
                (s32)(M2C_FIELD(arg3, s32 *, 0x1C) & 0xBFFFFFFF);
            temp_v0_2 = func_800BCB04(
                (M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20,
                (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20,
                (s16)(M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
            M2C_FIELD(arg0, u16 *, 0x92) =
                (u16)(M2C_FIELD(arg0, u16 *, 0x92) +
                      (M2C_FIELD(arg3, u16 *, 0x88) - temp_v0_2));
            M2C_FIELD(arg3, u16 *, 0x88) = temp_v0_2;
            if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x40000)) {
                M2C_FIELD(arg0, s32 *, 0x90) = 0;
            }
        }
        return 1;
    }
    return 0;
}
