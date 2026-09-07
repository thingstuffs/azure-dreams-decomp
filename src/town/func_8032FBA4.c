#include "common.h"

typedef struct {
    u32 flags;
    u8 pad[24];
} Struct8032FBA4Entry;

void func_8001A3A4(Struct8032FBA4Entry *arg0, u8 *arg1) {
    u8 *p = arg1;

    if (*p != 0xFF) {
        do {
            arg0[*p].flags |= 0x8000;
            p++;
        } while (*p != 0xFF);
    }
}
