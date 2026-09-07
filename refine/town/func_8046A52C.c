#include "common.h"

extern u8 *D_8001E950;

s32 func_8001A664();
void func_8001E578();

// Updates the selected entry's value and signals the update when the state is 2.
s32 func_8001B52C(void *entryOwner, s32 entryIndex) {
    s32 entryValue;
    s32 entriesBase;

    if (D_8001E950[5] == 2) {
        entryValue = func_8001A664(D_8001E950[4]);
        entriesBase = *(s32 *)((u8 *)entryOwner + 0x10);
        *(s32 *)((entryIndex << 4) + entriesBase + 8) = entryValue;
        func_8001E578(0x402, entriesBase);
        return 0;
    }
    return 1;
}
