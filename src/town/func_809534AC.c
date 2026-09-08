#include "common.h"

extern s32 D_800814A0[3];

/* Propagate bit 15 from the linked record when the record status is zero. */
void func_800204AC(void *record) {
    void *linked_record = *(void **)((u8 *)record + 0xC);

    if (*(s16 *)record == 0 &&
        (*(u16 *)((u8 *)linked_record + 4) & 0x8000) != 0) {
        *(u16 *)((u8 *)record - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
