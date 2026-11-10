#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"


/* Returns whether func_80018B5C reports zero for ID 0x5BE. */
s32 is_script_flag_5be_clear(void) {
    return get_script_flag_mask(F_sbs11_pad27) == 0;
}
