#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

s32 dungeonCheckDiagonalSideHeight(s32, u8, u8, s16);
s32 findEligibleActorAtTileAndHeight(void *, u16, u16, s16);
s32 func_800A2CB8(void *, s32);

/* Returns the first valid candidate found while checking eight neighboring positions. */
s32 dungeonFindMonsterNeighborCandidate(void *entity, u16 x, u16 y) {
    u16 *x_offsets;
    u16 *y_offsets;
    void *entity_data;
    void *entity_ptr;
    u16 origin_x;
    u16 origin_y;
    s32 candidate;
    s32 attempt;
    s32 direction;

    entity_ptr = entity;
    origin_x = x;
    origin_y = y;
    x_offsets = dirStepX;
    y_offsets = dirStepY;
    entity_data = *(void **)((s8 *)entity_ptr - 0x14);
    direction = dungeonStatus.unk_1E & 7;
    for (attempt = 0; attempt < 8; attempt++, direction = (direction + 1) & 7) {
        candidate = findEligibleActorAtTileAndHeight(entity_ptr, (origin_x + x_offsets[direction]) & 0xFFFF, (origin_y
            + y_offsets[direction]) & 0xFFFF, *(s16 *)((s8 *)entity_ptr + 0x88));
        if (candidate != 0 && ((func_800A2CB8(entity_ptr, candidate) << 16) != 0)) {
            if (((dungeonCheckDiagonalSideHeight(direction, *(u8 *)((s8 *)entity_data + 0x24), *(u8 *)((s8 *)entity_data + 0x25),
                (s16)((u16)*(s16 *)((s8 *)entity_ptr + 0x88) - 0x20)) << 16) == 0)) {
                continue;
            }
            entity_ptr = entity;
            return candidate;
        }
    }
    return 0;
}
