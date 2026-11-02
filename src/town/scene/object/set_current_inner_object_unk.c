#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern s32 D_80018FEC;
extern s32 *D_800190D8;
extern s32 D_80019A74;

extern void func_80018C74(s32 bit_index);
extern void func_80018CEC(s32 bit_index);
extern s32 func_80018D6C(s32 flagIndex);

/* Initializes state pointers and updates flags based on the current state. */
void set_current_inner_object_unk(void) {
    D_800190D8 = &D_80018FEC;
    func_80018C74(F_sb24_door_dummy);
    func_80018CEC(F_sb24_nd_dummy0);

    if (func_80018D6C(Ft_name_to_cheril) == 0) {
        func_80018CEC(F_sb24_door_dummy);
        func_80018C74(F_sb24_nd_dummy0);
        town_scene_root->position->unk_40 = &D_80019A74;
    }

    if (func_80018D6C(Fp_cheriru_kangofu) != 0) {
        func_80018CEC(F_kangofu);
        return;
    }

    func_80018C74(F_kangofu);
}
