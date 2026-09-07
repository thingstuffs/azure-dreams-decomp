#include "common.h"

void *func_800999B0(void *arg0) {
    *(u8 *)arg0 = 0x12;
    arg0 = (u8 *)arg0 + 1;
    *(u8 *)arg0 = 0x10;
    arg0 = (u8 *)arg0 + 1;
    *(u8 *)arg0 = 0;
    return (u8 *)arg0 + 1;
}
