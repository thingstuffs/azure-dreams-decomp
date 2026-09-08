#include "common.h"
#include "m2c_compat.h"

void func_80019B54(s32, s32);             /* extern */
void func_80019BC0(void);                 /* extern */
s32 func_8001B0C8(void);                  /* extern */

/* Process the request after checking the threshold of 15. */
void func_800168AC(s32 request, M2C_UNK context) {
    if (func_8001B0C8() >= 0xF) {
        func_80019BC0();
    }
    func_80019B54(request, context);
}
