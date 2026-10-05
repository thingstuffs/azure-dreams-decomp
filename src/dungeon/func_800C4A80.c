#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"
#include "shared/entity.h"

typedef struct S_800CA1E0_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} S_800CA1E0_2;   /* object in func_800CA1E0 */

extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];
s16 func_8009A350(s16 x, s16 y, s16 offset_index, u16 *flags);
s32 func_8009A540(s32 direction, s16 tile_x, s16 tile_y, s16 height);
s32 func_8009FB34(s32 point_x, s32 point_y);
s32 func_800BCB04(s32 x, s32 y, s16 min_height);

/* Checks whether a directional step is in bounds and clear of obstacles. */
s32 func_800CA1E0(u32 action_flags, EntityRec *position, S_800CA1E0_2 *object, u16 height_offset) {
    u16 tile_flags;
    s16 direction;
    u16 target_x;
    u16 target_y;
    u32 world_x;
    u32 world_y;
    MapGrid *map;
    u16 height;
    s16 room;

    direction = (action_flags >> 9) & 7;
    target_x = position->tileX + (u16)dirStepX[direction];
    map = &gameWork.map;
    if (target_x == 0 || ((1 << map->shiftX) - 1) < target_x) {
        return -1;
    }
    target_y = position->tileY + (u16)dirStepY[direction];
    if (target_y == 0 || ((1 << map->shiftY) - 1) < target_y) {
        return -1;
    }
    world_x = position->tileX << 6;
    world_y = position->tileY << 6;
    target_x = world_x + 0x20;
    height = object->unk_88;
    target_y = world_y + 0x20;
    if ((func_8009A540((u16)direction, target_x >> 6, target_y >> 6, (s16)(height - height_offset)) << 16) == 0) {
        return 0;
    }
    target_x = D_800DCEAC[direction] + target_x;
    target_y = D_800DCEBC[direction] + target_y;
    func_8009A350(position->tileX, position->tileY, direction, &tile_flags);
    if (tile_flags & 0x8002) {
        return 0;
    }
    if ((s8)position->unk_26 < 0) {
        room = func_8009FB34((position->tileX + (u16)dirStepX[direction]) & 0xFFFF, (position->tileY + (u16)dirStepY[direction]) & 0xFFFF);
        if (room >= 0 && (D_800E2970[room].flags & 2) && !(object->unk_1C & 0x2000)) {
            return 0;
        }
    }
    if ((s16)func_800BCB04(target_x, target_y, (s16)(height - height_offset)) >= 0x201) {
        return -1;
    }
    return 1;
}
