#include "common.h"

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
    u8 pad0c[0x0c];
    u16 flags;
    u8 tail[6];
} FuncMonster;

typedef struct {
    u16 value;
    u8 pad02[6];
} StackU16;

extern s16 D_8006CCD8[];
extern s16 D_8008333C[];
extern s16 D_8006CCE8[];
extern s16 D_800DCEAC[];
extern s16 D_800DCEBC[];
extern FuncMonster D_800E2970[];
extern s32 func_8009A350(s32, s32, s32, u16 *);
extern s32 func_8009A540(s32, s32, s32, s16);
s32 func_8009B25C(FuncArg2 *, s32, s32, s32);
s16 func_8009FB34(u16, u16);
s32 func_800BCB04(s32, s32, s16);

/* Check a directional move against map bounds, collisions, monsters, and floor height. */
s32 func_8009A8C0(u32 move_flags, FuncArg1 *actor, FuncArg2 * volatile body, u16 height_offset) {
    StackU16 collision;
    u16 saved_offset;
    s16 monster_index;
    register s16 floor_height ASM_REG("$18");
    s32 target_height;
    u32 direction_bits;
    u8 *x_steps;
    s32 direction;
    s32 coord_work;
    register s32 target_x ASM_REG("$17");
    s32 step_offset;
    register s32 offset_work ASM_REG("$2");
    s32 result;
    register s32 coord_or_height ASM_REG("$3");
    s32 next_x;
    s16 *map_limits;
    u16 *x_step;
    u16 *y_step;
    u16 height;
    u32 target_y_u16;
    u32 target_x_u16;
    register u32 center_y ASM_REG("$20");
    register s32 direction_or_x ASM_REG("$4");
    register s32 tile_coord ASM_REG("$5");
    s32 y_or_direction;
    u32 collision_out;
    register u16 offset_arg ASM_REG("$7");
    u32 body_addr;

    offset_arg = height_offset;
    ASM_KEEP_NV(offset_arg);
    direction_bits = (move_flags >> 9) & 7;
    direction = direction_bits;
    ASM_KEEP_NV(direction);
    x_steps = (u8 *)D_8006CCD8;
    step_offset = direction * 2;
    x_step = (u16 *)((s32)step_offset + (s32)x_steps);
    coord_or_height = actor->x;
    offset_work = *x_step;
    direction_or_x = direction;
    saved_offset = offset_arg;
    target_x = coord_or_height + offset_work;
    map_limits = D_8008333C;
    next_x = target_x & 0xFFFF;
    if (next_x != 0) {
        if (((1 << map_limits[10]) - 1) >= next_x) {
            ASM_USE_NV(target_x);
            y_step = (u16 *)((u8 *)D_8006CCE8 + step_offset);
            coord_or_height = actor->y;
            offset_work = *y_step;
            coord_work = coord_or_height + offset_work;
            coord_or_height = coord_work & 0xFFFF;
            if (coord_or_height != 0) {
                if (((1 << map_limits[11]) - 1) >= coord_or_height) {
                    coord_or_height = *(volatile u8 *)&actor->x;
                    ASM_KEEP_NV(coord_or_height);
                    offset_work = *(volatile u8 *)&actor->y;
                    ASM_KEEP_NV(offset_work);
                    body_addr = (u32)body;
                    ASM_KEEP_NV(body_addr);
                    height = ((FuncArg2 *)body_addr)->height;
                    coord_or_height <<= 6;
                    tile_coord = (u32)coord_or_height >> 6;
                    offset_work <<= 6;
                    ASM_KEEP_NV(offset_work);
                    y_or_direction = (u32)offset_work >> 6;
                    ASM_KEEP_NV(y_or_direction);
                    coord_work = coord_or_height + 0x20;
                    center_y = offset_work + 0x20;
                    result = func_8009A540(direction_or_x, tile_coord, y_or_direction,
                                          (s16)(height - offset_arg)) << 0x10;
                    if (result != 0) {
                        y_or_direction = direction;
                        collision_out = (u32)&collision.value;
                        ASM_SET(offset_work);
                        coord_or_height = (s32)((u8 *)D_800DCEAC + step_offset);
                        ASM_KEEP_NV(coord_or_height);
                        offset_work = (s32)((u8 *)D_800DCEBC + step_offset);
                        direction_or_x = actor->x;
                        tile_coord = actor->y;
                        coord_or_height = *(u16 *)coord_or_height;
                        offset_work = *(u16 *)offset_work;
                        target_x = coord_or_height + coord_work;
                        coord_work = offset_work + center_y;
                        func_8009A350(direction_or_x, tile_coord, y_or_direction, (u16 *)collision_out);
                        if ((collision.value & 0x8002) == 0) {
                            goto collision_clear;
                        }
                    }
                    ASM_SCHED_BARRIER();
                    result = 0;
                    return 0;
collision_clear:
                    if ((actor->flag >= 0) ||
                        (monster_index = func_8009FB34((actor->x + *x_step) & 0xFFFF,
                                                       (actor->y + *y_step) & 0xFFFF),
                         (monster_index < 0)) ||
                        !(D_800E2970[monster_index].flags & 2) ||
                        (result = 0, ((body_addr = (u32)body,
                                       ((FuncArg2 *)body_addr)->flags & 0x2000) != 0))) {
                        if (collision.value & 0x3300) {
                            target_x_u16 = target_x & 0xFFFF;
                            if (collision.value & 0x40) {
                                {
                                    u16 sample_x;
                                    register u32 sample_offset ASM_REG("$8");
                                    sample_x = target_x_u16;
                                    target_y_u16 = coord_work & 0xFFFF;
                                    ASM_USE(target_y_u16);
                                    sample_offset = saved_offset;
                                    floor_height = func_800BCB04(sample_x, target_y_u16,
                                                                (s16)(height - sample_offset));
                                }
                                tile_coord = target_x_u16 >> 6;
                                y_or_direction = target_y_u16 >> 6;
                                target_height = (s16)floor_height;
                                if (target_height >= 0x201) {
                                    body_addr = (u32)body;
                                    target_height = (s16)((FuncArg2 *)body_addr)->height;
                                }
                                ASM_KEEP_NV(floor_height);
                                result = func_8009B25C(body, tile_coord, y_or_direction, target_height);
                                if (result == 0) {
                                    coord_or_height = floor_height << 0x10;
                                    goto check_height;
                                }
                            }
                            coord_or_height = floor_height << 0x10;
move_failed:
                            ASM_SCHED_BARRIER();
                            result = -1;
                            return -1;
                        }
                        {
                            register u32 sample_offset ASM_REG("$8");
                            sample_offset = saved_offset;
                            floor_height = func_800BCB04(target_x & 0xFFFF, coord_work & 0xFFFF,
                                                        (s16)(height - sample_offset));
                        }
                        coord_or_height = floor_height << 0x10;
check_height:
                        result = -1;
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
