#include "common.h"
#include "town/devkit.h"
#define AZ_FOREIGN_LOCAL_FUNC_80701060
#include "town/devkit/flag_test_imports.h"
#undef AZ_FOREIGN_LOCAL_FUNC_80701060


/* Devkit flag-test entry: select page 0, redraw the grid, then run the flag scan. */
s32 run_devkit_page_0_redraw_scan(void) {
    func_80700C08(0);
    func_8070114C();
    dispatch_devkit_callback_by_run_length();
    return 0;
}
