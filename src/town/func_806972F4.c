#include "common.h"
void func_80017A48(void *, s32);                            /* extern */

/* Dispatch an object's indexed entry to the shared handler. */
void func_806972F4(void *object, s32 entry_index) {
    func_80017A48(object, entry_index);
}
