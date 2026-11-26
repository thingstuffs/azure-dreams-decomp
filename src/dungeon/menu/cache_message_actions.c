#include "dungeon/menu_cache_selection.h"
#include "dungeon/menu_cache_close.h"
#include "dungeon/menu_cache_party_menu.h"
#include "shared/audio_commands.h"
#include "shared/game_work.h"
#include "slus.h"

/* Queue a script message and install the panel-specific continuation. */
void queue_menu_message(ObjectNodeHeader *node)
{
    if (node != 0) {
        enqueue_script_message_command();
        node->update_callback = complete_cached_message_transition;
    }
}

/* Queue a script message and resume the party preview when it closes. */
void queue_menu_restore_message(ObjectNodeHeader *node)
{
    if (node != 0) {
        enqueue_script_message_command();
        node->update_callback = finish_party_preview;
    }
}

/* Run the message mode handler and defer showing the result. */
void start_menu_message_mode(ObjectNodeHeader *node)
{
    if (node != 0) {
        call_message_mode_handler();
        node->update_callback = open_party_behavior_panel;
    }
}

/* Play the cancellation sound and schedule the owning node to close. */
void poll_party_menu_cancel(void *body)
{
    if (g_game_work.buttons != 0 && (g_game_work.pressed_buttons & 0x20)) {
        SD_Call(AUDIO_CANCEL);
        schedule_party_menu_close(NODE_HEADER(body));
    }
}

/* Play the cancellation sound and schedule the action menu to close. */
void poll_cached_action_owner_cancel(void *body)
{
    if (g_game_work.buttons != 0 && (g_game_work.pressed_buttons & 0x20)) {
        SD_Call(AUDIO_CANCEL);
        schedule_action_menu_close(NODE_HEADER(body));
    }
}
