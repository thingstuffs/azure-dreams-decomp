#include "modules/ovmovie_libpress.h"


/* Forwards the value to func_8006005C with a zero first argument. */
s32 func_80177958(void (*callback)(void)) {
    return func_8006005C(0, callback);
}
