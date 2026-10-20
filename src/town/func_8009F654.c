#include "town/menu/window.h"

/* Initializes the shared data pointer, clears its first word and returns it. */
s32 *initialize_shared_script_data(void) {
    D_801007F4 = D_80100900;
    D_80100900[0] = 0;
    return D_80100900;
}
