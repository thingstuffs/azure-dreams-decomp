#include "common.h"

#define FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    s8 f3;
    s32 f4;
    u8 pad[2];
    u8 f10;
    u8 f11;
} Entry;

extern s32 D_800294E4;

void *func_80025C6C(void *arg0) {
    s32 i;
    s32 data;
    Entry *entries;

    i = 0;
    entries = arg0;
    do {
        entries[i].f1 = 40;
        data = D_800294E4;
        entries[i].f3 = (i * 16) - 62;
        entries[i].f2 = 2;
        entries[i].f10 = 12;
        entries[i].f11 = 12;
        entries[i].f4 = data;
        i += 1;
    } while (i < 5);
    FIELD(((i * 12) + arg0), u8 *, -12) = 128;
    return arg0;
}
