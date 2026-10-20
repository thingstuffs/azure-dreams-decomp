#include "common.h"

extern s32 get_mode_selected_value(void);

/* Return the computed value for mode 1 or 0x14 for other modes. */
s32 get_mode_value_or_default(s32 mode) {
    if (mode != 1) {
        return 0x14;
    }
    return get_mode_selected_value();
}
