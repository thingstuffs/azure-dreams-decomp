#include "common.h"
#include "records/Rec_func_80036210_arg0.h"

#include "common.h"
#include "engine/message.h"
#include "engine/script/vm.h"
#include "engine/window.h"
#include "engine/window/message.h"

typedef struct S_80036154_2 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x71];
    s8 unk_85;
} S_80036154_2;   /* ((S_80036154_1 *)arg0)->unk_74 in func_80036154 */

/* Selects a handler from the linked object, initializes its data, and sets its flag. */
void select_menu_initializer_from_message_handler(void *object) {
    s32 source_handler;

    source_handler = ((S_80036154_2 *)(((Rec_func_80036210_arg0 *)object)->unk_74.as_pv))->unk_10;
    if (source_handler == &advance_message_on_flag) {
        ((Rec_func_80036210_arg0 *)object)->unk_68 = &create_window_cursor_and_install_reset;
    } else if (source_handler == &advance_message_on_confirm_flag) {
        ((Rec_func_80036210_arg0 *)object)->unk_68 = &init_menu_choice_object;
    } else if (source_handler == &advance_message_on_input_flag) {
        ((Rec_func_80036210_arg0 *)object)->unk_68 = &init_menu_choice_timed;
    } else if (source_handler == &advance_message_on_ready_flag) {
        ((Rec_func_80036210_arg0 *)object)->unk_68 = &init_menu_choice_wide;
    } else if (source_handler == &noop_runtime_record_idle) {
        ((Rec_func_80036210_arg0 *)object)->unk_68 = &mark_menu_slot_used;
    }
    copy_window_offset_rectangle(object + 0xC, ((Rec_func_80036210_arg0 *)object)->unk_74.as_pv);
    ((S_80036154_2 *)(((Rec_func_80036210_arg0 *)object)->unk_74.as_pv))->unk_85 = 1;
}
