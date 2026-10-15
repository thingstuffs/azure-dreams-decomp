#include "modules/town_town_windows.h"

/* t_soukowin_close_check: Returns the storage window close flag. */
s32 t_soukowin_close_check(void) {
    return ((func_800A0D8C_S_8009E4EC_0 *)D_80100A08)->unk_1E & 0x8000;
}
