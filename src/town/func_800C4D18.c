#include "modules/town_minigame_dispatch.h"
#include "common.h"
void func_80020298(void);                            /* extern */
void finalize_town_resource_operation();                            /* extern */

/* Run the two handlers for town script call 100. */
void scr_func_sn_casino(void) {
    finalize_town_resource_operation();
    func_80020298();
}
