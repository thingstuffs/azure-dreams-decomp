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

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80175DD0_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s16 * unk_20;
    u8 pad_24[0x1C];
    s16 unk_40;
} S_80175DD0_1;   /* object in spawn_offset_motion_object */


   /* arg1 in spawn_offset_motion_object */

extern s32 resolve_record_orientation_or_fallback();
extern void *allocate_list_node();
extern s32 register_node();
extern s32 select_sprite_entry();

extern s32 D_80175C60;
extern s32 D_80175D74;

/* Creates an object at a source position offset and sets its orientation from the parent. */
void spawn_offset_motion_object(void *parent_data, MovingPosition *origin, Rec_D_80082E80 *source_data, s16 position_index) {
    u16 position_offset[3];
    u16 angle;
    s32 direction_offset;
    ObjectPosition *coords;
    SpriteFrameState *object_data;
    S_80175DD0_1 *object;

    if (resolve_record_orientation_or_fallback(source_data->unk_08, source_data, position_offset, position_index) != 0) {
        object = allocate_list_node(0x300, (u8 *)parent_data - 0x20);
        if ((object != NULL) &&
            ((object_data = object->unk_0C,
              coords = object->unk_08,
              object->unk_10 = &D_80175C60,
              object_data->scale_y = 0x400,
              object_data->scale_x = 0x400,
              object_data->color.word = 0x808080,
              object_data->animation_resource = source_data->unk_28.at00_s32.v,
              coords->x.w.i = origin->x + position_offset[0],
              coords->y.w.i = origin->y + position_offset[1],
              coords->z.w.i = origin->z + position_offset[2],
              direction_offset = (((Rec_func_80173D78_arg0 *)parent_data)->unk_2A >> 8) & 0xE,
              *((u16 *)&coords->velocity_x + 1) = *(u16 *)(((s8 *)dir_step_x) + direction_offset),
              *((u16 *)&coords->velocity_y + 1) = *(u16 *)(((s8 *)dir_step_y) + direction_offset),
              object->unk_40 = 0x10,
              object->unk_20 = (s16 *)((u8 *)parent_data + 0x2A),
              select_sprite_entry(object_data, 0x45, 0),
              register_node(object, &D_80175D74),
              angle = ((((g_game_work.view.camera_rotation.parts.viewAngle + *object->unk_20 + 0x100) >> 9) & 7) + 2) << 9,
              object_data->angle_y = angle,
              angle == 0x400) ||
             (angle == 0xC00))) {
            object_data->angle_y = angle + 0x100;
        }
    }
}
