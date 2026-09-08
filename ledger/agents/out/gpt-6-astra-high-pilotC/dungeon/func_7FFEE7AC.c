#include "common.h"

extern int D_800814A0[];
void func_80033C84(void *);

/* Processes the referenced object and marks the record and global state. */
void func_8008BF0C(void *record) {
    int global_flags;
    func_80033C84(*(void **)record);
    ((u16 *)record)[-1] |= 0x8000;
    global_flags = D_800814A0[0];
    ((s32 *)record)[-4] = 0;
    D_800814A0[0] = global_flags | 0x8000;
}
