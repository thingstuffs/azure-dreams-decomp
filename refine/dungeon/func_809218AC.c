#include "common.h"

extern int D_800814A0[];
extern void func_800478B8(void *);

/* Adjust the position, update the object, and propagate its status to state and global flags. */
void func_809218AC(s16 *state, s32 *position, u16 *object) {
    *(s32 *)((u8 *)position + 8) += 0xFFFE8000;
    func_800478B8(object);
    if (*(u16 *)((u8 *)object + 0x14) & 0x6000) {
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
