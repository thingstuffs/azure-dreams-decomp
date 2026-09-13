#include "common.h"


extern s32 func_80700D20();
extern u8 D_80700638[];
extern u8 D_8070063A[];

/* Process the pair of 16-bit table entries at byte offset four. */
void func_808813CC(void) {
    s32 byte_offset;
    u16 second_entry;

    byte_offset = 4;
    do {
        func_80700D20(*(u16 *)(D_80700638 + byte_offset));
        second_entry = *(u16 *)(D_8070063A + byte_offset);
        byte_offset += 4;
        func_80700D20(second_entry);
    } while (byte_offset < 8);
}
