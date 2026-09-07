#include "common.h"

typedef struct {
    unsigned char bytes[16];
} Raw16;

typedef struct {
    s32 unused;
    s32 *dst;
} Entry;

typedef struct {
    unsigned char pad[0x5C];
    Entry **entries;
} Arg0;

extern Raw16 D_80089298;

void func_800B3D04(Arg0 *arg0, s32 arg1) {
    Raw16 sp;

    do { sp = D_80089298; } while (0);
    arg0->entries[arg1]->dst[0] = ((s32 *)sp.bytes)[arg1 - 2];
}
