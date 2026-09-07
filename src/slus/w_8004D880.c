#include "common.h"

extern s32 func_8004D828(s32);

s32 func_8004D880(s32 arg0)
{
    s32 value;
    s32 value_use;
    s32 offset;
    s32 result;

    if (arg0 & 1) {
        value = arg0;
    } else {
        value = arg0;
    }

    if (value & 2) {
        offset = value + 0x7DB1;
    } else {
        offset = value + 0x7DB1;
    }
    arg0 = value;
    if ((u32)(offset & 0xFFFF) < 10) {
        result = offset + 0x30;
        goto done;
    }

    if (value & 4) {
        value_use = value;
    } else {
        value_use = value;
    }
    if (value_use & 8) {
        offset = value_use + 0x7DA0;
    } else {
        offset = value_use + 0x7DA0;
    }
    if ((u32)(offset & 0xFFFF) < 26) {
        result = offset + 0x41;
        goto done;
    }

    value_use += 0x7D7F;
    if ((u32)(value_use & 0xFFFF) < 26) {
        result = value_use + 0x61;
    } else {
        result = func_8004D828(arg0 & 0xFFFF);
    }

done:
    return result & 0xFF;
}
