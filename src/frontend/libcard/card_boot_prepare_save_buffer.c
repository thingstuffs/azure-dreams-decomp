#include "frontend/card/save_image.h"
#include "shared/game_state.h"
#include "common.h"

extern CardSaveHeaderPrefix D_80028064;

#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"

/* Copies the initial word into the buffer and initializes state for the selected mode. */
void card_boot_prepare_save_buffer(CardSaveImage *save, s32 config, s32 mode) {
    GameState *gs = GAME_STATE;
    s16 is_mode_two;

    save->prefix = D_80028064;
    is_mode_two = (mode == 2);
    gs->dungeon_save_marker = is_mode_two;
    gs->resume_in_dungeon = is_mode_two;
    gs->saved_money = gs->town_money;
    gs->saved_flag_mask = card_boot_build_resident_bit_mask();
    gs->saved_building_total = card_boot_sum_slot_lookup_values();
    card_boot_build_save_description(save, config);
    card_boot_store_save_icon_clut_and_frames(save, config);
}
