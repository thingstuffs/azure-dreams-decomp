#include "common.h"
#include "m2c_compat.h"

void clear_byte_offset_4_eight();                            /* extern */
extern s32 D_8001967C;
extern s32 D_80019AFC;

/* Set state 4 and run the transition handler when the mode is 2. */
void enter_mode_4_when_state_2(void) {
    if (D_80019AFC == 2) {
        D_8001967C = 4;
        clear_byte_offset_4_eight();
    }
}
