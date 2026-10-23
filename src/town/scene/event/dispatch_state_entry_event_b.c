#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern void func_80018B58(s32);
extern void func_80018BD0(s32);
extern s32 func_80018C50(s32);

typedef void (*Callback)(s32, s32);




/* Runs the conditional action or invokes the fallback callback. */
s32 dispatch_state_entry_event_8(void) {
    Rec_D_80016000 *callback_owner;

    func_80018BD0(F_hos_first_cheriru);
    func_80018BD0(F_hos_first_hush);

    if (func_80018C50(F_sbs16_top) != 0) {
        if (func_80018C50(F_sbs16_pad00) == 0) {
            func_80018B58(F_sbs16_pad04);
            return 1;
        }
    }
    callback_owner = town_scene_root;
    ((Callback)callback_owner->services->callback_2F8)(0x10, 0x200);
    return 0;
}
