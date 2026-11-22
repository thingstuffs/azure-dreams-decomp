#include "engine/window/cursor_source.h"
#include "common.h"
#include "engine/window/choice_info.h"
#include "slus/window_choice_data.h"
#include "engine/window.h"
#include "engine/window/cursor_init.h"


typedef void (*Callback)(CursorState *, s32, s32);

typedef struct S_func_800362D0_0 {
    WindowCursorSource source;
    u8 pad_28[0x25];
    u8 unk_4D;
    u8 pad_4E[0x1A];
    Callback unk_68;
    u8 pad_6C[0x08];
    CursorInfo *unk_74;
} S_func_800362D0_0;

/* Initializes the object from its child data and sets the next callback. */
void init_menu_choice_object(S_func_800362D0_0 *object) {
    CursorInfo *info;
    u8 child_byte;
    u8 index_base;
    s16 index_offset;

    info = object->unk_74;
    child_byte = info->selection;
    index_base = info->count;
    index_offset = info->line - (index_base - 1);
    object->unk_4D = child_byte;

    init_cursor_display_object(&menu_choice_cursor_storage, &menu_choice_display_data, &object->source, 1, index_offset,
                  object->unk_74->list_head);
    object->unk_68 = handle_wrapping_menu_cursor_input;
}
