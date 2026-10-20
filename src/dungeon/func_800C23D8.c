#include "common.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

/* Entity transition state */
typedef struct Entity {
    u8    pad0[0xC];
    void *unkC;      /* 0x0C -> Sub */
    s32   unk10;     /* 0x10 */
    u8    pad14[4];
    s32   unk18;     /* 0x18 state selector */
    u8    pad1C[8];
    s16   unk24;     /* 0x24 countdown */
    u16   unk26;     /* 0x26 */
} Entity;

typedef struct Sub {
    u8  pad0[2];
    s16 f2;   /* 0x02 */
    u8  pad4[2];
    s16 f6;   /* 0x06 */
    u8  pad8[2];
    s16 fA;   /* 0x0A */
} Sub;

/* View over the D_80083178 dispatch/blend record (fields not in game.h struct) */

extern s16 D_800120A2;
extern s16 D_800DD264[];
extern s16 D_800DCE66[5];

extern s32 select_nearby_target_and_initialize_slot(s32 slot_id, void *target, s32 target_id, s32 slot_value);

/* Blend toward the entity target, then dispatch the next state. */
void blend_entity_toward_target_state(void *entity_data) {
    Entity *entity = entity_data;
    GameView *blend = &g_game_work.view;
    s32 state = entity->unk18;

    switch (state) {
    case 0:
        if (entity->unk24 > 0) {
            s16 half_ticks;
            s16 *table = D_800DD264;
            entity->unk10 -= entity->unk10 >> 2;
            blend->view_offset.parts.view_offset_z = entity->unk26 + (u16)entity->unk10;
            blend->camera_rotation.parts.camera_rotation_x = (u16)blend->camera_rotation.parts.camera_rotation_x + (table[D_800120A2] - blend->camera_rotation.parts.camera_rotation_x) / entity->unk24;
            blend->camera_rotation.parts.viewAngle = (u16)blend->camera_rotation.parts.viewAngle + (0 - blend->camera_rotation.parts.viewAngle) / entity->unk24;
            blend->camera_position.parts.camera_position_x = (u16)blend->camera_position.parts.camera_position_x + (((Sub *)entity->unkC)->f2 - blend->camera_position.parts.camera_position_x) / entity->unk24;
            blend->camera_position.parts.camera_position_y = (u16)blend->camera_position.parts.camera_position_y + (((Sub *)entity->unkC)->f6 - blend->camera_position.parts.camera_position_y) / entity->unk24;
            half_ticks = (s16)(u16)entity->unk24 / 2;
            if (half_ticks != 0) {
                blend->camera_position.parts.camera_position_z = (u16)blend->camera_position.parts.camera_position_z + (((Sub *)entity->unkC)->fA - blend->camera_position.parts.camera_position_z) / half_ticks;
            }
            {
                s16 ticks_left = (u16)entity->unk24 - 1;
                entity->unk24 = ticks_left;
                if (ticks_left > 0) {
                    return;
                }
            }
        }
        {
            s16 *table = D_800DD264;
            blend->camera_rotation.parts.camera_rotation_x = (u16)table[D_800120A2];
        }
        blend->camera_rotation.parts.viewAngle = 0;
        blend->view_offset.parts.view_offset_z = entity->unk26;
        entity->unk18 += 1;
        return;
    case 1:
        select_nearby_target_and_initialize_slot((void *)(((s32)D_800E3D7C) - 0x20), ((u8 *)(&D_80083780)), 8, D_800DCE66[0]);
        g_dungeon_status.activity_counts.parts.pending_action_count = g_dungeon_status.activity_counts.parts.pending_action_count - 1;
    }
}
