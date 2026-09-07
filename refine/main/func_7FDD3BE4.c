#include "common.h"

extern s32 D_800814A0[];

/* Packs three capped source components, copies an attribute, and propagates the high-bit flag. */
void func_7FDD3BE4(void *dest) {
    void *source;
    void *component_cursor;
    s32 component;
    s32 byte_index;
    s32 shift;
    s32 packed_value;

    source = *(void **) ((s8 *) dest + 4);
    byte_index = 2;
    *(s32 *) ((s8 *) dest + 8) = 0;
    component_cursor = (s8 *) source + 4;
    do {
        component = *(s16 *) ((s8 *) component_cursor + 0xE);
        if (component >= 0x100) {
            component = 0xFF;
        }
        component_cursor = (s8 *) component_cursor - 2;
        shift = byte_index * 8;
        byte_index -= 1;
        packed_value = *(s32 *) ((s8 *) dest + 8);
        packed_value = packed_value + (component << shift);
        *(s32 *) ((s8 *) dest + 8) = packed_value;
    } while (byte_index >= 0);
    *(u16 *) ((s8 *) dest + 0x14) = *(u16 *) ((s8 *) source + 0x14);
    if (*(s16 *) ((s8 *) source + 0x16) & 0x8000) {
        *(u16 *) ((s8 *) dest - 2) = *(u16 *) ((s8 *) dest - 2) | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
