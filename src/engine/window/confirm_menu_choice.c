#include "shared/audio_commands.h"
#include "common.h"
#include "engine/window/choice_info.h"

#include "engine/window.h"
#include "slus.h"

/* Saves the object's flags and enters state 0x11 with a new handler and flag 0x80 set. */
void confirm_menu_choice(CursorState *object, s32 unused_arg1, s32 unused_arg2) {
    object->info_74->selection = (u8) object->cursor_4D;
    object->countdown = 0x11;
    object->next_callback = &wait_menu_confirm_countdown;
    object->cursor_4D = (u8) (object->cursor_4D | 0x80);
    SD_Call(AUDIO_MENU_CONFIRM);
}
