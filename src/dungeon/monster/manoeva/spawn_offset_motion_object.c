#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80173D78_arg0.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/monster/manoeva.h"
#include "engine/graphics.h"
#include "engine/node/allocation.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80175DD0_body {
    s16 *unk_00;
    u8 pad_04[0x1C];
    s16 unk_20;
} S_80175DD0_body;


   /* arg1 in spawn_offset_motion_object */

extern s32 resolve_record_orientation_or_fallback();
s32 register_node(ObjectNodeHeader *entry, void *registration_id);

extern s32 D_80175C60;
extern s32 D_80175D74;

/* Creates an object at a source position offset and sets its orientation from the parent. */
void spawn_offset_motion_object(ActorRecord *parent_data, ObjectPosition *origin, SpriteFrameState *source_data, s16 position_index) {
    void *allocation_head_address;
    ObjectNodeHeader **allocation_head;
    u16 position_offset[3];
    u16 angle;
    s32 direction_offset;
    ObjectPosition *coords;
    SpriteFrameState *object_data;
    ObjectNodeHeader *object;
    S_80175DD0_body *motion;
    void *body_storage;

    if (resolve_record_orientation_or_fallback((s32)source_data->source, source_data, position_offset, position_index) != 0) {
        allocation_head_address = NODE_HEADER(parent_data);
        allocation_head = allocation_head_address;
        object = allocate_list_node(0x300,allocation_head);
        if ((object != NULL) &&
            ((body_storage = NODE_BODY(object),
              motion = body_storage,
              object_data = object->sprite,
              coords = object->position,
              object->update_callback = &D_80175C60,
              object_data->scale_y = 0x400,
              object_data->scale_x = 0x400,
              object_data->color.word = 0x808080,
              object_data->animation_resource = source_data->animation_resource,
              coords->x.w.i = origin->x.unsigned_parts.integer + position_offset[0],
              coords->y.w.i = origin->y.unsigned_parts.integer + position_offset[1],
              coords->z.w.i = origin->z.unsigned_parts.integer + position_offset[2],
              direction_offset = ((u16)parent_data->facing >> 8) & 0xE,
              *((u16 *)&coords->velocity_x + 1) = *(u16 *)(((s8 *)dir_step_x) + direction_offset),
              *((u16 *)&coords->velocity_y + 1) = *(u16 *)(((s8 *)dir_step_y) + direction_offset),
              motion->unk_20 = 0x10,
              motion->unk_00 = &parent_data->facing,
              select_sprite_entry(object_data, 0x45, 0),
              register_node(object, &D_80175D74),
              angle = ((((g_game_work.view.camera_rotation.parts.viewAngle + *motion->unk_00 + 0x100) >> 9) & 7) + 2) << 9,
              object_data->angle_y = angle,
              angle == 0x400) ||
             (angle == 0xC00))) {
            object_data->angle_y = angle + 0x100;
        }
    }
}
