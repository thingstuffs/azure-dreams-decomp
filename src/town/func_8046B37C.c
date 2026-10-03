#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"


s32 func_8001E670();                             /* extern */
extern s16 D_8001792C;

/* Return whether the identifier check passes when the state permits it. */
s32 func_8001C37C(void) {
    s32 check_passed;

    check_passed = 0;
    if (D_8001E950->unk_04 != 1) {
        check_passed = func_8001E670(D_8001792C) != 0;
    }
    return check_passed;
}
