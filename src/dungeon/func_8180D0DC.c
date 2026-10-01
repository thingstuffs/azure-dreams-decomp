#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dir_step.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(u8 **)((u8 *)(p) + (o)))

typedef struct {
    u8 pad[8];
    s32 height;
} HeightData;

extern s32 func_800644B8(s32, s32);


/* Updates position history, motion and shading, and flags objects whose positions have settled. */
void func_800260DC(u8 *obj, u8 *coords_out, u8 *rgb)
{
    u8 *linked_obj;
    u8 *linked_data;
    TileObject *room;
    u8 *history_src;
    u8 *history_dst;
    s16 *x_adjust;
    s16 *y_adjust;
    s32 history_index;
    s32 history_offset;
    s32 direction_offset;
    s32 shade;
    u8 *linked_rgb;
    s32 raw_shade;
    s16 linked_shade;
    s32 final_coord;
    u16 final_state;
    u16 final_z;
    s32 previous_z;
    s32 current_z;
    u16 z;

    U16_AT(obj, 0x1A) = U16_AT(obj, 0x2C);
    U16_AT(obj, 0x1E) = U16_AT(obj, 0x2E);
    U16_AT(obj, 0x22) = U16_AT(obj, 0x30);

    history_index = 1;
copy_history:
    history_offset = history_index * 8;
    history_index--;
    history_src = obj + history_index * 8;
    history_dst = obj + history_offset;
    U16_AT(history_dst, 0x24) = U16_AT(history_src, 0x24);
    U16_AT(history_dst, 0x26) = U16_AT(history_src, 0x26);
    U16_AT(history_dst, 0x28) = U16_AT(history_src, 0x28);
    if (history_index > 0) {
        goto copy_history;
    }

    final_z = U16_AT(obj, 0x12);
    z = U16_AT(obj, 0x16);
    U16_AT(obj, 0x24) = U16_AT(obj, 0x0E);
    linked_obj = PTR_AT(obj, 8);
    U16_AT(obj, 0x26) = final_z;
    U16_AT(obj, 0x28) = z;

    if (linked_obj == 0) {
        switch (S16_AT(obj, 0x64)) {
        case 0:
            direction_offset = ((-S16_AT(((u8 *)(&gameWork.view.viewAngle)), 0) + 0x500) >> 8) & 0xE;
            room = &D_80082E80;
            x_adjust = (s16 *)(((u8 *)dirStepX) + direction_offset);
            {
                s32 x_target;
                s32 x_current;

                x_target = (room->tileX + *x_adjust) << 6;
                x_current = S16_AT(obj, 0x0E) - 0x20;
                U16_AT(obj, 0x0E) += (x_target - x_current) / S16_AT(obj, 0x66);
            }
            y_adjust = (s16 *)(((u8 *)dirStepY) + direction_offset);
            {
                s32 y_target;
                s32 y_current;

                y_target = (room->tileY + *y_adjust) << 6;
                y_current = S16_AT(obj, 0x12) - 0x20;
                U16_AT(obj, 0x12) += (y_target - y_current) / S16_AT(obj, 0x66);
            }
            S32_AT(obj, 0x14) +=
                (D_80083780.z.v -
                 (func_800644B8(S16_AT(obj, 0x66) * 42, S16_AT(obj, 0x66)) << 12) -
                 S32_AT(obj, 0x14)) / S16_AT(obj, 0x66);

            if (S16_AT(obj, 0x6A) < 0x80) {
                U16_AT(obj, 0x6A) += 0x10;
            }
            shade = U8_AT(obj, 0x6A);
            U8_AT(rgb, 0x0D) = shade;
            U8_AT(rgb, 0x0E) = shade;
            U8_AT(rgb, 0x0C) = shade;

            U16_AT(obj, 0x66)--;
            if (S16_AT(obj, 0x66) <= 0) {
                final_coord = (room->tileX + *x_adjust) << 6;
                U16_AT(obj, 0x0E) = final_coord + 0x20;
                final_coord = (room->tileY + *y_adjust) << 6;
                U16_AT(obj, 0x12) = final_coord + 0x20;
                final_state = U16_AT(obj, 0x64);
                final_z = U16_AT(((HeightData *)&D_80083780), 0x0A);
                U16_AT(obj, 0x64) = final_state + 1;
                U16_AT(obj, 0x16) = final_z;
            }
            break;
        case 1:
            if (S16_AT(obj, 0x1A) == S16_AT(obj, 0x0E) && S16_AT(obj, 0x1E) == S16_AT(obj, 0x12)) {
                previous_z = S16_AT(obj, 0x22);
                current_z = S16_AT(obj, 0x16);
                if (previous_z == current_z) {
                    U16_AT(obj, -2) |= 0x8000;
                    objectFlagBlock.flags |= 0x8000;
                    return;
                }
            }
            break;
        }
    } else {
        linked_data = linked_obj + 0x20;
        U16_AT(obj, 0x0E) = U16_AT(linked_data, 0x2C);
        U16_AT(obj, 0x12) = U16_AT(linked_data, 0x2E);
        z = U16_AT(linked_data, 0x30);
        U16_AT(obj, 0x16) = z;

        if (S16_AT(obj, 0x64) == 0) {
            linked_rgb = PTR_AT(PTR_AT(obj, 8), 0x0C);
            raw_shade = U8_AT(linked_rgb, 0x0C) - S16_AT(obj, 0x6E) * 8;
            linked_shade = raw_shade;
            if ((s16)raw_shade < 0) {
                linked_shade = 0;
            }
            U8_AT(rgb, 0x0E) = linked_shade;
            U8_AT(rgb, 0x0D) = linked_shade;
            U8_AT(rgb, 0x0C) = linked_shade;

            U16_AT(obj, 0x66)--;
            if (S16_AT(obj, 0x66) <= 0) {
                U16_AT(obj, 0x64)++;
            }
        } else if (S16_AT(obj, 0x1A) == S16_AT(obj, 0x0E) && S16_AT(obj, 0x1E) == S16_AT(obj, 0x12)) {
            previous_z = S16_AT(obj, 0x22);
            current_z = (s16)z;
            if (previous_z == current_z) {
                U16_AT(obj, -2) |= 0x8000;
                objectFlagBlock.flags |= 0x8000;
                return;
            }
        }
    }
copy_out:
    U16_AT(coords_out, 2) = U16_AT(obj, 0x1A);
    U16_AT(coords_out, 6) = U16_AT(obj, 0x1E);
    U16_AT(coords_out, 0x0A) = U16_AT(obj, 0x22);
    U16_AT(coords_out, 0x0E) = U16_AT(obj, 0x0E);
    U16_AT(coords_out, 0x12) = U16_AT(obj, 0x12);
    U16_AT(coords_out, 0x16) = U16_AT(obj, 0x16);
    U16_AT(obj, 0x68)++;

    return;
}
