#include "common.h"

typedef struct {
    u8 *ptr;
    u8 pad[8];
} D_800E3D7C_t;

extern D_800E3D7C_t D_800E3D7C;

s32 func_800A1C14(s32 arg0) {
    s32 i;
    s32 *entry;
    s32 value;
    s16 index;

    do { i = 0; } while (0);
    entry = (s32 *)D_800E3D7C.ptr;
loop:
    value = entry[0x39];
    if (value != arg0) {
        i++;
        entry++;
        if (i < 4) {
            goto loop;
        }
        return -1;
    }
    index = (s16)i;
    return index;
}
