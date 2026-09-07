#include "common.h"

s32 func_8008FE78(s32 arg0, s32 arg1) {
    return (u32) (((arg0 & 0xFFF) - (arg1 & 0xFFF)) + 0x1FF) < 0x3FFU;
}
