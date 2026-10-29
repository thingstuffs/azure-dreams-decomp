#include "script_symbols.h"
#include "common.h"
#include "town/scene/flags.h"

extern void func_80018B58(s32);
extern void func_80018BD0(s32);
extern s32 func_80018C50(s32);

/* Reset two flags and set flag 0x67C when the prerequisite flags allow it. */
s32 reset_two_flags_flag_prerequisite(void) {
    func_80018BD0(F_hos_first_cheriru);
    func_80018BD0(F_hos_first_hush);
    if (func_80018C50(F_sbs16_top) == 0) {
        return 0;
    }
    if (func_80018C50(F_sbs16_pad00) != 0) {
        return 0;
    }
    func_80018B58(F_sbs16_pad02);
    return 1;
}
