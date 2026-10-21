#include "common.h"

#include "common.h"
#include "engine/message.h"
#include "engine/script/vm.h"
#include "engine/window.h"
#include "engine/window/message.h"

typedef struct S_80036154_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_80036154_1;   /* arg0 in func_80036154 */

typedef struct S_80036154_2 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x71];
    s8 unk_85;
} S_80036154_2;   /* ((S_80036154_1 *)arg0)->unk_74 in func_80036154 */


typedef struct S_80036154_0 {
    u8 pad_00[0x68];
    s32 * unk_68;
    u8 pad_6C[0x8];
    void * unk_74;
} S_80036154_0;   /* arg0 in func_80036154 */

/* Selects a handler from the linked object, initializes its data, and sets its flag. */
void select_menu_initializer_from_message_handler(void *object) {
    s32 source_handler;

    source_handler = ((S_80036154_2 *)(((S_80036154_1 *)object)->unk_74))->unk_10;
    if (source_handler == &advance_message_on_flag) {
        ((S_80036154_0 *)object)->unk_68 = &create_window_cursor_and_install_reset;
    } else if (source_handler == &advance_message_on_confirm_flag) {
        ((S_80036154_0 *)object)->unk_68 = &init_menu_choice_object;
    } else if (source_handler == &advance_message_on_input_flag) {
        ((S_80036154_0 *)object)->unk_68 = &init_menu_choice_timed;
    } else if (source_handler == &advance_message_on_ready_flag) {
        ((S_80036154_0 *)object)->unk_68 = &init_menu_choice_wide;
    } else if (source_handler == &noop_runtime_record_idle) {
        ((S_80036154_0 *)object)->unk_68 = &mark_menu_slot_used;
    }
    copy_window_offset_rectangle(object + 0xC, ((S_80036154_0 *)object)->unk_74);
    ((S_80036154_2 *)(((S_80036154_1 *)object)->unk_74))->unk_85 = 1;
}
