#include "dungeon/menu_cache_fusion.h"
#include "dungeon/menu_cache_close.h"
#include "dungeon/menu_cache_selection.h"
#include "dungeon/data.h"
#include "engine/runtime.h"
#include "shared/audio_commands.h"
#include "engine/object.h"
#include "script_symbols.h"
#include "shared/game_work.h"
#include "slus.h"

/* Set up the fusion error message for a missing second familiar. */
void show_fusion_need_two(void)
{
    set_message_mode(1);
    call_message_mode_handler();
    build_object_registration_script(cached_fusion_need_two_message);
}

/* Show the error for a pair of familiars that cannot be fused. */
void show_fusion_invalid_pair(void)
{
    set_message_mode(1);
    call_message_mode_handler();
    build_object_registration_script(fusion_invalid_pair_message);
}

/* Open the text prompt for confirming or cancelling a fusion. */
void show_fusion_confirmation(void)
{
    set_message_mode(1);
    call_message_mode_handler();
    dispatch_control_coded_message(cached_fusion_confirm_message);
}

/* Close on the window signal or poll for cancellation. */
void check_fusion_close_signal(void *body)
{
    if (test_resident_bitmap_bit(sn_win_sw0) != 0) {
        clear_resident_bitmap_bit(sn_win_sw0);
        schedule_fusion_close(NODE_HEADER(body));
    } else {
        poll_fusion_cancel(body);
    }
}

/* Close the action menu on the window signal or poll for cancellation. */
void check_action_close_signal(void *body)
{
    if (test_resident_bitmap_bit(sn_win_sw0) != 0) {
        clear_resident_bitmap_bit(sn_win_sw0);
        schedule_action_menu_close(NODE_HEADER(body));
    } else {
        poll_cached_action_owner_cancel(body);
    }
}

/* The window switch either confirms the fusion or schedules cancellation. */
void poll_fusion_confirmation(void *body)
{
    s32 result = poll_window_switch_flags();

    if (result != 0) {
        if (result == 1) {
            selected_item_action_alias = 10;
            SD_Call(AUDIO_MENU_CONFIRM);
            schedule_fusion_cleanup(NODE_HEADER(body));
        } else {
            SD_Call(AUDIO_CANCEL);
            schedule_fusion_close(NODE_HEADER(body));
        }
    } else {
        poll_fusion_cancel(body);
    }
}

/* Play the cancellation sound and schedule the fusion menu to close. */
void poll_fusion_cancel(void *body)
{
    if (g_game_work.buttons != 0 && (g_game_work.pressed_buttons & 0x20)) {
        SD_Call(AUDIO_CANCEL);
        schedule_fusion_close(NODE_HEADER(body));
    }
}
