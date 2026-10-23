#include "dungeon/actor/motion.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dir_step.h"

#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))

typedef struct {
    u8 pad[8];
    s32 height;
} HeightData;

extern s32 rsin(s32, s32);

/* Updates position history, motion and shading, and flags objects whose positions have settled. */
void update_position_history_and_shading(ActorTrailWork *obj, TrailMotion *coords_out, SpriteFrameState *rgb)
{
    ObjectNodeHeader *linked_obj;
    ActorTrailWork *linked_data;
    TileObject *room;
    u8 *history_src;
    u8 *history_dst;
    s16 *x_adjust;
    s16 *y_adjust;
    s32 history_index;
    s32 direction_offset;
    s32 shade;
    SpriteFrameState *linked_rgb;
    s32 raw_shade;
    s16 linked_shade;
    s32 final_coord;
    u16 final_state;
    u16 final_z;
    s32 previous_z;
    s32 current_z;
    u16 z;

    obj->previous.x.parts.whole.u = obj->history[1].x.u;
    obj->previous.y.parts.whole.u = obj->history[1].y.u;
    obj->previous.z.parts.whole.u = obj->history[1].z.u;

    for (history_index = 1; history_index > 0; history_index--) {
        history_dst = (u8 *)obj + history_index * 8;
        history_src = (u8 *)obj + (history_index - 1) * 8;
        U16_AT(history_dst, 0x24) = U16_AT(history_src, 0x24);
        U16_AT(history_dst, 0x26) = U16_AT(history_src, 0x26);
        U16_AT(history_dst, 0x28) = U16_AT(history_src, 0x28);
    }

    final_z = obj->position.y.parts.whole.u;
    z = obj->position.z.parts.whole.u;
    obj->history[0].x.u = obj->position.x.parts.whole.u;
    linked_obj = obj->follow;
    obj->history[0].y.u = final_z;
    obj->history[0].z.u = z;

    if (linked_obj == 0) {
        switch (obj->state.s) {
        case 0:
            direction_offset = ((-g_game_work.view.camera_rotation.parts.viewAngle + 0x500) >> 8) & 0xE;
            room = &reference_tile_object;
            x_adjust = (s16 *)(((u8 *)dir_step_x) + direction_offset);
            {
                s32 x_target;
                s32 x_current;

                x_target = (room->tile_position.parts.tile_x + *x_adjust) << 6;
                x_current = obj->position.x.parts.whole.s - 0x20;
                obj->position.x.parts.whole.u += (x_target - x_current) / obj->timer.s;
            }
            y_adjust = (s16 *)(((u8 *)dir_step_y) + direction_offset);
            {
                s32 y_target;
                s32 y_current;

                y_target = (room->tile_position.parts.tile_y + *y_adjust) << 6;
                y_current = obj->position.y.parts.whole.s - 0x20;
                obj->position.y.parts.whole.u += (y_target - y_current) / obj->timer.s;
            }
            obj->position.z.value +=
                (view_reference_entity.z.v -
                 (rsin(obj->timer.s * 42, obj->timer.s) << 12) -
                 obj->position.z.value) / obj->timer.s;

            if (obj->brightness.s < 0x80) {
                obj->brightness.u += 0x10;
            }
            shade = obj->brightness.byte;
            rgb->color.c.g = shade;
            rgb->color.c.b = shade;
            rgb->color.c.r = shade;

            obj->timer.u--;
            if (obj->timer.s <= 0) {
                final_coord = (room->tile_position.parts.tile_x + *x_adjust) << 6;
                obj->position.x.parts.whole.u = final_coord + 0x20;
                final_coord = (room->tile_position.parts.tile_y + *y_adjust) << 6;
                obj->position.y.parts.whole.u = final_coord + 0x20;
                final_state = obj->state.u;
                final_z = (u16)view_reference_entity.z.w.i;
                obj->state.u = final_state + 1;
                obj->position.z.parts.whole.u = final_z;
            }
            break;
        case 1:
            if (obj->previous.x.parts.whole.s == obj->position.x.parts.whole.s && obj->previous.y.parts.whole.s == obj->position.y.parts.whole.s) {
                previous_z = obj->previous.z.parts.whole.s;
                current_z = obj->position.z.parts.whole.s;
                if (previous_z == current_z) {
                    U16_AT(obj, -2) |= NODE_REMOVE;
                    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                    return;
                }
            }
            break;
        }
    } else {
        linked_data = (ActorTrailWork *)(linked_obj + 1);
        obj->position.x.parts.whole.u = linked_data->history[1].x.u;
        obj->position.y.parts.whole.u = linked_data->history[1].y.u;
        z = linked_data->history[1].z.u;
        obj->position.z.parts.whole.u = z;

        if (obj->state.s == 0) {
            linked_rgb = obj->follow->sprite;
            raw_shade = linked_rgb->color.c.r - obj->shade_offset.s * 8;
            linked_shade = raw_shade;
            if ((s16)raw_shade < 0) {
                linked_shade = 0;
            }
            rgb->color.c.b = linked_shade;
            rgb->color.c.g = linked_shade;
            rgb->color.c.r = linked_shade;

            obj->timer.u--;
            if (obj->timer.s <= 0) {
                obj->state.u++;
            }
        } else if (obj->previous.x.parts.whole.s == obj->position.x.parts.whole.s && obj->previous.y.parts.whole.s == obj->position.y.parts.whole.s) {
            previous_z = obj->previous.z.parts.whole.s;
            current_z = (s16)z;
            if (previous_z == current_z) {
                U16_AT(obj, -2) |= NODE_REMOVE;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                return;
            }
        }
    }
copy_out:
    coords_out->position.x.parts.whole.u = obj->previous.x.parts.whole.u;
    coords_out->position.y.parts.whole.u = obj->previous.y.parts.whole.u;
    coords_out->position.z.parts.whole.u = obj->previous.z.parts.whole.u;
    coords_out->velocity.x.parts.whole.u = obj->position.x.parts.whole.u;
    coords_out->velocity.y.parts.whole.u = obj->position.y.parts.whole.u;
    coords_out->velocity.z.parts.whole.u = obj->position.z.parts.whole.u;
    obj->ticks++;

    return;
}
