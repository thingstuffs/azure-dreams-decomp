#include "modules/dungeon_engine_tile_map_fragment_b4f0c.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/dir_step.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))



extern s16 find_active_rect_containing_point(u16, u16);

extern s16 D_800DCEAC[];
extern s16 D_800DCEBC[];

/* Checks movement clearance and classifies the destination height relative to the actor. */
s32 check_movement_clearance_and_height(u32 move_flags, FuncArg1 *position, FuncArg2 *actor, s16 height_offset) {
    s16 offset_or_height;
    s32 call_direction;
    s16 *x_table;
    u16 flags;
    u16 *flags_out;
    s32 direction;
    u32 x_shifted;
    u32 y_shifted;
    s32 x_base;
    s32 y_base;
    u16 x_pos;
    s32 y_pos;
    u16 height;
    s16 monster_index;
    s32 dest_height;
    s32 signed_height;
    s32 status;

    direction = (move_flags >> 9) & 7;
    height = actor->height;
    x_shifted = position->x << 6;
    y_shifted = position->y << 6;
    x_base = x_shifted + 0x20;
    y_base = y_shifted + 0x20;

    if ((check_diagonal_side_height(direction, (u32)x_base >> 6, (u32)y_base >> 6,
                       (s16)(height - height_offset)) << 16) != 0) {

        call_direction = direction;
        flags_out = &flags;
        x_table = D_800DCEAC;
        offset_or_height = call_direction << 1;
        x_pos = *(u16 *)((u8 *)x_table + offset_or_height) + x_base;
        y_pos = *(u16 *)((u8 *)D_800DCEBC + offset_or_height) + y_base;
        if ((get_offset_map_cell_value_and_flags(position->x, position->y, call_direction, flags_out) << 16) == 0) {
            return 0;
        }

        if (position->flag < 0) {
            monster_index = find_active_rect_containing_point(
                (u16)(position->x +
                      *(u16 *)((u8 *)dir_step_x + offset_or_height)),
                (u16)(position->y +
                      *(u16 *)((u8 *)dir_step_y + offset_or_height)));
            if (monster_index >= 0 &&
                (D_800E2970[monster_index].flags & 2) &&
                !(actor->flags & 0x2000)) {
                return 0;
            }
        }

        if (flags & 0x8402) {
            return 0;
        }

        if (flags & 0x3300) {
            s32 y_coord;
            s32 x_coord;

            if (!(flags & 0x40)) {
                status = -1;
                return status;
            }
            x_pos &= 0xFFFF;
            x_coord = x_pos;
            y_coord = y_pos & 0xFFFF;
            offset_or_height = terrain_height_short(x_coord, y_coord, (s16)(height - height_offset));
            if (find_eligible_actor_at_tile_and_height(actor, (u32)x_pos >> 6, (u32)y_coord >> 6,
                              (s16)offset_or_height)) {
                status = -1;
                return status;
            }
        } else {
            offset_or_height = terrain_height_short(x_pos & 0xFFFF, y_pos & 0xFFFF,
                                   (s16)(height - height_offset));
        }

        status = (u32)offset_or_height << 16;
        dest_height = status >> 16;
        if (dest_height >= 0x200) {
            return 0;
        }
        status = (u32)height << 16;
        signed_height = status >> 16;
        if (dest_height == signed_height) {
            return 1;
        }
        if (signed_height < dest_height) {
            return 2;
        }
        return 3;
    }
    return 0;
}
