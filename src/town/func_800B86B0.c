#include "common.h"

/* Maps value 0x39 to 2 and returns other values unchanged. */
s32 func_800B5E10(s32 value) {
    s32 mapped_value;

    mapped_value = 2;
    if (value != 0x39) {
        mapped_value = value;
    }
    return mapped_value;
}
