#include "script_symbols.h"
#include "common.h"

extern s32 test_resident_bitmap_bit(s32);
extern void SD_Call(s32);
extern void clear_global_80110_ec_0_global_80082_a_39(void);
extern s32 create_item_menu_object(s32);

/*
 * Returns zero while F_minigame_tyu is set; otherwise plays sound 0x514, clears the two action
 * globals, and returns the created item-menu object.
 */
s32 run_the_action_sequence_context_unless_flag_hex_a_5_set(s32 context) {
    if (test_resident_bitmap_bit(F_minigame_tyu) != 0) {
        return 0;
    }
    SD_Call(0x514);
    clear_global_80110_ec_0_global_80082_a_39();
    return create_item_menu_object(context);
}
