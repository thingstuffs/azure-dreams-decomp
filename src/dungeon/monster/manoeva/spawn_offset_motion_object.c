#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80173D78_arg0.h"
#include "shared/dungeon_moving_views.h"

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

typedef struct S_80175DD0_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x8];
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80175DD0_2;   /* object_data in spawn_offset_motion_object */

typedef struct S_80175DD0_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
} S_80175DD0_3;   /* coords in spawn_offset_motion_object */

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
    S_80175DD0_3 *coords;
    S_80175DD0_2 *object_data;
    S_80175DD0_1 *object;

    if (resolve_record_orientation_or_fallback(source_data->unk_08, source_data, position_offset, position_index) != 0) {
        object = allocate_list_node(0x300, (u8 *)parent_data - 0x20);
        if ((object != NULL) &&
            ((object_data = object->unk_0C,
              coords = object->unk_08,
              object->unk_10 = &D_80175C60,
              object_data->unk_1E = 0x400,
              object_data->unk_1C = 0x400,
              object_data->unk_0C = 0x808080,
              object_data->unk_28 = source_data->unk_28.at00_s32.v,
              coords->unk_02 = origin->unk_02 + position_offset[0],
              coords->unk_06 = origin->unk_06 + position_offset[1],
              coords->unk_0A = origin->unk_0A + position_offset[2],
              direction_offset = (((Rec_func_80173D78_arg0 *)parent_data)->unk_2A >> 8) & 0xE,
              coords->unk_0E = *(u16 *)(((s8 *)dir_step_x) + direction_offset),
              coords->unk_12 = *(u16 *)(((s8 *)dir_step_y) + direction_offset),
              object->unk_40 = 0x10,
              object->unk_20 = (s16 *)((u8 *)parent_data + 0x2A),
              select_sprite_entry(object_data, 0x45, 0),
              register_node(object, &D_80175D74),
              angle = ((((g_game_work.view.viewAngle + *object->unk_20 + 0x100) >> 9) & 7) + 2) << 9,
              object_data->unk_18 = angle,
              angle == 0x400) ||
             (angle == 0xC00))) {
            object_data->unk_18 = angle + 0x100;
        }
    }
}
