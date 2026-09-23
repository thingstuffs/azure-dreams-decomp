#include "common.h"
extern u8 D_8008BA00[];
extern u8 D_8008BC58[];

extern u8 D_800FC418;

/* Select and store an address based on the global byte value. */
void func_8008BED8(void *object) {
    u8 value = D_800FC418;

    if (value == 0xFF) {
        *(void **)((u8 *)object + 0x68) = D_8008BA00;
    } else if (value == 0) {
        *(void **)((u8 *)object + 0x68) = D_8008BC58;
    }
}
