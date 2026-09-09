#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094AF8();                            /* extern */
s32 open_twin_souko();                         /* extern */
extern s32 D_80100A08;

/* t_soukowin_open: Initialize and open the storage window, saving its handle. */
s32 t_soukowin_open(void) {
    func_80094AF8();
    D_80100A08 = open_twin_souko(0);
    return 0;
}
