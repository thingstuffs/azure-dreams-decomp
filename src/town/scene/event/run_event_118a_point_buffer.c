#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene/event.h"
void func_8001A5CC(s32);                     /* extern */
extern M2C_UNK D_8001AFB8;
extern s32 *D_8001B170;

/* Calls func_8001A5CC with 0x118A and points D_8001B170 at D_8001AFB8. */
void run_event_118a_point_buffer(void) {
    func_8001A5CC(F_bar_top);
    D_8001B170 = &D_8001AFB8;
}
