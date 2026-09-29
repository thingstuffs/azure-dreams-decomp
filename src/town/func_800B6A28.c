#include "common.h"

typedef struct {
    u8 bytes[0x30];
} Packed48;

typedef struct {
    u8 bytes[0xC];
} Packed12;

typedef struct {
    Packed48 first;
    Packed12 second;
} CopyTarget;

extern u8 D_800D16D8[0xC];
extern u8 D_800D16FC[0x30];

/* Copies the 48-byte and 12-byte global blocks into the target. */
void func_800B4188(CopyTarget *target)
{
    target->first = *(Packed48 *)D_800D16FC;
    target->second = *(Packed12 *)D_800D16D8;
}
