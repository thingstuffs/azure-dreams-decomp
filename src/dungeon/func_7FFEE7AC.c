#include "common.h"
#include "shared/object_flags.h"

void func_80033C84(void *);

/* Processes the referenced object and marks the record and global state. */
void func_8008BF0C(void *record) {
    int global_flags;
    func_80033C84(*(void **)record);
    ((u16 *)record)[-1] |= 0x8000;
    global_flags = objectFlagBlock.flags;
    ((s32 *)record)[-4] = 0;
    objectFlagBlock.flags = global_flags | 0x8000;
}
