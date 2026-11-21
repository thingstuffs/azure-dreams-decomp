#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/libcard.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/server_menu.h"


typedef void (*Callback)(void *);

extern void func_80403B84(void *object, s32 option_param);

/* Initializes or retrieves the memory card options object. */
void * init_card_options_object(s32 option_param) {
    s32 object_status;
    u8 *object = D_80409C90;
    CardDevMenu18 *subobject;
    u8 *object_arg;

    object_arg = object;
    subobject = NODE_BODY(object);
    object_status = func_80047FD8(object_arg);
    if (object_status == 0) {
        object = func_8003C714(0, object, 0x118);
        if (object == 0) {
            printf_8007C040(card_options_assert_format, card_options_assert_filename, 0x151);
            exit_8007BEF0(1);
        }
        func_80040560(object, card_dev_render_panel_hierarchy);
    } else {
        card_dev_refresh_options_object(object);
        D_80409CAE &= 0x7FFF;
        bzero_8007BFE0(subobject, 0x440);
    }
    card_dev_init_options_menu_entries(subobject, 0x12);
    (*(void * *)(object + (0xC))) = &subobject->heading;
    subobject->heading.unk_0C = card_dev_bind_panel_template(subobject->entries);
    func_80403B84(subobject, option_param);
    (*(Callback *)(object + (0x10))) = card_animate_selection_marker_rows;
    card_animate_selection_marker_rows(subobject);
    return object;
}
