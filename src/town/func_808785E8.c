#include "common.h"
#include "m2c_compat.h"

void townShopSetIndexedFlag();                     /* extern */

/* Calls townShopSetIndexedFlag with 0x20C and returns the value at 0x80701FBC. */
s32 townShopPrepareSpecialValue(void) {
    townShopSetIndexedFlag(0x20C);
    return *(s32 *)0x80701FBC;
}
