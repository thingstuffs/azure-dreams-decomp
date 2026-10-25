#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"



s32 func_80017684(s32);
s32 func_800176FC(s32);
s32 func_8001777C(s32 flagIndex);                         /* extern */
s32 func_80017918(void);                                /* extern */
extern s16 D_80017A6C;
extern s16 D_80017A74;


/* Refresh the four menu labels plus the two fixed rows from the scene's state query. */
void invoke_callback_and_set_shared_pointer(void) {
    s16 *label_cursor;
    s16 *state_cursor;
    s32 state;
    s32 slot;

    state = town_scene_root->services->callback_330(0);
    slot = 0;
    label_cursor = &D_80017A6C;
    state_cursor = &D_80017A74;
    do {
        if (state == *state_cursor) {
            func_80017684(*label_cursor++);
        } else {
            func_800176FC(*label_cursor++);
        }
        state_cursor += 1;
        slot += 1;
    } while (slot < 4);
    if (town_scene_root->services->callback_334(0) != 5) {
        func_80017684(F_sbs48_pad06);
    } else {
        func_800176FC(F_sbs48_pad06);
    }
    if ((func_80017918() < 5) || ((func_80017918() >= 5) && (func_8001777C(Ftt_fkoya_isaku_scene01_ok) != 0))) {
        func_80017684(F_sbs48_pad07);
    } else {
        func_800176FC(F_sbs48_pad07);
    }
}
