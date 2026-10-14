#include "modules/ovmovie_libpress.h"


/* Apply the requested mode, performing setup when it is zero. */
void func_801776D8(s32 mode) {
    if (mode == 0) {
        func_8005FFFC();
    }
    func_801779A0(mode);
}
