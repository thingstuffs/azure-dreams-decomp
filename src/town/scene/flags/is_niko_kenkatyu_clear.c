#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"


/* Return whether func_80018B5C reports zero for 0x11FA. */
s32 is_niko_kenkatyu_clear(void) {
    return get_script_flag_mask(Fp_niko_kenkatyu) == 0;
}
