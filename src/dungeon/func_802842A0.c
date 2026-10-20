#include "modules/dungeon_dungeon_setup.h"

void initialize_random_effect_position(dungeon_setup_802842A0_S_800172A0_0 *source, s16 base_offset) {
    s16 state_offset;
    s16 position_x;
    s16 position_y;
    GameView *state;
    void *effect;
    s32 random_angle;
    dungeon_setup_802842A0_S_800172A0_2 *bounds;
    s16 rotation_step;
    s32 random_bits;

    state = &g_game_work.view;
    bounds = (u8 *)state + 0x1C4;
    effect = (u8 *)state + 0xB8;
    random_angle = (rand() & 0x1FFF) - 0x1000;
    if (!((u16) *((s16 *)&D_80013714) & 2)) {
        position_x = source->unk_02 + (func_80064584(random_angle) * 2);
        state->camera_position.parts.camera_position_x = position_x;
        if (position_x < 0) {
            state->camera_position.parts.camera_position_x = 0;
        } else if (position_x >= bounds->unk_1C) {
            state->camera_position.parts.camera_position_x = (s16) ((u16) bounds->unk_1C - 1);
        }
        position_y = source->unk_06 + (func_800644B8(random_angle) * 2);
        state->camera_position.parts.camera_position_y = position_y;
        if (position_y < 0) {
            state->camera_position.parts.camera_position_y = 0;
        } else if (position_y >= bounds->unk_1E) {
            state->camera_position.parts.camera_position_y = (s16) ((u16) bounds->unk_1E - 1);
        }
        state_offset = (s16) (source->unk_0A - 0x400);
        state->camera_rotation.parts.camera_rotation_x = 0;
        state->camera_position.parts.camera_position_z = state_offset;
        random_bits = rand();
        rotation_step = -0x800;
        if (random_bits & 1) {
            rotation_step = 0x800;
        }
        state->camera_rotation.parts.viewAngle = rotation_step;
        ((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_00 = (void *) (effect + 4);
        ((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_14 = 1;
        ((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_24 = 0x40;
        ((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_0C = source;
        ((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_18 = 0;
        ((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_26 = base_offset;
        state->slot[0].callback = &D_800C7B38;
        state_offset = base_offset + ((((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_24 + 1) * 0x30);
        state->view_offset.parts.view_offset_z = state_offset;
        ((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_10 = (s32) state_offset;
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
    }
}
/* Warning: struct S_80083178 is not defined (only forward-declared) */
