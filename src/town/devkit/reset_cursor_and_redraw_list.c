#include "common.h"
#include "town/devkit.h"
#include "town/data.h"
#include "town/devkit/flag_test_imports.h"

extern s32 D_80700630_return[];


/* Devkit scene step: reset the cursor, rebuild the list, latch its length and redraw. */
s32 reset_cursor_and_redraw_list(void) {
    s32 list_length;

    func_80700868(0);
    func_80700BCC();
    list_length = dispatch_first_rejected_entry();
    devkit_cursor_state[0] = list_length;
    func_80700ED8(list_length, devkit_cursor_state[1]);
    return D_80700630_return[0];
}
