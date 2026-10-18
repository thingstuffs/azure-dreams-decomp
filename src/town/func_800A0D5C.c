#include "modules/town_town_windows.h"

/* t_soukowin_open: Initialize and open the storage window, saving its handle. */
s32 t_soukowin_open(void) {
    clear_global_80110_ec_0_global_80082_a_39();
    D_80100A08 = open_twin_souko(0);
    return 0;
}
