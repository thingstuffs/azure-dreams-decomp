#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s8 M2C_UNK8;
extern u8 D_800198A4[];
extern s32 D_80019B8C;
/* Returns the 32-bit field at offset 0x10 in the selected 24-byte record. */
s32 func_80017958(void)
{
    s32 *record_field;
    s32 record_offset;
    u8 *records;
    records = D_800198A4;
    record_offset = ((unsigned int) D_80019B8C) * 0x18;
    record_field = (s8 *) (records + record_offset);
    record_field = record_field + 4;
    return *record_field;
}
