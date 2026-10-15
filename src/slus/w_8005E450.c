#include "slus/sound_reset_state.h"

/* Records and returns whether enabled and the stored pointer has no matching entry. */
s32 func_8005E450(s32 enabled) {
    s32 check_result;

    if (enabled != 0) {
        check_result = func_8005D9DC(D_80079500);
        if (check_result == 0) {
            D_800794FC = 1;
            return 1;
        }
    }
    D_800794FC = 0;
    return 0;
}
