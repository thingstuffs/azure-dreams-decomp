#include "common.h"
#include "shared/object_flags.h"

extern s32 func_800478B8();

/* Marks the referenced object and updates entry and global flags based on target status. */
void func_80024AA4(void *entry, void *unused, void *target) {
    void *object;

    object = *(void **)entry;
    *(u16 *)((u8 *)object + 0x52) =
        (u16)(*(u16 *)((u8 *)object + 0x52) | 0x8000);
    func_800478B8(target);
    if (*(u16 *)((u8 *)target + 0x14) & 0x6000) {
        *(u16 *)((u8 *)entry - 2) =
            (u16)(*(u16 *)((u8 *)entry - 2) | 0x8000);
        objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
    }
}
