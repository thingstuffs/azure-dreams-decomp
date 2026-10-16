#include "modules/town_town_windows.h"

/* Passes D_80100AF4 to townProcessObjectPointerArray and returns zero. */
s32 townPassSharedDataToWindowHandler(void) {
    townProcessObjectPointerArray(D_80100AF4);
    return 0;
}
