#include "common.h"

extern void func_8004491C(s32, void *);
extern u8 D_80046398[];
extern u8 D_80083160[];

/* Initializes an object with default transform and global state values. */
void func_8009CD18(s32 slot_id, void *object, s32 object_id)
{
    u8 *state;

    *(s16 *)((u8 *)object + 0x20) = 0x1000;
    *(s16 *)((u8 *)object + 0x1E) = 0x1000;
    *(s16 *)((u8 *)object + 0x1C) = 0x1000;
    *(s16 *)((u8 *)object + 0x12) = 0;
    *(s16 *)((u8 *)object + 0x14) = 0;
    *(s16 *)((u8 *)object + 0x10) = 0;
    state = D_80083160;
    *(u8 *)((u8 *)object + 0xC) = state[0xA8];
    *(u8 *)((u8 *)object + 0xD) = state[0xA9];
    *(u8 *)((u8 *)object + 0xE) = state[0xAA];
    *(s16 *)((u8 *)object + 0x14) = 0;
    *(s16 *)((u8 *)object + 0x1A) = 0;
    *(s16 *)((u8 *)object + 0x18) = 0;
    *(s16 *)((u8 *)object + 0x16) = 0;
    *(s32 *)((u8 *)object + 0) = 0;
    *(s8 *)((u8 *)object + 4) = 0;
    *(s8 *)((u8 *)object + 5) = 0;
    func_8004491C(slot_id - 0x20, D_80046398);
    *(s32 *)((u8 *)object + 8) = object_id;
}
