/* Relinked copy of town/func_80875204 (func_80875204.c); retail differs only at relocation sites. */
#include "common.h"
#include "town/map/state.h"

void func_80700188();                     /* extern */
s32 func_80700590(void);                            /* extern */
void func_80700674(void);                            /* extern */

/* Devkit flag-test entry: select page 0, redraw the grid, then run the flag scan. */
s32 select_flag_test_page_and_redraw_grid(void) {
    func_80700188(0);
    func_80700674();
    func_80700590();
    return 0;
}
