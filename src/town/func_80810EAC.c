#include "common.h"

extern s32 D_80084D5C;

/* Set record and global flags when the record is zero and linked flag 2 is set. */
void func_80810EAC(void *record) {
    void *linked_record;

    linked_record = *(void **)((u8 *)record + 0xC);
    if (*(s16 *)record == 0) {
        if (*(u16 *)((u8 *)linked_record + 0xC) & 2) {
            *(u16 *)((u8 *)record - 2) =
                (u16)(*(u16 *)((u8 *)record - 2) | 0x8000);
            D_80084D5C |= 0x8000;
        }
    }
}
