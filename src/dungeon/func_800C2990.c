#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 D_800E3D7C;

s32 func_800C80F0(void *arg0) {
    s32 var_a0;
    void *temp_v0;
    void *var_v1;

    if (*(s32 *)((u8 *)arg0 + 0x14) & 0x4000) {
        var_a0 = 1;
        var_v1 = D_800E3D7C + 4;
        do {
            temp_v0 = *(void **)((u8 *)var_v1 + 0xAC);
            if ((temp_v0 != NULL) && (*(s32 *)((u8 *)temp_v0 + 0x54) & 0x10000)) {
                return 1;
            }
            var_a0 -= 1;
            var_v1 -= 4;
        } while (var_a0 >= 0);
    }
    return 0;
}
