#include "common.h"
#include "shared/game_work.h"

/* Sparse view of the shared global state struct D_80083160: only the two
 * fields this function reads (offsets 0x8 and 0x10). Declared >8 bytes so
 * codegen uses %hi/%lo addressing, matching sibling functions elsewhere
 * that touch other fields of the same global. */
typedef struct {
    u8 pad00[0x8];
    s32 unk08;
    u8 pad0C[0x4];
    s32 unk10;
} S_80050308_D80083160;


/* Object struct for this function's argument. The object is embedded 0x20
 * bytes into a larger allocation (base = (char*)obj - 0x20, passed to the
 * sibling init/reset routines func_80050DA8/func_80050EA8), and has a
 * "next state" callback pointer at offset -0x10. */
typedef struct S_80050308 {
    u8 pad00[0x4];
    s32 unk04;        /* saved previous state-fn value */
    u8 pad08[0x4];
    s32 unk0C;         /* counter */
    s32 unk10;         /* mode value (2 or 3) */
    s32 unk14;
    s32 unk18;
    s32 unk1C;         /* wrapped index */
    s32 unk20;         /* result of func_800502E0 */
    u8 pad24[0x4];
    void *unk28;       /* arg passed to func_800502E0 */
    u8 pad2C[0x68 - 0x2C];
    s32 unk68;         /* arg0 for animate_six_entry_selection_cursor */
} S_80050308;

typedef void (*StateFn_80050308)(void *);

extern s16 SD_Call(s32 a0);
extern void begin_selection_menu_teardown_and_fade(void *a0);
extern void release_selection_menu_and_preserve_pending_value(void *a0);
extern s32 resolve_selected_menu_entry(void *a0);
extern s32 call_state_callback(void *a0);
extern void run_state_callback_and_restore(void *a0);
extern s32 advance_index_with_single_wrap(s32 a0, s32 a1, s32 a2);
extern void animate_six_entry_selection_cursor(s32 a0, void *a1);

/* Handles object state changes and directional index updates from global input flags. */
void handle_object_input(void *object)
{
    S_80050308 *obj = (S_80050308 *)object;
    s32 action_flags;
    s32 direction;

    if (g_game_work.buttons != 0) {
        action_flags = ((s32)g_game_work.pressed_buttons);
        if (action_flags & 0x20) {
            SD_Call(0x515);
            begin_selection_menu_teardown_and_fade((char *)obj - 0x20);
        } else if (action_flags & 0x40) {
            SD_Call(0x514);
            obj->unk20 = resolve_selected_menu_entry(obj->unk28);
            if (call_state_callback(obj) == 0) {
                s32 prev_callback = *(s32 *)((char *)obj - 0x10);

                *(StateFn_80050308 *)((char *)obj - 0x10) = run_state_callback_and_restore;
                obj->unk04 = prev_callback;
            } else {
                release_selection_menu_and_preserve_pending_value((char *)obj - 0x20);
            }
        } else if (g_game_work.buttons & 0x5000) {
            direction = 0;
            if (action_flags & 0x4000) {
                direction = 1;
                obj->unk0C = 0;
                obj->unk10 = 3;
            } else if (action_flags & 0x1000) {
                direction = -1;
                obj->unk0C = 0;
                obj->unk10 = 3;
            } else if (obj->unk0C >= 3) {
                s32 repeat_flags;

                obj->unk0C = obj->unk0C - 1;
                repeat_flags = g_game_work.buttons;
                if (repeat_flags & 0x4000) {
                    direction = 1;
                    obj->unk10 = 2;
                } else if (repeat_flags & 0x1000) {
                    direction = -1;
                    obj->unk10 = 2;
                }
            } else {
                obj->unk0C = obj->unk0C + 1;
            }
            if (direction != 0) {
                SD_Call(0x502);
                obj->unk18 = obj->unk1C;
                obj->unk14 = 0;
                obj->unk1C = advance_index_with_single_wrap(obj->unk1C, direction, 6);
            }
        }
    }
    animate_six_entry_selection_cursor(obj->unk68, obj);
}
