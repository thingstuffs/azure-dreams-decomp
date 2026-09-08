#include "common.h"

extern int D_800814A0[];
void func_80033C84(void *);

/* Processes the entry payload, clears its header word, and sets entry and global flags. */
void func_8008BF0C(void *entry) {
    int global_flags;
    func_80033C84(*(void **)entry);
    ((u16 *)entry)[-1] |= 0x8000;
    global_flags = D_800814A0[0];
    ((s32 *)entry)[-4] = 0;
    D_800814A0[0] = global_flags | 0x8000;
}
