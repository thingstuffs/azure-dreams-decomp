#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"

s32 func_80017744(s32);
s32 func_800177BC(s32);
extern M2C_UNK D_80017A00;
extern s32 *D_80017A98;

/* Ask the scene object for its mode and raise the matching 0xBE9 event, then arm the next handler. */
void raise_event_be9_by_mode(void) {
    if (town_scene_root->services->callback_334(0) != 5) {
        func_80017744(F_sbs48_pad15);
    } else {
        func_800177BC(F_sbs48_pad15);
    }
    D_80017A98 = &D_80017A00;
}
