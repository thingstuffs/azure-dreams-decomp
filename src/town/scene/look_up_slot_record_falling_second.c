#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"


typedef void (*Callback)(s32, s32);


extern void func_80018B58(s32 bit_index);
extern void func_80018BD0(s32 bit_index);
extern s32 func_80018C50(s32 flagIndex);

/* Updates event state and checks completion conditions, invoking a callback if unmet. */
s32 look_up_slot_record_falling(void)
{
    func_80018BD0(F_hos_first_cheriru);
    func_80018BD0(F_hos_first_hush);

    if (func_80018C50(F_sbs16_top) != 0 &&
        func_80018C50(F_sbs16_pad00) == 0 &&
        func_80018C50(Fr_hospital_scene06) != 0) {
        func_80018B58(F_sbs16_pad03);
        return 1;
    }

    ((Callback)town_scene_root->services->callback_2F8)(0x10, 0x200);
    return 0;
}
