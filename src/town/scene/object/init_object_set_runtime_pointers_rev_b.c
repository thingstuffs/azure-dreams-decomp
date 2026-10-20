#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


void func_80016098();                            /* extern */
void update_flag_test_target();                    /* extern */
void build_object_set_and_select_lists_rev_b();   /* extern */
extern s16 D_800160B0;
extern s16 D_800160B2;
extern s32 D_80016E40;
extern M2C_UNK D_80016E48;
extern M2C_UNK D_80016F88;
extern s32 D_80016FC8;
extern M2C_UNK D_8001700C;

/* Initialize shared state and attach its data pointers. */
void init_object_set_runtime_pointers_rev_b(void) {
    update_flag_test_target(D_800160B0, D_800160B2);
    func_80016098();
    build_object_set_and_select_lists_rev_b(D_80016E40, &D_80016E48, &D_80016F88);
    D_80016000->unk_34 = &D_80016FC8;
    D_80016000->unk_28 = &D_80016E48;
    D_80016000->unk_2C = &D_8001700C;
}
