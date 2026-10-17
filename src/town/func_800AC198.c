#include "common.h"
#include "m2c_compat.h"

s32 testResidentBitmapBit();
/* Returns the selected query result, testing for zero for check type 3. */
s32 func_800A98F8(s32 check_type)
{
    switch (check_type) {
    case 0:
        return testResidentBitmapBit(0x11FA);
    case 2:
        return testResidentBitmapBit(0x11FB);
    case 3:
        return testResidentBitmapBit(0x4FA) == 0;
    default:
        return 0;
    }
}
