#include "common.h"

s32 func_80017B98();                /* extern */

/* Return whether func_80017B98 reports zero for (0xD, 2). */
s32 func_8059E640(void) {
    return func_80017B98(0xD, 2) == 0;
}
