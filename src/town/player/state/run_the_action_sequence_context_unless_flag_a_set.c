#include "shared/audio_commands.h"
#include "script_symbols.h"
#include "common.h"
#include "engine/object.h"
#include "slus.h"
#include "town/player.h"
#include "town/player/state.h"
#include "town/shop.h"

/*
 * Returns zero while F_minigame_tyu is set; otherwise plays sound 0x514, clears the two action
 * globals, and returns the created item-menu object.
 */
s32 run_the_action_sequence_context_unless_flag_hex_a_5_set(s32 context) {
    if (test_resident_bitmap_bit(F_minigame_tyu) != 0) {
        return 0;
    }
    SD_Call(AUDIO_ACCEPT);
    clear_global_80110_ec_0_global_80082_a_39();
    return create_item_menu_object(context);
}
