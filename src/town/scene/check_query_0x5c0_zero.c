#include "script_symbols.h"
#include "shared/town_pointees.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"
#include "shared/town_root.h"

extern s32 D_8001C9F4;
extern s32 func_80018BD0(s32);
extern s32 func_80018C50(s32);

typedef void (*TownCallback)(s32, s32);

/* Conditionally updates the town state pointer and invokes the town callback. */
s32 check_query_0x5c0_zero(void) {
    func_80018BD0(F_hos_first_cheriru);
    func_80018BD0(F_hos_first_hush);
    if (func_80018C50(F_cheril_orei) == 0) {
        town_scene_root->position->unk_40 = &D_8001C9F4;
    }
    ((TownCallback)(town_scene_root->services->callback_2F8))(0x10, 0x200);
    return 0;
}
