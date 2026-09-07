#include "common.h"

s16 func_800AD568(void *arg0) {
    s16 temp_v0;
    u8 temp_a1;
    u8 temp_v1;

    temp_v0 = *(s16 *)((u8 *)arg0 + 0x64);
    temp_a1 = *((u8 *)arg0 + 0x28);
    temp_v1 = *((u8 *)arg0 + 0x29);
    if ((s32)temp_v1 < (temp_v0 + temp_a1)) {
        *(s16 *)((u8 *)arg0 + 0x64) = (s16)(temp_v1 - temp_a1);
    }
    return *(s16 *)((u8 *)arg0 + 0x64);
}
