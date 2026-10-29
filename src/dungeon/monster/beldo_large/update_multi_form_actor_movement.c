#include "shared/entity.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "dungeon/monster/beldo_large.h"
#include "engine/graphics.h"

typedef struct {
    u8 pad_00[0x8C];
    u8 *field_8C;
    u8 pad_90[0x1C];
    u8 mode;
} DungeonObject;

typedef struct {
    u8 pad_00[0x2C];
    u8 *field_2C;
} DungeonState;

typedef struct {
    u8 pad_00[0x2A];
    s16 field_2A;
} DungeonInput;

extern u8 beldo_large_frame_set_2[];
extern u8 beldo_large_frame_set_5[];
extern u8 beldo_large_frame_set_1[];
extern u8 beldo_large_frame_set_3[];
extern void beldo_large_action_resume_address(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);

extern s32 update_actor_transform_from_parent(void *, void *, void *, void *);


/*
 * Selects idle frames for Beldo's four forms, updates parent-relative movement, and handles the
 * floor-trap result.
 */
void update_multi_form_actor_movement(ActorRecord *object, ObjectPosition *update_param, SpriteFrameState *state, ActorRecord *input) {
    s32 mode;
    u8 *mode_table;
    u8 *current_table;

    mode = object->unk_AC.byte;
    switch (mode) {
    case 0:
        current_table = state->frameTable;
        mode_table = beldo_large_frame_set_2;
        break;
    case 1:
        current_table = state->frameTable;
        mode_table = beldo_large_frame_set_5;
        break;
    case 2:
        current_table = state->frameTable;
        mode_table = beldo_large_frame_set_1;
        break;
    case 3:
        current_table = state->frameTable;
        mode_table = beldo_large_frame_set_3;
        break;
    default:
        if (update_actor_transform_from_parent(object, update_param, state, input) != 0) {
            if ((check_actor_floor_trap(state, input) << 0x10) > 0) {
                object->unk_8C.address = beldo_large_action_resume_address;
            }
        }
        return;
        return;
    }
    if (current_table != mode_table) {
        state->frameTable = mode_table;
        select_sprite_entry(state, *(u8 *)((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + input->facing + 0x100) >> 9) & 7)
            + (u32) mode_table), 0);
    }

    if (update_actor_transform_from_parent(object, update_param, state, input) != 0) {
        if ((check_actor_floor_trap(state, input) << 0x10) > 0) {
            object->unk_8C.address = beldo_large_action_resume_address;
        }
    }
    return;
}
