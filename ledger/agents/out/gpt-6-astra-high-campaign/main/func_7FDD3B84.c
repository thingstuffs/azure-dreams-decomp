#include "common.h"

extern s32 D_8008B2F0[];
extern int D_800814A0[4];
__asm__(".set D_8008B2F0, 0x8008B2F0");

typedef struct {
    /* 0x00 */ char pad0[4];
    /* 0x04 */ void *unk04;
    /* 0x08 */ char pad08[0x18 - 0x08];
    /* 0x18 */ s32 unk18;
} EntA;

/* Load a table value divided by four and propagate the source flag. */
void func_7FDD3B84(EntA *entry)
{
    unsigned short *scaled_value = (unsigned short *)((char *)entry + 0x10);
    *(short *)scaled_value = (s16)(D_8008B2F0[entry->unk18] >> 2);
    if (*(short *)((char *)entry->unk04 + 0x16) & 0x8000) {
        *(unsigned short *)((char *)entry - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
