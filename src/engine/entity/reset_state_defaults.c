#include "common.h"
#include "shared/game_state.h"

#include "engine/entity.h"

/* Reset global state and initialize default parameters. */
void reset_state_defaults(void)
{
    GameState *globals_base = GAME_STATE;

    GAME_STATE->options.unk_3185 = 1;
    GAME_STATE->town_money = 0;
    GAME_STATE->unk_2D68 = 0;
    GAME_STATE->carry.dungeon_money = 0;
    GAME_STATE->tower_entry_count = 0;
    reset_entry_flags();
    GAME_STATE->map_view.rect[0] = 0xD5;
    globals_base->map_view.rect[1] = 0x38;
    globals_base->map_view.rect[2] = 0x6B;
    globals_base->map_view.rect[3] = 0x70;
    GAME_STATE->map_view.unk_08 = 0x100;
    GAME_STATE->map_view.unk_0A = 0x78;
    GAME_STATE->map_view.scale = 0x4000;
    GAME_STATE->camera_depth_index = 0;
    GAME_STATE->camera_pitch_index = 0;
    GAME_STATE->unk_20A4 = 0;
}
