#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void setResidentBitmapBit();                     /* extern */
void clearResidentBitmapBit();                     /* extern */

/* Selects which runtime call receives 1000 and which receives 10. */
void func_8003B42C(s32 mode) {
    if (mode != 0) {
        setResidentBitmapBit(0x3E8);
        clearResidentBitmapBit(0xA);
        return;
    }
    clearResidentBitmapBit(0x3E8);
    setResidentBitmapBit(0xA);
}
