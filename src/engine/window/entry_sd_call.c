#include "shared/audio_commands.h"
#include "common.h"
#include "engine/window.h"
#include "engine/window/choice_info.h"
#include "shared/game_work.h"

#include "slus.h"

/* Wrap the cursor on directional input and dispatch the selected action. */
void handle_wrapping_menu_cursor_input(CursorState *cursor, s32 unused_1, s32 unused_2)
{
    GameWork *runtime;
    u32 next_cursor;
    u32 flags_or_count;

    runtime = &g_game_work;
    flags_or_count = ((u32)runtime->pressed_buttons);
    if (flags_or_count & 0x4000) {
        SD_Call(AUDIO_CURSOR_MOVE);
        next_cursor = cursor->cursor_4D + 1;
        flags_or_count = (u32)cursor->info_74;
        cursor->cursor_4D = next_cursor;
        next_cursor = cursor->cursor_4D;
        flags_or_count = *(u8 *)(flags_or_count + 0x26);
        flags_or_count = next_cursor % flags_or_count;
        cursor->cursor_4D = flags_or_count;
    } else if (flags_or_count & 0x1000) {
        SD_Call(AUDIO_CURSOR_MOVE);
        flags_or_count = (u32)cursor->info_74;
        flags_or_count = *(u8 *)(flags_or_count + 0x26);
        next_cursor = cursor->cursor_4D + flags_or_count;
        next_cursor -= 1;
        cursor->cursor_4D = next_cursor;
        flags_or_count = (u32)cursor->info_74;
        next_cursor = cursor->cursor_4D;
        flags_or_count = *(u8 *)(flags_or_count + 0x26);
        flags_or_count = next_cursor % flags_or_count;
        cursor->cursor_4D = flags_or_count;
    }
    if (((u32)runtime->pressed_buttons) & 0x40) {
        confirm_menu_choice(cursor, unused_1, unused_2);
    }
}
