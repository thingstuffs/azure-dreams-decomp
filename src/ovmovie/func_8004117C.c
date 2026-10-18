#include "modules/ovmovie_libpress.h"


/* Passes 1 and the supplied value to func_8006005C. */
s32 register_mode_one_callback(void (*callback)(void)) {
    return func_8006005C(1, callback);
}
