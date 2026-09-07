#include "common.h"

typedef struct TownRecord {
    u8 bytes[0x54];
} TownRecord;

typedef struct TownIndexEntry {
    u8 value;
    u8 pad[3];
} TownIndexEntry;

typedef struct TownPage {
    u8 pad[0x980];
    TownIndexEntry entries[0x40];
} TownPage;

extern s32 func_8004B854(s32 arg0, void *arg1, s32 arg2);
extern u8 *D_800CFCC4[];
extern s32 D_80100AF0[];

s32 func_8009E370(void)
{
    TownRecord *records = (TownRecord *)0x80010AB4;
    s32 index = D_800CFCC4[0][0x4F] & 0x3F;

    D_80100AF0[0] = func_8004B854(
        0,
        records[index].bytes,
        ((TownPage *)0x80010000)->entries[index].value);
    return 0;
}
