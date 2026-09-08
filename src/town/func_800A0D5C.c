#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094AF8();                            /* extern */
s32 func_800B2BA0();                         /* extern */
extern s32 D_80100A08;

/* t_soukowin_open: Initialize and open the storage window, saving its handle. */
s32 func_8009E4BC(void) {
    func_80094AF8();
    D_80100A08 = func_800B2BA0(0);
    return 0;
}
