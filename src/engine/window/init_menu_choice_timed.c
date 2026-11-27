#include "engine/window/cursor_source.h"
#include "common.h"
#include "slus/window_choice_data.h"
#include "engine/window.h"

typedef struct Child {
    u8 unk00[0x22];
    s16 base_row;
    u8 unk24[2];
    u8 option_count;
    u8 selected_option;
    u8 unk28[0x58];
    void *choice_list;
} Child;

typedef struct Object Object;

struct Object {
    WindowCursorSource source;
    u8 pad_28[0x25];
    u8 cursor_index;
    u8 unk4e[0x16];
    s16 timeout_ticks;
    u8 unk66[2];
    void (*unk68)(Object *);
    u8 unk6c[8];
    Child *child;
};

/* Initializes the object from its child and sets a 90-tick delay and next callback. */
void init_menu_choice_timed(Object *object) {
    s16 adjusted_value;

    adjusted_value = object->child->base_row - (object->child->option_count - 1);
    object->cursor_index = object->child->selected_option;
    init_cursor_color_object(&menu_choice_cursor_storage, &menu_choice_display_data, &object->source, 1, adjusted_value,
                  object->child->choice_list);
    object->timeout_ticks = 0x5a;
    object->unk68 = update_menu_choice_timed;
}
