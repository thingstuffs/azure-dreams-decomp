#include "script_symbols.h"
#include "shared/town_pointees.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"
#include "shared/town_root.h"

extern s32 func_80018BD0(s32);
extern s32 func_80018C50(s32);
extern s32 D_8001A3B5;

// Processes IDs 0xFB7 and 0xFB8, conditionally sets a data pointer, and invokes the context callback.
s32 process_ids_conditionally_pointer(void) {
    func_80018BD0(F_hos_first_cheriru);
    func_80018BD0(F_hos_first_hush);
    if (func_80018C50(Fr_cheriru_scene03) != 0) {
        town_scene_root->position->unk_40 =
            &D_8001A3B5;
    }
    ((s32 (*)(s32, s32))(town_scene_root->services->callback_2F8))(0x10,
        0x200);
    return 0;
}
