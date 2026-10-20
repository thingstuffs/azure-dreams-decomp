#include "script_symbols.h"
#include "common.h"

extern s32 func_80018B58();
extern s32 func_80018BD0();
extern s32 func_80018C50();

/* Reset two flags, set flag 0xFE4, and set flag 0x680 if flag 0x11FD is active. */
s32 reset_two_flags_flag_flag(void) {
    func_80018BD0(F_hos_first_cheriru);
    func_80018BD0(F_hos_first_hush);
    func_80018B58(Ft_tai);
    if (func_80018C50(Fp_cheriru_kangofu) != 0) {
        func_80018B58(F_sbs16_pad06);
        return 1;
    }
    return 0;
}
