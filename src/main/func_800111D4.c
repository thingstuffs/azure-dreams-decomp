#include "common.h"

extern s32 D_800786E8[];

void func_800241D4(s32 arg0, s32 arg1) {
    s8 *v0;
    void *a0;

    if (arg0 != 0) {
        v0 = (s8 *) arg0 + 0x20;
        a0 = *(void **) (v0 + 0x280);
        *(s32 *) (v0 + 0x224) = 0x808080;
        if (arg1 != 0) {
            *(s32 **) a0 = D_800786E8;
        } else {
            *(s32 *) a0 = 0;
        }
        *(s16 *) (*(s8 **) ((s8 *) a0 + 4) + 8) = 0x60;
        *(s16 *) (*(s8 **) ((s8 *) a0 + 4) + 0xA) = 0x18;
    }
}
