#include "common.h"

extern int D_800814A0[];
void func_80033C84(void *);

/* Processes an entry's payload and updates its local and global state flags. */
void func_8008BF0C(void *entry) {
    int global_flags;
    func_80033C84(*(void **)entry);
    ((u16 *)entry)[-1] |= 0x8000;
    global_flags = D_800814A0[0];
    ((s32 *)entry)[-4] = 0;
    D_800814A0[0] = global_flags | 0x8000;
}
