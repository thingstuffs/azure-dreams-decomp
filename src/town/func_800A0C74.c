#include "modules/town_town_windows.h"

/* Return the high-bit flag from D_80100AF0->unk_1E. */
s32 func_8009E3D4(void) {
    return D_80100AF0->unk_1E & 0x8000;
}
