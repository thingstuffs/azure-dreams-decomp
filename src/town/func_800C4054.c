#include "common.h"

s32 func_80053EF0();                         /* extern */

/* tw_seq_end_chk: check whether sequence 1 has ended. */
s32 tw_seq_end_chk(void) {
    return func_80053EF0(1) == 0;
}
