#include "common.h"

extern s32 townApplyEntryPosition(void *, void *, s32, s32);
extern u8 D_8001BDBC[];
extern u8 D_8001C358[];

/* Forward two values to townApplyEntryPosition with the fixed data buffers. */
s32 townForwardValuesToFixedDataHandler(s32 first_value, s32 unused, s32 second_value)
{
    return townApplyEntryPosition(D_8001BDBC, D_8001C358, first_value, second_value);
}
