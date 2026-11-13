#include "shared/audio_commands.h"
#include "common.h"
#include "shared/object_node.h"
#include "engine/menu/selection_menu.h"
#include "shared/game_work.h"
#include "engine/menu.h"

/* Sparse view of the shared global state struct D_80083160: only the two
 * fields this function reads (offsets 0x8 and 0x10). Declared >8 bytes so
 * codegen uses %hi/%lo addressing, matching sibling functions elsewhere
 * that touch other fields of the same global. */

/* Object struct for this function's argument. The object is embedded 0x20
 * bytes into a larger allocation (base = (char*)obj - 0x20, passed to the
 * sibling init/reset routines func_80050DA8/func_80050EA8), and has a
 * "next state" callback pointer at offset -0x10. */

typedef void (*StateFn_80050308)(void *);

extern s16 SD_Call(s32 a0);
extern void begin_selection_menu_teardown_and_fade(u8 *object);
extern void release_selection_menu_object(void *a0);
extern s32 resolve_selected_menu_entry(void *a0);
extern s32 advance_index_with_single_wrap(s32 a0, s32 a1, s32 a2);

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
            begin_selection_menu_teardown_and_fade((char *)obj - 0x20);
        } else if (action_flags & 0x40) {
            SD_Call(AUDIO_ACCEPT);
            obj->result = resolve_selected_menu_entry(obj->unk_28);
            if (call_menu_state_callback(obj) == 0) {
                s32 prev_callback = *(s32 *)((char *)obj - 0x10);

                *(StateFn_80050308 *)((char *)obj - 0x10) = run_state_callback_and_restore;
                obj->saved_callback_word = prev_callback;
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
