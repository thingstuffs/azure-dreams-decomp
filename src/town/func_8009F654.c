#include "modules/town_town_windows.h"

/* Initializes the shared data pointer, clears its first word and returns it. */
s32 *townInitializeSharedScriptData(void) {
    D_801007F4 = D_80100900;
    D_80100900[0] = 0;
    return D_80100900;
}
