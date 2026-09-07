#include "common.h"

#include "common.h"

s32 func_8003C5F0();                                /* extern */

s32 func_8003C890(s32 arg0, s32 arg1) {
    s32 temp_v0;

    if ((arg1 < 0) || (temp_v0 = func_8003C5F0(), (temp_v0 == 0))) {
        return 0;
    }
    return (*(s32 *)((u8 *)(temp_v0) + ((arg1) * 8))) != 0;
}
