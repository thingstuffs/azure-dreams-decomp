#include "common.h"

extern s32 D_800814A0[3];

/* Set object and global flags when the state is zero and linked bit 1 is set. */
void func_80024954(void *object) {
    void *linked_data = *(void **)((u8 *)object + 0xC);

    if (*(s16 *)object == 0 &&
        (*(u16 *)((u8 *)linked_data + 0xC) & 2) != 0) {
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
