#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/position_views.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
#include "engine/node.h"
#include "sdk/libc.h"
#include "town/map/object.h"
#include "town/menu.h"




/* Deactivate the object when triggered; otherwise update its spin from nearby motion and advance rotation. */
void update_player_spun_object(void *object_arg, ObjectPosition *origin, LitMeshSprite *mesh) {
    ObjectPosition *position = origin;
    LitMeshSprite *rotation = mesh;
    TownObjectRecord *object = object_arg;
    u8 *active_flag;
    ObjectPosition *town_state;
    s32 dx;
    s32 dy;
    s32 near_x;
    s32 speed_sq;
    s32 position_y;
    s32 raw_speed;
    s32 angle_step;
    s32 t;

    if (classify_object_against_bounds(object_arg, position) != 0) {
        active_flag = object->spawn_active;
        if (active_flag != 0) {
            *active_flag = 0;
        }
        unlink_node_if_registered(object);
        NODE_HEADER(object)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    raw_speed = ((u16)object->unk_66);
    position_y = object->unk_66;
    if (position_y >= 0x100) {
        object->unk_66 = raw_speed - 0x20;
    } else {
        if (position_y >= 0x10) {
            object->unk_66 = raw_speed - 0x10;
        } else {
            object->unk_66 = 0;
        }
    }
    town_state = &view_reference_entity;
    dx = town_state->x.w.i;
    dy = position->x.w.i;
    position_y = position->y.w.i;
    dx -= dy;
    dx = abs(dx);
    dx = (s16)dx;
    dy = town_state->y.w.i;
    near_x = dx < 0x81;
    dy -= position_y;
    dy = abs(dy);

    if (near_x && ((s16)dy < 0x81)) {
        speed_sq = (((Fixed1616 *)&town_state->velocity_x)->w.i * ((Fixed1616 *)&town_state->velocity_x)->w.i) +
              (((Fixed1616 *)&town_state->velocity_y)->w.i * ((Fixed1616 *)&town_state->velocity_y)->w.i);
        object->unk_66 =
            ((u16)object->unk_66) +
            ((s32)(speed_sq + ((u32)speed_sq >> 31)) >> 1);
    }

    if (object->unk_66 >= 0x601) {
        object->unk_66 = 0x600;
    }

    angle_step = ((u16)object->unk_66) + 0x80;
    rotation->rotation[2] = (u16)rotation->rotation[2] + angle_step;
    t = (u16)rotation->rotation[2];
    rotation->rotation[2] = t & 0xFFF;

    return;
}
