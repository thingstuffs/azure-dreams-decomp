#include "modules/ovmovie_libpress.h"


static s32 func_80177BC0(void) {
    volatile s32 polls_left = 0x100000;
    if (*D_80178380 & 0x20000000) {
        do {
            if (--polls_left == -1) {
                func_80177D08((const char *)&D_8017681C);
                return -1;
            }
        } while (*D_80178380 & 0x20000000);
    }
    return 0;
}
