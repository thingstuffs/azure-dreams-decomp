#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef void (*TownCallback)(s32, s32);



extern s32 func_80016CC4();
extern s32 func_8001991C();
extern s32 update_entry_flags();
extern s32 func_8001A5CC();
extern s32 func_8001A64C();

/* Advance the town scene: clear flag 0x943 when it is set and the step check passes, otherwise hand back to the scene callback. */
s32 update_and_test_pending_entry_flags(s32 kind, s32 value) {
    Rec_D_80016000 *root;

    func_80016CC4();
    if (func_8001A64C(F_sbs32_pad25) != 0) {
        update_entry_flags();
        if (func_8001991C(kind, value) != 0) {
            func_8001A5CC(F_sbs32_pad25);
            return 1;
        }
    }

    root = town_scene_root;
    ((TownCallback)root->services->callback_2F8)(0xF, 0x200);
    return 0;
}
