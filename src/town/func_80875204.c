#include "common.h"

s32 func_80700C08(s32);
s32 func_80701060(void);
s32 func_8070114C(void);

/* Devkit flag-test entry: select page 0, redraw the grid, then run the flag scan. */
s32 run_devkit_page_0_redraw_scan(void) {
    func_80700C08(0);
    func_8070114C();
    func_80701060();
    return 0;
}
