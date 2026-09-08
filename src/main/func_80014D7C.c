#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80027AFC();                /* extern */
M2C_UNK func_80027C60();                            /* extern */
M2C_UNK func_80064F00();            /* extern */
M2C_UNK func_80064F20();                     /* extern */
extern s32 D_80083200;

/* Set up the request with scale 512 and center (160, 120), then dispatch in mode 0. */
void func_80027D7C(s32 request) {
    func_80027C60();
    D_80083200 = 0x200;
    func_80064F20(0x200);
    func_80064F00(0xA0, 0x78);
    func_80027AFC(request, 0);
}
