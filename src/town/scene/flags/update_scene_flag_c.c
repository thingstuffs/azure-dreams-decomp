#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"


/* Updates flag 0x5C4 to reflect flag 0x5C3 and returns its state. */
s32 update_scene_flag_5_c_4(void) {
    if (func_80018B5C(F_sbs11_pad32) != 0) {
        func_80018A64(F_sbs11_pad33);
        return 1;
    }

    func_80018ADC(F_sbs11_pad33);
    return 0;
}
