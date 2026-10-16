/* Relink of matched town/func_800A0C74; every changed retail word is a paired relocation. */
#include "modules/town_town_windows.h"

/* Return the high-bit flag from D_80100AF0->unk_1E. */
s32 func_800C1804(void) {
    return D_80100AF0->unk_1E & 0x8000;
}
