#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
} Func95440Input;

typedef struct {
    u8 pad0[0x24];
    u8 x;
    u8 y;
} Func95440Actor;

typedef struct {
    u8 pad0[0x14];
    u32 mask14;
    u8 pad18[4];
    u32 flags1c;
    u8 pad20[0x4c];
    s16 value6c;
    s16 value6e;
} Func95440Object;


extern s32 func_8009A540(u32, u32, u32, s32);
extern s32 func_8009A350(u8, u8, u32, u16 *);
extern s32 func_800BCB04(s32, s32, s32);
extern Func95440Object *func_8009B25C(s32, s32, s32, s32);

/* Checks the adjacent tile and classifies its height relative to the source height. */
s32 func_8009ABA0(u32 direction_bits, Func95440Input *position, Func95440Actor *actor, u32 source_height, s32 height_offset) {
    u16 tile_flags;
    s32 target_height;
    s16 initial_height;
    s32 saved_height;
    u32 direction;
    s32 y;
    s32 x;
    u16 wrapped_x;
    u16 wrapped_y;
    s32 signed_height;
    s32 level_result;
    Func95440Object *object;

    direction = (direction_bits >> 9) & 7;
    x = position->x;
    y = position->y;
    initial_height = (s16)(source_height - height_offset);
    saved_height = source_height;
    if ((func_8009A540(direction, x >> 6, y >> 6, initial_height) << 16) == 0) {
        return -2;
    }
    target_height = initial_height;

    x += dirStepX[direction] << 6;
    y += dirStepY[direction] << 6;
    if ((func_8009A350(actor->x, actor->y, direction, &tile_flags) << 16) == 0) {
        return 0;
    }
    if (tile_flags & 0x8000) {
        return -2;
    }
    if (tile_flags & 0x400) {
        return 0;
    }

    if (tile_flags & 0x3300) {
        wrapped_x = x;
        wrapped_y = y;
        target_height = func_800BCB04(wrapped_x, wrapped_y, target_height);
        x = wrapped_x;
        y = wrapped_y;
        object = func_8009B25C(((s32)D_800814A8), x >> 6, y >> 6, (s16)target_height);
        if (object != 0) {
            if (!(object->flags1c & 0x2000)) {
                goto object_failure;
            }
            if (object->flags1c & 0x628) {
                goto object_failure;
            }
            if (object->mask14 & 0x40000000) {
                goto object_failure;
            }
            if (object->value6c + ((object->value6e * dungeonStatus.unk_00) >> 8) < 0x100) {
                goto object_failure;
            }
        }
        goto compare;

object_failure:
        return -1;
    } else {
        target_height = func_800BCB04(x & 0xffff, y & 0xffff, target_height);
    }

compare:
    signed_height = (target_height << 16) >> 16;
    if (signed_height < 0x200) {
        level_result = 1;
        if (signed_height == (s16)saved_height) {
            return level_result;
        }
        if ((s16)saved_height < signed_height) {
            if ((signed_height - (s16)saved_height) >= 0x41) {
                return 4;
            }
            return 2;
        }
        return 3;
    }
    return -2;
}
