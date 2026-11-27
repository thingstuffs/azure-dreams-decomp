#include "common.h"
#include "shared/game_work.h"
#include "engine/window.h"

typedef struct Child {
    u8 unk00[0x22];
    u8 unk22[2];
    u8 unk24[2];
    u8 option_count;
    u8 selected_option;
} Child;

typedef struct Object Object;

struct Object {
    u8 unk00[0x4d];
    u8 cursor_index;
    u8 unk4e[3];
    u8 unk51;
    u8 unk52[0x12];
    u16 timeout_ticks;
    u8 unk66[2];
    void (*unk68)(Object *);
    u8 unk6c[8];
    Child *child;
};

/* Decrement the countdown, restoring the callback on expiry or updating the selection from state flags. */
void update_menu_choice_timed(Object *object) {
    u16 ticks_left;
    GameWork *state;

    state = &g_game_work;
    ticks_left = object->timeout_ticks - 1;
    object->timeout_ticks = ticks_left;
    if ((s16)ticks_left <= 0) {
        object->cursor_index = 0xff;
        object->unk51 = 0;
        object->child->selected_option = object->child->option_count;
        object->unk68 = request_message_advance_on_second_flag;
    } else {
        if ((((u32)state->pressed_buttons)) & 0x20) {
            object->cursor_index = object->child->option_count - 1;
            confirm_timed_menu_choice(object);
        } else if ((((u32)state->pressed_buttons)) & 0x40) {
            object->cursor_index = 0;
            confirm_timed_menu_choice(object);
        }
    }
}
