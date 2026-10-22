#include "common.h"
#include "shared/game_work.h"

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

extern u8 D_801739A0[];
extern u8 D_801739A8[];
extern u8 D_801739B0[];
extern u8 D_801739B8[];
extern u8 D_8016A36C[];

extern void select_sprite_entry(void *, s32, s32);
extern s32 update_actor_transform_from_parent(void *, s32, void *, void *);
extern s32 check_actor_floor_trap(void *, void *);

/* Selects the mode table and updates the dungeon object state. */
/* Selects idle frames for Beldo's four forms, updates parent-relative movement, and handles the floor-trap
 * result. */
void update_multi_form_actor_movement(DungeonObject *object, s32 update_param, DungeonState *state, DungeonInput *input) {
    s32 mode;
    u8 *mode_table;
    u8 *current_table;

    mode = object->mode;
    switch (mode) {
    case 0:
        current_table = state->field_2C;
        mode_table = D_801739A0;
        break;
    case 1:
        current_table = state->field_2C;
        mode_table = D_801739A8;
        break;
    case 2:
        current_table = state->field_2C;
        mode_table = D_801739B0;
        break;
    case 3:
        current_table = state->field_2C;
        mode_table = D_801739B8;
        break;
    default:
        if (update_actor_transform_from_parent(object, update_param, state, input) != 0) {
            if ((check_actor_floor_trap(state, input) << 0x10) > 0) {
                object->field_8C = D_8016A36C;
            }
        }
        return;
        return;
    }
    if (current_table != mode_table) {
        state->field_2C = mode_table;
        select_sprite_entry(state, *(u8 *)((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + input->field_2A + 0x100) >> 9) & 7)
            + (u32) mode_table), 0);
    }

    if (update_actor_transform_from_parent(object, update_param, state, input) != 0) {
        if ((check_actor_floor_trap(state, input) << 0x10) > 0) {
            object->field_8C = D_8016A36C;
        }
    }
    return;
}
