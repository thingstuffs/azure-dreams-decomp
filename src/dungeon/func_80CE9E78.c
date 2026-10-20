#include "dungeon/monster/troll/advance_actor_stored_path.h"
#include "shared/sprite_frame_state.h"

/* Reset display state and apply the kind-specific directional entry when its table changes. */
void reset_actor_directional_animation(Rec_func_80172CC0_arg0 *state, s32 unused, SpriteFrameState *display, T_80173678_S_80173678_1 *entity) {
    s32 kind;
    u8 *direction_table;
    u8 *previous_table;

    state->unk_9A.as_s8 = 0x10;
    state->unk_9B.as_s8 = 0;
    kind = entity->unk_48;
    switch (kind) {
    case 0xD:
        direction_table = D_80175E9C;
        previous_table = *(u8 * *)&display->frameTable;
        if (previous_table == direction_table) {
            return;
        }
        display->frameTable = direction_table;
        select_sprite_entry(display,
                      direction_table[((g_game_work.view.viewAngle + entity->unk_2A + 0x100) >> 9) & 7],
                      0);
        return;
    case 0xE:
        direction_table = D_80175EA4;
        previous_table = *(u8 * *)&display->frameTable;
        if (previous_table == direction_table) {
            return;
        }
        display->frameTable = direction_table;
        select_sprite_entry(display,
                      direction_table[((g_game_work.view.viewAngle + entity->unk_2A + 0x100) >> 9) & 7],
                      0);
        return;
    case 0xF:
        direction_table = D_80175EAC;
        previous_table = *(u8 * *)&display->frameTable;
        if (previous_table == direction_table) {
            return;
        }
        display->frameTable = direction_table;
        select_sprite_entry(display,
                      direction_table[((g_game_work.view.viewAngle + entity->unk_2A + 0x100) >> 9) & 7],
                      0);
    }
}
