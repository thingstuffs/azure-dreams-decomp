#include "common.h"
#include "m2c_compat.h"

s32 func_80019B54();                /* extern */
void func_80019BC0();                            /* extern */
void func_8001ACE8();                     /* extern */
s32 func_8001B0C8();                                /* extern */

/* Conditionally reset the subsystem, select 0xD7F, and forward the request. */
void func_800183C4(s32 request, s32 request_data) {
    if (func_8001B0C8() >= 5) {
        func_80019BC0();
    }
    func_8001ACE8(0xD7F);
    func_80019B54(request, request_data);
}
