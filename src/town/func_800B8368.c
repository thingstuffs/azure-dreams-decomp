#include "common.h"
#include "m2c_compat.h"

void *func_800B5174(s32, void *, s32);                            /* extern */
void func_800B52F4();                /* extern */
void func_800B5774();                /* extern */
void func_800B59A4();                /* extern */

/* Run four setup routines with the supplied context and data. */
void func_800B5AC8(s32 context, void * data, s32 value) {
    func_800B5174(context, data, value);
    func_800B52F4(context, data);
    func_800B5774(context, data);
    func_800B59A4(context, data);
}
