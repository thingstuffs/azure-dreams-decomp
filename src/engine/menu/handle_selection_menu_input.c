#include "shared/audio_commands.h"
#include "common.h"
#include "shared/object_node.h"
#include "engine/menu/selection_menu.h"
#include "shared/game_work.h"
#include "engine/menu.h"
#include "slus.h"

extern void release_selection_menu_object(ObjectNodeHeader *object);

/* Handles object state changes and directional index updates from global input flags. */
void handle_selection_menu_input(void *object)
{
    MenuSelectionBody *obj = object;
    s32 action_flags;
    s32 direction;

    if (g_game_work.buttons != 0) {
        action_flags = (g_game_work.pressed_buttons);
        if (action_flags & 0x20) {
            SD_Call(AUDIO_CANCEL);
            begin_selection_menu_teardown_and_fade(NODE_HEADER(obj));
        } else if (action_flags & 0x40) {
            SD_Call(AUDIO_ACCEPT);
            obj->result = resolve_selected_menu_entry(obj->attachment);
            if (call_menu_state_callback(obj) == 0) {
                void *prev_callback = NODE_HEADER(obj)->update_callback;

                NODE_HEADER(obj)->update_callback = run_state_callback_and_restore;
                obj->saved_callback = prev_callback;
            } else {
                release_selection_menu_object(NODE_HEADER(obj));
            }
        } else if (g_game_work.buttons & 0x5000) {
            direction = 0;
            if (action_flags & 0x4000) {
                direction = 1;
                obj->repeat_ticks = 0;
                obj->animation_frames = 3;
            } else if (action_flags & 0x1000) {
                direction = -1;
                obj->repeat_ticks = 0;
                obj->animation_frames = 3;
            } else if (obj->repeat_ticks >= 3) {
                s32 repeat_flags;

                obj->repeat_ticks = obj->repeat_ticks - 1;
                repeat_flags = g_game_work.buttons;
                if (repeat_flags & 0x4000) {
                    direction = 1;
                    obj->animation_frames = 2;
                } else if (repeat_flags & 0x1000) {
                    direction = -1;
                    obj->animation_frames = 2;
                }
            } else {
                obj->repeat_ticks = obj->repeat_ticks + 1;
            }
            if (direction != 0) {
                SD_Call(AUDIO_CURSOR_MOVE);
                obj->previous_selection = obj->selected_entry;
                obj->animation_tick = 0;
                obj->selected_entry = advance_index_with_single_wrap(obj->selected_entry, direction, 6);
            }
        }
    }
    animate_six_entry_selection_cursor(obj->widgets, obj);
}
