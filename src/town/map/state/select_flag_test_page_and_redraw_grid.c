/* Relinked copy of town/func_80875204 (func_80875204.c); retail differs only at relocation sites. */
#include "common.h"
#include "town/devkit.h"
#include "town/map/state.h"
void func_80700674(void);                            /* extern */

/* Devkit flag-test entry: select page 0, redraw the grid, then run the flag scan. */
s32 select_flag_test_page_and_redraw_grid(void) {
    propagate_devkit_flag_pair(0);
    func_80700674();
    dispatch_by_leading_id_flags();
    return 0;
}
