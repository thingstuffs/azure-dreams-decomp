#include "common.h"
extern u8 D_800E3D7C[128];
/* Clears seven bytes of D_800E3D7C starting at offset 0x24. */
void func_80017018(void) {
    s32 byte_index;
    s32 clear_base;
    byte_index = 6;
    clear_base = (s32)&D_800E3D7C[0x24];
    do {
        *(u8*)(byte_index + clear_base) = 0;
        byte_index -= 1;
    } while (byte_index >= 0);
}
