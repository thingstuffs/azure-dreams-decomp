#include "common.h"

#include "common.h"

s32 rand();                                         /* extern */

u32 func_800374F4(s32 arg0) {
    return (u32) ((arg0 & 0xFFFF) * ((rand() * 2) & 0xFFFF)) >> 0x10;
}
