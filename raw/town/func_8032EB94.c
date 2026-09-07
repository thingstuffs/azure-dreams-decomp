#include "common.h"

typedef struct Entry Entry;

struct Entry {
    u8 pad0[8];
    s32 value;
    Entry *next;
    u8 pad10[4];
};

extern void *D_80016000;
extern void func_8001A5E4(s32);

void func_80019394(s32 arg0, s32 arg1) {
    void *root;
    Entry *level;
    register Entry *first ASM_REG("$3");
    Entry *second;

    ASM_USE(arg0);
    root = D_80016000;
    level = *(Entry **)((u8 *)root + 0x24);
    first = *(Entry **)((u8 *)level + 0x6C);
    ASM_KEEP(first);
    do { second = first[arg0].next; } while (0);
    func_8001A5E4(second[arg1].value);
}
