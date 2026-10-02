#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"

typedef struct {
    u8 pad24[0x24];
    u8 x;
    u8 y;
    s8 flag;
} FuncArg1;

typedef struct {
    u8 pad1c[0x1c];
    u32 flags;
    u8 pad20[0x68];
    u16 height;
} FuncArg2;

typedef struct {
    u16 value;
    u8 pad02[6];
} StackU16;

extern s16 D_800DCEAC[];
extern s16 D_800DCEBC[];
extern s32 func_8009A350(s32, s32, s32, u16 *);
extern s32 func_8009A540(s32, s32, s32, s16);
s32 func_8009B25C(FuncArg2 *, s32, s32, s32);
s16 func_8009FB34(u16, u16);
s32 func_800BCB04(s32, s32, s16);

/* Check a directional move against map bounds, collisions, monsters, and floor height. */
s32 func_8009A8C0(u32 move_flags, FuncArg1 *actor, FuncArg2 *body, u16 height_offset) {
    StackU16 collision;
    s16 monster_index;
    /* The actor is finished before the floor-height samples begin. */
    union {
        FuncArg1 *actor;
        s32 height;
    } actor_or_height;
    s32 target_height;
    u32 direction_bits;
    u8 *x_steps;
    s32 direction;
    s32 coord_work;
    s32 coord_work_2;
    u32 target_x;
    s32 step_offset;
    u32 offset_work;
    s32 result;
    register s32 coord_or_height ASM_REG("$3");
    s32 next_x;
    MapGrid *map_limits;
    u16 *x_step;
    u16 *y_step;
    u16 height;
    u32 target_y_u16;
    register u32 center_y ASM_REG("$20");
    u8 direction_arg;
    s16 direction_or_x;
    register s32 tile_coord ASM_REG("$5");
    s32 y_or_direction;
    u32 collision_out;
    u32 body_addr;
    u16 tile_x8;
    u16 tile_y8;

    actor_or_height.actor = actor;
    direction_bits = (move_flags >> 9) & 7;
    direction_arg = direction_bits;
    direction = (s16)direction_bits;
    x_steps = (u8 *)dirStepX;
    step_offset = direction * 2;
    x_step = (u16 *)((s32)step_offset + (s32)x_steps);
    coord_or_height = actor_or_height.actor->x;
    offset_work = *x_step;
    direction_or_x = direction_arg;
    target_x = coord_or_height + offset_work;
    map_limits = &gameWork.map;
    next_x = target_x & 0xFFFF;
    if (next_x != 0) {
        if (((1 << map_limits->shiftX) - 1) >= next_x) {
            y_step = (u16 *)((u8 *)dirStepY + step_offset);
            coord_or_height = actor_or_height.actor->y;
            offset_work = *y_step;
            coord_work = coord_or_height + offset_work;
            coord_or_height = coord_work & 0xFFFF;
            if (coord_or_height != 0) {
                if (((1 << map_limits->shiftY) - 1) >= coord_or_height) {
                    tile_x8 = actor_or_height.actor->x;
                    tile_y8 = actor_or_height.actor->y;
                    coord_or_height = tile_x8;
                    offset_work = tile_y8;
                    body_addr = (u32)body;
                    height = (*(u16 *)((u8 *)body_addr + 0x88));
                    coord_or_height <<= 6;
                    tile_coord = (u32)coord_or_height >> 6;
                    offset_work <<= 6;
                    y_or_direction = (u32)offset_work >> 6;
                    coord_work_2 = coord_or_height + 0x20;
                    offset_work += 0x20;
                    center_y = offset_work;
                    result = func_8009A540(direction_or_x, tile_coord, y_or_direction,
                                           (s16)(height - height_offset)) << 0x10;
                    if (result != 0) {
                        y_or_direction = direction;
                        collision_out = (u32)&collision.value;
                        {
                            u16 *pa = (u16 *)((u8 *)D_800DCEAC + step_offset);
                            u16 *pb = (u16 *)((u8 *)D_800DCEBC + step_offset);
                            target_x = *pa + coord_work_2;
                            coord_work = *pb + center_y;
                        }
                        func_8009A350(actor_or_height.actor->x, actor_or_height.actor->y,
                                     y_or_direction, (u16 *)collision_out);
                        if ((collision.value & 0x8002) != 0) {
                            result = 0;
                            return 0;
                        }
                    } else {
                        result = 0;
                        return 0;
                    }
                    if ((actor_or_height.actor->flag >= 0) ||
                        (monster_index = func_8009FB34((actor_or_height.actor->x + *x_step) & 0xFFFF,
                                                       (actor_or_height.actor->y + *y_step) & 0xFFFF),
                         (monster_index < 0)) ||
                        !(D_800E2970[monster_index].flags & 2) ||
                        (result = 0, ((body_addr = (u32)body,
                                       ((FuncArg2 *)body_addr)->flags & 0x2000) != 0))) {
                        if (collision.value & 0x3300) {
                            target_x &= 0xFFFF;
                            if (collision.value & 0x40) {
                                {
                                    u16 sample_x;
                                    sample_x = target_x;
                                    target_y_u16 = coord_work & 0xFFFF;
                                    actor_or_height.height = func_800BCB04(
                                        sample_x, target_y_u16, (s16)(height - height_offset));
                                }
                                tile_coord = target_x >> 6;
                                y_or_direction = target_y_u16 >> 6;
                                target_height = (s16)actor_or_height.height;
                                if (target_height >= 0x201) {
                                    body_addr = (u32)body;
                                    target_height = (s16)((FuncArg2 *)body_addr)->height;
                                }
                                /* Target X is dead after the tile argument is formed. */
                                target_x = func_8009B25C(body, tile_coord, y_or_direction, target_height);
                                if (target_x == 0) {
                                    goto check_height;
                                }
                            }
move_failed:
                            ASM_SCHED_BARRIER();
                            result = -1;
                            return -1;
                        }
                        {
                            actor_or_height.height = func_800BCB04(
                                target_x & 0xFFFF, coord_work & 0xFFFF, (s16)(height - height_offset));
                        }
check_height:
                        result = -1;
                        coord_or_height = actor_or_height.height << 0x10;
                        if ((coord_or_height >> 0x10) < 0x201) {
                            result = 1;
                        }
                        return result;
                    }
                    return result;
                }
            }
        }
        return -1;
    }
    goto move_failed;
}
