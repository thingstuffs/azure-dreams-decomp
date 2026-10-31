#include "shared/audio_commands.h"
#include "common.h"
#include "shared/game_work.h"
#include "engine/menu.h"
#include "slus.h"

/* If global flag 0x20 is set, dispatches 0x515 and forwards the payload. */
void handle_animated_selection_menu_cancel(AnimatedSelectionMenuOwnerBody *payload)
{
    if ((g_game_work.pressed_buttons) & 0x20) {
        SD_Call(AUDIO_CANCEL);
        destroy_animated_selection_menu_owner(payload);
    }
}
