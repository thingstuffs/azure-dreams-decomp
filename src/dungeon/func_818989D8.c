#include "common.h"
#include "shared/object_flags.h"

extern void func_800478B8(void *target);

/* Increment entry and object counters, process the target, and propagate its status flags. */
void func_800241D8(void *entry, void *unused, void *target)
{
    void *object;

    object = *(void **)entry;
    *(u16 *)((u8 *)object + 0x14) += 1;
    *(u16 *)((u8 *)entry + 4) += 1;
    func_800478B8(target);
    if (*(u16 *)((u8 *)target + 0x14) & 0x6000) {
        *(u16 *)((u8 *)entry - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
